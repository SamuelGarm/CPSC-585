#pragma once
#include "physx/PxPhysicsAPI.h"
//#include "graphics/Geometry.h"
//#include "graphics/Texture.h"

#include "engine/PxConversionUtils.h"
#include <glm/gtc/random.hpp>

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
	TransformComponent(glm::vec3 _position, glm::quat _rotation) : position(_position)
	{
		setRotation(_rotation);
	};

	//functions to maniplate the transform
	//when getting the transform if it is attached to a physx body we need to make sure it is relative to that
	glm::vec3 getTranslation() {
		if (actor == nullptr)
			return glm::vec3(position);
		else
			return PxtoGLM(actor->getGlobalPose().p) + glm::rotate(PxtoGLM(actor->getGlobalPose().q), position);
	}

	glm::vec3 getLocalTranslation() {
		return glm::vec3(position);
	}

	glm::quat getRotation() {
		glm::quat local = glm::angleAxis(rotationAngle, rotationAxis);
		if (actor == nullptr)
			return glm::quat(local);
		else
			return PxtoGLM(actor->getGlobalPose().q) * local;
	}
	glm::vec3 getScale() {
		return scale;
	}

	void setPosition(glm::vec3 _position) {
		position = _position;
	}
	void setRotation(glm::vec3 _rotationAxis, float _angle) {
		//rotationQ = glm::angleAxis(glm::radians(_angle), _rotationAxis);
		rotationAngle = _angle;
		rotationAxis = _rotationAxis;
	}

	void setRotation(glm::quat _rotation) {
		//rotationQ = _rotation;
		rotationAxis = glm::axis(_rotation);
		rotationAngle = glm::angle(_rotation);
	}

	void setScale(glm::vec3 _scale) {
		scale = _scale;
	}

	glm::mat4 getTransformationMatrix()
	{
		return glm::translate(glm::mat4(1), getTranslation()) * toMat4(getRotation()) * glm::scale(glm::mat4(1), getScale());
	}

private:
	friend class GraphicsSystem;
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotationAxis = glm::vec3(1, 0, 0);
	float rotationAngle = 0;
	glm::vec3 scale = glm::vec3(1);
	physx::PxRigidActor* actor = nullptr;

};