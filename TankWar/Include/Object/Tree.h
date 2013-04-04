#ifndef TREE_H
#define TREE_H

#include "Ogre.h"
#include "Object\BaseObject.h"


namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{
	
	const static std::string TREE_MESH_NAME = "tree.mesh";
	
	class Tree:public BaseObject
	{
	public: Tree(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *mSceneManager):
				BaseObject(ID,position, orientation, mSceneManager, TREE_MESH_NAME)
			{
				setupObjectUnit();
				placeObject();/*override*/
				setupVariables();/*override*/
				mainNode->scale(40, 40, 40);
				entity->getMesh()->setAutoBuildEdgeLists(false);
			
			}
		
			void update(float time);

			//void destroy();

	protected:

			Ogre::ParticleSystem		*mParticle;					
			Ogre::ParticleSystem		*mExplosionParticle;		
			Ogre::SceneNode			*mParticleNode;
			Ogre::SceneNode			*mExplosionParticleNode;


	private: /*some private funcs*/
		    
	};
}

#endif