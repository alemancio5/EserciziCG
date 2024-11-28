#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"

std::vector<SingleText> outText = {
	{2, {"Adding an object", "Press SPACE to save the screenshots","",""}, 0, 0},
	{1, {"Saving Screenshots. Please wait.", "", "",""}, 0, 0}
};

// The uniform buffer objects
#define NSHIP 16
struct BlinnUniformBufferObject {
	alignas(16) glm::mat4 mvpMat[NSHIP];
	alignas(16) glm::mat4 mMat[NSHIP];
	alignas(16) glm::mat4 nMat[NSHIP];
};

struct BlinnMatParUniformBufferObject {
	alignas(4)  float Power;
};

struct EmissionUniformBufferObject {
	alignas(16) glm::mat4 mvpMat;
};

struct GlobalUniformBufferObject {
	alignas(16) glm::vec3 lightDir;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 eyePos;
};

struct skyBoxUniformBufferObject {
	alignas(16) glm::mat4 mvpMat;
};

// **A10** Place here the CPP struct for the uniform buffer for the matrices
struct NewObjectMatricesUniformBufferObject {
    alignas(16) glm::mat4 mvpMat;
    alignas(16) glm::mat4 mMat;
    alignas(16) glm::mat4 nMat;
};

// **A10** Place here the CPP struct for the uniform buffer for the parameters
struct NewObjectParametersUniformBufferObject {
    alignas(4) float Pow;
    alignas(4) float Ang;
    alignas(4) float ShowCloud;
    alignas(4) float ShowTexture;
};



// The vertices data structures
struct BlinnVertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

struct EmissionVertex {
	glm::vec3 pos;
	glm::vec2 UV;
};

struct skyBoxVertex {
	glm::vec3 pos;
};

// **A10** Place here the CPP struct for the vertex definition
struct NewObjectVertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 UV;
    glm::vec4 tan;
};



// The main class
class A10 : public BaseProject {
	protected:
	
	// The descriptor set layouts ("classes" of what will be passed to the shaders)
	DescriptorSetLayout DSLGlobal;
	DescriptorSetLayout DSLBlinn;
	DescriptorSetLayout DSLEmission;
	DescriptorSetLayout DSLskyBox;
// **A10** Place here the variable for the descriptor set layouts
    DescriptorSetLayout DSLNewObject;  // For the new object that you're adding

	// Vertex formats
	VertexDescriptor VDBlinn;
	VertexDescriptor VDEmission;
	VertexDescriptor VDskyBox;
// **A10** Place here the variable for the new vertex descriptor
    VertexDescriptor VDNewObject;

	// Pipelines (shader couples)
	Pipeline PBlinn;
	Pipeline PEmission;
	Pipeline PskyBox;
// **A10** Place here the variable for the new pipeline
    Pipeline PNewObject;

	// Scenes and texts
    TextMaker txt;

	// Models, textures and descriptor sets (values assigned to the uniforms)
	DescriptorSet DSGlobal;
	
	Model Mship;
	Texture Tship;
	DescriptorSet DSship;
	
	Model Msun;
	Texture Tsun;
	DescriptorSet DSsun;
	
	Model MskyBox;
	Texture TskyBox, Tstars;
	DescriptorSet DSskyBox;

// **A10** Place here the variables for the model, the five texture (diffuse, specular, normal map, emission and clouds) and the descriptor set
    Model MNewObject; // New object model
    Texture TNewObjectDiffuse;   // New object's diffuse texture
    Texture TNewObjectSpecular;  // New object's specular texture
    Texture TNewObjectNormal;    // New object's normal map
    Texture TNewObjectEmission;  // New object's emission map
    Texture TNewObjectClouds;    // New object's cloud texture
    DescriptorSet DSNewObject;   // Descriptor set for the new object
	
	// Other application parameters
	int currScene = 0;
	int subpass = 0;
		
	glm::vec3 CamPos = glm::vec3(0.0, 0.1, 5.0);
	glm::mat4 ViewMatrix;

	float Ar;


	// Here you set the main application parameters
	void setWindowParameters() {
        windowWidth = 800;
		windowHeight = 600;
		windowTitle = "A10 - Adding an object";
    	windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.1f, 0.1f, 0.1f, 1.0f};
		Ar = (float)windowWidth / (float)windowHeight;
	}


    void onWindowResize(int w, int h) {
		std::cout << "Window resized to: " << w << " x " << h << "\n";
		Ar = (float)w / (float)h;
	}


	void localInit() {
        // Descriptor set layouts initializations
		DSLGlobal.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS, sizeof(GlobalUniformBufferObject), 1}
				});
		DSLBlinn.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(BlinnUniformBufferObject), 1},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
					{2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(BlinnMatParUniformBufferObject), 1}
				});
		DSLEmission.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(EmissionUniformBufferObject), 1},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1}
				});
		DSLskyBox.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(skyBoxUniformBufferObject), 1},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
					{2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1}
				  });
// **A10** Place here the initialization of the new descriptor set layout
        DSLNewObject.init(this, {
                {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, sizeof(NewObjectMatricesUniformBufferObject), 1},
                {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
                {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1},
                {3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 2, 1},
                {4, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 3, 1},
                {5, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 4, 1},
                {6, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(NewObjectParametersUniformBufferObject), 1},
        });

		// Vertex descriptors initialization
		VDBlinn.init(this, {
				  {0, sizeof(BlinnVertex), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(BlinnVertex, pos), sizeof(glm::vec3), POSITION},
				  {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(BlinnVertex, norm), sizeof(glm::vec3), NORMAL},
				  {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(BlinnVertex, UV), sizeof(glm::vec2), UV}
				});
		VDEmission.init(this, {
				  {0, sizeof(EmissionVertex), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(EmissionVertex, pos), sizeof(glm::vec3), POSITION},
				  {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(EmissionVertex, UV), sizeof(glm::vec2), UV}
				});
		VDskyBox.init(this, {
				  {0, sizeof(skyBoxVertex), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(skyBoxVertex, pos), sizeof(glm::vec3), POSITION}
				});
// **A10** Place here the initialization for the new vertex descriptor
        VDNewObject.init(this, {
                {0, sizeof(NewObjectVertex), VK_VERTEX_INPUT_RATE_VERTEX}
        }, {
                {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(NewObjectVertex, pos),sizeof(glm::vec3), POSITION},
                {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(NewObjectVertex, norm),sizeof(glm::vec3), NORMAL},
                {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(NewObjectVertex, UV),sizeof(glm::vec2), UV},
                {0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(NewObjectVertex, tan),sizeof(glm::vec4), TANGENT}
        });

		// Pipelines initializations
		PBlinn.init(this, &VDBlinn,  "shaders/BlinnVert.spv",    "shaders/BlinnFrag.spv", {&DSLGlobal, &DSLBlinn});
		PEmission.init(this, &VDEmission,  "shaders/EmissionVert.spv",    "shaders/EmissionFrag.spv", {&DSLEmission});
		PskyBox.init(this, &VDskyBox, "shaders/SkyBoxVert.spv", "shaders/SkyBoxFrag.spv", {&DSLskyBox});
		PskyBox.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
 								    VK_CULL_MODE_BACK_BIT, false);
// **A10** Place here the initialization of the pipeline. Remember that it should use shaders in files "shaders/NormalMapVert.spv" and "shaders/NormalMapFrag.spv", it should receive the new VertexDescriptor you defined and should receive two DescriptorSetLayout, the first should be DSLGlobal, while the other must be the one you defined
        PNewObject.init(this, &VDNewObject, "shaders/NormalMapVert.spv", "shaders/NormalMapFrag.spv", {&DSLGlobal, &DSLNewObject});

		// Create models
		Mship.init(this, &VDBlinn, "models/X-WING-baker.obj", OBJ);
		Msun.init(this, &VDEmission, "models/Sphere.obj", OBJ);
		MskyBox.init(this, &VDskyBox, "models/SkyBoxCube.obj", OBJ);
// **A10** Place here the loading of the model. It should be contained in file "models/Sphere.gltf", it should use the Vertex descriptor you defined, and be of GLTF format.
        MNewObject.init(this, &VDNewObject, "models/Sphere.gltf", GLTF);

		// Create the textures
		Tship.init(this, "textures/XwingColors.png");
		Tsun.init(this, "textures/2k_sun.jpg");
		TskyBox.init(this, "textures/starmap_g4k.jpg");
		Tstars.init(this, "textures/constellation_figures.png");
// **A10** Place here the loading of the four textures
		// Diffuse color of the planet in: "2k_earth_daymap.jpg"
        TNewObjectDiffuse.init(this, "textures/2k_earth_daymap.jpg");
		// Specular color of the planet in: "2k_earth_specular_map.png"
        TNewObjectSpecular.init(this, "textures/2k_earth_specular_map.png");
		// Normal map of the planet in: "2k_earth_normal_map.png". Note that it must add a special feature to support the normal map, in particular the init function should be the following: .init(this, "textures/2k_earth_normal_map.png", VK_FORMAT_R8G8B8A8_UNORM);
        TNewObjectNormal.init(this, "textures/2k_earth_normal_map.png", VK_FORMAT_R8G8B8A8_UNORM);
		// Emission map in: "2k_earth_nightmap.jpg"
        TNewObjectEmission.init(this, "textures/2k_earth_nightmap.jpg");
		// Clouds map in: "2k_earth_clouds.jpg"
        TNewObjectClouds.init(this, "textures/2k_earth_clouds.jpg");

		// Descriptor pool sizes
		// WARNING! Must be set before initializing the text and the scene
// **A10** Update the number of elements to correctly size the descriptor sets pool
        DPSZs.uniformBlocksInPool = 5 + 2;
        DPSZs.texturesInPool = 4 + 5;
        DPSZs.setsInPool = 4 + 1;

        std::cout << "Initializing text\n";
        txt.init(this, &outText);

		std::cout << "Initialization completed!\n";
		std::cout << "Uniform Blocks in the Pool  : " << DPSZs.uniformBlocksInPool << "\n";
		std::cout << "Textures in the Pool        : " << DPSZs.texturesInPool << "\n";
		std::cout << "Descriptor Sets in the Pool : " << DPSZs.setsInPool << "\n";
		
		ViewMatrix = glm::translate(glm::mat4(1), -CamPos);
	}


	void pipelinesAndDescriptorSetsInit() {
		// This creates a new pipeline (with the current surface), using its shaders
		PBlinn.create();
		PEmission.create();
		PskyBox.create();
// **A10** Add the pipeline creation
        PNewObject.create();

		// Here you define the data set
		DSship.init(this, &DSLBlinn, {&Tship});
		DSsun.init(this, &DSLEmission, {&Tsun});
		DSskyBox.init(this, &DSLskyBox, {&TskyBox, &Tstars});
// **A10** Add the descriptor set creation. Textures should be passed in the diffuse, specular, normal map, emission and clouds order.
        DSNewObject.init(this, &DSLNewObject, {&TNewObjectDiffuse, &TNewObjectSpecular, &TNewObjectNormal, &TNewObjectEmission, &TNewObjectClouds});
			
		DSGlobal.init(this, &DSLGlobal, {});

		txt.pipelinesAndDescriptorSetsInit();		
	}


	void pipelinesAndDescriptorSetsCleanup() {
		// Cleanup pipelines
		PBlinn.cleanup();
		PEmission.cleanup();
		PskyBox.cleanup();
// **A10** Add the pipeline cleanup
        PNewObject.cleanup();

        // Cleanup DSs
		DSship.cleanup();
		DSsun.cleanup();
		DSskyBox.cleanup();
		DSGlobal.cleanup();
// **A10** Add the descriptor set cleanup
        DSNewObject.cleanup();

		txt.pipelinesAndDescriptorSetsCleanup();
	}


	void localCleanup() {
        // Cleanup for models and textures
		Tship.cleanup();
		Mship.cleanup();
		Tsun.cleanup();
		Msun.cleanup();
		TskyBox.cleanup();
		Tstars.cleanup();
		MskyBox.cleanup();
// **A10** Add the cleanup for new models and textures
        TNewObjectDiffuse.cleanup();
        TNewObjectSpecular.cleanup();
        TNewObjectNormal.cleanup();
        TNewObjectEmission.cleanup();
        TNewObjectClouds.cleanup();
        MNewObject.cleanup();
		
		// Cleanup descriptor set layouts
		DSLBlinn.cleanup();
		DSLEmission.cleanup();
		DSLGlobal.cleanup();
		DSLskyBox.cleanup();
// **A10** Add the cleanup for the descriptor set layout
        DSLNewObject.cleanup();
		
		// Destroy the pipelines
		PBlinn.destroy();
		PEmission.destroy();
		PskyBox.destroy();
// **A10** Add the cleanup for the pipeline
        PNewObject.destroy();

		txt.localCleanup();		
	}


	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
		// Binds the pipeline
		PBlinn.bind(commandBuffer);
		
		// The models (both index and vertex buffers)
		Mship.bind(commandBuffer);
		
		// The descriptor sets, for each descriptor set specified in the pipeline
		DSGlobal.bind(commandBuffer, PBlinn, 0, currentImage);	// For global, at 0
		DSship.bind(commandBuffer, PBlinn, 1, currentImage);	// For material and position, at 1
					
		// The actual draw call
		vkCmdDrawIndexed(commandBuffer,static_cast<uint32_t>(Mship.indices.size()), NSHIP, 0, 0, 0);
		PEmission.bind(commandBuffer);
		Msun.bind(commandBuffer);
		DSsun.bind(commandBuffer, PEmission, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,static_cast<uint32_t>(Msun.indices.size()), 1, 0, 0, 0);

		PskyBox.bind(commandBuffer);
		MskyBox.bind(commandBuffer);
		DSskyBox.bind(commandBuffer, PskyBox, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,static_cast<uint32_t>(MskyBox.indices.size()), 1, 0, 0, 0);

// **A10** Add the commands to bind the pipeline, the mesh its two descriptor sets, and the draw call of the planet
        PNewObject.bind(commandBuffer);
        MNewObject.bind(commandBuffer);
        DSGlobal.bind(commandBuffer, PNewObject, 0, currentImage);
        DSNewObject.bind(commandBuffer, PNewObject, 1, currentImage);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(MNewObject.indices.size()), 1, 0, 0, 0);

		txt.populateCommandBuffer(commandBuffer, currentImage, currScene);
	}


	void updateUniformBuffer(uint32_t currentImage) {
		static bool debounce = false;
		static int curDebounce = 0;

		float deltaT;
		glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
		bool fire = false;
		getSixAxis(deltaT, m, r, fire);
		
		static float autoTime = true;
		static float cTime = 0.0;
		const float turnTime = 72.0f;
		const float angTurnTimeFact = 2.0f * M_PI / turnTime;
		
		if(autoTime) {
			cTime = cTime + deltaT;
			cTime = (cTime > turnTime) ? (cTime - turnTime) : cTime;
		}

		static float tTime = 0.0;
		const float TturnTime = 60.0f;
		const float TangTurnTimeFact = 1.0f / TturnTime;
		
		if(autoTime) {
			tTime = tTime + deltaT;
			tTime = (tTime > TturnTime) ? (tTime - TturnTime) : tTime;
		}
		
		const float ROT_SPEED = glm::radians(120.0f);
		const float MOVE_SPEED = 2.0f;
		
		static float ShowCloud = 1.0f;
		static float ShowTexture = 1.0f;
		
        // Update the fly model
		ViewMatrix = glm::rotate(glm::mat4(1), ROT_SPEED * r.x * deltaT,glm::vec3(1, 0, 0)) * ViewMatrix;
		ViewMatrix = glm::rotate(glm::mat4(1), ROT_SPEED * r.y * deltaT,glm::vec3(0, 1, 0)) * ViewMatrix;
		ViewMatrix = glm::rotate(glm::mat4(1), -ROT_SPEED * r.z * deltaT,glm::vec3(0, 0, 1)) * ViewMatrix;
		ViewMatrix = glm::translate(glm::mat4(1), -glm::vec3(MOVE_SPEED * m.x * deltaT, MOVE_SPEED * m.y * deltaT, MOVE_SPEED * m.z * deltaT)) * ViewMatrix;
		static float subpassTimer = 0.0;

		if(glfwGetKey(window, GLFW_KEY_SPACE)) {
			if(!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_SPACE;
				if(currScene != 1) {
					currScene = (currScene+1) % outText.size();
				}
				if(currScene == 1) {
					if(subpass >= 4) {
						currScene = 0;
					}
				}
				std::cout << "Scene : " << currScene << "\n";
				RebuildPipeline();
			}
		} else {
			if((curDebounce == GLFW_KEY_SPACE) && debounce) {
				debounce = false;
				curDebounce = 0;
			}
		}

		// Standard procedure to quit when the ESC key is pressed
		if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if(glfwGetKey(window, GLFW_KEY_V)) {
			if(!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_V;
				printMat4("ViewMatrix  ", ViewMatrix);				
				std::cout << "cTime    = " << cTime    << ";\n";
				std::cout << "tTime    = " << tTime    << ";\n";
				std::cout << "ShowCloud    = " << ShowCloud    << ";\n";
				std::cout << "ShowTexture    = " << ShowTexture    << ";\n";
			}
		} else {
			if((curDebounce == GLFW_KEY_V) && debounce) {
				debounce = false;
				curDebounce = 0;
			}
		}

		if(glfwGetKey(window, GLFW_KEY_C)) {
			if(!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_C;
				ShowCloud = 1.0f - ShowCloud;
			}
		} else {
			if((curDebounce == GLFW_KEY_C) && debounce) {
				debounce = false;
				curDebounce = 0;
			}
		}

		if(glfwGetKey(window, GLFW_KEY_T)) {
			if(!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_T;
				ShowTexture = 1.0f - ShowTexture;
			}
		} else {
			if((curDebounce == GLFW_KEY_T) && debounce) {
				debounce = false;
				curDebounce = 0;
			}
		}
	
		if(currScene == 1) {
            switch(subpass) {
			    case 0:
                    ViewMatrix = glm::mat4(-0.0656882, -0.162777, 0.984474, 0, 0.0535786, 0.984606, 0.166374, 0, -0.996401, 0.0636756, -0.0559558, 0, 0.0649244, -0.531504, -3.26128, 1);
                    cTime = 22.3604;
                    tTime = 22.3604;
                    ShowCloud = 1;
                    ShowTexture = 1;
                    autoTime = false;
                    break;
			    case 1:
                    ViewMatrix = glm::mat4(-0.312507, -0.442291, 0.840666, 0, 0.107287, 0.862893, 0.493868, 0, -0.943837, 0.24453, -0.222207, 0, -0.0157694, -0.186147, -1.54649, 1);
                    cTime = 38.9919;
                    tTime = 38.9919;
                    ShowCloud = 0;
                    ShowTexture = 1;
				    break;
			    case 2:
                    ViewMatrix = glm::mat4(-0.992288, 0.00260993, -0.12393, 0, -0.0396232, 0.940648, 0.337063, 0, 0.117454, 0.339374, -0.93329, 0, 0.0335061, -0.0115242, -2.99662, 1);
                    cTime = 71.0587;
                    tTime = 11.0587;
                    ShowCloud = 1;
                    ShowTexture = 1;
			    	break;
			    case 3:
                    ViewMatrix = glm::mat4(0.0942192, -0.242781, 0.965495, 0, 0.560756, 0.814274, 0.150033, 0, -0.822603, 0.527272, 0.212861, 0, -0.567191, -0.254532, -1.79143, 1);
                    cTime = 55.9355;
                    tTime = 7.93549;
                    ShowCloud = 1;
                    ShowTexture = 0;
				    break;
			}
		}
		
		if(currScene == 1) {
			subpassTimer += deltaT;
			if(subpassTimer > 4.0f) {
				subpassTimer = 0.0f;
				subpass++;
				std::cout << "Scene : " << currScene << " subpass: " << subpass << "\n";
				char buf[20];
				sprintf(buf, "A10_%d.png", subpass);
				saveScreenshot(buf, currentImage);
				if(subpass == 4) {
					ViewMatrix = glm::translate(glm::mat4(1), -CamPos);
					cTime = 0;
					tTime = 0;
					ShowCloud = 1;
					ShowTexture = 1;
					autoTime = true;
					currScene = 0;
					std::cout << "Scene : " << currScene << "\n";
					RebuildPipeline();
				}
			}
		}

		// Here is where you actually update your uniforms
		glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 160.0f);
		M[1][1] *= -1;

		glm::mat4 Mv = ViewMatrix;

		glm::mat4 ViewPrj =  M * Mv;
		glm::mat4 baseTr = glm::mat4(1.0f);								

		// Updates global uniforms
        GlobalUniformBufferObject gubo{};
		gubo.lightDir = glm::vec3(cos(glm::radians(135.0f)) * cos(cTime * angTurnTimeFact), sin(glm::radians(135.0f)), cos(glm::radians(135.0f)) * sin(cTime * angTurnTimeFact));
		gubo.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.eyePos = glm::vec3(glm::inverse(ViewMatrix) * glm::vec4(0, 0, 0, 1));
		DSGlobal.map(currentImage, &gubo, 0);

		// Objects
		BlinnUniformBufferObject blinnUbo{};
		BlinnMatParUniformBufferObject blinnMatParUbo{};

		for(int j = 0; j < 4; j++) {
			for(int k = 0; k < 4; k++) {
				int i = j*4+k;
				blinnUbo.mMat[i] = glm::translate(glm::mat4(1),glm::vec3((k-1)*5+((j+5)*3+10)*cos(j*1.4),(j-1)*5+((k+5)*2.5+10)*sin(j*1.4)*cos(i*0.2),((k+2.5)*3.2+8)*sin(j*1.4)*sin(k*0.2))) * glm::scale(glm::mat4(1), glm::vec3(0.5,0.5,0.5)) * baseTr;
				blinnUbo.mvpMat[i] = ViewPrj * blinnUbo.mMat[i];
				blinnUbo.nMat[i] = glm::inverse(glm::transpose(blinnUbo.mMat[i]));
			}
		}
		DSship.map(currentImage, &blinnUbo, 0);

		blinnMatParUbo.Power = 200.0;
		DSship.map(currentImage, &blinnMatParUbo, 2);

		EmissionUniformBufferObject emissionUbo{};
		emissionUbo.mvpMat = ViewPrj * glm::translate(glm::mat4(1), gubo.lightDir * 40.0f) * baseTr;
		DSsun.map(currentImage, &emissionUbo, 0);
		
		skyBoxUniformBufferObject sbubo{};
		sbubo.mvpMat = M * glm::mat4(glm::mat3(Mv));
		DSskyBox.map(currentImage, &sbubo, 0);
		
// **A10** Add to compute the uniforms and pass them to the shaders. You need two uniforms: one for the matrices, and the other for the material parameters
        NewObjectMatricesUniformBufferObject uboNewMat{};
        NewObjectParametersUniformBufferObject uboNewPar{};

        // World and normal matrix should be the identity. The World-View-Projection should be variable ViewPrj
        uboNewMat.mvpMat = ViewPrj;
        uboNewMat.mMat = glm::mat4(1.0f);
        uboNewMat.nMat = glm::mat4(1.0f);

		// These informations should be used to fill the uniform buffer object in binding 0 of your DSL
        DSNewObject.map(currentImage, &uboNewMat, 0);

		// The specular power of the uniform buffer containing the material parameters of the new object should be set to:
		// XXX.Power = 200.0
        uboNewPar.Pow = 200.0;

		// The texture angle parameter of the uniform buffer containing the material parameters of the new object should be set to: tTime * TangTurnTimeFact
		// XXX.Ang = tTime * TangTurnTimeFact;
        uboNewPar.Ang = tTime * TangTurnTimeFact;

		// The selector for showing the clouds of the uniform buffer containing the material parameters of the new object should be set to:
		// XXX.ShowCloud = ShowCloud
        uboNewPar.ShowCloud = ShowCloud;

		// The selector for showing the clouds of the uniform buffer containing the material parameters of the new object should be set to:
		// XXX.ShowTexture = ShowTexture
        uboNewPar.ShowTexture = ShowTexture;

		// These informations should be used to fill the Uniform Buffer Object in Binding 6 of your DSL
        DSNewObject.map(currentImage, &uboNewPar, 6);
	}
};



// This is the main: probably you do not need to touch this!
int main() {
    A10 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}