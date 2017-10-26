#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
using glm::vec4;
using glm::vec3;

#include "Component.h"

class Light :public Component
{
public:
	Light();
	~Light(); 

	vec4& getDiffuseColour();
	void setDiffuseColour(float r, float g, float b, float a);

	vec4& getSpecularColour();
	void setSpecularColour(float r, float g, float b, float a);

	vec4& getAmbientColour();
	void setAmbientColour(float r, float g, float b, float a);

	vec3& getDirection();
	void setDirection(float x, float y, float z);
private:
	vec4 m_DiffuseColour;
	vec4 m_SpecularColour;
	vec4 m_AmbientColour;

	vec3 m_LightDirection;
protected:
};

#endif