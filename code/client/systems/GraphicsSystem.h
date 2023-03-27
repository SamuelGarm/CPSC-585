#pragma once
#include "core/ecs.h"
#include <GL/glew.h>
#include "graphics/Geometry.h"
#include "../client/Window.h"
#include "graphics/Camera.h"
#include "graphics/ShaderProgram.h"
#include "components.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "PxPhysicsAPI.h"




struct GraphicsSystem : ecs::ISystem {
public:
	GraphicsSystem(Window& _window);
	~GraphicsSystem();
	void ImGuiPanel();
	void renderUI();
	void Update(ecs::Scene& scene, float deltaTime);
	void input(SDL_Event&, int _cameraID);
	glm::mat4 getCameraView();
	glm::vec3 GraphicsSystem::g_cameraPosition();
	glm::vec3 GraphicsSystem::g_cameraVelocity();
	static void importOBJ(CPU_Geometry& _geometry, const std::string _fileName);
	static void importOBJ(RenderModel& _component, const std::string _fileName);
	static void importSplineFromOBJ(CPU_Geometry& _geometry, std::string filename);
private:

	Camera cameras[4];
	//uniforms
	int numCamerasActive = 1;

	int cam_mode = 1; // Used to determine what mode the camera should use (free, fixed, follow)
	glm::mat4 V = glm::mat4(1.f); // Had to declare this variable here for the rest of the program to work

	//debug panel variables
	bool showColliders = false;
	struct renderableInfo {
		std::vector<Guid> ids; 
		std::vector<std::string> names; 
		std::vector<glm::vec3> positions; 
		std::vector <glm::vec3> scales;
		std::vector <glm::vec4> rotations;
		std::vector <char> read_write; //0 = nothing, 1 = read, 2 = write
		int count = 0;
	};
	renderableInfo entityTransforms;

	float depthDiffWeight = 1;
	float normalDiffWeight = 1;
	glm::vec3 lightDirection = glm::vec3(1, -3, 1);
	float ambiantStrength = 1;
	float diffuseWeight = 0.3;
	int numQuantizedSplits = 10;
	glm::vec3 goochCool = glm::vec3(125 / 255.f, 249 / 255.f, 255 / 255.f);
	glm::vec3 goochWarm = glm::vec3(149 / 255.f, 53 / 255.f, 83 / 255.f);
	float goochStrength = 0.1f;

	//billboard default quad
	GLuint billboard_vertexArray;
	GLuint billboard_vertexBuffer;

	//instanced particle buffer
	GLuint particles_vertexArray;
	GLuint particles_instanceTransformBuffer;
	GLuint particles_quadVertexBuffer;

	//shader variables
	ShaderProgram modelShader;
	ShaderProgram lineShader;
	ShaderProgram wireframeShader;
	ShaderProgram gShader;
	ShaderProgram celShader;
	ShaderProgram shadowGShader;
	ShaderProgram VFXshader;
	ShaderProgram skyboxShader;
	ShaderProgram particleShader;
	//buffer for offscreen rendering
	//buffers
	GLuint gBuffer;
	GLuint gShadowBuffer;
	GLuint gVFXBuffer;
	//textures used in g buffer
	GLuint gDepth;
	GLuint gColor;
	GLuint gNormal;
	GLuint gPosition;
	GLuint gShadow;
	GLuint gVFXColor;
	GLuint gVFXDepth;
	//skybox texture
	GLuint skyboxCubemap;
	//texture used in shadow map calculation
	GLuint gLightDepth;
	//variables for rendering whole screen quad
	GLuint quad_vertexArray;
	GLuint quad_vertexBuffer;
	//variables for rendering the skybox
	GLuint skybox_vertexArray;
	GLuint skybox_vertexBuffer;

	glm::ivec2 windowSize;
	static void processNode(aiNode* node, const aiScene* scene, RenderModel& _component);
	static void processNode(aiNode* node, const aiScene* scene, CPU_Geometry& _geometry);

	//follo camera variables
	float follow_cam_x;
	float follow_cam_y;
	float follow_cam_z;
	float follow_correction_strength;
	float maximum_follow_distance;
	bool faceCulling;
	bool front_face;
	bool back_face;
};