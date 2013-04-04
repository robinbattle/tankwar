#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "Factory\TankFactory.h"

namespace Ogre {
    class RenderWindow;
}

namespace OIS {
    class Keyboard;
	class Mouse;
    class InputManager;
}


namespace TankWar
{
	class TankWarWorld;
	class TankWarCamera;
	class InputHandler {
	public:

		InputHandler(Ogre::RenderWindow* win, TankWarWorld *w, TankWarCamera *c, TankFactory* tankFactory);
		bool Think(float time);
	

		OIS::Keyboard *mKeyboard;
		OIS::Mouse *mMouse;

		bool godMode;

		bool pause;

	protected:

		TankWarWorld *mWorld;
		TankWarCamera *mTankWarCamera;
		Ogre::RenderWindow *mRenderWindow;

		OIS::InputManager* mInputManager;
		TankFactory* tankFactory;
		
		void bufferVariableController(float time);
		void playerTankController(float time);
		void cameraController(float time);
	

	
		bool mSpaceDown;
		bool mZeroDown;
		bool mPDown;
		bool jUpLastFrame;
		bool mHDown;


	};

}

#endif