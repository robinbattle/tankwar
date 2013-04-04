#include "OgreCamera.h"
#include "TankWarCamera.h"
#include "World.h"
#include "Constants.h"
#include "Ogre.h"
#include "Object\Tank.h"
using namespace Ogre;


namespace TankWar
{
	TankWarCamera::TankWarCamera(Ogre::Camera *renderCamera, TankWarWorld *world, Ogre::SceneManager *mSceneManager, TankFactory* tankFactory) :
	mRenderCamera(renderCamera), mWorld(world),mSceneManager(mSceneManager), tankFactory(tankFactory)
	{
		// Any other initialization that needs to happen
		camera1 = mSceneManager->getRootSceneNode()->createChildSceneNode("Camera1");
		camera2 = mSceneManager->getRootSceneNode()->createChildSceneNode("Camera2");
		camera3 = mSceneManager->getRootSceneNode()->createChildSceneNode("Camera3");
		//camera1->attachObject(mRenderCamera);

		firstPerson = false;
		thirdPerson = true;
		godMode = false;
		mCameraMan = new OgreBites::SdkCameraMan(mRenderCamera);
	}


	void
	TankWarCamera::Think(float time)
	{
		if(tankFactory->playerTank != NULL){
			// Any code needed here to move the camera about per frame
			//  (use mRenderCamera to get the actual render camera, of course!)
			Ogre::SceneNode *mTank = tankFactory->playerTank->getSceneNode();
			Ogre::Vector3 direction = Matrix2Vector(mTank->getOrientation());

			
			/************First person View***************/
			/*
			Ogre::Vector3 v = mWorld->mTank->getPosition()-50 *direction;
			v.y = 50;
			mRenderCamera->setPosition(v);
			mRenderCamera->setOrientation(mWorld->mTank->getOrientation());
			mRenderCamera->lookAt(mWorld->mTank->getPosition() + 200 * direction);

			//camera1->lookAt(mWorld->mTank->getPosition(), Ogre::Node::TransformSpace::TS_WORLD,Matrix2Vector( mWorld->mTank->getOrientation()));
			*/
			/************First person View***************/
	
			if(thirdPerson == true){
				Ogre::Vector3 v = mTank->getPosition()-100 *direction;
				v.y = 100;
				mRenderCamera->setPosition(v);
				mRenderCamera->setOrientation(mTank->getOrientation());
				mRenderCamera->lookAt(mTank->getPosition() + 200 * direction);
			}else if(firstPerson == true){
				Ogre::Vector3 v = mTank->getPosition()+ direction;
				v.y = 50;
				mRenderCamera->setPosition(v);
				mRenderCamera->setOrientation(mTank->getOrientation());
				mRenderCamera->lookAt(mTank->getPosition() + 200 * direction);
			}else if(godMode == true) {
			
			}
		
		
		
		}



	}

	void TankWarCamera::thirdPersonView(){
		resetMode();
		thirdPerson = true;
		mCameraMan->manualStop();
	}
	void TankWarCamera::firstPersonView(){
		resetMode();
		firstPerson = true;
		mCameraMan->manualStop();
	}
	void TankWarCamera::godView(){
		resetMode();
		godMode = true;
		mCameraMan = new OgreBites::SdkCameraMan(mRenderCamera);
	}

	void TankWarCamera::resetMode(){
		firstPerson = false;
		thirdPerson = false;
		godMode = false;
	}


	Ogre::Vector3 TankWarCamera::Matrix2Vector(Ogre::Quaternion q){
		Ogre::Vector3 v = q *Ogre::Vector3::UNIT_Z;
		return v;
	}
}