#ifndef AIMANAGER_H
#define AIMANAGER_H

namespace TankWar
{
	class TankWarWorld;

	class AIManager 
	{

	public:
		// You may want to add parameters to the AI Manager constructor
		AIManager(TankWarWorld *world);
		~AIManager();

		// Go through all of the AIs, and call think on each one
		void Think(float time);

	protected:
		TankWarWorld *mWorld;
		// Probablay want a list of individual AI classes here ...
	};
}

#endif