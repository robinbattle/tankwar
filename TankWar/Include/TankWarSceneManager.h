#ifndef TANKWARSCENEMANAGER_H
#define TANKWARSCENEMANAGER_H

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	class TankWarSceneManager 

	{
	public:
	
		TankWarSceneManager(Ogre::SceneManager *mSceneManager, Ogre::RenderWindow* mWindow);
		//~TankWarSceneManager(void);

    
		Ogre::TerrainGlobalOptions* mTerrainGlobals;
		Ogre::TerrainGroup* mTerrainGroup;
		bool mTerrainsImported;
		void generate();
		void defineTerrain(long x, long y);
		void initBlendMaps(Ogre::Terrain* terrain);
		void configureTerrainDefaults(Ogre::Light* light);

		Ogre::SceneManager *mSceneManager;
		Ogre::RenderWindow* mWindow;
  

	};
}


#endif
