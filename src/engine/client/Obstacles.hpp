#pragma once
#include "engine/ecs.hpp"
#include "engine/systems/Graphics.hpp"
#include "engine/systems/PhysicsSystem.hpp"

using namespace physx;

void setUpLogs(ecs::Scene& mainScene);
void addRigidBody(physics::PhysicsSystem physicsSystem);
void clearObstacles(physics::PhysicsSystem physicsSystem, ecs::Scene& mainScene);
void obstaclesImGui(ecs::Scene& mainScene, physics::PhysicsSystem physicsSystem);
void resetTransforms(ecs::Scene& mainScene);