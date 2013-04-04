#ifndef TANKWARCAMERA_H
#define TANKWARCAMERA_H

#include "Factory\TankFactory.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>

namespace Ogre
{
    class Camera;
    class Vector3;
	class SceneManager;
}

namespace TankWar
{
	class TankWarWorld;


	class TankWarCamera
	{



	public:
		TankWarCamera(Ogre::Camera *renderCamera, TankWarWorld *world, Ogre::SceneManager *mSceneManager, TankFactory* tankFactory); 
		void Think(float time);
		// If you have a different cameras, you'll want some acessor methods here.
		//  If your camera always stays still, you could remove this class entirely
		OgreBites::SdkCameraMan* mCameraMan;

		void thirdPersonView();
		void firstPersonView();
		void godView();


	protected:

		bool firstPerson;
		bool thirdPerson;
		bool godMode;

		void resetMode();

		Ogre::Camera *mRenderCamera;
		TankWarWorld *mWorld;
		Ogre::SceneManager *mSceneManager;
		Ogre::SceneNode *camera1;
		Ogre::SceneNode *camera2;
		Ogre::SceneNode *camera3;
		Ogre::Vector3 Matrix2Vector(Ogre::Quaternion q);
		TankFactory* tankFactory;
	
	};
}

#endif