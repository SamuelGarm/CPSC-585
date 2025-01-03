#pragma once
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_opengl.h"
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "engine/ecs.hpp"
#include "engine/components/Transform.hpp"

class Camera {
public:
	Camera();
	void lookat(glm::vec3 _target);
	glm::mat4 getView();
	void input(const SDL_Event&);
	glm::vec3 getPos();
	void setPos(glm::vec3 _position);
	void update(TransformComponent& _carTransform, bool isReversing, glm::vec3 carVelocity, float dt);
	Guid targetEntity = 0;
private:
	friend class GraphicsSystem;
	glm::vec3 cameraPos = glm::vec3(0);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f); //DO not set, it is overwritten on construction!
	float fspeed = 0, hspeed = 0, panHorizontal = 90.0f, panVertical = -10.0f, lastX = 0, lastY = 0;
	bool leftMouseButtonPressed = false, firstMouse = true;
	const float cameraSpeed = 0.1;
	bool initalized = false;
	bool fixCamera = true;
	glm::vec3 cameraTargetLocation = glm::vec3(0);
	const int rollingAverageAmount = 60;
	int rollingIndex = 0;
	std::vector<glm::vec3> rollingAverageDownvector = std::vector<glm::vec3>(rollingAverageAmount, glm::vec3(0, -1, 0));

	const int cameraRollingAverageAmount = 15;
	int cameraRollingIndex = 0;
	//averages the target camera position over a series of frames to smooth out movement and allow for the vehicle to spin out without the camera swinging
	std::vector<glm::vec3> rollingAverageCamera = std::vector<glm::vec3>(cameraRollingAverageAmount, glm::vec3(0, 0, 0));

	float FOV = 30;
	glm::vec3 cameraVelocity = { 0,0,0 };

	float cameraResetTimer = 5.f;
};