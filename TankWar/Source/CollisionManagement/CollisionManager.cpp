#include "CollisionManagement/CollisionManager.h"
#include "CollisionManagement/CollisionTools.h"
#include "Ogre.h"
//#include "Object/Tank.h"
//#include "Object/Bullet.h"
#include "Factory/TankFactory.h"
#include "Factory/BulletFactory.h"
#include "Factory/TreeFactory.h"
#include "Factory/ItemFactory.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

using namespace Ogre;


namespace TankWar
{
	OverlayManager *olm;
	OverlayContainer *panel ;
	Overlay *overlay;
	TextAreaOverlayElement *textArea;
	String szElement;
	char border_s[16];

	//CollisionManager::CollisionManager(Ogre::SceneManager *sceneManager):mSceneManager(sceneManager)
	CollisionManager::CollisionManager(Ogre::SceneManager *sceneManager, TankFactory *tankFactory, BulletFactory *bulletFactory, ItemFactory *itemFactory, TreeFactory* treeFactory, TankWarWorld *world):mSceneManager(sceneManager), bulletFactory(bulletFactory), tankFactory(tankFactory), itemFactory(itemFactory), mWorld(world), treeFactory(treeFactory)
	{
		playerScore = 0;
		collisionTools = new CollisionTools(mSceneManager);      //have bug now, maybe fix later

		olm=OverlayManager::getSingletonPtr();

		// First, create an overlay: 

		overlay=olm->create("MyTextDisplayOverlay");  // We can call this anything we like, 
										   //  If we have multiple overlays, the name
										   //  needs to be unique

		// Next, we create a panel within this overlay:
		panel=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel"));
		panel->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel->setPosition(.2,.2);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel->setDimensions(0.5,0.5);           // Panel is half the width and half the height of the screen
		//panel->setMaterialName("background");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel);                   // Add our panel to the overlay

		// Create a TextArea element.  The 1st parameter "TextArea" tells the constructor to create
		//   a TextArea element.  The second paramater "text1" is just a name we give the element
		//   (needs to be unique!) so that we can retreive the element later
		textArea=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text1"));

		textArea->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
													  // screen relative (We don't need to do this, I'm only doing
													  // it to show the difference between screen relative and
		//textArea->setCaption("HELLO!");	              // Set what we want the text area to show
    
		textArea->setCharHeight(20);	              // Set the height of the text (in pixels)
    
		// Add the text area to the panel
		panel->addChild(textArea);
    
		// Show the overlay
		overlay->show();

		team1 = 0;
		team2 = 0;
	}

	/*current useless fuction, should be used later, a high effective collision fuction*/
	Ogre::Entity* CollisionManager::checkCollision(const Ogre::Vector3& fromPoint, const Ogre::Vector3& toPoint, float collisionRadius, int queryMask){
	
			Ogre::Entity* entity = collisionTools->collidesWithObject(fromPoint, toPoint, collisionRadius, queryMask);
			//if(Entity)
			return entity;
			
	}
	

	void CollisionManager::update(float time){
		Ogre::AxisAlignedBox p;
		Ogre::AxisAlignedBox q;
		detectTankVsBulletCollsion(p, q);           // bullet hits tank
		detectBulletVsGeometryCollsion(p, q);       // bullet hits Geometry
		detectTankVsTankCollsion(p, q, time);       // tank blocks tank
		detectTankVsGeometryCollsion(p, q, time);   // border blocks tank
		detectPlayerTankVsBonusItemsCollsion(p, q, time);//player tank gets bonus item
		detectBulletVsTree(p,q, time);			// tank vs tree;
	}

	void CollisionManager::detectBulletVsTree(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time){
		
		if(tankFactory->playerTank == NULL) return;
		for (BulletFactory::BulletIterator b = bulletFactory->bulletList.begin(); b != bulletFactory->bulletList.end(); b++){ //iterator of bulletList
			Bullet* bullet = *b;
			
			p = bullet->getEntity()->getWorldBoundingBox();
				for (TreeFactory::TreeIterator t = treeFactory->treeList.begin(); t != treeFactory->treeList.end();){
				Tree *tree = *t;
				q = tree->getEntity()->getWorldBoundingBox();
				if(p.intersects(q)){
					t++;
					tree->setStatus(false);
					//textArea->setCaption("boom");
					mWorld->geometryList.remove(tree->getEntity());
					
				}else{
					t++;
				}
			}
			

		}
		
	}

	void CollisionManager::detectPlayerTankVsBonusItemsCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time){
		if(tankFactory->playerTank == NULL) return;

		for (ItemFactory::ItemIterator i = itemFactory->itemList.begin(); i != itemFactory->itemList.end(); i++ ){
			Item *item = *i;
			p = item->getEntity()->getWorldBoundingBox();
			q = tankFactory->playerTank->getEntity()->getWorldBoundingBox();
			if(p.intersects(q)){
				itemFactory->processItemTanken(item->getType());
				item->setStatus(false);
			}
		
		}
	
	}

	void CollisionManager::detectBulletVsGeometryCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q){
		for (BulletFactory::BulletIterator b = bulletFactory->bulletList.begin(); b != bulletFactory->bulletList.end(); b++){ //iterator of bulletList
					//use a border list
					Bullet *bullet = *b;
					p = bullet->getEntity()->getWorldBoundingBox();
					for (TankWarWorld::GeometryIterator g = mWorld->geometryList.begin(); g != mWorld->geometryList.end(); g++){ //iterator of geometryList
						Entity *e = *g;
						q = e->getWorldBoundingBox();
						if(p.intersects(q)){
							bullet->setStatus(false);
						}

					}

					if (bullet->getSceneNode()->getPosition().y <= 0){ // I didn't add plane to world geometry list, for tanks always intersects with plane...
						bullet->setStatus(false);
					}


					/*
					if (bullet->getPosition().y <= 0){
						bullet->setStatus(false);
					}

					p = bullet->getEntity()->getWorldBoundingBox();
					q = mSceneManager->getEntity("TESTBOX")->getWorldBoundingBox();
					if (p.intersects(q)){
							bullet->setStatus(false);
					}
					for (int border_iter = 0; border_iter <=3; border_iter++){
						sprintf(border_s, "Border%d", border_iter);
						q = mSceneManager->getEntity(border_s)->getWorldBoundingBox();
						if(p.intersects(q)){
							bullet->setStatus(false);
							break;
						}
					}

					*/
				}
	}

	/*my if statement, but O(n^2)*/
	void CollisionManager::detectTankVsBulletCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q){
		for (BulletFactory::BulletIterator b = bulletFactory->bulletList.begin(); b != bulletFactory->bulletList.end(); b++){ //iterator of bulletList
				Bullet *bullet = *b;
				p = bullet->getEntity()->getWorldBoundingBox();
				for (TankFactory::TankIterator t = tankFactory->tankList.begin(); t != tankFactory->tankList.end(); t++){//iterator of tankList
					Tank *tank = *t;
					q = tank->getEntity()->getWorldBoundingBox();
					if(q.intersects(p)){
						if(bullet->getLauncherID() != tank->getID()){ //not hurting its launcher
							bullet->setStatus(false);
							if(bullet->getRank() != tank->getRank()){ //not hurting its teamate	
								float damage = bullet->getDamage() - tank->getDefence();
								if(damage < 0) damage = 0;
								tank->setLife(tank->getLife()- damage);
								if(tank->getLife() <= 0){ //is dying
									if(tank->isAlive() == true){
										if(bullet->getLauncher()->getType() == TANK_PLAYER) {
											if(tank->getType() == TANK_A) playerScore += 1;
											else if(tank->getType() == TANK_C) playerScore += 2;
											else if(tank->getType() == TANK_B) playerScore += 10;
										}
									}
									//socremanager(tank); //this socre manager need to be deleted later, just show a sore here  ////////////////////
									tank->setStatus(false); //set tank alive status to false;
										
								} 
								break;
							}
						}
					}
				}	
		}
	}
	void CollisionManager::detectTankVsTankCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time){//iterator of tankList

		if(tankFactory->playerTank != NULL){ 
			tankFactory->playerTank->freeBlock();
		}
		for (TankFactory::TankIterator t0 = tankFactory->tankList.begin(); t0 != tankFactory->tankList.end(); t0++){
					Tank *tank0 = *t0;
					p = tank0->getEntity()->getWorldBoundingBox();

					for (TankFactory::TankIterator t1 = tankFactory->tankList.begin(); t1 != tankFactory->tankList.end(); t1++){//iterator of tankList
						Tank *tank1 = *t1;
						q = tank1->getEntity()->getWorldBoundingBox();
						if(p.intersects(q) && tank0->getID() != tank1->getID()){
							tank0->setMoveCD(0.0f);  //set moveCD to 0, so update will call resetAction();
							tank1->setMoveCD(0.0f);

							

							break;
						}	
					}
					
					if(tankFactory->playerTank != NULL){ 
						q = tankFactory->playerTank->getEntity()->getWorldBoundingBox();
						if (p.intersects(q) && tank0->getID() != tankFactory->playerTank->getID()){
							if(tankFactory->playerTank->level >= 3 && tank0->getType() != TANK_B){      //roller compaction condition
								tank0->setStatus(false);
								return;
							}
							tank0->setMoveCD(0.0f);
							
							tankFactory->playerTank->setBlock(time);
						}
					}
					

		}
	}
	void CollisionManager::detectTankVsGeometryCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time){ //


		for (TankWarWorld::GeometryIterator g = mWorld->geometryList.begin(); g != mWorld->geometryList.end(); g++){ //iterator of geometryList
					Entity *e = *g;
					q = e->getWorldBoundingBox();
					for (TankFactory::TankIterator t0 = tankFactory->tankList.begin(); t0 != tankFactory->tankList.end(); t0++){
						Tank *tank0 = *t0;
						p = tank0->getEntity()->getWorldBoundingBox();
						if(q.intersects(p)){
							tank0->setMoveCD(0.0f); //for AI tanks
						}

					}

					//for player tank
					if(tankFactory->playerTank != NULL){ 
						p = tankFactory->playerTank->getEntity()->getWorldBoundingBox();
						tankFactory->playerTank->freeBlock();
					
						if (p.intersects(q)){
								tankFactory->playerTank->setBlock(time);
						}	
					}
		}



		/*

		for (TankFactory::TankIterator t0 = tankFactory->tankList.begin(); t0 != tankFactory->tankList.end(); t0++){
					Tank *tank0 = *t0;
					p = tank0->getEntity()->getWorldBoundingBox();

					q = mSceneManager->getEntity("TESTBOX")->getWorldBoundingBox();
					if (p.intersects(q)){
						tank0->setMoveCD(0.0f); 
					}
					for (int border_iter = 0; border_iter <=3; border_iter++){
						sprintf(border_s, "Border%d", border_iter);
						q = mSceneManager->getEntity(border_s)->getWorldBoundingBox();
						if(p.intersects(q)){
							tank0->setMoveCD(0.0f); 
							break;
						}
					}

					Tank *playertank = tankFactory->getPlayerTank();
					p = playertank->getEntity()->getWorldBoundingBox();

					playertank->freeBlock();

					q = mSceneManager->getEntity("TESTBOX")->getWorldBoundingBox();
					if (p.intersects(q)){
							playertank->setBlock(time);
					}

					for (int border_iter = 0; border_iter <=3; border_iter++){
						sprintf(border_s, "Border%d", border_iter);
						q = mSceneManager->getEntity(border_s)->getWorldBoundingBox();
						if(p.intersects(q)){
							playertank->setBlock(time);
							break;
						}
					}
		}
		*/
	}
	/*stupid manager, just for fun, need to be deleted*/
	void CollisionManager::socremanager(Tank* tank){
		if(tank->getRank() == 0){
			team2++;
		}else{
			team1++;
		}
		char h[30];
		sprintf(h, "Team1 vs Team2 : %d : %d", team1, team2);;
		textArea->setCaption(h);	 
	}

}