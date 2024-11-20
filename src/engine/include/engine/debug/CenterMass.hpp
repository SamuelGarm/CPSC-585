#pragma once

#include "engine/ecs.hpp"
#include "engine/physx/PxPhysicsAPI.h"
#include "engine/components/Transform.hpp"
#include "engine/vehicle/Car.hpp"

using namespace physx;

void renderCMassSphere(TransformComponent& _target, TransformComponent& sphere_transform);
void renderCMassSphere(PxTransform& _target, TransformComponent& sphere_transform);
void setupSphere(ecs::Scene& mainScene, Car& car);