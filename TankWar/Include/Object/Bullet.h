#ifndef BULLET_H
#define BULLET_H

#include "Ogre.h"
#include "Object\BaseObject.h"
#include "Object\Tank.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	enum BULLET_TYPE
	{
		BULLET_GENERAL,		
		BULLET_MISSILE,	
		BULLET_PIERCING,
		BULLET_ROCKET
	};


	class Tank;

	class Bullet:public BaseObject
	{
	public: Bullet(int ID, int launcherID, float lifeTime, float damage, Ogre::Vector3 position, Ogre::Matrix3 orientation,Ogre::Vector3 direction, Ogre::SceneManager *mSceneManager, Tank* launcher, BULLET_TYPE type, std::string meshName):
				BaseObject(ID,position, orientation, mSceneManager, meshName), 
					damage(damage), lifeTime(lifeTime),launcherID(launcherID),launcher(launcher), type(type), direction(direction)
			{
				//setupObjectUnit();
				//placeObject();/*override*/
				//setupVariables();/*override*/
			
			}
		
			~Bullet();

			float getLifeTime();
			float getDamage();


			int getLauncherID();
			int getRank();


	
			Bullet* getBulletObject();


			void update(float time);

			Tank* launcher;
			Tank* getLauncher();
			BULLET_TYPE getBulletType();

			//void destroy();

	protected:
			float lifeTime;  /*how long this bullet can exist*/
			float damage;    /*damage may cause if hits on Objects*/
		

			int launcherID;  /* uniqure ID of the Tank that launches this bullet*/
			int rank;		 /* which team this bullet belongs to*/
			BULLET_TYPE type;/* type of this bullet*/
	
			float speed;   /*speed of the bullet*/
		
			Ogre::ParticleSystem		*mParticle;					
			Ogre::ParticleSystem		*mExplosionParticle;		
			Ogre::SceneNode			*mParticleNode;
			Ogre::SceneNode			*mExplosionParticleNode;

			Ogre::SceneNode         *tailNode;
			Ogre::Entity            *tail;

			void setupVariables();/*override*/
			void placeObject();/*override*/
			Ogre::Vector3 direction;

	private: /*some private funcs*/
		    
	};
}

#endif