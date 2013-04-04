
#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H


#include "Ogre.h"
#include "Object/Bullet.h"
#include "Object/BulletRocket.h"
#include "Object/BulletGeneral.h"
#include "Object/BulletMissile.h"
#include "Object/BulletPiercing.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{

	//class Bullet;
	class Tank;
	class CollisionManager;


	class BulletFactory
	{
		 /*plz see the explanation of TankFactory, not much different, lazy here*/

	public: BulletFactory(Ogre::SceneManager *sceneManager);   
			//BulletFactory(Ogre::SceneManager *sceneManager, CollisionManager* mCollisionManager);
			Bullet* generateBullet(int launcherID, float damage, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::Vector3 direction, Tank* launcher, float timeSinceLastFrame, BULLET_TYPE type);
			/*generate bullets based on input */
			//update
			void update(float time); /* update all bullets in bulletlist by every time frame*/

			
			//define type
			typedef std::list<Bullet*>::iterator BulletIterator;  
			std::list<Bullet*> bulletList;								/* a list holds all bullets created*/

			void clearAll();												/*clear all bullets in list*/

			

	protected:
		
			int IDCounter;
			float life;
			Bullet* newBullet;
			Ogre::Vector3 position;
			Ogre::Matrix3 orientation;
			Ogre::SceneNode* sceneNodeHolder;
			Ogre::Entity* entityHolder;
			Ogre::SceneManager* mSceneManager;
			CollisionManager* mCollisionManager;

			BULLET_TYPE type;

	private:
			std::string convertInt(int n);
			void destroyBullet(Bullet* bullet);
			
	};


}

#endif