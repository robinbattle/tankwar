#include "Object/Tank.h"
#include "Ogre.h"
#include "Factory/BulletFactory.h"


namespace TankWar
{
	

	void Tank::setupVariables(){
		damage = 60.0f;
		defence = 20.0f;
		if(type==TANK_PLAYER){movingSpeed = 100.0f;}else{movingSpeed = 20.0f;}

		

		fireCD = 1.0f;
		moveCD = 3.0f;
		switchCD = 1.0f;
		rotateTolerence = 0.0f;
		//mineEffectCD = 2.5f;
		mFire = false;
		mForward = false;
		mBackward = false;
		mLeft = false;
		mRight = false;
		permit = true;
		mMovingLock = 'z';

		alive = true;
		explodeTime = 5.0f;
		equipmentTaken = false;
		stepOnMine = false;
		entity->getAnimationState("gogo")->setLoop(false); 
        entity->getAnimationState("gogo")->setEnabled(true); 
		entity->getAnimationState("gogo")->setWeight(1.0); 
		
		

		headEntity->getAnimationState("gogo")->setLoop(false); 
        headEntity->getAnimationState("gogo")->setEnabled(true); 
		headEntity->getAnimationState("gogo")->setWeight(1.0);

		barrelEntity->getAnimationState("gogo")->setLoop(false); 
        barrelEntity->getAnimationState("gogo")->setEnabled(true); 
		barrelEntity->getAnimationState("gogo")->setWeight(1.0);

	}

	void Tank::setupAccessories(const std::string head, const std::string barrel, const std::string machineGun){
		headEntity = mSceneManager->createEntity(IDString + "headEntity", head);
		headNode = mainNode->createChildSceneNode(IDString + "headNode");
		headNode->attachObject(headEntity);
		headEntity->getMesh()->setAutoBuildEdgeLists(false);

		barrelEntity = mSceneManager->createEntity(IDString + "barrelEntity", barrel);
		barrelNode = headNode->createChildSceneNode(IDString + "barrelNode");
		barrelNode->attachObject(barrelEntity);
		barrelEntity->getMesh()->setAutoBuildEdgeLists(false);
		
		equipmentNode = barrelNode->createChildSceneNode(IDString + "equipmentNode");
		equipmentEntity = mSceneManager->createEntity(IDString + "equipmentEntity", machineGun);
	}


	void Tank::updateExplode(float time){
	    entity->getAnimationState("gogo")->addTime(time); //play animation
		headEntity->getAnimationState("gogo")->addTime(time); //play animation
		barrelEntity->getAnimationState("gogo")->addTime(time); //play animation
		//leftWheelEntity->getAnimationState("gogo")->addTime(time); //play animation
		//rightWheelEntity->getAnimationState("gogo")->addTime(time); //play animation

		explodeTime -= time;                              //decrement time counter
	}

	bool Tank::ifExplodeFinished(){
		return explodeTime < 0;
	}


	void Tank::addNewEquipment(ITEM_TYPE type){
		
		if(equipmentTaken == false){
			equipmentTaken = true;

			equipmentNode->attachObject(equipmentEntity);
			addtionalEquipmentCD = 0.2f;
			addtionalEquipmentAmount = 20;
			addtionalEquipmentType = type;

		}else{
			addtionalEquipmentAmount += 20;
		}
	
	}

	void Tank::effectedbyMine(){
		stepOnMine = true;
		mineEffectCD = 3.0f;
	}

	void Tank::rotateTankQuickly(float time){
		mineEffectCD -= time;
		Ogre::Radian degrees = Ogre::Radian(-time * 7);
		Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);

		mainNode->setOrientation (headNode->getOrientation() * tmp);
	}


	bool Tank::ifEquipmentTaken(){
		return equipmentTaken;
	}

	


	float Tank::getLife(){
		return life;
	}


	void Tank::setMoveCD(float newCD){
		moveCD = newCD;
	}

	int Tank::getRank(){
		return rank;
	}

	TANK_TYPE Tank::getType(){
		return type;
	}


	void Tank::setLife(float newLife){
		life = newLife;
	}

	void Tank::setBlock(float delta){
		if (mForward){
			mMovingLock = 'f';
			moveBackward(delta);
		}
		else if (mBackward){
			mMovingLock = 'b';
			moveForward(delta);
		}
		else if (mLeft){
			mMovingLock = 'l';
			turnRight(delta);
		}
		else if (mRight){
			mMovingLock = 'r';
			turnLeft(delta);
		}
	}

	char Tank::getMovingLock(){
		return mMovingLock;
	}

	void Tank::setMovingStatus(char d){
		mForward = false;
		mBackward = false;
		mLeft = false;
		mRight = false;
		if (d == 'f'){
			mForward = true;
		}
		else if (d == 'b'){
			mBackward = true;
		}
		else if (d == 'l'){
			mLeft = true;
		}
		else if (d == 'r'){
			mRight = true;
		}
	}

	void Tank::freeBlock(){
		mMovingLock = 'z';
	}

	

	Tank* Tank::getObject(){
		return this;
	}

	void Tank::fire(float timeSinceLastFrame){
		if(type == TANK_B){
			fireScattering(timeSinceLastFrame);
			return;
		}

		if(fireCD <= 0){
			Ogre::Quaternion q = barrelNode->_getDerivedOrientation();
			ori = QuaternionToVector(q);
			pos = mainNode->getPosition();
			pos.y = 25;
			pos = pos + 15 * ori;

			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_GENERAL);
			fireCD = 1.0f;

		}
	}

	



	void Tank::addtionalGunFire(float timeSinceLastFrame){
		if(addtionalEquipmentCD <= 0 && addtionalEquipmentAmount > 0){
			addtionalEquipmentAmount--;
			Ogre::Quaternion q = barrelNode->_getDerivedOrientation();
			ori = QuaternionToVector(q);
			pos = mainNode->getPosition();
			pos.y = 25;
			pos = pos + 15 * ori;

			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_ROCKET);
			addtionalEquipmentCD = 0.2f;

		}
	}

	void Tank::fireScattering(float timeSinceLastFrame){

		if(fireCD <= 0){
			Ogre::Quaternion q = barrelNode->_getDerivedOrientation();
			ori = QuaternionToVector(q);
			pos = mainNode->getPosition();
			pos.y = 50;
			pos = pos + 15 * ori;
			
			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_GENERAL);
			ori.x = -ori.x;
			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_GENERAL);
			ori.z = -ori.z;
			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_GENERAL);
			ori.x = -ori.x;
			bulletFactory->generateBullet(ID, damage, pos, Ogre::Matrix3::IDENTITY, 25 * ori, this, 5, BULLET_GENERAL);


			fireCD = 1.0f;

		}
	}


	void Tank::moveForward(float timeSinceLastFrame){
		if (mMovingLock!='f'){
			Ogre::Quaternion q = mainNode->getOrientation();
			mainNode->translate(QuaternionToVector(q) * movingSpeed *timeSinceLastFrame);
		}
	}

	void Tank::moveBackward(float timeSinceLastFrame){
		if (mMovingLock!='b'){
			Ogre::Quaternion q = mainNode->getOrientation();
			mainNode->translate(-QuaternionToVector(q) * movingSpeed * timeSinceLastFrame);
		}
	}

	void Tank::turnLeft(float timeSinceLastFrame){
		//rotate along y axis
		if (mMovingLock!='l'){
			Ogre::Radian degrees = Ogre::Radian(-timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);

	
	
			mainNode->setOrientation(mainNode->getOrientation() * tmp);
		}
	}

	void Tank::turnRight(float timeSinceLastFrame){
		if (mMovingLock!='r'){
			Ogre::Radian degrees = Ogre::Radian(timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);
	
			mainNode->setOrientation(mainNode->getOrientation() * tmp);
		}
	}


	void Tank::lookUp(float timeSinceLastFrame){
		float tmp_ori_x = barrelNode->getOrientation().x;
		if(tmp_ori_x > -0.30){
			barrelNode->pitch(-Ogre::Radian(timeSinceLastFrame));
		}
		
	}
	void Tank::lookDown(float timeSinceLastFrame){
		float tmp_ori_x = barrelNode->getOrientation().x;
		if(tmp_ori_x < 0.00){
			barrelNode->pitch(Ogre::Radian(timeSinceLastFrame));
		}
	}

	void Tank::lookLeft(float timeSinceLastFrame){
		float tmp_ori_y = headNode->getOrientation().y;
		if(tmp_ori_y < 0.40){
			Ogre::Radian degrees = Ogre::Radian(-timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
																 0,1,0,
											Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
														);

	
	
			headNode->setOrientation (headNode->getOrientation() * tmp);
		}
	}

	void Tank::lookRight(float timeSinceLastFrame){
		float tmp_ori_y = headNode->getOrientation().y;
		if(tmp_ori_y > -0.40){
			Ogre::Radian degrees = Ogre::Radian(timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
																 0,1,0,
											Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
														);
	
			headNode->setOrientation (headNode->getOrientation() * tmp);
		}
	}


	void Tank::addLife(float addtionalLife){
		life = life + addtionalLife;
		if(life > 300){  //max 
			life = 300;
		}
	}

	void Tank::update(float time){
		if(life <= 0) alive = false;

		if(alive){
			if(fireCD > 0){						//for all
				fireCD -= time;
			}

			if(type == TANK_PLAYER){			//for player
				if(equipmentTaken){                   //weapon
					if(addtionalEquipmentAmount <= 0) {
						equipmentNode->detachObject(equipmentEntity);
						equipmentTaken = false;
					}
					else // amount > 0
						addtionalEquipmentCD -= time;
				}

				if(stepOnMine){						 //step on mine
					rotateTankQuickly(time);
					if(mineEffectCD <= 0) stepOnMine = false;
				}
			}

			if(type != TANK_PLAYER){				//for AI
				sillyAI(time);
			}

			
		}else{
			updateExplode(time);
		}

	}

	void Tank::switchMode()
	{
		if(mode == TANK_DEFENCE){
			attackMode();
			mode = TANK_ATTACK;
		}else if(mode == TANK_ATTACK){
			defenceMode();
			mode = TANK_DEFENCE;
		}
	
	}

	void Tank::attackMode(){
		damage = damage * 2;
		defence = defence / 2;
		movingSpeed *= 2;
	}

	void Tank::defenceMode(){
		damage = damage / 2;
		defence = defence * 2;
		movingSpeed /= 2;
	}



	void Tank::sillyAI(float time){
		moveCD -= time;

		if(moveCD <= 0){
			resetAction();
			int r = rand()%6;
			if(type != TANK_B){ //TANK_A && C
				if(r == 1){
					mFire = true;
					moveCD = 1.0f;
				}else if(r == 2){
					mForward = true;
					moveCD = 3.0f;
				}else if(r == 3){
					mBackward = true;
					moveCD = 3.0f;
				}else if(r == 4){
					mLeft = true;
					moveCD = 2.0f;
				}else if(r == 5){
					mRight = true;
					moveCD = 2.0f;
				}
			
			}else{//boss  TANK_B
				if(r ==1 || r == 2 || r == 3){
					mFire = true;
					moveCD = 1.0f;
				}else if(r == 4){
					mLeft = true;
					moveCD = 2.0f;
				}else if(r == 5){
					mRight = true;
					moveCD = 2.0f;
				}
			
			}
		}

		if(mForward){
				moveForward(time);
		}else if(mBackward){
				moveBackward(time);
		}else if(mLeft){
				turnLeft(time);
		}else if(mRight){
				turnRight(time);
		}else if(mFire){
				fire(time);
		}
	}

	void Tank::resetAction(){
		mFire = false;
		mForward = false;
		mBackward = false;
		mLeft = false;
		mRight = false;
		permit = true;
	}

	void Tank::setupUniqueVariable(){
		damage = 60;
		defence = 20;
		movingSpeed = 20;
	}

	float Tank::getDamage(){
		return damage;
	}
	void Tank::setDamage(float newValue){
		damage = newValue;
	}
	float Tank::getDefence(){
		return defence;
	}
	void Tank::setDefence(float newValue){
		defence = newValue;
	}
	float Tank::getMovingSpeed(){
		return movingSpeed;
	}
	void Tank::setMovingSpeed(float newValue){
		movingSpeed = newValue;
	}

	void Tank::levelUp(){
		damage += 10;
		defence += 10;
		movingSpeed += 10;
		level++;
	}

	void Tank::destroy(){
		BaseObject::destroy();
		mSceneManager->destroyEntity(IDString + "headEntity");
		mSceneManager->destroySceneNode(IDString + "headNode");
		mSceneManager->destroyEntity(IDString + "barrelEntity");
		mSceneManager->destroySceneNode(IDString + "barrelNode");

		if(equipmentTaken){
			mSceneManager->destroyEntity(IDString + "equipmentEntity");
			mSceneManager->destroySceneNode(IDString + "equipmentNode");
		}
	}

}