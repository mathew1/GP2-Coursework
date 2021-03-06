#version 150

in vec3 vertexPosition;
in vec4 vertexColour;

out vec4 vertexColourOut;

uniform mat4 MVP;

void main()
{
	vertexColourOut = vertexColour;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}