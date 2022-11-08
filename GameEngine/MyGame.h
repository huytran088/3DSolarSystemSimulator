#pragma once

#include "GameEngine.h" 

class MyGame : public Game
{

public:

	MyGame(std::string windowTitle = "Project 3")
		: Game(windowTitle)
	{}

protected:

	virtual void loadScene() override
	{
		// Build shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/perPixelLightingfragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		// Build the shader program
		GLuint shaderProgram = BuildShaderProgram(shaders);	

		// Set up the uniform bufferes and blocks
		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedTransformations::setUniformBlockForShader(shaderProgram);
		SharedLighting::setUniformBlockForShader(shaderProgram);

		// Set the clear color for the rendering window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Create a container to hold the box
		GameObject* firstGameObject = new GameObject(); //******************* Week 8 ********************

		// Create a "blue" material for a cylinder
		Material sphereMat;
		sphereMat.diffuseMat = BLUE_RGBA;

		// Assign the texture as the diffuse texture for the sphere
		sphereMat.setDiffuseTexture(Texture::GetTexture("Textures/sun.jpg")->getTextureObject());

		// Instantiate a sphere shaped mesh
		auto* sphere = new SphereMeshComponent(shaderProgram, sphereMat);

		// Add the sphere to a GameObject
		firstGameObject->addComponent(sphere); 
		firstGameObject->addComponent(new ArrowRotateComponent(100));
		firstGameObject->addComponent(new MakeVisableComponent(GLFW_KEY_C));
		firstGameObject->addComponent(new ContinuousRotateComponent(20.0f, UNIT_Z_V3));

		// Waypoints
		std::vector<vec3> waypoints;
		waypoints.push_back(vec3(2.0f, 0.0f, 2.0f));
		waypoints.push_back(vec3(0.0f, 0.0f, 2.0f));
		waypoints.push_back(vec3(-2.0f, 0.0f, 3.0f));
		waypoints.push_back(vec3(-3.0f, 0.0f, -2.0f));

		// Light object
		GameObject* lightObject = new GameObject();  

		// Set up the positional light
		auto* posLightComponent = new PositionalLightComponent(GLFW_KEY_P);
		posLightComponent->setAmbientColor(vec4(0.1f, 0.1f, 0.1f, 1.0f));
		posLightComponent->setDiffuseColor(WHITE_RGBA);
		//posLightComponent->setAttenuationFactors(0.5f);

		// Set up the directional light
		auto* dirLightComponent = new DirectionalLightComponent(GLFW_KEY_D);
		dirLightComponent->setAmbientColor(vec4(0.1f, 0.1f, 0.1f, 1.0f));
		dirLightComponent->setDiffuseColor(WHITE_RGBA);

		// Set up the spot light
		auto* spotLightComponent = new SpotLightComponent(GLFW_KEY_S);
		spotLightComponent->setCutoffAngleInDegrees(120.0f);
		spotLightComponent->setAmbientColor(vec4(0.1f, 0.1f, 0.1f, 1.0f));
		spotLightComponent->setDiffuseColor(WHITE_RGBA);

		// Add light components to light objects
		lightObject->addComponent(posLightComponent);
		lightObject->addComponent(dirLightComponent);
		lightObject->addComponent(spotLightComponent);

		// Camera object #1
		auto* cameraObject1 = new GameObject();
		auto* camera1 = new CameraComponent(0, 60.0f);
		// Add the camera to the object
		cameraObject1->addComponent(camera1);
		// Camera object #2
		auto* cameraObject2 = new GameObject();
		auto* camera2 = new CameraComponent(1, 45.0f);
		camera2->setViewPort(0.0f, 0.7f, 0.3f, 0.3f);
		cameraObject2->addComponent(camera2);

		// Sound components for the sun
		auto* soundSource = new SoundSourceComponent("Sounds/ambient.wav");
		soundSource->play();
		soundSource->setLooping(true);
		auto* soundListener = new SoundListenerComponent();
		firstGameObject->addComponent(soundSource);

		// Add the game objects to the game
		this->addChildGameObject(firstGameObject);
		this->addChildGameObject(lightObject);
		this->addChildGameObject(cameraObject1);
		this->addChildGameObject(cameraObject2);

		// Rotate the box game object that contains the cube
		firstGameObject->setRotation(glm::rotate(PI / 4.0f, UNIT_Y_V3)); //******************* Week 8 ********************
		lightObject->setPosition(vec3(1.0f, 5.0f, 0.0f));
		// Set the position/rotation of the camera
		cameraObject1->setPosition(vec3(0.0f, 15.0f, 0.0f), LOCAL);
		cameraObject1->setRotation(glm::rotate(-PI_OVER_2, UNIT_X_V3), LOCAL);
		cameraObject2->setPosition(vec3(5.0f, 40.0f, 0.0f));
		cameraObject2->setRotation(glm::rotate(-PI_OVER_2, UNIT_X_V3));
	}; // end loadScene

	virtual void processGameInput() override
	{
		// Call the super class method
		Game::processGameInput();
	}
};
