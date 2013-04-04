#ifndef ITEM_H
#define ITEM_H

#include "Object/BaseObject.h"
#include "Ogre.h"
using namespace Ogre;

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	 enum ITEM_TYPE
	{
		ITEM_HEALTH,		
		ITEM_LAND_MINE,	
		ITEM_MACHINE_GUN
	};
	
	class Item: public BaseObject
	{

	public: Item(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, std::string meshName, ITEM_TYPE type):	
				BaseObject(ID,position, orientation, sceneManager, meshName), 
				type(type) {
					//setupObjectUnit();
					//placeObject();
					//setupVariables();
				}

			ITEM_TYPE getType();

			int amount;
			float CD;
			
			void update(float time);

	protected:
			ITEM_TYPE type;
			void setupVariables();

	};
}

#endif