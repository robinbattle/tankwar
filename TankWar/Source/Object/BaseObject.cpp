#include "Object/BaseObject.h"
#include "Ogre.h"



namespace TankWar
{   

	


	BaseObject::BaseObject(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, std::string meshName):
		ID(ID),position(position), orientation(orientation), mSceneManager(sceneManager), meshName(meshName)
	{
		/* object is built up here*/
		//setupVariables();
		//setupObjectUnit();
		//placeObject();

		IDString = convertInt(ID);

		olmCurrent=OverlayManager::getSingletonPtr();

		// First, create an overlay: 
	
		Ogre::String name = IDString + "MyTextDisplayOverlay";
		overlayCurrent=olmCurrent->create(name);  // We can call this anything we like, 
										   //  If we have multiple overlays, the name
										   //  needs to be unique

		// Next, we create a panel within this overlay:
		name = IDString + "TextPanel";
		panelCurrent=static_cast<OverlayContainer*>(olmCurrent->createOverlayElement("Panel",name));
		panelCurrent->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panelCurrent->setPosition(.2,.2);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panelCurrent->setDimensions(0.5,0.5);           // Panel is half the width and half the height of the screen
		// panelCurrent->setMaterialName("Dirt"); // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlayCurrent->add2D(panelCurrent);                   // Add our panel to the overlay

		// Create a TextArea element.  The 1st parameter "TextArea" tells the constructor to create
		//   a TextArea element.  The second paramater "text1" is just a name we give the element
		//   (needs to be unique!) so that we can retreive the element later
		name = IDString + "text1";
		textAreaCurrent=static_cast<TextAreaOverlayElement*>(olmCurrent->createOverlayElement("TextArea",name));

		textAreaCurrent->setFontName("StarWars");  	      // Set the font of the displayed text
		textAreaCurrent->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
													  // screen relative (We don't need to do this, I'm only doing
													  // it to show the difference between screen relative and
		
		textAreaCurrent->setCharHeight(20);	              // Set the height of the text (in pixels)
    
		// Add the text area to the panel
		panelCurrent->addChild(textAreaCurrent);
    
		// Show the overlay
		overlayCurrent->show();

	}

	void BaseObject::setupVariables(){
		alive = true;
	}

	void BaseObject::setupObjectUnit(){

		Ogre::String name = IDString + "mainNode";
		mainNode = mSceneManager->getRootSceneNode()->createChildSceneNode(name); 
		name =  IDString + "mainEntity";
		entity = mSceneManager->createEntity(name, meshName);
		mainNode->attachObject(entity);
		entity->getMesh()->setAutoBuildEdgeLists(false);
		entity->setCastShadows(false);
		
	}

	void BaseObject::placeObject(){
		mainNode->setPosition(position);
		mainNode->setOrientation(orientation);
	}

	bool BaseObject::isAlive(){
		return alive;
	}

	void BaseObject::setStatus(bool newStatus){
		alive = newStatus;
	}

	int BaseObject::getID(){
		return ID;
	}


	Ogre::Vector3 BaseObject::getPosition(){
		return mainNode->getPosition();
	}
	Ogre::Quaternion BaseObject::getOrientation(){
		return mainNode->getOrientation();
	}
	Ogre::SceneNode* BaseObject::getSceneNode(){
		return mainNode;
	}
	Ogre::Entity* BaseObject::getEntity(){
		return entity;
	}

	BaseObject* BaseObject::getObject(){
		return this;
	}

	Ogre::Vector3 BaseObject::QuaternionToVector(Ogre::Quaternion q){
		return q *Ogre::Vector3::UNIT_Z;
	}

	void BaseObject::update(float time){
		if(alive){
			//update
			//position = mainNode->getPosition();
		}

	}




	void BaseObject::destroy(){
		mSceneManager->destroyEntity(IDString + "mainEntity");
		mSceneManager->destroySceneNode(IDString + "mainNode");
	}

	std::string BaseObject::convertInt(int n){
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	void BaseObject::setText(std::string newText){
		textAreaCurrent->setCaption(newText);
	}


}