
#ifndef TANKB_H
#define TANKB_H

#include "Ogre.h"
#include "Object\Tank.h"
#include "Object\Bullet.h"
#include "Factory\BulletFactory.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{

	const static std::string TANK_B_BODY_MESH_NAME = "MyTank.mesh";
	const static std::string TANK_B_HEAD_MESH_NAME = "TankHead.mesh";
	const static std::string TANK_B_BARREL_MESH_NAME = "TankBarrel.mesh";
	const static std::string TANK_B_BARREL_MACHINE_MESH_NAME = "TankBarrelMachine.mesh";

	class BulletFactory;

	class TankB: public Tank
	{


		public: TankB(int ID, float life, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, BulletFactory* bulletFactory, int rank, TANK_TYPE type): Tank(ID,life, position,orientation, sceneManager, bulletFactory,rank, type, TANK_B_BODY_MESH_NAME)
		{
			setupObjectUnit();
			placeObject();
			setupAccessories(TANK_B_HEAD_MESH_NAME, TANK_B_BARREL_MESH_NAME, TANK_B_BARREL_MACHINE_MESH_NAME);
			setupVariables();
			setupUniqueVariable();
		}
		protected:
			void setupUniqueVariable();
	
	};
}

#endif