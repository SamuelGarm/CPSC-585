#pragma once

#include "glm/glm.hpp"
#include "engine/ecs.hpp"
#include "engine/NavPath.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/vehicle/Car.hpp"

#include <vector>

Guid spawnCar(DriverType type, ecs::Scene& scene, physics::PhysicsSystem* physicsSystem, glm::vec3 position, glm::vec3 direction, Curve* track, NavPath* navPath, std::string name);

std::vector<glm::vec3> spawnpointsAlongAxis(int rows, int cols,float spread, glm::vec3 axis, glm::vec3 start);
std::vector<std::string> getPlayerNames();
