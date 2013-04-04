#ifndef ITEM_MACHINEGUN_H
#define ITEM_MACHINEGUN_H

#include "Object/Item.h"
#include "Ogre.h"
using namespace Ogre;

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	const static std::string ITEM_MACHINE_GUN_MESH_NAME = "MachineGunBonus.mesh";
	class ItemMachineGun: public Item
	{

	public: ItemMachineGun(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, ITEM_TYPE type):	
				Item(ID, position, orientation, sceneManager, ITEM_MACHINE_GUN_MESH_NAME, type){
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