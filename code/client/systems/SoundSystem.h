#pragma once

#include "../Car.h"

void init_sound_system();

void update_sounds(Car& car);

void handle_fmod_error();

void play_beep_sound();