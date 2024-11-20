#pragma once

#include "engine/ecs.hpp"
#include "engine/vehicle/Car.hpp"

void setupCarVFX(ecs::Scene& mainScene, Guid _ID);
void updateCarVFX(ecs::Scene mainScene, float _dt);

void tireTrackImgui();
