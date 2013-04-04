#include "InputHandler.h"
#include "World.h"
#include "TankWarCamera.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include <stdio.h>
#include "OgreSceneManager.h"
#include "Object\Tank.h"


namespace TankWar
{
	InputHandler::InputHandler(Ogre::RenderWindow *renderWindow, TankWarWorld *world, TankWarCamera *c, TankFactory* tankFactory) : 
		mWorld(world), mRenderWindow(renderWindow), mTankWarCamera(c), mSpaceDown(false), mZeroDown(false), godMode(false),mPDown(false), pause(false), tankFactory(tankFactory),mHDown(false)
	{
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		renderWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		mInputManager = OIS::InputManager::createInputSystem( pl );

		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true /* buffered */ ));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true /* buffered */ ));

	}

	bool 
	InputHandler::Think(float time)
	{
	
		// Capture input for this frame
		mKeyboard->capture();
		mMouse->capture();

	
		bufferVariableController(time);
		playerTankController(time);
		cameraController(time);


		
		/*  I feel it is not safe for now, maybe reuse later
		else if(mKeyboard->isKeyDown(OIS::KC_R)){
			if(tankFactory->playerTank != NULL){
				mWorld->clearAll();
			}
		}
		*/
		

		// Handling other keys ...

		return true;
	}


	void InputHandler::playerTankController(float time){
		if(tankFactory->playerTank != NULL && tankFactory->playerTank->isAlive()){
				if(mKeyboard->isKeyDown(OIS::KC_SPACE) && mSpaceDown){
					mSpaceDown = false;
					
					if(tankFactory->playerTank->ifEquipmentTaken()){ //machine gun
						tankFactory->playerTank->addtionalGunFire(time);
					}else{											//regular one
						tankFactory->playerTank->fire(time);
					}
				}
				if(mKeyboard->isKeyDown(OIS::KC_A)||mKeyboard->isKeyDown(OIS::KC_LEFT)){    //body
						tankFactory->playerTank->setMovingStatus('l');
						tankFactory->playerTank->turnLeft(time);
				}
				if(mKeyboard->isKeyDown(OIS::KC_S)||mKeyboard->isKeyDown(OIS::KC_DOWN) ){   //body
						tankFactory->playerTank->setMovingStatus('b');
						tankFactory->playerTank->moveBackward(time);
				}
				if(mKeyboard->isKeyDown(OIS::KC_W)||mKeyboard->isKeyDown(OIS::KC_UP)){      //body
						tankFactory->playerTank->setMovingStatus('f');
						tankFactory->playerTank->moveForward(time);
				}
				if(mKeyboard->isKeyDown(OIS::KC_D)||mKeyboard->isKeyDown(OIS::KC_RIGHT)){    //body
						tankFactory->playerTank->setMovingStatus('r');
						tankFactory->playerTank->turnRight(time);
				}


				if(mKeyboard->isKeyDown(OIS::KC_J)){						//tank head
						//tankFactory->playerTank->setMovingStatus('l');
						tankFactory->playerTank->lookLeft(time);
				}
				if(mKeyboard->isKeyDown(OIS::KC_K)){						//barrel
						//tankFactory->playerTank->setMovingStatus('l');    
						tankFactory->playerTank->lookDown(time);
				}	
				if(mKeyboard->isKeyDown(OIS::KC_I)){						//barrel
						//tankFactory->playerTank->setMovingStatus('l');    
						tankFactory->playerTank->lookUp(time);
				}
				if(mKeyboard->isKeyDown(OIS::KC_L)){					    //tank head
						//tankFactory->playerTank->setMovingStatus('l');
						tankFactory->playerTank->lookRight(time);
				}

				

			}
	}
	void InputHandler::bufferVariableController(float time){
			if(mKeyboard->isKeyDown(OIS::KC_SPACE)){
				mSpaceDown = true;
			}
			if(mKeyboard->isKeyDown(OIS::KC_0)){
				mZeroDown = true;
			}
			if(mKeyboard->isKeyDown(OIS::KC_P)){
				mPDown = true;
			}
			if(mKeyboard->isKeyDown(OIS::KC_H)){
				mHDown = true;
			}
	}
	void InputHandler::cameraController(float time){
		if(mKeyboard->isKeyDown(OIS::KC_3) && mZeroDown){
			mZeroDown = false;
			if(godMode){
				godMode = false;
			}else {
				godMode = true;
			}

			mTankWarCamera->godView();

		}else if(mKeyboard->isKeyDown(OIS::KC_1)){
			if(tankFactory->playerTank != NULL){
				mTankWarCamera->thirdPersonView();
			}
		}else if(mKeyboard->isKeyDown(OIS::KC_2)){
			if(tankFactory->playerTank != NULL){
				mTankWarCamera->firstPersonView();
			}
		}
	}

}

