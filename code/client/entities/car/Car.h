#pragma once

#include "PxPhysicsAPI.h"
#include "vehicle2/PxVehicleAPI.h"

#include <glm/glm.hpp>

#include "../../systems/PhysicsSystem.h"

using namespace physx;
using namespace physx::vehicle2;
using namespace snippetvehicle2;
using namespace glm;


// HACK(beau): make these visible to tuning imgui panel
extern float carThrottle;
extern float carBrake;
extern float carAxis;
extern float carAxisScale;


// Commands are issued to the vehicle in a pre-choreographed sequence.
struct Command
{
    PxF32 brake;
    PxF32 throttle;
    PxF32 steer;
    PxU32 gear;
    // PxF32 duration;
};


// The path to the vehicle json files to be loaded.

extern const char *gVehicleDataPath;

struct Car {

    

    physics::PhysicsSystem* physicsSystem;
    std::vector<glm::vec3>* m_track;
    char* m_vehicleName = "Player";

    // The vehicle with engine drivetrain
    EngineDriveVehicle m_Vehicle;

    // Vehicle simulation needs a simulation context
    // to store global parameters of the simulation such as
    // gravitational acceleration.
    PxVehiclePhysXSimulationContext m_VehicleSimulationContext;

    PxU32 m_TargetGearCommand = PxVehicleEngineDriveTransmissionCommandState::eAUTOMATIC_GEAR;
    Command m_Commands[5] = 
    {
        {
            0.5f,
            0.0f,
            0.0f,
            m_TargetGearCommand,
        }, // 2.0f},  // brake on and come to rest for 2 seconds
        {
            0.0f,
            0.65f,
            0.0f,
            m_TargetGearCommand,
        }, // 5.0f}, // throttle for 5 seconds
        {
            0.5f,
            0.0f,
            0.0f,
            m_TargetGearCommand,
        }, // 5.0f},  // brake for 5 seconds
        {
            0.0f,
            0.75f,
            0.0f,
            m_TargetGearCommand,
        }, // 5.0f}, // throttle for 5 seconds
        {
            0.0f,
            0.25f,
            0.5f,
            m_TargetGearCommand,
        } // 5.0f}  // light throttle and steer for 5 seconds.
};

    PxU32 m_NbCommands = sizeof(m_Commands) / sizeof(Command);

    Car() : physicsSystem(nullptr) {};

    bool initVehicle(PxVec3 initialPosition);
    void cleanupVehicle();
    bool getCTethered();
    void setClosestTetherPoint(PxTransform _loc);
    void setClosestTetherPoint(glm::vec3 _loc);

    glm::vec3 getForwardDir();


    void carImGui();
    void baseSetup();
    void setup1();

    void resetModifications();
    bool isGroundedDelay(Car& car);
    void TetherSteer(PxTransform _loc);
    bool TetherJump();
    bool AiTetherJump();

    PxRigidBody* getVehicleRigidBody();

    glm::vec3 getPosition();

    virtual void Update(Guid carGuid, ecs::Scene& scene, float deltaTime);

protected: 
    void Car::checkFlipped(PxTransform carPose);

    glm::vec3 getTrackNormal();

    void keepRigidbodyUpright(PxRigidBody* rigidbody);

    float STRENGTH_UP_CORRECTION{20000.f};

};


