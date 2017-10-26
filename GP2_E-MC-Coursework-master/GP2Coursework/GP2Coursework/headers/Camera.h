//
//  Camera.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <SDL.h>

#include <gl\glew.h>
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

enum MovementType { FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT, RESET, UP, DOWN, STEADY };

class Camera : public Component
{
	const float movementSpeed = 0.5f;

public:
	Camera();
	~Camera();

	void update();

	void setLook(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setNearClip(float near);
	void setFarClip(float far);
	void setFOV(float FOV);

	void setAspectRatio(float ratio);


	mat4& getView();
	mat4& getProjection();

	void setMousePosition(int X, int Y, int xVel, int yVel);
	void movement(MovementType movementType);
	void mouseUpdate(const glm::vec2& newMousePos);
	void strafeLeft();
	void strafeRight();

	vec3 getPosition();


protected:
private:
	vec3 strafedirection;
	glm::vec2 oldMousePos;

	vec3 m_position;
	vec3 m_direction;

	vec3 m_LookAt;
	vec3 m_Up;

	mat4 m_View;
	mat4 m_Projection;

	float m_NearClip;
	float m_FarClip;
	float m_FOV;
	float m_AspectRatio;
};

#endif
