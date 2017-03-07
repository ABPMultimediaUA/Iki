#include "TDisplay.h"

#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TCamara.h"


#define WIDTH 800
#define HEIGHT 600

using namespace std;


int main(int argc, char *argv[])
{

//   	TDisplay display(WIDTH, HEIGHT,"Motor grafico");



    //cout << "Hello world!" << endl;
    TNodo* noditoEsc= new TNodo();
    TNodo* nodito0= new TNodo();
    TNodo* nodito1= new TNodo();
    TNodo* nodito2= new TNodo();

    TMalla* malla0= new TMalla();
    TTransform* transform0 = new TTransform();
    TTransform* transform1 = new TTransform();

    nodito0->setEntidad(transform0);
    nodito1->setEntidad(transform1);
    nodito2->setEntidad(malla0);

    noditoEsc->addHijo(nodito0);
    nodito0->addHijo(nodito1);
    nodito1->addHijo(nodito2);

    transform0->rotar(90, 5, 5, 5);
    transform1->trasladar(10, 10, 10);

    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();*/


    noditoEsc->draw();

//   while(!display.IsClosed())
	//{
	//	display.Clear(0.0f,0.15f,0.3f,1.0f);
    /*
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.getPos().x = sinCounter;
		transform.getPos().z = cosCounter;

		transform.getRot().x = counter;
		transform.getRot().y = counter;
		transform.getRot().z = counter;//cosf(counter * 50);
		//transform.setScale(glm::vec3(cosCounter,cosCounter,cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform,camera);
		mesh2.Draw();
*/
//		display.Update();
		//counter += 0.0001f;
//	}
    return 0;
}
