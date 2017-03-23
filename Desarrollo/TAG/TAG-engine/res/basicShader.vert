#version 450

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

void main()
{
	Color= VertexColor;
	gl_Position= vec4(VertexPosition, 1.0);
}


//varying vec2 texCoord0;
//varying vec3 normal0;

//uniform sampler2D diffuse;

//void main()
//{
	//gl_FragColor = texture2D(diffuse,texCoord0) * clamp(dot(-vec3(0,0,1), normal0),0.0,1.0);
//}