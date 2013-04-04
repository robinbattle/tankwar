#include "Factory/ItemFactory.h"
#include "Ogre.h"



namespace TankWar
{
	

	ItemFactory::ItemFactory(Ogre::SceneManager *sceneManager, TankFactory *tankFactory): mSceneManager(sceneManager), tankFactory(tankFactory){
		IDCounter = 100000;
	
	}
	
	Item* ItemFactory::generateItem(Ogre::Vector3 position, float timeSinceLastFrame, ITEM_TYPE type){

		switch(type){
			case ITEM_HEALTH: /*Player*/{
					newItem = new ItemHealth(IDCounter, position, Ogre::Matrix3::IDENTITY, mSceneManager,type);
			}break;
			case ITEM_LAND_MINE:/*AI*/{
					newItem = new ItemLandMine(IDCounter, position, Ogre::Matrix3::IDENTITY, mSceneManager,type);
			}break;
			case ITEM_MACHINE_GUN:/*AI*/{
					newItem = new ItemMachineGun(IDCounter, position, Ogre::Matrix3::IDENTITY, mSceneManager,type);
			}break;
		}


		//add to item list
		itemList.push_back(newItem);

		//increment ID No.
		IDCounter++;
		
		return newItem;
	}


	std::string ItemFactory::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}




	void ItemFactory::update(float time){
		if(!itemList.empty()){
			for (ItemIterator i = itemList.begin(); i != itemList.end();  ){
				Item *item = *i;
				item->update(time);

				if (!item->isAlive())
				{	
						//delete
						destroyItem(item);
						Item* tmp = item;
						i++;
						itemList.remove(tmp);
				
				}
				else
				{
					i++;
				}
			
			}
		}
		

		
	}

	void ItemFactory::processItemTanken(ITEM_TYPE type){
		if(type == ITEM_LAND_MINE){
					tankFactory->playerTank->addLife(-50);    // nagative life
					tankFactory->playerTank->effectedbyMine();    // quickly rotate player tank
		}else if(type == ITEM_MACHINE_GUN){
					tankFactory->playerTank->addNewEquipment(type);
		}else if(type == ITEM_HEALTH){
					tankFactory->playerTank->addLife(100);
		}
	}

	void ItemFactory::destroyItem(Item* item){
		//Ogre::String IDString = convertInt(bullet->getID());
		//mSceneManager->destroySceneNode(IDString + "mainNode");
		//mSceneManager->destroyEntity(IDString + "mainEntity");
		item->destroy();
	}


	void ItemFactory::clearAll(){
		for (ItemIterator i = itemList.begin(); i != itemList.end();  ){
				Item *item = *i;     
				//delete bullet
				item->setStatus(false);
				i++;
		}
	}

}