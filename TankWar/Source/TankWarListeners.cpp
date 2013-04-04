#include "TankWarListeners.h"
#include "AIManager.h"
#include "InputHandler.h"
#include "World.h"
#include "TankWarCamera.h"
#include <stdio.h>
#include "Factory\TankFactory.h"
#include "Factory\BulletFactory.h"
#include "Factory\ItemFactory.h"
#include "Factory\TreeFactory.h"
#include "CollisionManagement\CollisionManager.h"
#include "GUIManager.h"


namespace TankWar
{
	


	TankWarFrameListener::TankWarFrameListener(InputHandler *inputHandler, AIManager *aiManager, TankWarWorld *world, TankWarCamera *cam, Ogre::RenderWindow* windows, TankFactory* tankFactory, BulletFactory* bulletFactory, ItemFactory *itemFactory, TreeFactory* treeFactory, CollisionManager* mCollisionManager, GUIManager* guiManager) :
		mInputHandler(inputHandler), mAIManager(aiManager), mWorld(world), mTankWarCamera(cam),mWindows(windows),tankFactory(tankFactory), bulletFactory(bulletFactory),itemFactory(itemFactory), mCollisionManager(mCollisionManager), guiManager(guiManager), treeFactory(treeFactory)
	{
		
	
	}       

	// On every frame, call the appropriate managers
	bool 
	TankWarFrameListener::frameStarted(const Ogre::FrameEvent &evt)
	{
	
	
		
		
		if(!guiManager->ifPause()){
		
			mAIManager->Think(evt.timeSinceLastFrame);
			mInputHandler->Think(evt.timeSinceLastFrame);
			mWorld->Think(evt.timeSinceLastFrame);
			mTankWarCamera->Think(evt.timeSinceLastFrame);
	

			tankFactory->update(evt.timeSinceLastFrame); 
			bulletFactory->update(evt.timeSinceLastFrame);
			itemFactory->update(evt.timeSinceLastFrame);
			treeFactory->update(evt.timeSinceLastFrame);
			mCollisionManager->update(evt.timeSinceLastFrame);
			
		
		}
		bool keepGoing = guiManager->frameRenderingQueued(evt);

		return keepGoing;
	}

	
 
}