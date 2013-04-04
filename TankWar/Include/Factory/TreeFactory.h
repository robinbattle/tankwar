
#ifndef TREEFACTORY_H
#define TREEFACTORY_H


#include "Ogre.h"
#include "Object/Tree.h"


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{


	class CollisionManager;


	class TreeFactory
	{
		 /*plz see the explanation of TankFactory, not much different, lazy here*/

	public: TreeFactory(Ogre::SceneManager *sceneManager);   
			
			Tree* generateTree(Ogre::Vector3 position, Ogre::Matrix3 orientation);
			/*generate bullets based on input */
			//update
			void update(float time); /* update all bullets in bulletlist by every time frame*/

			
			//define type
			typedef std::list<Tree*>::iterator TreeIterator;
			std::list<Tree*> treeList;	

			//void clearAll();												/*clear all bullets in list*/

			

	protected:
		
			int IDCounter;
			Ogre::SceneManager* mSceneManager;
			Tree *newTree;

	private:
			std::string convertInt(int n);
			void destroyTree(Tree* tree);
			
	};


}

#endif