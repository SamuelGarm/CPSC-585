#include "SoundSystem.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include <cstdio>
#include <cstdlib>

FMOD_RESULT result;

struct SoundSystem {
	FMOD::System* system = NULL;
	FMOD::Sound* beepsound = NULL;
	FMOD::Channel* playerchannel = NULL;
	FMOD::Channel* opponentchannel = NULL;
} soundsystem;

void handle_fmod_error() {
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void init_sound_system() {
	result = FMOD::System_Create(&soundsystem.system);      // Create the main system object.
	handle_fmod_error();

	result = soundsystem.system->init(512, FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	handle_fmod_error();

	result = soundsystem.system->createSound("audio/beep.ogg", FMOD_3D, 0, &soundsystem.beepsound);
	handle_fmod_error();
}

FMOD_VECTOR px_to_fmod_vec3(PxVec3 v) {
	return FMOD_VECTOR{
		v.x,
		v.y,
		v.z
	};
}

void update_sounds(Car& player) {
	auto playerbody = player.getVehicleRigidBody();
	auto playerpose = playerbody->getGlobalPose();
	auto playerveloc = px_to_fmod_vec3(playerbody->getLinearVelocity());
	auto playerposition = px_to_fmod_vec3(playerpose.p);

	PxMat33 playerrotation(playerpose.q);

	{
		bool isPlaying = false;
		// XXX(beau): atm I'm ignoring the result, maybe that's a bad idea
		soundsystem.playerchannel->isPlaying(&isPlaying);
		if (isPlaying)
			soundsystem.playerchannel->set3DAttributes(&playerposition, &playerveloc);

		// TODO: ai position
		//isPlaying = false;
		//soundsystem.opponentchannel->isPlaying(&isPlaying);
		//if (isPlaying)
			//soundsystem.opponentchannel->get3DAttributes(&)
	}

	// set player listener position
	auto forward = px_to_fmod_vec3(playerrotation * PxVec3{ 0, 0, 1 });
	auto up = px_to_fmod_vec3(playerrotation * PxVec3{ 0, 1, 0 });
	result = soundsystem.system->set3DListenerAttributes(0, &playerposition, &playerveloc, &forward, &up);
	handle_fmod_error();

	result = soundsystem.system->update();
	handle_fmod_error();
}

void play_beep_sound() {
	puts("pressed the sound key");
	result = soundsystem.system->playSound(soundsystem.beepsound, 0, false, &soundsystem.playerchannel);
	handle_fmod_error();
}