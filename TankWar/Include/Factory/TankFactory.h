#ifndef TANKFACTORY_H
#define TANKFACTORY_H

#include "Ogre.h"
#include "Object/Tank.h"
#include "Object/TankA.h"
#include "Object/TankB.h"
#include "Object/TankC.h"
#include "Object/TankPlayer.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}



namespace TankWar
{
	//using namespace TankWar;
	//class Tank;
	class BulletFactory;
	class CollisionManager;

	class TankFactory
	{
	public: TankFactory(Ogre::SceneManager *sceneManager, BulletFactory* bulletFactory);
			//TankFactory(Ogre::SceneManager *sceneManager, CollisionManager* mCollisionManager, BulletFactory* bulletFactory);
			Tank* generateTank(Ogre::Vector3 position, int rank, TANK_TYPE type); /*generate tanks based on input varialbes*/
																			/* rank is for team, type is like Player or AI*/
			//update
			void update(float time);                                        /*update tankList for every time frame*/
			//define type
			typedef std::list<Tank*>::iterator TankIterator;
			std::list<Tank*> tankList;										/*a tank list that holds all tank objects create by tank factory*/

			void autoGenerate(int rank, TANK_TYPE type);
			void clearAll();												/*clear all tanks in list*/

			Tank* playerTank;
	
	protected:
		
			int IDCounter;													/*Uniqure name counter*/
			float life;														/*this should be useless for now, the default life of tank*/
			Tank* newTank;													
			Ogre::Vector3 position;											/*some varialbes declare, so no need to be redecalre again*/
			Ogre::Vector3 direction;
			Ogre::SceneNode* sceneNodeHolder;
			Ogre::Entity* entityHolder;
			Ogre::SceneManager* mSceneManager;
			CollisionManager* mCollisionManager;
			BulletFactory* bulletFactory;

			/*used to reborn player*/

			float rebornCD;
		
	private:
			std::string convertInt(int n);
			void destroyTank(Tank *tank);
			
			void checkIfNeedToRebornPlayer(float time);
			void updateAllTankStatus(float time);
			void rebornPlayer();

	};

}

#endif