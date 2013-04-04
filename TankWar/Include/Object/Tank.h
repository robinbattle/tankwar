#ifndef TANK_H
#define TANK_H


#include "Ogre.h"
#include "Object/BaseObject.h"
#include "Object/Item.h"
namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{

	enum TANK_TYPE
	{
		TANK_PLAYER,		
		TANK_A,
		TANK_B,
		TANK_C
	};

	enum TANK_MODE
	{
		TANK_ATTACK,
		TANK_DEFENCE
	};


	//const static std::string TANK_BODY_MESH_NAME = "MyTank.mesh";
	//const static std::string TANK_HEAD_MESH_NAME = "TankHead.mesh";
	//const static std::string TANK_BARREL_MESH_NAME = "TankBarrel.mesh";
	//const static std::string TANK_BARREL_MACHINE_MESH_NAME = "TankBarrelMachine.mesh";
	//const static std::string TANK_BARREL_WHEEL;
	
	class BulletFactory;

	class Tank: public BaseObject
	{

	public: Tank::Tank(int ID, float life, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, BulletFactory* bulletFactory, int rank, TANK_TYPE type, std::string meshName): 
				BaseObject(ID,position, orientation, sceneManager, meshName), 
					life(life), bulletFactory(bulletFactory),rank(rank),type(type) 
			{
			//setupObjectUnit();
			//placeObject();
			//setupAccessories();
			//setupVariables(); /*override*/
			}

			float getDamage();
			void setDamage(float newValue);
			float getDefence();
			void setDefence(float newValue);
			float getMovingSpeed();
			void setMovingSpeed(float newValue);

			void switchMode();
			TANK_MODE mode;
			void attackMode();
			void defenceMode();
		
			void setupUniqueVariable();
			
			float getLife();
			void setLife(float newLife);
			bool ifEquipmentTaken();

			void levelUp();

			Tank* getObject();

			void fire(float timeSinceLastFrame);
			void addtionalGunFire(float timeSinceLastFrame);
			void fireScattering(float timeSinceLastFrame);
			void moveForward(float timeSinceLastFrame);
			void moveBackward(float timeSinceLastFrame);
			void turnLeft(float timeSinceLastFrame);
			void turnRight(float timeSinceLastFrame);
			void lookUp(float timeSinceLastFrame);
			void lookDown(float timeSinceLastFrame);
			void lookLeft(float timeSinceLastFrame);
			void lookRight(float timeSinceLastFrame);
			void setBlock(float delta);
			void freeBlock();

			void addLife(float addtionalLife);

			void update(float time);
		
			int getRank();
			TANK_TYPE getType();
			char getMovingLock();
			void setMovingStatus(char direction);
			void destroy();

			void addNewEquipment(ITEM_TYPE type); /*add new will unload previous additional equipment */
			void effectedbyMine();
			void activedShadow();   /* not yet implements */

			void setMoveCD(float newCD);
			bool ifExplodeFinished();
			void updateExplode(float time);
			Ogre::SceneNode         *headNode;
			Ogre::Entity            *headEntity;
			Ogre::SceneNode         *barrelNode;
			Ogre::Entity            *barrelEntity;
			Ogre::SceneNode         *equipmentNode;
			Ogre::Entity            *equipmentEntity;
	
			int level;
			
	protected:
			/*some varialbes that controls tank status*/
			int rank;    /* team it belongs to */
			TANK_TYPE type;    /* type of the tank, for now, just Player and AI */
			float life;  /* life of the tank */
			float fireCD; /* firing cooldown */
			float moveCD;/* moving cooldown */
			float switchCD;
			float rotateTolerence;/* restrict rotate degree   -0.3 <--> 1.0*/
			float explodeTime;
			void setupAccessories(const std::string head, const std::string barrel, const std::string machineGun); /* tank head, barrel, etc.*/
			void setupVariables();/*override*/
			
			bool equipmentTaken;    /* if player tank already has an equipment*/
			float addtionalEquipmentCD;
			int addtionalEquipmentAmount;
			ITEM_TYPE addtionalEquipmentType;

			bool stepOnMine;    /* if player tank already has an equipment*/
			float mineEffectCD;
			void rotateTankQuickly(float time);

			BulletFactory* bulletFactory;

			//unique
			float damage;
			float defence;
			float movingSpeed;

			void resetAction();               /*reset the sillyAi control bools*/
			void sillyAI(float time);		  /*a simple and silly AI, for every x second, turns left, right, goes forward, backward, or fires*/
	//private:
			

			
			/*control variables*/
			bool mFire;
			bool permit;
			char mMovingLock;
			bool mForward;
			bool mBackward;
			bool mLeft;
			bool mRight;
			Ogre::Vector3 pos;
			Ogre::Vector3 ori;
		
	};
}

#endif