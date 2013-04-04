#ifndef BULLETMISSILE_H
#define BULLETMISSILE_H

#include "Ogre.h"
#include "Object\Bullet.h"


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	const static std::string BULLET_MISSILE_MESH_NAME = "Bullet.mesh";

	class BulletMissile:public Bullet
	{
	public: BulletMissile(int ID, int launcherID, float lifeTime, float damage, Ogre::Vector3 position, Ogre::Matrix3 orientation,Ogre::Vector3 direction, Ogre::SceneManager *mSceneManager, Tank* launcher, BULLET_TYPE type):
				Bullet(ID, launcherID, lifeTime, damage, position, orientation, direction, mSceneManager, launcher, type, BULLET_MISSILE_MESH_NAME)
			{
				setupObjectUnit();
				placeObject();
				setupVariables();
			}
		
			
	};
}

#endif