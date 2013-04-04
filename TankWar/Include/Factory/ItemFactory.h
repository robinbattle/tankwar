
#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H


#include "Ogre.h"
#include "Object/Item.h"
#include "Object/ItemHealth.h"
#include "Object/ItemLandMine.h"
#include "Object/ItemMachineGun.h"
#include "Factory/tankFactory.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{


	class CollisionManager;


	class ItemFactory
	{
		 /*plz see the explanation of TankFactory, not much different, lazy here*/

	public: ItemFactory(Ogre::SceneManager *sceneManager, TankFactory *tankFactory);   
			
			Item* generateItem(Ogre::Vector3 position, float timeSinceLastFrame, ITEM_TYPE type);
			/*generate items based on input */
			//update
			void update(float time); /* update all items in itemslist by every time frame*/
			void processItemTanken(ITEM_TYPE type);
			
			//define type
			typedef std::list<Item*>::iterator ItemIterator;  
			std::list<Item*> itemList;								/* a list holds all items created*/

			void clearAll();												/*clear all items in list*/

			

	protected:
		
			int IDCounter;
			float life;
			Item* newItem;
			Ogre::Vector3 position;
			Ogre::SceneNode* sceneNodeHolder;
			Ogre::Entity* entityHolder;
			Ogre::SceneManager* mSceneManager;
			CollisionManager* mCollisionManager;
			TankFactory *tankFactory;
			ITEM_TYPE type;

	private:
			std::string convertInt(int n);
			void destroyItem(Item* item);
			
	};


}

#endif