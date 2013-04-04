#include "Factory/BulletFactory.h"
#include "Ogre.h"
#include "Object/Tank.h"
#include "CollisionManagement/CollisionManager.h"



namespace TankWar
{
	

	BulletFactory::BulletFactory(Ogre::SceneManager *sceneManager):mSceneManager(sceneManager)
	//BulletFactory::BulletFactory(Ogre::SceneManager *sceneManager, CollisionManager* mCollisionManager):mSceneManager(sceneManager), mCollisionManager(mCollisionManager)

	{
		IDCounter = 10000;


	}



	Bullet* BulletFactory::generateBullet(int launcherID, float damage, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::Vector3 direction, Tank* launcher, float timeSinceLastFrame, BULLET_TYPE type){
		


		switch(type){
			case BULLET_GENERAL: {
					newBullet = new BulletGeneral(IDCounter, launcherID, timeSinceLastFrame, damage, position, orientation, direction, mSceneManager, launcher, type);
			}break;
			case BULLET_MISSILE:{
					newBullet = new BulletMissile(IDCounter, launcherID, timeSinceLastFrame,  damage, position, orientation, direction, mSceneManager, launcher, type);
			}break;
			case BULLET_PIERCING:{
					newBullet = new BulletPiercing(IDCounter, launcherID, timeSinceLastFrame, damage, position, orientation, direction, mSceneManager, launcher, type);
			}break;
			case BULLET_ROCKET:{
					newBullet = new BulletRocket(IDCounter, launcherID, timeSinceLastFrame, damage, position, orientation, direction, mSceneManager, launcher, type);
			}break;
		}

		
		//add to bulletlist
		bulletList.push_back(newBullet);

		//increment ID No.
		IDCounter++;
		
		return newBullet;
	}

	

	std::string BulletFactory::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	void BulletFactory::update(float time){

		for (BulletIterator b = bulletList.begin(); b != bulletList.end();  ){
				Bullet *bullet = *b;
				bullet->update(time);

				if (!bullet->isAlive())
				{	
						//delete
						destroyBullet(bullet);
						Bullet* tmp = bullet;
						b++;
						bulletList.remove(tmp);
				
				}
				else
				{
					b++;
				}
			
		}


	}

	void BulletFactory::destroyBullet(Bullet* bullet){
		//Ogre::String IDString = convertInt(bullet->getID());
		//mSceneManager->destroySceneNode(IDString + "mainNode");
		//mSceneManager->destroyEntity(IDString + "mainEntity");
		bullet->destroy();
	}


	void BulletFactory::clearAll(){
		for (BulletIterator b = bulletList.begin(); b != bulletList.end();  ){
				Bullet *bullet = *b;          
				//delete bullet
				bullet->setStatus(false);
				b++;
		}
	}

}