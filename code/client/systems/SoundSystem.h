#pragma once

#include "../entities/car/Car.h"
#include "../entities/car/AICar.h"

#include "fmod.hpp"

struct CarSoundEmitter {
    FMOD::Channel* enginechannel = NULL;
    FMOD::Channel* brakechannel = NULL;
    // FMOD::Channel* collisionchannel = NULL;
};

struct SoundUpdater : ecs::ISystem
{
    void Initialize();
    void Initialize(ecs::Scene &scene);
    void Update(ecs::Scene &scene, float deltaTime);
};


void init_sound_system();

void update_sounds(Car& car, AICar& opponent, bool playSounds);

void handle_fmod_error();

void play_beep_sound();
