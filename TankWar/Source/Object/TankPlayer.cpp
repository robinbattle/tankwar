#include "Object\TankPlayer.h"


namespace TankWar
{
	
	void TankPlayer::setupUniqueVariable(){
		damage = 80;
		defence = 30;
		movingSpeed = 120;
	    mode = TANK_ATTACK;
		level = 1;
	}
	
}