#pragma once
#include "engine/ecs.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/geometry/Curve.hpp"
#include "engine/NavPath.hpp"
#include "engine/physx/PxPhysicsAPI.h"
#include "engine/physx/vehicle2/PxVehicleAPI.h"

#include <glm/glm.hpp>
#include <vector>

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
enum DriverType {
    COMPUTER,
    HUMAN
};

extern const char *gVehicleDataPath;

struct Car {

    // needed for controller support lmao
    int controllerIndex = -1;

    DriverType m_driverType = DriverType::COMPUTER;

    physics::PhysicsSystem* physicsSystem;
    Curve* m_track;
    char* m_vehicleName = "Player";

    // The vehicle with engine drivetrain
    EngineDriveVehicle m_Vehicle;

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

    // Initialization & updating
    void Initialize(DriverType type, PxTransform initialPose, physics::PhysicsSystem* ps, Curve* track, NavPath* pathToFollow, std::string name);
    virtual void Update(Guid carGuid, ecs::Scene& scene, float deltaTime);
    void cleanupVehicle();
    void baseSetup();
    void setup1();
    void setup2();

    float carSpeed();

    bool carGetControllerStartPressed();
    bool carGetControllerSelectPressed();

    // movement 
    Command drive(Guid carGuid, ecs::Scene& scene, float deltaTime);
    void setClosestTetherPoint(PxTransform _loc);
    void setClosestTetherPoint(glm::vec3 _loc);
    //bool getCTethered();
    bool isGroundedDelay(Car& car);
    bool Jump();
    bool AiJump();
    void Car::checkFlipped(PxTransform carPose);

    void BoostForward(float magnitude);

    // navigation
    glm::vec3 getForwardDir();

    // utility
    void carImGui();
    void resetModifications();
    //void TetherSteer(PxTransform _loc);
    bool isWrongWay();

    // position
    PxRigidBody* getVehicleRigidBody();
    glm::vec3 getPosition();
    PxTransform getTransformPx();

    /////////////////////////////////////////
    // AI methods / etc.  ///////////////////
    /////////////////////////////////////////
    NavPath* m_navPath;
    Command pathfind(ecs::Scene& scene, float deltaTime);
    /////////////////////////////////////////

    float m_timeSinceLastRamp = 10.f;
    float m_timeSinceLastBoost = 10.f;
    std::string m_name;
    bool m_grounded{ false };

private:
    glm::vec3 getTrackNormal();
    void keepRigidbodyUpright(PxRigidBody* rigidbody);

    float STRENGTH_UP_CORRECTION{300.f};
    float updateTimer = 0;
    Command lastCommand = Command({ 1,0,0,0 });
    float m_stuckTimer{ 0.f };
    float m_timeSinceLastJump{ 0.f };
};


