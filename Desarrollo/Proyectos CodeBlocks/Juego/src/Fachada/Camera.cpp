#include "Fachada/Camera.h"
#include "Fachada/GraphicsFacade.h"

Camera::Camera(Structs::TPosicion position)
{
	//GraphicsFacade::getInstance().smgr->setAmbientLight(video::SColorf(255, 255, 255));
	int anch = GraphicsFacade::getInstance().getWidth();
	int alt  = GraphicsFacade::getInstance().getHeight();

	camera = GraphicsFacade::getInstance().motor->crearCamara(glm::vec3(position.X, position.Y, position.Z), 45.f, anch, alt, 0.1f, 1000.f);
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
