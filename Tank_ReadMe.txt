Final Tank Version: Please check out the Fianl_tank folder

In this version, we complete:

1. We could control our tank to move and fire.  
	control: WASD: tank body;
	         JLIK: barrel; 
                 space: fire
		 H: switch between attack/defence mode;		

2. Basic Random AI: AI tanks will do random things: go forward/backward, turn left/right, fires

3. Player tank and AI tanks will stopped by world geometry(border of the plane and one big box on the plane) and other tanks.

4. different tanks have different damage, defence and speed properties;
		at beginning, for player, 
				  damage = 80, defence 30, speed = 120  
				enemy
				  ordinary: 60, 20, 20;
				  thin/fast:200,100,40;
				  boss:120, 10, 150;
		 if player levels up, each property +10, after reach level 3, player tank can roll compact through any tanks expect boss.

   Item can be collected: MachineGun: 20 bullet/each, 0.2invertal/each.
			  First aid capsule: recover some health
			  Land Mine: damange player tank, and cause camera shake effect.
			  (Item can only be collected by player)

   

 
5. This is a gravity enviornment, so bullets will fly in an arc. 

6. player vs AI Mode

7. add three types of item: mine, machine gun and first aid.


8. camara: 1.third person, 2. first person

9. Add CEGUI on, so before compiles, please add libs and dlls.

10."Load Classic" will load a .scene file which will add some light, new geometry, such as pyramid, and shaow of the previous geometries.

   But the frame of game will decrease.

10. Upload a runnnable version in "Runnable" folder

11.only debug for win32


CEGUI DePENDENCY

	1.Project Include Directories
		$(CEGUI_HOME)/cegui/include
	2.Project Library Directories
          	CEGUI_HOME/lib
	  
	3.Dynamic link lib
	  CEGUIBase_d.dll               CEGUIBase.dll
	  CEGUIFalagardWRBase_d.dll     CEGUIFalagardWRBase.dll 
	  CEGUIOgreRenderer_d.dll       CEGUIOgreRenderer.dll
	  CEGUIExpatParser_d.dll        CEGUIExpatParser.dll
	
	4.Project Additional Library Dependencies in Linker
		
    	  CEGUIBase_d.lib   		CEGUIBase.lib
	  CEGUIOgreRenderer_d.lib       CEGUIOgreRenderer.lib

	5.May have something forgot

