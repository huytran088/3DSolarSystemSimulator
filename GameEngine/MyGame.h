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

		//******************************************* Sun
		// Create a container to hold the sun
		GameObject* sunGO = new GameObject(); 

		// Create a "yellow" material for the sun
		Material sunMat;
		sunMat.diffuseMat = YELLOW_RGBA;

		// Assign the texture as the diffuse texture for the sphere
		sunMat.setDiffuseTexture(Texture::GetTexture("Textures/2k_sun.jpg")->getTextureObject());
		sunMat.setTextureMode(DECAL);

		// Instantiate a sphere shaped sun
		auto* sun = new SphereMeshComponent(shaderProgram, sunMat, 7.5f);
		//auto* shipModel1 = new ModelMeshComponent("jet_models/F-15C_Eagle.3ds", shaderProgram);
		//sunGO->setScale(vec3(2.0f, 2.0f, 2.0f), LOCAL);

		// Add the sun to a GameObject
		sunGO->addComponent(sun); 
		//sunGO->addComponent(new MakeVisableComponent(GLFW_KEY_C));
		//sunGO->addComponent(new SpinComponent(120.0f));

		/*******************************************/

		//******************************************* Earth
		// Create a empty spin GameObject
		auto* earthOrbitGO = new GameObject();
		earthOrbitGO->addComponent(new SpinComponent(11.4f));
		
		// Add the empty translate GO to the earth
		auto* earthLocationGameObject = new GameObject();
		earthOrbitGO->addChildGameObject(earthLocationGameObject);
		earthLocationGameObject->setPosition(vec3(26.25f, 0.0f, 0.0f), LOCAL);

		
		// Create a container to hold the earth
		GameObject* earthGO = new GameObject();
		// Add the earthGO as the child of the spin object
		earthLocationGameObject->addChildGameObject(earthGO);
		earthGO->addComponent(new SpinComponent(1.145f));
		// Create a material for the earth
		Material earthMat;
		earthMat.diffuseMat = BLUE_RGBA;

		// Assign the texture as the diffuse texture for the sphere
		earthMat.setDiffuseTexture(Texture::GetTexture("Textures/2k_earth_daymap.jpg")->getTextureObject());

		// Instantiate a sphere shaped earth
		auto* earth = new SphereMeshComponent(shaderProgram, earthMat, 2.0f);

		// Add the earth to a GameObject
		earthGO->addComponent(earth);
		/*******************************************/
		
		//******************************************* Moon
		// Add the empty spin GO to the moon
		auto* moonOrbitGO = new GameObject();
		earthLocationGameObject->addChildGameObject(moonOrbitGO);
		moonOrbitGO->addComponent(new SpinComponent(-152.4f));

		auto* moonGO = new GameObject();
		moonOrbitGO->addChildGameObject(moonGO);
		moonGO->setPosition(vec3(3.0f, 0.0f, 0.0f), LOCAL);
		moonGO->addComponent(new SpinComponent(-14.09f));

		Material moonMat;
		moonMat.diffuseMat = WHITE_RGBA;
		// Assign the texture as the diffuse texture for the sphere
		moonMat.setDiffuseTexture(Texture::GetTexture("Textures/2k_moon.jpg")->getTextureObject());
		// Instantiate a sphere shaped moon
		auto * moon = new SphereMeshComponent(shaderProgram, moonMat, 0.5f);
		// Add the moon to the moonGO
		moonGO->addComponent(moon);
		/*******************************************/

		//******************************************* Mars
		// Add the empty spin to Mars
		auto* marsOrbitGO = new GameObject();
		marsOrbitGO->addComponent(new SpinComponent(6.1f));

		// Add the empty translate GO to the earth
		auto* marsLocationGameObject = new GameObject();
		marsOrbitGO->addChildGameObject(marsLocationGameObject);
		marsLocationGameObject->setPosition(vec3(37.5f, 0.0f, 0.0f), LOCAL);


		// Create a container to hold the earth
		GameObject* marsGO = new GameObject();
		// Add the earthGO as the child of the spin object
		marsLocationGameObject->addChildGameObject(marsGO);
		marsGO->addComponent(new SpinComponent(0.87f));
		// Create a material for the earth
		Material marsMat;
		marsMat.diffuseMat = RED_RGBA;

		// Assign the texture as the diffuse texture for the sphere
		marsMat.setDiffuseTexture(Texture::GetTexture("Textures/2k_mars.jpg")->getTextureObject());

		// Instantiate a sphere shaped earth
		auto* mars = new SphereMeshComponent(shaderProgram, marsMat, 1.0f);

		// Add the earth to a GameObject
		marsGO->addComponent(mars);
		/*******************************************/

		//******************************************* Moon Phobos
		// Add the empty spin GO to the moon
		auto* phobosOrbitGO = new GameObject();
		marsLocationGameObject->addChildGameObject(phobosOrbitGO);
		phobosOrbitGO->addComponent(new SpinComponent(-123.4f));

		auto* phobosGO = new GameObject();
		phobosOrbitGO->addChildGameObject(phobosGO);
		phobosGO->setPosition(vec3(1.5f, 0.0f, 0.0f), LOCAL);
		phobosGO->addComponent(new SpinComponent(-3.435f));

		Material phobosMat;
		phobosMat.diffuseMat = WHITE_RGBA;
		// Assign the texture as the diffuse texture for the sphere
		phobosMat.setDiffuseTexture(Texture::GetTexture("Textures/phobos.jpg")->getTextureObject());
		// Instantiate a sphere shaped moon
		auto* phobos = new SphereMeshComponent(shaderProgram, phobosMat, 0.5f);
		// Add the moon to the moonGO
		phobosGO->addComponent(phobos);
		/*******************************************/

		//******************************************* Moon Deimos
		// Add the empty spin GO to the moon
		auto* deimosOrbitGO = new GameObject();
		marsLocationGameObject->addChildGameObject(deimosOrbitGO);
		deimosOrbitGO->addComponent(new SpinComponent(-18.45f));

		auto* deimosGO = new GameObject();
		deimosOrbitGO->addChildGameObject(deimosGO);
		deimosGO->setPosition(vec3(3.2f, 0.0f, 0.0f), LOCAL);
		deimosGO->addComponent(new SpinComponent(-0.916f));

		Material deimosMat;
		deimosMat.diffuseMat = WHITE_RGBA;
		// Assign the texture as the diffuse texture for the sphere
		deimosMat.setDiffuseTexture(Texture::GetTexture("Textures/phobos.jpg")->getTextureObject());
		// Instantiate a sphere shaped moon
		auto* deimos = new SphereMeshComponent(shaderProgram, deimosMat, 0.5f);
		// Add the moon to the moonGO
		deimosGO->addComponent(deimos);
		/*******************************************/

		//******************************************* Venus
		// Add the empty spin to Venus
		auto* venusOrbitGO = new GameObject();
		venusOrbitGO->addComponent(new SpinComponent(18.24f));

		// Add the empty translate GO to the earth
		auto* venusLocationGameObject = new GameObject();
		venusOrbitGO->addChildGameObject(venusLocationGameObject);
		venusLocationGameObject->setPosition(vec3(17.5f, 0.0f, 0.0f), LOCAL);


		// Create a container to hold the earth
		GameObject* venusGO = new GameObject();
		// Add the earthGO as the child of the spin object
		venusLocationGameObject->addChildGameObject(venusGO);
		venusGO->addComponent(new SpinComponent(0.04f));
		// Create a material for the earth
		Material venusMat;
		venusMat.diffuseMat = vec4(1.0f, 1.0f, 0.0f, 0.0f);

		// Assign the texture as the diffuse texture for the sphere
		venusMat.setDiffuseTexture(Texture::GetTexture("Textures/2k_venus_atmosphere.jpg")->getTextureObject());

		// Instantiate a sphere shaped earth
		auto* venus = new SphereMeshComponent(shaderProgram, venusMat, 1.875f);

		// Add the earth to a GameObject
		venusGO->addComponent(venus);
		/*******************************************/

		//******************************************* Spaceship
		auto* shipGO = new GameObject();
		auto* shipLocationGO = new GameObject();
		shipGO->addChildGameObject(shipLocationGO);
		shipLocationGO->setRotation(glm::rotate(-PI_OVER_2, UNIT_X_V3), LOCAL);
		//shipGO->setScale(vec3(0.5f, 0.5f, 0.5f), LOCAL);
		auto* shipModel = new ModelMeshComponent("jet_models/F-15C_Eagle.3ds", shaderProgram);
		shipLocationGO->setScale(vec3(0.7f, 0.7f, 0.7f));
		shipLocationGO->addComponent(shipModel);
		shipGO->addComponent(new TranslateComponent(vec3(3.0f, 0.0f, 0.0f)));\
		shipGO->addComponent(new SteerComponent(45.0f));
		/*******************************************/

		//******************************************* Space Travel
		// Waypoints of planets
		std::vector<GameObject*> solarWaypoints;
		// Push back the location of the ship, the sun, and the planets
		solarWaypoints.push_back(shipGO);
		solarWaypoints.push_back(sunGO);
		solarWaypoints.push_back(earthGO);
		solarWaypoints.push_back(marsGO);
		solarWaypoints.push_back(venusGO);
		SpaceTravelComponent* solarTravel = new SpaceTravelComponent(solarWaypoints, vec3(5.0f, 0.0f, 0.0f));
		shipGO->addComponent(solarTravel);
		/*******************************************/

		// Light object
		GameObject* lightObject = new GameObject();  

		// Set up the positional light
		auto* posLightComponent = new PositionalLightComponent(GLFW_KEY_P);
		posLightComponent->setAmbientColor(vec4(0.5f, 0.5f, 0.5f, 1.0f));
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
		/*lightObject->addComponent(dirLightComponent);
		lightObject->addComponent(spotLightComponent);*/

		// Camera object #1
		auto* cameraObject1 = new GameObject();
		auto* camera1 = new CameraComponent(0, 90.0f);
		camera1->setViewPort(0.0f, 0.5f, 1.0f, 0.5f);
		camera1->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		// Add the camera to the object
		cameraObject1->addComponent(camera1);
		// Camera object #2
		auto* cameraObject2 = new GameObject();
		auto* camera2 = new CameraComponent(1, 100.0f);
		camera2->setViewPort(0.0f, 0.0f, 1.0f, 0.5f);
		camera2->setCameraClearColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
		cameraObject2->addComponent(camera2);

		// Sound components for the sun
		auto* sunSoundSource = new SoundSourceComponent("Sounds/enter_sandman.wav", 4.0f, 3.0f, 8.0f);
		sunSoundSource->play();
		sunSoundSource->setLooping(true);
		sunSoundSource->setGain(0.25f);
		sunGO->addComponent(sunSoundSource);

		// Sound components for the earth
		auto* earthSoundSource = new SoundSourceComponent("Sounds/paranoid.wav", 2.0f, 2.0f, 4.0f);
		earthSoundSource->play();
		earthSoundSource->setLooping(true);
		earthSoundSource->setGain(0.15f);
		earthGO->addComponent(earthSoundSource);

		// Sound components for the mars
		auto* marsSoundSource = new SoundSourceComponent("Sounds/children_of_the_damned.wav", 2.0f, 2.0f, 4.0f);
		marsSoundSource->play();
		marsSoundSource->setLooping(true);
		marsSoundSource->setGain(0.1f);
		marsGO->addComponent(marsSoundSource);

		// Sound components for the venus
		auto* venusSoundSource = new SoundSourceComponent("Sounds/speak_english_or_die.wav", 1.0f, 4.0f, 4.0f);
		venusSoundSource->play();
		venusSoundSource->setLooping(true);
		venusSoundSource->setGain(0.25f);
		venusGO->addComponent(venusSoundSource);

		// Sound Listener for the ship
		auto* listener = new SoundListenerComponent();
		shipGO->addComponent(listener);

		// Add the game objects to the game
		// Solar system
		this->addChildGameObject(sunGO);
		this->addChildGameObject(earthOrbitGO);
		this->addChildGameObject(marsOrbitGO);
		this->addChildGameObject(venusOrbitGO);
		// Spaceship
		this->addChildGameObject(shipGO);
		// Light is the sun's center
		sunGO->addChildGameObject(lightObject);
		// Camera
		this->addChildGameObject(cameraObject1);
		shipGO->addChildGameObject(cameraObject2);

		// Rotate the sun object
		sunGO->setRotation(glm::rotate(PI / 4.0f, UNIT_Y_V3)); 
		// Set the position of the ship
		shipGO->setPosition(vec3(20.0f, 0.0f, 0.0f));
		//shipGO->setRotation(glm::rotate(PI, UNIT_X_V3)* glm::rotate(PI, UNIT_Y_V3));
		//lightObject->setPosition(vec3(0.0f, 0.0f, 0.0f), WORLD);
		// Set the position/rotation of the camera
		cameraObject1->setPosition(vec3(0.0f, 40.0f, 0.0f));
		cameraObject1->setRotation(glm::rotate(-PI_OVER_2, UNIT_X_V3), LOCAL);
		cameraObject2->setPosition(vec3(0.0f, 5.0f, 10.0f), LOCAL);
		//cameraObject2->setRotation(glm::rotate(-PI/9, UNIT_X_V3), LOCAL);
	}; // end loadScene

	virtual void processGameInput() override
	{
		// Call the super class method
		Game::processGameInput();
	}
};
