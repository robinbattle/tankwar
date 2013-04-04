#include "GUIManager.h"
#include "World.h"



namespace TankWar
{
	OverlayManager *olmGUI;
	OverlayContainer *panelGUI ;
	Overlay *overlayGUI;
	TextAreaOverlayElement *textAreaGUI;
	String szElementGUI;
	OverlayContainer *panelGUI2 ;
	Overlay *overlayGUI2;
	TextAreaOverlayElement *textAreaGUI2;
			
	OverlayContainer *attackMode;
	OverlayContainer *defenceMode;
	OverlayContainer *tankExp;

	float previouslife;
	char cc[70];

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
	{
		switch (buttonID)
		{
		case OIS::MB_Left:
			return CEGUI::LeftButton;
 
		case OIS::MB_Right:
			return CEGUI::RightButton;
 
		case OIS::MB_Middle:
			return CEGUI::MiddleButton;
 
		default:
			return CEGUI::LeftButton;
		}
	}


	//-------------------------------------------------------------------------------------
	GUIManager::GUIManager(Ogre::Root *root, TankWarWorld *world, Ogre::RenderWindow *window, Ogre::SceneManager *sceneMgr, InputHandler* inputHandler, TankFactory* tankFactory, CollisionManager *mCollisionManager):
		mRoot(root), mWorld(world), mWindow(window), mSceneMgr(sceneMgr), mInputHandler(inputHandler), tankFactory(tankFactory), mCollisionManager(mCollisionManager)
	{
		setupVariables();
		initGUI();
		setupMenuGUI();

		miniMap();
		
	}

	void GUIManager::initGUI(){ 
		mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
		CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
		CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

		setupMenuBackGround();

		/*healthy bar  temporary*/                                                    //healthy bar
		olmGUI=OverlayManager::getSingletonPtr();
		overlayGUI2=olmGUI->create("GUIOverlay2");
		panelGUI2=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Health Bar"));
		panelGUI2->setMetricsMode(Ogre::GMM_RELATIVE);
		panelGUI2->setPosition(0.05,0.05);
		panelGUI2->setDimensions(0.15, 0.02);           
		panelGUI2->setMaterialName("healthy_bar");       
		overlayGUI2->add2D(panelGUI2);                  
		
		attackMode=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","PlayerTank Attack Mode"));
		attackMode->setMetricsMode(Ogre::GMM_RELATIVE);
		attackMode->setPosition(0.05,0.15);
		attackMode->setDimensions(0.08, 0.08);
		attackMode->setMaterialName("attackMode");       
		overlayGUI2->add2D(attackMode);

		defenceMode=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","PlayerTank Defence Mode"));
		defenceMode->setMetricsMode(Ogre::GMM_RELATIVE);
		defenceMode->setPosition(0.15,0.15);
		defenceMode->setDimensions(0.04, 0.04);
		defenceMode->setMaterialName("defenceMode");       
		overlayGUI2->add2D(defenceMode);

		tankExp=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","PlayerTank Exp"));
		tankExp->setMetricsMode(Ogre::GMM_RELATIVE);
		tankExp->setPosition(0.05,0.10);
		tankExp->setDimensions(0.005, 0.02);
		tankExp->setMaterialName("exp_bar");       
		


		level = 1; range = 2;
		textAreaGUI2=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tank Level"));
		textAreaGUI2->setFontName("StarWars");  	      
		textAreaGUI2->setMetricsMode(Ogre::GMM_PIXELS); 
		textAreaGUI2->setPosition(0.30, 0.10);
		textAreaGUI2->setCharHeight(15);	 
		textAreaGUI2->show();
		tankExp->addChild(textAreaGUI2);
		
		//sprintf(cc,  "Level %, damage: %d, defence: %d", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
		//textAreaGUI2->setCaption(cc);
		overlayGUI2->add2D(tankExp);
	}

	void GUIManager::setupMenuBackGround(){
		olmGUI=OverlayManager::getSingletonPtr();
		overlayGUI=olmGUI->create("GUIOverlay");  // We can call this anything we like, 
		// Next, we create a panel within this overlay:
		panelGUI=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","TextPanelGUI"));
		panelGUI->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		//panelGUI->setPosition(.,.2);                // Panel starts at 20$ to the right, and 20% down from the top

		panelGUI->setDimensions(1.0, 1.0);           // Panel is half the width and half the height of the screen
		panelGUI->setMaterialName("background");       // Give the panel a background material.
		overlayGUI->add2D(panelGUI);                   // Add our panel to the overlay

		// Show the overlay
		overlayGUI->show();
		
	
	}

	void GUIManager::setupVariables(){
		mShutDown = false;
		pause = true;	
		ifNewGame = false;
		ifLoadedClassic = false;
		ifstart = false;
	}

	void GUIManager::setupMenuGUI(){

		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		sheet = wmgr.createWindow("DefaultWindow", "TankWarMenu");

		/* new game button  */
		new_game = wmgr.createWindow("TaharezLook/Button", "newgame");
		new_game->setText("New Game");
		new_game->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		new_game->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		sheet->addChildWindow(new_game);
		new_game->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::newGame, this));

		/* load classic button  */
		load_classic = wmgr.createWindow("TaharezLook/Button", "load");
		load_classic->setText("Load Classic");
		load_classic->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		load_classic->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.4f, 0)));
		sheet->addChildWindow(load_classic);
		load_classic->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::loadClassic, this));

		/* battle editor button  */
		battle_editor = wmgr.createWindow("TaharezLook/Button", "editor");
		battle_editor->setText("Battle Editor");
		battle_editor->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		battle_editor->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.6f, 0)));
		sheet->addChildWindow(battle_editor);
		battle_editor->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::battleEditor, this));
	
		/* quit game button  */
		quit = wmgr.createWindow("TaharezLook/Button", "quit");
		quit->setText("Quit");
		quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.8f, 0)));
		sheet->addChildWindow(quit);
		quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::quitGame, this));

		
		
		CEGUI::System::getSingleton().setGUISheet(sheet);
		
	}

	void GUIManager::miniMap(){
		Ogre::TexturePtr tex = mRoot->getTextureManager()->createManual(
			"RTT",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D,
			512,
			512,
			0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

		Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();
		cam = mSceneMgr->createCamera("RearCam");
		//Vector3 fool = Ogre::Vector3(1550,0,1250);
		cam->setPosition(1250, 300, 1000);
		//cam->lookAt(0,0,0);
		
		Ogre::Viewport *v = rtex->addViewport(cam);
		v->setOverlaysEnabled(false);
		v->setClearEveryFrame(true);
		v->setBackgroundColour(Ogre::ColourValue::Black);
		CEGUI::Texture &guiTex = mRenderer->createTexture(tex);
		CEGUI::Imageset &imageSet =
		CEGUI::ImagesetManager::getSingleton().create("RTTImageset", guiTex);
	imageSet.defineImage("RTTImage",
						 CEGUI::Point(0.0f, 0.0f),
						 CEGUI::Size(guiTex.getSize().d_width,
									 guiTex.getSize().d_height),
						 CEGUI::Point(0.0f, 0.0f));

		mini_map = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "RTTWindow");
		mini_map->setSize(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		mini_map->setPosition(CEGUI::UVector2(CEGUI::UDim(0.69f, 0),CEGUI::UDim(0.0f, 0)));
		mini_map->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
		sheet->addChildWindow(mini_map);
		mini_map->setVisible(false);
	
	}


	//-------------------------------------------------------------------------------------
	
	bool
	GUIManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
	{
			mInputHandler->mKeyboard->capture();	
			mInputHandler->mMouse->capture();
			mInputHandler->mMouse->setEventCallback(this);
			mInputHandler->mKeyboard->setEventCallback(this);


			if(!pause){
				if(previouslife != tankFactory->playerTank->getLife()){
					//mSceneMgr->getCamera("RearCam")->lookAt(tankFactory->playerTank->getSceneNode()->getPosition());
					panelGUI2->setDimensions(tankFactory->playerTank->getLife()/100 * 0.15, 0.02);
					previouslife = tankFactory->playerTank->getLife();
				}
				
				tankExp->setDimensions(mCollisionManager->playerScore * 0.3 / range,0.02);
				if(mCollisionManager->playerScore >= range){

					tankFactory->playerTank->levelUp();
					mCollisionManager->playerScore = 0;
					level++;
					range++;
					sprintf(cc,  "Level %d, damage: %5.1f, defence: %5.1f", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
					textAreaGUI2->setCaption(cc);
				}

				sprintf(cc,  "Level %d, damage: %5.1f, defence: %5.1f", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
				textAreaGUI2->setCaption(cc);	 

				if(ifstart && tankFactory->playerTank != NULL){
				//Ogre::Vector3 p = ;
					cam->lookAt(tankFactory->playerTank->getSceneNode()->getPosition());//look at player
				}

			
			}
			//if(mInputHandler->godMode){
				//mTankWarCamera->mCameraMan->frameRenderingQueued(evt);
			//}

			if(mShutDown)return false;
			if(mWindow->isClosed())return false;

			return true;
	}

	bool
	GUIManager::keyPressed(const OIS::KeyEvent& evt){	
		//if(godMode == true){
		//	mTankWarCamera->mCameraMan->injectKeyDown(evt);
		//}

		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectKeyDown(evt.key);
		sys.injectChar(evt.text);



		if(evt.key == OIS::KC_ESCAPE){
			if(!pause)
				showMenu(); //true now
			else{
				if(ifstart)
					hideMenu(); //false now
			}
				
		}

		//switch mode
		if(evt.key == (OIS::KC_H)){
			if(tankFactory->playerTank->mode == TANK_ATTACK){
				tankFactory->playerTank->switchMode();
				attackMode->setDimensions(0.04, 0.04);
				defenceMode->setDimensions(0.08, 0.08);
				
			}else{
				tankFactory->playerTank->switchMode();
				attackMode->setDimensions(0.08, 0.08);
				defenceMode->setDimensions(0.04, 0.04);
			}

					
		}
		
		return true;
	}

	bool GUIManager::ifPause(){
		return pause;
	}
	

	void GUIManager::showMenu(){
		overlayGUI->show();
		pause = true;
		new_game->setVisible(true);
		load_classic->setVisible(true);
		battle_editor->setVisible(true);
		quit->setVisible(true);

		mini_map->setVisible(false);
		overlayGUI2->hide();
	}
	void GUIManager::hideMenu(){
		overlayGUI->hide();
		pause = false;
		new_game->setVisible(false);
		load_classic->setVisible(false);
		battle_editor->setVisible(false);
		quit->setVisible(false);

		mini_map->setVisible(true);
		overlayGUI2->show();
	}


	bool
	GUIManager::keyReleased(const OIS::KeyEvent& evt){ 
		//if(this->godMode == true){
			//mTankWarCamera->mCameraMan->injectKeyUp(evt);
		//}

		CEGUI::System::getSingleton().injectKeyUp(evt.key);

		return true;
	}


	bool 
	GUIManager::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{
		/* normal mouse processing here... */
		//if(mInputHandler->godMode == true){
		//	mTankWarCamera->mCameraMan->injectMouseDown(evt, id);
		//}

		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));

		return true;
	}
 
	bool 
	GUIManager::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{
		/* normal mouse processing here... */
		//if(mInputHandler->godMode == true){
		//	mTankWarCamera->mCameraMan->injectMouseUp(evt, id);
		//}

		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));

		return true;
	}
 
	bool 
	GUIManager::mouseMoved(const OIS::MouseEvent& evt)
	{
		/* normal mouse processing here... */
		//if(mInputHandler->godMode == true){
		//	mTankWarCamera->mCameraMan->injectMouseMove(evt);
		//}


		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
		// Scroll wheel.
		if (evt.state.Z.rel)
			sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);

		return true;
	}
	
	//-------------------------------------------------------------------------------------


	bool GUIManager::newGame(const CEGUI::EventArgs &e)
	{
		hideMenu();
		ifstart = true;
		
		if(!ifNewGame){
			mWorld->SetupDefaultGame();
			ifNewGame = true;
		}else{
			mWorld->clearAll();
			mWorld->createTanks();
			range = 2;
			level = 1;
			mCollisionManager->playerScore = 0;
		}
		
		return true;
	}

	bool GUIManager::loadClassic(const CEGUI::EventArgs &e)
	{	
		if(ifstart){
			hideMenu();
			ifstart = true;
			if(!ifLoadedClassic){
				mWorld->loadScene();
				ifLoadedClassic = true;
				mWorld->showShadows();
			}else{
				load_classic->setText("Already loaded");
			}
			
		}
		
		return true;
	}


	bool GUIManager::battleEditor(const CEGUI::EventArgs &e)
	{
		//hideMenu();
		battle_editor->setText("Not finished");
		return true;
	}

	bool GUIManager::quitGame(const CEGUI::EventArgs &e)
	{	
		mShutDown = true;
		return true;
	}

}



