#include "Factory/TankFactory.h"
#include "Factory/BulletFactory.h"
#include "Ogre.h"

#include "CollisionManagement/CollisionManager.h"




//TankFactory::TankFactory(Ogre::SceneManager *sceneManager, CollisionManager* mCollisionManager, BulletFactory* bulletFactory):mSceneManager(sceneManager), mCollisionManager(mCollisionManager), bulletFactory(bulletFactory)
namespace TankWar
{
	TankFactory::TankFactory(Ogre::SceneManager *sceneManager, BulletFactory* bulletFactory):mSceneManager(sceneManager), bulletFactory(bulletFactory)
	{
		IDCounter = 100;
		rebornCD = 3.0f;
	}



	Tank* TankFactory::generateTank(Ogre::Vector3 position, int rank, TANK_TYPE type){


		switch(type){
			case TANK_PLAYER: /*Player*/{
					newTank = new TankPlayer(IDCounter, 200, position, Ogre::Matrix3::IDENTITY, mSceneManager, bulletFactory, rank, type);	
					newTank->getSceneNode()->scale(1.5, 1.5, 1.5);
					playerTank = newTank;
					
			}break;
			case TANK_A:/*AI*/{
					newTank = new TankA(IDCounter, 100, position, Ogre::Matrix3::IDENTITY, mSceneManager, bulletFactory, rank, type);	
					newTank->getSceneNode()->scale(1.5, 1.5, 1.5);
					

			}break;
			case TANK_B: /*Player*/{
					newTank = new TankB(IDCounter, 100, position, Ogre::Matrix3::IDENTITY, mSceneManager, bulletFactory, rank, type);	
					newTank->getSceneNode()->scale(3, 3, 3);
					
			}break;
			case TANK_C: /*Player*/{
					newTank = new TankC(IDCounter, 100, position, Ogre::Matrix3::IDENTITY, mSceneManager, bulletFactory, rank, type);	
					newTank->getSceneNode()->scale(1, 1, 3);
					
			}break;
		}

		IDCounter++;
		//add to tankList
		tankList.push_back(newTank);
		return newTank;

		
	}


	std::string TankFactory::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}


	void TankFactory::update(float time){
	
		updateAllTankStatus(time);
		
		//checkIfNeedToRebornPlayer(time);
	}


	void TankFactory::updateAllTankStatus(float time){
		for (TankIterator t = tankList.begin(); t != tankList.end();){ //t shouldn't be increment in for loop, may cause program crashes.
				Tank* tank = *t;             
				tank->update(time);
				if (tank->ifExplodeFinished())
				{	
					if(tank->getType() != TANK_PLAYER){
						//delete tank
						destroyTank(tank);
						Tank* tmp = tank;
						t++;
						tankList.remove(tmp);
					}else{
						destroyTank(tank);
						Tank* tmp = tank;
						t++;
						tankList.remove(tmp);
						rebornPlayer();
					}	
				}
				else
				{
					t++;
				}
		}
	}

	void TankFactory::destroyTank(Tank* tank){
		int type = tank->getType();
		tank->destroy();

		//may need to be deleted
		//autoGenerate(type);                 /*  -----------   auto generates a new one after current one destroyed, close it now for preventing potential unexpected error----    */
	
	}


	void TankFactory::autoGenerate(int rank, TANK_TYPE type){
		Ogre::Vector3 randomPosition(Ogre::Math::RangeRandom(-1500,1500), 0, Ogre::Math::RangeRandom(-1500,1500));
	
		generateTank(randomPosition, rank, type);
	}

	void TankFactory::rebornPlayer(){
		//Ogre::Vector3 randomPosition(Ogre::Math::RangeRandom(-1500,1500), 0, Ogre::Math::RangeRandom(-1500,1500));
		playerTank = new TankA(IDCounter, 200, Ogre::Vector3(1550,0,1250), Ogre::Matrix3::IDENTITY, mSceneManager, bulletFactory, 0, TANK_PLAYER);	
		playerTank->getSceneNode()->scale(1.5, 1.5, 1.5);
		IDCounter++;
		//add to tankList
		tankList.push_back(playerTank);

	}

	void TankFactory::clearAll(){ //exception is player tank
		for (TankIterator t = tankList.begin(); t != tankList.end();){ //t shouldn't be increment in for loop, may cause program crashes.
				Tank* tank = *t;             

				if(tank->getType() == TANK_PLAYER){
					playerTank = NULL;
				}
				t++;
				destroyTank(tank);
				tankList.remove(tank);
		}

		//tankList.clear();
	}
}