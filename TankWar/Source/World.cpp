#include "World.h"
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
//#include "Constants.h"
#include "OgreSphere.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "DotSceneLoader.h"
#include "TankWarSceneManager.h"
#include "Factory\TankFactory.h"
#include "Factory\BulletFactory.h"
#include "Factory\ItemFactory.h"
#include "Factory\TreeFactory.h"

//#include "Object\Tank.h"
//#include "Object\Bullet.h"
#include "Tools/SoundManager.h"
using namespace Ogre;



namespace TankWar
{

	TankWarWorld::TankWarWorld(SceneManager *sceneManager, Ogre::RenderWindow* mWindow, TankWarSceneManager *sceneTemple, TankFactory* tankFactory, BulletFactory* bulletFactory, ItemFactory* itemFactory, TreeFactory* treeFactory) : 
	mSceneManager(sceneManager), mWindow(mWindow), mSceneTemple(sceneTemple), tankFactory(tankFactory), bulletFactory(bulletFactory), itemFactory(itemFactory), treeFactory(treeFactory)
	{	
		//SetupDefaultGame();
	}

	void TankWarWorld::SetupDefaultGame()
	{

		createPlanes();
		createLights();
		createTanks();
	}

	void TankWarWorld::loadScene(){
		SceneNode *wor = mSceneManager->getRootSceneNode()->createChildSceneNode();

		DotSceneLoader* mLoader = new DotSceneLoader();
		mLoader->parseDotScene("111.scene", "General", mSceneManager, mSceneManager->getRootSceneNode());
		geometryList.push_back(mSceneManager->getEntity("Cone001"));        //add to list
		geometryList.push_back(mSceneManager->getEntity("Pyramid001"));     //add to list
		geometryList.push_back(mSceneManager->getEntity("Pyramid002"));     //add to list
		// Load more files if needed.
		delete mLoader;
	}

	void TankWarWorld::worldEditor(){
		
	
	}
	


	void TankWarWorld::createPlanes(){  /*this part could be replaced by other scene*/

		/******************************************/
		//used for generate beautiful world
		//mSceneTemple->generate();
		/******************************************/

		/******************************************/
		//a simple rock plane, loading fast



		mSceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
		Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 5000, 5000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
		Ogre::Entity* entGround = mSceneManager->createEntity("GroundEntity", "ground");
		mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
		//geometryList.push_back(entGround); //shouldn't add plane to list....


		

		//create border
		Ogre::Entity* entBorder = mSceneManager->createEntity("Border0","MyCube.mesh");
		Ogre::SceneNode* mBorder0 = mSceneManager->getRootSceneNode()->createChildSceneNode("Border0", Vector3(2500,0,0));
		mBorder0->attachObject(entBorder);
		mBorder0->scale(5,50,2500);
		geometryList.push_back(entBorder);//1
		entBorder = mSceneManager->createEntity("Border1","MyCube.mesh");
		Ogre::SceneNode* mBorder1 = mSceneManager->getRootSceneNode()->createChildSceneNode("Border1", Vector3(-2500,0,0));
		mBorder1->attachObject(entBorder);
		mBorder1->scale(5,50,2500);
		geometryList.push_back(entBorder);//2
		entBorder = mSceneManager->createEntity("Border2","MyCube.mesh");
		Ogre::SceneNode* mBorder2 = mSceneManager->getRootSceneNode()->createChildSceneNode("Border2", Vector3(0,0,2500));
		mBorder2->attachObject(entBorder);
		mBorder2->scale(2500,50,5);
		geometryList.push_back(entBorder);//3
		entBorder = mSceneManager->createEntity("Border3","MyCube.mesh");
		Ogre::SceneNode* mBorder3 = mSceneManager->getRootSceneNode()->createChildSceneNode("Border3", Vector3(0,0,-2500));
		mBorder3->attachObject(entBorder);
		mBorder3->scale(2500,50,5);
		geometryList.push_back(entBorder);//4
		entBorder = mSceneManager->createEntity("BARRIER","barrier1.mesh");
		Ogre::SceneNode* barrier = mSceneManager->getRootSceneNode()->createChildSceneNode("BARRIER", Vector3(-1250,0,1250));
		barrier->attachObject(entBorder);
		barrier->scale(50,40,50);
        geometryList.push_back(entBorder);//5
		entBorder = mSceneManager->createEntity("GASCAN","gasCan.mesh");
		Ogre::SceneNode* gascan = mSceneManager->getRootSceneNode()->createChildSceneNode("GASCAN", Vector3(1250,0,-1250));
		gascan->attachObject(entBorder);
		gascan->scale(50,40,50);
        geometryList.push_back(entBorder);
		entBorder->setCastShadows(false);

		entBorder = mSceneManager->createEntity("FACTORY0","factory.mesh");
		Ogre::SceneNode* factory0 = mSceneManager->getRootSceneNode()->createChildSceneNode("FACTORY0", Vector3(-1250,0,-1250));
		factory0->attachObject(entBorder);
		factory0->scale(50,40,50);
		geometryList.push_back(entBorder);
		entBorder->setCastShadows(false);

		entBorder = mSceneManager->createEntity("FACTORY1","factory.mesh");
		Ogre::SceneNode* factory1 = mSceneManager->getRootSceneNode()->createChildSceneNode("FACTORY1", Vector3(1250,0,1250));
		factory1->attachObject(entBorder);
		factory1->scale(50,40,50);
		geometryList.push_back(entBorder);
		entBorder->setCastShadows(false);

		entBorder = mSceneManager->createEntity("pBase","pBase.mesh");
		Ogre::SceneNode* pBase = mSceneManager->getRootSceneNode()->createChildSceneNode("pBase", Vector3(0,0,0));
		pBase->attachObject(entBorder);
		pBase->scale(50,40,50);
		geometryList.push_back(entBorder);
		entBorder->setCastShadows(false);
		

		

		entBorder = mSceneManager->createEntity("FACTORY","factory.mesh");
		Ogre::SceneNode* factory = mSceneManager->getRootSceneNode()->createChildSceneNode("FACTORY", Vector3(-1250,0,-1250));
		factory->attachObject(entBorder);
		factory->scale(40,40,40);
		geometryList.push_back(entBorder);
		entGround->setMaterialName("Examples/Rockwall");
		entGround->setCastShadows(false);
		/******************************************/

	}




	void TankWarWorld::createLights(){
		/*light*/
		Ogre::Light* pointLight = mSceneManager->createLight("pointLight");
		pointLight->setType(Ogre::Light::LT_POINT);
		pointLight->setPosition(Ogre::Vector3(0, 150, 250));
 
		pointLight->setDiffuseColour(0.0, 1.0, 0.0);
		pointLight->setSpecularColour(.75, 0.0, 1.0);
		Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");
		directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
		directionalLight->setSpecularColour(Ogre::ColourValue(.25, 0, .25));
 
		directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 
 
		Ogre::Light* spotLight = mSceneManager->createLight("spotLight");
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDiffuseColour(0, 0, 1.0);
		spotLight->setSpecularColour(0, 0, 1.0);
 
		spotLight->setDirection(-1, -1, 0);
		spotLight->setPosition(Ogre::Vector3(300, 300, 0));
 
		spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

		mSceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
		mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	}
	void TankWarWorld::createTanks(){
		/*tank*/
		Vector3 fool = Ogre::Vector3(1550,0,1250);
		tankFactory->playerTank = tankFactory->generateTank(fool, 0, TANK_PLAYER);   //player tank
		
	}

	


	void 
	TankWarWorld::Think(float time)
	{
		addBonusItems(time);
		addNewTanks(time);
		createTrees(time);
	}

	void TankWarWorld::addBonusItems(float time){
		if(itemFactory->itemList.size() < 25){
			//srand(time);
			Ogre::Vector3 randomPosition(Ogre::Math::RangeRandom(-1500,1500), 10, Ogre::Math::RangeRandom(-1500,1500));
			int r = rand()%3;
			if(r == 0) itemFactory->generateItem(randomPosition, time, ITEM_MACHINE_GUN);	 
			else if(r == 1) itemFactory->generateItem(randomPosition, time, ITEM_HEALTH);	 
			else if(r == 2) itemFactory->generateItem(randomPosition, time, ITEM_LAND_MINE);	 

		}
	}

	void TankWarWorld::createTrees(float time){
		Tree *t;
		Ogre::Vector3 randomPosition(Ogre::Math::RangeRandom(-1500,1500), 0, Ogre::Math::RangeRandom(-1500,1500));
		if(treeFactory->treeList.size() < 10){
			t = treeFactory->generateTree(randomPosition, Ogre::Matrix3::IDENTITY);
			geometryList.push_back(t->getEntity());
		}
		
	}

	void TankWarWorld::addNewTanks(float time){
		if(tankFactory->tankList.size() < 20){
			int r = rand()%4;
	
			if(r == 0) tankFactory->autoGenerate(1, TANK_A); 
			else if(r == 1) {
				tankFactory->autoGenerate(1, TANK_A); 
				tankFactory->autoGenerate(1, TANK_C); 
			} 
			else if(r == 3) {
				tankFactory->autoGenerate(1, TANK_A); 
				tankFactory->autoGenerate(1, TANK_B); 
				tankFactory->autoGenerate(1, TANK_A); 
			} 

		}
	}



	void TankWarWorld::clearGeometryList(){
		Entity* e;
		std::string name;
		for (GeometryIterator g = geometryList.begin(); g != geometryList.end(); ){
			e = *g;
			g++;
			name = e->getName();
			mSceneManager->destroySceneNode(name);
			mSceneManager->destroyEntity(name);
		}

		geometryList.clear();

		
	}

	void
	TankWarWorld::clearAll(){
		tankFactory->clearAll();
		bulletFactory->clearAll();
		itemFactory->clearAll();
		//clearGeometryList();
		//mSceneManager->destroyAllLights();
		//mSceneManager->destroyEntity("GroundEntity"); // not in geometry list
	



	}

	void TankWarWorld::showShadows(){
		for (GeometryIterator g = geometryList.begin(); g != geometryList.end(); g++){ //iterator of geometryList
					Entity *e = *g;
					e->setCastShadows(true);
		}
	}


	void
	TankWarWorld::DoSometing(){ //this one is only used to crash program, so carefully used it
		mSceneManager->setAmbientLight(ColourValue(1,1,1));
		Entity* ball = mSceneManager->createEntity("cube2", "MyCube.mesh");
		SceneNode *mBall = mSceneManager->getRootSceneNode()->createChildSceneNode();
		mBall->attachObject(ball);
		mBall->setPosition(50,50,0);
		ball = mSceneManager->createEntity("cube2", "MyCube.mesh"); //same name, check if program sticks in a loop

	}
}