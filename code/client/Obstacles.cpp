#include "Obstacles.h"

void addRigidBody(physics::PhysicsSystem physicsSystem) {
	PxBoxGeometry boxGeom(PxVec3(15.0f, 2.0f, 1.0f));

	// create a rigid body with the box geometry
	PxTransform transform(PxVec3(56.0f, 0.0f, 0.0f));
	PxRigidDynamic* actor = PxCreateDynamic(
		*physicsSystem.m_Physics,
		transform,
		boxGeom,
		*physicsSystem.m_Material,
		100000.0f // This is the density value
	);

	// add the actor to the scene
	physicsSystem.m_Scene->addActor(*actor);
}

void setUpLogs(ecs::Scene &mainScene) {
	// Finish line logs
	ecs::Entity log1_e = mainScene.CreateEntity();
	RenderModel log1_r = RenderModel();
	GraphicsSystem::importOBJ(log1_r, "cube.obj");
	mainScene.AddComponent(log1_e.guid, log1_r);
	TransformComponent log1_t = TransformComponent();
	log1_t.setPosition(glm::vec3(56.f, 0.f, 0.f));
	log1_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log1_e.guid, log1_t);



	ecs::Entity log2_e = mainScene.CreateEntity();
	RenderModel log2_r = RenderModel();
	GraphicsSystem::importOBJ(log2_r, "cube.obj");
	mainScene.AddComponent(log2_e.guid, log2_r);
	TransformComponent log2_t = TransformComponent();
	log2_t.setPosition(glm::vec3(12.f, 0.f, 0.f));
	log2_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log2_e.guid, log2_t);

	// First quarter logs
	ecs::Entity log3_e = mainScene.CreateEntity();
	RenderModel log3_r = RenderModel();
	GraphicsSystem::importOBJ(log3_r, "cube.obj");
	mainScene.AddComponent(log3_e.guid, log3_r);
	TransformComponent log3_t = TransformComponent();
	log3_t.setPosition(glm::vec3(35.f, 0.f, 60.f));
	log3_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log3_e.guid, log3_t);

	ecs::Entity log4_e = mainScene.CreateEntity();
	RenderModel log4_r = RenderModel();
	GraphicsSystem::importOBJ(log4_r, "cube.obj");
	mainScene.AddComponent(log4_e.guid, log4_r);
	TransformComponent log4_t = TransformComponent();
	log4_t.setPosition(glm::vec3(25.f, 0.f, 120.f));
	log4_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log4_e.guid, log4_t);

	ecs::Entity log5_e = mainScene.CreateEntity();
	RenderModel log5_r = RenderModel();
	GraphicsSystem::importOBJ(log5_r, "cube.obj");
	mainScene.AddComponent(log5_e.guid, log5_r);
	TransformComponent log5_t = TransformComponent();
	log5_t.setPosition(glm::vec3(45.f, 0.f, 160.f));
	log5_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log5_e.guid, log5_t);

	// Second quarter logs
	ecs::Entity log6_e = mainScene.CreateEntity();
	RenderModel log6_r = RenderModel();
	GraphicsSystem::importOBJ(log6_r, "cube.obj");
	mainScene.AddComponent(log6_e.guid, log6_r);
	TransformComponent log6_t = TransformComponent();
	log6_t.setPosition(glm::vec3(-35.f, 0.f, 60.f));
	log6_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log6_e.guid, log6_t);

	ecs::Entity log7_e = mainScene.CreateEntity();
	RenderModel log7_r = RenderModel();
	GraphicsSystem::importOBJ(log7_r, "cube.obj");
	mainScene.AddComponent(log7_e.guid, log7_r);
	TransformComponent log7_t = TransformComponent();
	log7_t.setPosition(glm::vec3(-25.f, 0.f, 120.f));
	log7_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log7_e.guid, log7_t);

	ecs::Entity log8_e = mainScene.CreateEntity();
	RenderModel log8_r = RenderModel();
	GraphicsSystem::importOBJ(log8_r, "cube.obj");
	mainScene.AddComponent(log8_e.guid, log8_r);
	TransformComponent log8_t = TransformComponent();
	log8_t.setPosition(glm::vec3(-45.f, 0.f, 160.f));
	log8_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log8_e.guid, log8_t);

	//Third Quarter logs
	ecs::Entity log9_e = mainScene.CreateEntity();
	RenderModel log9_r = RenderModel();
	GraphicsSystem::importOBJ(log9_r, "cube.obj");
	mainScene.AddComponent(log9_e.guid, log9_r);
	TransformComponent log9_t = TransformComponent();
	log9_t.setPosition(glm::vec3(-35.f, 0.f, -60.f));
	log9_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log9_e.guid, log9_t);

	ecs::Entity log10_e = mainScene.CreateEntity();
	RenderModel log10_r = RenderModel();
	GraphicsSystem::importOBJ(log10_r, "cube.obj");
	mainScene.AddComponent(log10_e.guid, log10_r);
	TransformComponent log10_t = TransformComponent();
	log10_t.setPosition(glm::vec3(-25.f, 0.f, -120.f));
	log10_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log10_e.guid, log10_t);

	ecs::Entity log11_e = mainScene.CreateEntity();
	RenderModel log11_r = RenderModel();
	GraphicsSystem::importOBJ(log11_r, "cube.obj");
	mainScene.AddComponent(log11_e.guid, log11_r);
	TransformComponent log11_t = TransformComponent();
	log11_t.setPosition(glm::vec3(-45.f, 0.f, -160.f));
	log11_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log11_e.guid, log11_t);

	// Fourth Quarter Logs
	ecs::Entity log12_e = mainScene.CreateEntity();
	RenderModel log12_r = RenderModel();
	GraphicsSystem::importOBJ(log12_r, "cube.obj");
	mainScene.AddComponent(log12_e.guid, log12_r);
	TransformComponent log12_t = TransformComponent();
	log12_t.setPosition(glm::vec3(35.f, 0.f, -60.f));
	log12_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log12_e.guid, log12_t);

	ecs::Entity log13_e = mainScene.CreateEntity();
	RenderModel log13_r = RenderModel();
	GraphicsSystem::importOBJ(log13_r, "cube.obj");
	mainScene.AddComponent(log13_e.guid, log13_r);
	TransformComponent log13_t = TransformComponent();
	log13_t.setPosition(glm::vec3(25.f, 0.f, -120.f));
	log13_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log13_e.guid, log13_t);

	ecs::Entity log14_e = mainScene.CreateEntity();
	RenderModel log14_r = RenderModel();
	GraphicsSystem::importOBJ(log14_r, "cube.obj");
	mainScene.AddComponent(log14_e.guid, log14_r);
	TransformComponent log14_t = TransformComponent();
	log14_t.setPosition(glm::vec3(45.f, 0.f, -160.f));
	log14_t.setScale(glm::vec3(15.f, 2.f, 1.f));
	mainScene.AddComponent(log14_e.guid, log14_t);
}
