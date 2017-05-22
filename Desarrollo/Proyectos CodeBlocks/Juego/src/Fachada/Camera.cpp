#include "Fachada/Camera.h"
#include "Fachada/GraphicsFacade.h"

Camera::Camera(Structs::TPosicion position)
{
	camera = GraphicsFacade::getInstance().motor->crearCamara(glm::vec3(position.X, position.Y, position.Z)
                                                            , 1.25664f
                                                            , GraphicsFacade::getInstance().getWindowWidth()
                                                            , GraphicsFacade::getInstance().getWindowHeigth()
                                                            , 1.f
                                                            , 3000.f);
	positionInitial = position;


}

Camera::~Camera(){
}

void Camera::render(Structs::TPosicion positionPlayer){

	//camera->setTarget(vector3df(positionPlayer.X, positionPlayer.Y, positionPlayer.Z));
	//camera->setPosition(vector3df(positionPlayer.X + 20, positionPlayer.Y + 40, positionPlayer.Z));

}
