#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Ogre.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
using namespace Ogre;

namespace Ogre {
    class SceneNode;
    class SceneManager;
}

namespace TankWar
{

	
	class BaseObject
	{


	public: BaseObject(int ID, Ogre::Vector3 position, Ogre::Matrix3 orientation, Ogre::SceneManager *sceneManager, std::string meshName);
		

			int getID();
			Ogre::Vector3 getPosition();
			Ogre::Quaternion getOrientation();
			Ogre::SceneNode* getSceneNode(); /*Main Node*/
			Ogre::Entity* getEntity();
			BaseObject* getObject();
			
			
			void update(float time);

		    bool isAlive();
			void setStatus(bool newStatus);

			void destroy();

			void setText(std::string newText);
			

	protected:
			/*some varialbes that controls tank status*/
			int ID;      /* uniqure ID */
		    bool alive;  /* is alive or dead */


			Ogre::Vector3 position;      /*initial position*/
			Ogre::Matrix3 orientation;   /*initial orientation*/
			Ogre::SceneNode* mainNode;  /**main node of this tank object*/
			Ogre::Entity* entity;

			std::string meshName;
			std::string IDString;
			
			Ogre::SceneManager *mSceneManager;
			Ogre::Vector3 QuaternionToVector(Ogre::Quaternion m);
			std::string convertInt(int i);

		    void setupVariables();
			void setupObjectUnit();
			void placeObject();


			TextAreaOverlayElement *textAreaCurrent;
			OverlayManager *olmCurrent;
			OverlayContainer *panelCurrent ;
			Overlay *overlayCurrent;
			

	};
}

#endif