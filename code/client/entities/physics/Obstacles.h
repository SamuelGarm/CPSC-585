#pragma once
#include "core/ecs.h"
#include "../../systems/GraphicsSystem.h"
#include "../../systems/components.h"
#include "../../systems/PhysicsSystem.h"
#include "PxPhysicsAPI.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

using namespace physx;

void setUpLogs(ecs::Scene& mainScene);
void addRigidBody(physics::PhysicsSystem physicsSystem);
void clearObstacles(physics::PhysicsSystem physicsSystem, ecs::Scene& mainScene);
void obstaclesImGui(ecs::Scene& mainScene, physics::PhysicsSystem physicsSystem);
void resetTransforms(ecs::Scene& mainScene);