#include "Fachada/Camera.h"
#include "Fachada/GraphicsFacade.h"

Camera::Camera(Structs::TPosicion position, Structs::TPosicion lookAt)
{

	//GraphicsFacade::getInstance().smgr->setAmbientLight(video::SColorf(255, 255, 255));

	camera = GraphicsFacade::getInstance().smgr->addCameraSceneNode(0, vector3df(position.X, position.Y, position.Z), vector3df(lookAt.X, lookAt.Y, lookAt.Z));
	//camera->setAspectRatio(16.0f / 9.0f);
	//camera->setNearValue(1.0f);
	//camera->setFOV(PI / 2.5f);
	//camera->setFarValue(20.0f);
	positionInitial = position;


}

Camera::~Camera(){
}

void Camera::render(Structs::TPosicion positionPlayer){

	camera->setTarget(vector3df(positionPlayer.X, positionPlayer.Y, positionPlayer.Z));
	camera->setPosition(vector3df(positionPlayer.X + 20, positionPlayer.Y + 40, positionPlayer.Z));

}
