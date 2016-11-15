/** Example 019 Mouse and Joystick

This tutorial builds on example 04.Movement which showed how to
handle keyboard events in Irrlicht.  Here we'll handle mouse events
and joystick events, if you have a joystick connected and a device
that supports joysticks.  These are currently Windows, Linux and SDL
devices.
*/

#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

/*
Just as we did in example 04.Movement, we'll store the latest state of the
mouse and the first joystick, updating them as we receive events.
*/
class MyEventReceiver : public IEventReceiver
{
public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}

	}

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}


	MyEventReceiver()
	{
	}

};

/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/
int main()
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// create device
	MyEventReceiver receiver;

	IrrlichtDevice* device = createDevice(driverType,
			core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	scene::IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(10);
    if(cubeNode) {
          cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
          cubeNode->setPosition(core::vector3df(5,15,5));
    }

	scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

	// As in example 04, we'll use framerate independent movement.
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 25.f;

	while(device->run())
	{
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;


		core::vector3df nodePosition = cubeNode->getPosition();


			// Create a ray through the mouse cursor.
			if(receiver.GetMouseState().LeftButtonDown){
			core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
				receiver.GetMouseState().Position, camera);

			// And intersect the ray with a plane around the node facing towards the camera.
			core::plane3df plane(nodePosition, core::vector3df(0, -1, 0));
			core::vector3df mousePosition;

			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
			{
				// We now have a mouse position in 3d space; move towards it.
				core::vector3df toMousePosition(mousePosition - nodePosition);
				const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

				if(toMousePosition.getLength() <= availableMovement)
					nodePosition = mousePosition; // Jump to the final position
				else
					nodePosition += toMousePosition.normalize() * availableMovement; // Move towards it
			}

			}
		cubeNode->setPosition(nodePosition);


		driver->beginScene(true, true, video::SColor(255,113,113,133));
		smgr->drawAll(); // draw the 3d scene
		driver->endScene();
	}

	/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();

	return 0;
}

/*
**/
