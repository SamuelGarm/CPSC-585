#include "TetherJoint.h"

std::vector<PxRigidStatic*> tetherPoints;
PxRigidStatic* tetherPoint1;

// Function to populate tether points array
void setTetherPoints(std::vector<PxRigidStatic*> tp) {
    tetherPoints = tp;
}

void setupJoint(physics::PhysicsSystem &physicsSystem, Car &car) {

    tetherPoint1 = tetherPoints[0];

    PxTransform testTransform1(PxVec3(0.0f, 0.0f, 0.0f));
    PxTransform testTransform2(PxVec3(1.f, 0.f, 0.f));

    PxTransform localFrame1 = PxTransform(PxIdentity);
    PxTransform localFrame2 = PxTransform(PxVec3(0.0f, 0.0f, 1.0f));

    assert(physicsSystem.m_Physics != nullptr);

    PxRevoluteJoint* joint = PxRevoluteJointCreate(*physicsSystem.m_Physics,
                          tetherPoint1, localFrame1,
                          car.m_Vehicle.mPhysXState.physxActor.rigidBody, localFrame2);
      
}

void testJoint(physics::PhysicsSystem physicsSystem, Car& car) {
    PxInitExtensions(*physicsSystem.m_Physics, physicsSystem.m_Pvd);

    // create a dynamic rigid body
    auto dynamicActor = physicsSystem.m_Physics->createRigidDynamic(PxTransform(PxVec3(30.0f, 1.0f, 20.0f)));

    // create a shape for the dynamic rigid body
    auto dynamicBox = physicsSystem.m_Physics->createShape(PxSphereGeometry(1.0f), *physicsSystem.m_Material);
    dynamicActor->attachShape(*dynamicBox);

    // create a static rigid body
    auto staticActor = physicsSystem.m_Physics->createRigidStatic(PxTransform(PxVec3(30.0f, 1.0f, 30.0f)));

    // create a shape for the static rigid body
    auto staticPlane = physicsSystem.m_Physics->createShape(PxBoxGeometry(PxVec3(1.0f, 1.0f, 1.0f)), *physicsSystem.m_Material);
    staticActor->attachShape(*staticPlane);

    physicsSystem.m_Scene->addActor(*dynamicActor);
    physicsSystem.m_Scene->addActor(*staticActor);

    PxVec3 jointPos1(0.f, 0.f, 0.f);
    PxVec3 jointPos2(0.f, 0.f, 10.f);
    PxQuat jointRot(1.5f, PxVec3(0.0f, 0.f, 1.f));
    PxTransform jointTrans1(jointPos1, jointRot);
    PxTransform jointTrans2(jointPos2, jointRot);

    PxTransform relativeTransform = car.m_Vehicle.mPhysXState.physxActor.rigidBody->getGlobalPose().getInverse() * jointTrans1;

    //dynamicActor

    // create the joint
    auto joint = PxRevoluteJointCreate(*physicsSystem.m_Physics, NULL, PxTransform(PxIdentity), car.m_Vehicle.mPhysXState.physxActor.rigidBody, jointTrans2);
    //auto joint = PxRevoluteJointCreate(*physicsSystem.m_Physics, staticActor, jointTrans, car.m_Vehicle.mPhysXState.physxActor.rigidBody, jointTrans);
    //joint->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
    //joint->setLimit(PxJointAngularLimitPair(-4*PxPi , 4*PxPi));

    //Visualization stuff for joints:
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 5.0f);
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LIMITS, 5.0f);
    joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);
}

void testRope(physics::PhysicsSystem physicsSystem, Car& car) {
    PxInitExtensions(*physicsSystem.m_Physics, physicsSystem.m_Pvd);

    // Tether Point
    PxBoxGeometry boxGeom(PxVec3(1.0f, 2.0f, 1.0f));

    // create a rigid body with the box geometry
    PxTransform boxTransform(PxVec3(30.0f, 1.0f, 30.0f));


    // Create the rigid bodies
    physx::PxRigidStatic* rigidBody = PxCreateStatic(
        *physicsSystem.m_Physics,
        boxTransform,
        boxGeom,
        *physicsSystem.m_Material
    );    

    physicsSystem.m_Scene->addActor(*rigidBody);

    // Get the points to attach the constraint to
    physx::PxVec3 vehicleAttachPoint = PxVec3(0.f,0.f,0.f); // set the attach point on the vehicle
    physx::PxVec3 rigidBodyAttachPoint = PxVec3(5.f,1.f,5.f); // set the attach point on the rigid body

    // Create the constraint
    physx::PxD6Joint* constraint = PxD6JointCreate(
        *physicsSystem.m_Physics,
        rigidBody,
        physx::PxTransform(rigidBodyAttachPoint),
        car.m_Vehicle.mPhysXState.physxActor.rigidBody,
        physx::PxTransform(vehicleAttachPoint)
    );

    // Set the constraint properties // eLOCKED
    constraint->setMotion(physx::PxD6Axis::eX, physx::PxD6Motion::eLOCKED); // lock the X-axis
    constraint->setMotion(physx::PxD6Axis::eY, physx::PxD6Motion::eFREE); // lock the Y-axis
    constraint->setMotion(physx::PxD6Axis::eZ, physx::PxD6Motion::eLOCKED); // lock the Z-axis
    constraint->setMotion(physx::PxD6Axis::eTWIST, physx::PxD6Motion::eFREE); // allow twist motion
    constraint->setMotion(physx::PxD6Axis::eSWING1, physx::PxD6Motion::eFREE); // allow swing motion
    constraint->setMotion(physx::PxD6Axis::eSWING2, physx::PxD6Motion::eFREE); // allow swing motion
    constraint->setDistanceLimit(PxJointLinearLimit(10.0f, 10.0f)); // set the maximum distance between the two points
    //constraint->setStiffness(1000.0f); // set the stiffness of the constraint
    //constraint->setDamping(10.0f); // set the damping of the constraint
        

    //Visualization stuff for joints:
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 5.0f);
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LIMITS, 5.0f);
    constraint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);
}

void testFree(physics::PhysicsSystem physicsSystem) {
    PxInitExtensions(*physicsSystem.m_Physics, physicsSystem.m_Pvd);

    // Assume we have two rigid bodies named "actor1" and "actor2"
    // We want to create a revolute joint between them, with the joint positioned at the center of actor1

    // create a dynamic rigid body
    auto actor1 = physicsSystem.m_Physics->createRigidDynamic(PxTransform(PxVec3(30.0f, 1.0f, 20.0f)));

    // create a shape for the dynamic rigid body
    auto dynamicBox = physicsSystem.m_Physics->createShape(PxSphereGeometry(1.0f), *physicsSystem.m_Material);
    actor1->attachShape(*dynamicBox);

    physicsSystem.m_Scene->addActor(*actor1);

    PxVec3 jointLoc(20.f, 1.f, 10.f);
    PxQuat jointRot(1.5f, PxVec3(0.0f, 0.f, 1.f));
    PxTransform jointTrans(jointLoc, jointRot);

    // Create the joint
    PxRevoluteJoint* joint = PxRevoluteJointCreate(
        *physicsSystem.m_Physics,
        NULL, jointTrans,
        actor1, PxTransform(PxVec3(2.f, 0.f, 2.f)));

    // Set joint properties
    joint->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
    joint->setDriveVelocity(1.f);

    //Visualization stuff for joints:
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 5.0f);
    physicsSystem.m_Scene->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LIMITS, 5.0f);
    joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);
}