#ifndef TANKWARLISTENERS_H
#define TANKWARLISTENERS_H

#include "OgreFrameListener.h"
#include <CEGUI.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>


namespace TankWar
{
	

	class InputHandler;
	class AIManager;
	class TankWarWorld;
	class TankWarCamera;
	class BulletFactory;
	class TankFactory;
	class CollisionManager;
	class GUIManager;
	class ItemFactory;
	class TreeFactory;

	class TankWarFrameListener : public Ogre::FrameListener
	{
	public:
		TankWarFrameListener(InputHandler *inputHandler, AIManager *aiManager, TankWarWorld *world, TankWarCamera *tankWarCam, Ogre::RenderWindow* windows, TankFactory* tankFactory, BulletFactory* bulletFactory, ItemFactory *itemFactory, TreeFactory* treeFactory, CollisionManager* mCollisionManager, GUIManager* guiManager);

		virtual bool frameStarted(const Ogre::FrameEvent &evt);
		

	protected:
		InputHandler *mInputHandler;
		AIManager *mAIManager;
		TankWarWorld *mWorld;
		TankWarCamera *mTankWarCamera;
		Ogre::RenderWindow* mWindows;
		BulletFactory* bulletFactory;
		TankFactory* tankFactory;
		ItemFactory *itemFactory;
		CollisionManager* mCollisionManager;
		GUIManager* guiManager;
		TreeFactory* treeFactory;
	};

}

#endif