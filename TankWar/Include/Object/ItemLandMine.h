#ifndef ITEM_LANDMINE_H
#define ITEM_LANDMINE_H

#include "Object/Item.h"
#include "Ogre.h"
using namespace Ogre;

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	const static std::string ITEM_LAND_MINE_MESH_NAME = "LandMineBonus.mesh";
	class ItemLandMine: public Item
	{

	public: ItemLandMine(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, ITEM_TYPE type):	
				Item(ID, position, orientation, sceneManager, ITEM_LAND_MINE_MESH_NAME, type){
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