#include "Camera.h"
#include "GraphicsFacade.h"

Camera::Camera(Structs::TPosicion position, Structs::TPosicion lookAt)
{
    camera = GraphicsFacade::getInstance().smgr->addCameraSceneNode(0, vector3df(position.X, position.Y, position.Z), vector3df(lookAt.X, lookAt.Y, lookAt.Z));
	positionInitial = position;
}

Camera::~Camera()
{
    //dtor
}

void Camera::render(Structs::TPosicion positionPlayer){

	camera->setTarget(vector3df(positionPlayer.X, positionPlayer.Y, positionPlayer.Z));
	camera->setPosition(vector3df(positionInitial.X+positionPlayer.X, positionInitial.Y + positionPlayer.Y, positionInitial.Z + positionPlayer.Z));

}
