#ifndef BULLETPIERCING_H
#define BULLETPIERCING_H

#include "Ogre.h"
#include "Object\Bullet.h"


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	const static std::string BULLET_PIERCING_MESH_NAME = "Bullet.mesh";

	class BulletPiercing:public Bullet
	{
	public: BulletPiercing(int ID, int launcherID, float lifeTime, float damage, Ogre::Vector3 position, Ogre::Matrix3 orientation,Ogre::Vector3 direction, Ogre::SceneManager *mSceneManager, Tank* launcher, BULLET_TYPE type):
				Bullet(ID, launcherID, lifeTime, damage, position, orientation, direction, mSceneManager, launcher, type, BULLET_PIERCING_MESH_NAME)
			{
				setupObjectUnit();
				placeObject();
				setupVariables();
			}	
	};
}

#endif