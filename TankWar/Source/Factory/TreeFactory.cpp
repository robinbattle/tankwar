#include "Factory/TreeFactory.h"
#include "Ogre.h"
#include "CollisionManagement/CollisionManager.h"



namespace TankWar
{
	

	TreeFactory::TreeFactory(Ogre::SceneManager *sceneManager):mSceneManager(sceneManager)
	//BulletFactory::BulletFactory(Ogre::SceneManager *sceneManager, CollisionManager* mCollisionManager):mSceneManager(sceneManager), mCollisionManager(mCollisionManager)

	{
		IDCounter = 1000000;
	}



	Tree* TreeFactory::generateTree(Ogre::Vector3 position, Ogre::Matrix3 orientation){
		


		newTree = new Tree(IDCounter,position, orientation, mSceneManager);

		
		//add to bulletlist
		treeList.push_back(newTree);

		//increment ID No.
		IDCounter++;
		
		return newTree;
	}

	

	std::string TreeFactory::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	void TreeFactory::update(float time){

		for (TreeIterator t = treeList.begin(); t != treeList.end();  ){
				Tree *tree = *t;
				tree->update(time);

				if (!tree->isAlive())
				{	
						//delete
						destroyTree(tree);
						Tree* tmp = tree;
						t++;
						treeList.remove(tmp);
						
				
				}
				else
				{
					t++;
				}
			
		}


	}

	void TreeFactory::destroyTree(Tree* tree){
		tree->destroy();
	}


	

}