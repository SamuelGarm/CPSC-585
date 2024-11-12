#pragma once
#include <glm/glm.hpp>
#include "engine/physx/PxPhysicsAPI.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>


//Helper functions that allow for easy transforms between physx and glm
inline glm::vec3 PxtoGLM(const physx::PxVec3& _vec) {
	return glm::vec3(_vec.x, _vec.y, _vec.z);
}

/*
* Physx stores quaternions as xyzw and GLM uses wxyz
*/
inline glm::quat PxtoGLM(const physx::PxQuat& _quat) {
	return glm::quat(_quat.w, _quat.x, _quat.y, _quat.z);
}

inline physx::PxVec3 GLMtoPx(const glm::vec3& _vec) {
	return physx::PxVec3(_vec.x, _vec.y, _vec.z);
}

inline physx::PxQuat GLMtoPx(const glm::quat& _quat) {
	return physx::PxQuat(_quat.x, _quat.y, _quat.z, _quat.w);
}