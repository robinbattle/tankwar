#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H


#include "Ogre.h"
#include "World.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}


namespace TankWar
{
	class Bullet;
	class Tank;
	class CollisionTools;
	class BulletFactory;
	class TankFactory;
	class ItemFactory;
	class TreeFactory;

	class CollisionManager
	{

	public: CollisionManager(Ogre::SceneManager *sceneManager, TankFactory *tankFactory, BulletFactory *tulletFactory, ItemFactory* itemFactory, TreeFactory* treeFactory, TankWarWorld *world);

			//update
			void update(float time);
			Ogre::Entity* checkCollision(const Ogre::Vector3& fromPoint, const Ogre::Vector3& toPoint, float collisionRadius, int queryMask);

			float playerScore;

	protected:
			Ogre::SceneManager *mSceneManager;
			CollisionTools *collisionTools;
			TankFactory *tankFactory;
			BulletFactory *bulletFactory;
			ItemFactory* itemFactory;
			TankWarWorld *mWorld;
			TreeFactory* treeFactory;
	
	private:
			std::string convertInt(int n);
			void detectBulletVsGeometryCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q);
			void detectTankVsBulletCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q);
			void detectTankVsTankCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time);
			void detectTankVsGeometryCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time);
			void detectPlayerTankVsBonusItemsCollsion(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time);
			void detectBulletVsTree(Ogre::AxisAlignedBox p, Ogre::AxisAlignedBox q, float time);
		

			void socremanager(Tank* tank);

			int team1;
			int team2;
	};

}

#endif