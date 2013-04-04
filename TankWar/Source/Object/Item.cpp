#include "Object/Item.h"
#include "Ogre.h"
//#include "Factory/BulletFactory.h"


namespace TankWar
{

	void Item::update(float time){   //rotate along y axis
		Ogre::Radian degrees = Ogre::Radian(time);
		Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);
	
		mainNode->setOrientation (mainNode->getOrientation() * tmp);

	}

	ITEM_TYPE Item::getType(){
		return type;
	}
	
	void Item::setupVariables(){
		alive = true;
		//if(type == ITEM_MACHINE_GUN){
		//	amount = 50;
			//CD = 0.2;
		//}
	}

}