#pragma once
#include "systems/ecs.h"
#include <GL/glew.h>
#include "Geometry.h"
#include "Window.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "PxPhysicsAPI.h"

#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>


/*
* Render component is what is visible to the user
*/
struct RenderComponent
{
	GPU_Geometry* geom = new GPU_Geometry();
	int numVerts = 0;
	RenderComponent() = default;
	RenderComponent(CPU_Geometry* _geom) { geom->setCols(_geom->cols); geom->setVerts(_geom->verts); numVerts = _geom->verts.size(); }
};

glm::vec3 PxtoGLM(physx::PxVec3 _vec) {
	return glm::vec3(_vec.x, _vec.y, _vec.z);
}

glm::quat PxtoGLM(physx::PxQuat _quat) {
	return glm::quat(_quat.x, _quat.y, _quat.z, _quat.w);
}

physx::PxVec3 GLMtoPx(glm::vec3 _vec) {
	return physx::PxVec3(_vec.x, _vec.y, _vec.z);
}

physx::PxQuat GLMtoPx(glm::quat _quat) {
	return physx::PxQuat(_quat.x, _quat.y, _quat.z, _quat.w);
}

/*
* Transform describes the objects position in 3D space.
*/
struct TransformComponent
{
public:
	//constructors
	/*
	* This constructor will make the TransformComponent with a RigidActor already attached
	*/
	TransformComponent(physx::PxRigidActor* _actor) : actor(_actor) {};

	/*
	* This constructor will make the transform component with no defined actor attached.
	*/
	TransformComponent() {}

	/*
	* This constructor will make the transform component using glm transforms to initalize it and set its position
	*/
	TransformComponent(glm::vec3 _position, glm::quat _rotation) : position(_position), rotation(_rotation) {};

	//functions to maniplate the transform
	glm::vec3 getPosition() { 
		if (actor == nullptr)
			return glm::vec3(position);
		else
			return PxtoGLM(actor->getGlobalPose().p);
	}
	glm::quat getRotation() { 
		return glm::quat(rotation); 
	}

	void setPosition(glm::vec3 _position) {
		if (actor == nullptr)
			position = _position;
		else
			actor->setGlobalPose(physx::PxTransform(GLMtoPx(_position)));
	}
	void setRotation(glm::quat _rotation) {
		if (actor == nullptr)
			rotation = _rotation;
		else
			actor->setGlobalPose(physx::PxTransform(GLMtoPx(_rotation)));
	}
private:
	glm::vec3 position = glm::vec3(0);
	glm::quat rotation = glm::quat(0, 0, 0, 0);
	physx::PxRigidActor* actor = nullptr;
	
};

struct GraphicsSystem : ecs::ISystem {
public:
	GraphicsSystem(Window& _window);
	void Update(ecs::Scene& scene, float deltaTime);
	void input(SDL_Event&, int _cameraID);
	static void readVertsFromFile(RenderComponent& _component, const std::string _file);
private:
	Camera cameras[4];
	int numCamerasActive = 1;
	GLint modelUniform = -1;
	GLuint viewUniform = -1;
	GLuint perspectiveUniform = -1;
	ShaderProgram shader;
	glm::ivec2 windowSize;
	static void processNode(aiNode* node, const aiScene* scene, CPU_Geometry* geom);
};