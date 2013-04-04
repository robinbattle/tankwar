#include "Object/Bullet.h"
#include "Object/Tank.h"
#include "Ogre.h"


namespace TankWar
{   /*
	Bullet::Bullet(int ID, int launcherID, float lifeTime, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::Vector3 direction, Ogre::SceneManager *mSceneManager, Tank* launcher, BULLET_TYPE type, std::string meshName):ID(ID),lifeTime(lifeTime),launcherID(launcherID),
		position(position), orientation(orientation), launcher(launcher), mSceneManager(mSceneManager), type(type), direction(direction), meshName(meshName)
	{	
		

		setupObjectUnit();
		placeObject();
	}
	*/

	Bullet::~Bullet(){
	
	}
	


	void Bullet::setupVariables(){
		speed = 9.0f;
		/*
		if(type == BULLET_GENERAL)
			damage = 60.0f;
		else if(type == BULLET_PIERCING)
			damage = 100.0f;
		else if(type == BULLET_MISSILE)
			damage = 60.0f;
		else if(type == BULLET_ROCKET)
			damage = 20.0f;

		rank = launcher->getRank();
		alive = true;
		*/

	}
	void Bullet::placeObject(){
		mainNode->setPosition(position);
		//mainNode->setOrientation(orientation);
		mainNode->scale(2,2,2);

		//tail = mSceneManager->createEntity(IDString + "tail", "MyCube.mesh");
		//tailNode = mainNode->createChildSceneNode();
		//tailNode->attachObject(tail);
		//tailNode->translate(0,20,0);

	}


	float Bullet::getLifeTime(){
		return lifeTime;
	}
	float Bullet::getDamage(){
		return damage;
	}


	int Bullet::getRank(){
		return rank;
	}

	int Bullet::getLauncherID(){
		return launcherID;
	}

	BULLET_TYPE Bullet::getBulletType(){
		return type;
	}

	

	Bullet* Bullet::getBulletObject(){
		return this;
	}

	Tank* Bullet::getLauncher(){
		return launcher;
	}



	void Bullet::update(float time){
		//consume life
		lifeTime -= time;

		//translate
		direction.y -= 9.8*time;
		mainNode->translate(direction* speed * time);
		//position = position + direction * time;
		//mainNode->setPosition(position);

		//mainNode->translate(Ogre::Vector3(0,0,0.1));

		if(lifeTime <= 0) alive = false;

		//position = mainNode->getPosition();

		//textArea1->setCaption(c);
	}



}