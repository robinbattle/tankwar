#include "TankWarSceneManager.h"
#include "World.h"
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "Constants.h"
#include "OgreSphere.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "DotSceneLoader.h"

using namespace Ogre;



namespace TankWar
{
	TankWarSceneManager::TankWarSceneManager(SceneManager *sceneManager, Ogre::RenderWindow* mWindow) : mSceneManager(sceneManager), mWindow(mWindow),
		mTerrainGlobals(0),mTerrainGroup(0),mTerrainsImported(false)
	{

	}
	/*
	TankWarSceneManager::~TankWarSceneManager(void){
		OGRE_DELETE mTerrainGroup;
		OGRE_DELETE mTerrainGlobals;

	}
	*/
	void TankWarSceneManager::generate()
	{
		Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
		lightdir.normalise();
 
		Ogre::Light* light = mSceneManager->createLight("tstLight");
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(lightdir);
		light->setDiffuseColour(Ogre::ColourValue::White);
		light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
 
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
 
		mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
 
		mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneManager, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
		mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
		mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
 
		configureTerrainDefaults(light);
 
		for (long x = 0; x <= 0; ++x)
			for (long y = 0; y <= 0; ++y)
				defineTerrain(x, y);
 
		// sync load since we want everything in place when we start
		mTerrainGroup->loadAllTerrains(true);
 
		if (mTerrainsImported)
		{
			Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
			while(ti.hasMoreElements())
			{
				Ogre::Terrain* t = ti.getNext()->instance;
				initBlendMaps(t);
			}
		}
 
		mTerrainGroup->freeTemporaryResources();


		Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
		mSceneManager->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
		mWindow->getViewport(0)->setBackgroundColour(fadeColour);

		Ogre::Plane plane;
		plane.d = 100;
		plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
 
		//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
		mSceneManager->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150);


	}


	//-------------------------------------------------------------------------------------
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
	{
		img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		if (flipX)
			img.flipAroundY();
		if (flipY)
			img.flipAroundX();
 
	}
	//-------------------------------------------------------------------------------------
	void TankWarSceneManager::defineTerrain(long x, long y)
	{
		Ogre::String filename = mTerrainGroup->generateFilename(x, y);
		if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
		{
			mTerrainGroup->defineTerrain(x, y);
		}
		else
		{
			Ogre::Image img;
			getTerrainImage(x % 2 != 0, y % 2 != 0, img);
			mTerrainGroup->defineTerrain(x, y, &img);
			mTerrainsImported = true;
		}
	}
	//-------------------------------------------------------------------------------------
	void TankWarSceneManager::initBlendMaps(Ogre::Terrain* terrain)
	{
		Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
		Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
		Ogre::Real minHeight0 = 70;
		Ogre::Real fadeDist0 = 40;
		Ogre::Real minHeight1 = 70;
		Ogre::Real fadeDist1 = 15;
		float* pBlend1 = blendMap1->getBlendPointer();
		for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
		{
			for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
			{
				Ogre::Real tx, ty;
 
				blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
				Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
				Ogre::Real val = (height - minHeight0) / fadeDist0;
				val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
 
				val = (height - minHeight1) / fadeDist1;
				val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
				*pBlend1++ = val;
			}
		}
		blendMap0->dirty();
		blendMap1->dirty();
		blendMap0->update();
		blendMap1->update();
	}
	//-------------------------------------------------------------------------------------
	void TankWarSceneManager::configureTerrainDefaults(Ogre::Light* light)
	{
		// Configure global
		mTerrainGlobals->setMaxPixelError(8);
		// testing composite map
		mTerrainGlobals->setCompositeMapDistance(3000);
 
		// Important to set these so that the terrain knows what to use for derived (non-realtime) data
		mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
		mTerrainGlobals->setCompositeMapAmbient(mSceneManager->getAmbientLight());
		mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
 
		// Configure default import settings for if we use imported image
		Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
		defaultimp.terrainSize = 513;
		defaultimp.worldSize = 12000.0f;
		defaultimp.inputScale = 600;
		defaultimp.minBatchSize = 33;
		defaultimp.maxBatchSize = 65;
		// textures
		defaultimp.layerList.resize(3);
		defaultimp.layerList[0].worldSize = 100;
		defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
		defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
		defaultimp.layerList[1].worldSize = 30;
		defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
		defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
		defaultimp.layerList[2].worldSize = 200;
		defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
		defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

	
	}

}