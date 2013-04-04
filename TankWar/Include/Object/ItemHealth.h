#ifndef ITEM_HEALTH_H
#define ITEM_HEALTH_H

#include "Object/Item.h"
#include "Ogre.h"
using namespace Ogre;

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	const static std::string ITEM_HEALTH_MESH_NAME = "HealthBonus.mesh";
	class ItemHealth: public Item
	{

	public: ItemHealth(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, ITEM_TYPE type):	
				Item(ID, position, orientation, sceneManager, ITEM_HEALTH_MESH_NAME, type){
					setupObjectUnit();
					placeObject();
					setupVariables();
				}

	
			//void update(float time);

	protected:
			void setupVariables();

	};
}

#endif