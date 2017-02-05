#include <iostream>
#include <GL\glew.h>
#include "include/Display.h"
#include "include/Shader.h"
#include "include/Mesh.h"
#include "include/Texture.h"
#include "include/Transform.h"
#include "include/Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
	Display display(WIDTH, HEIGHT,"Motor gráfico");


	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
						 Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5,1.0)),
						 Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0.0)), };

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]),indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0,0,-5),70.0f,(float)WIDTH/(float)HEIGHT,0.01f,1000.0f);
	Transform transform;

	float counter = 0.0f;

	while(!display.IsClosed())
	{
		display.Clear(0.0f,0.15f,0.3f,1.0f);

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

		display.Update();
		counter += 0.0001f;
	}

	return 0;
}
