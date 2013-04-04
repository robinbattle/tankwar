#ifndef WORLD_H
#define WORLD_H

#include "OgreVector3.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
class TankWarSceneManager;
class TankFactory;
class BulletFactory;
class ItemFactory;
class TreeFactory;
class Tank;

class TankWarWorld
{
	public:
	
		TankWarWorld(Ogre::SceneManager *sceneManager, Ogre::RenderWindow* mWindow, TankWarSceneManager* sceneTemple, TankFactory* tankFactory, BulletFactory* bulletFactory, ItemFactory* itemFactory, TreeFactory* treeFactory);

	
        typedef std::list<Ogre::Entity*>::iterator GeometryIterator;
		std::list<Ogre::Entity*> geometryList;	

		

		bool load;

		void Think(float time);
    
		void SetupDefaultGame();
		void loadScene();

		void addBonusItems(float time); /* add some items*/
		void addNewTanks(float time); /* add some tanks if tanks are too less*/

		void worldEditor(); /* not yet implements*/

		void clearGeometryList();
		void clearAll();

		void DoSometing();


		void createTanks();
		void createTrees(float time);

		void showShadows();

		
		// You are going to want to keep track of your entities, in some kind 
		//  of list, map, table, set, or combination of lists, maps tables & sets.

		// For our example, we will just have a single instance variable.  You should
		//  Replace this with something else!
	protected:
		Ogre::SceneManager *mSceneManager; 
		Ogre::RenderWindow* mWindow;
    
		TankWarSceneManager* mSceneTemple;
		TankFactory* tankFactory;
		BulletFactory* bulletFactory;
		ItemFactory* itemFactory;
		TreeFactory* treeFactory;

		bool worldExist;

	private:
		void createPlanes();
		void createLights();


	};

}


#endif