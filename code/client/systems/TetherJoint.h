#pragma once
#include "PxPhysicsAPI.h"

#include "PhysicsSystem.h"
#include "../entities/car/Car.h"


void setTetherPoints(std::vector<PxRigidStatic*> tp);
void setupJoint(physics::PhysicsSystem &physicsSystem, Car &car);

void testJoint(physics::PhysicsSystem physicsSystem, Car& car);
void testRope(physics::PhysicsSystem physicsSystem, Car& car);
void testFree(physics::PhysicsSystem physicsSystem);