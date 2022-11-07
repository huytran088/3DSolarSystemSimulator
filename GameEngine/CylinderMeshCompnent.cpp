#include "CylinderMeshCompnent.h"

// Constructor
CylinderMeshComponent::CylinderMeshComponent(GLuint shaderProgram, Material mat,
	float radius, float height, int stacks,
	int slices, int updateOrder) :
	cylinderMat(mat), MeshComponent(shaderProgram, updateOrder), radius(radius),
	height(height), stacks(stacks), slices(slices)
{}  // end constructor



void CylinderMeshComponent::buildMesh() {

	// Cylinder's name
	this->scaleMeshName = "Cylinder" + std::to_string(radius) + std::to_string(height) +
		std::to_string(stacks) + std::to_string(slices) + std::to_string(this->cylinderMat._id);

	if (previsouslyLoaded() == false) {
		// Storing vertex's data & indices
		std::vector<pntVertexData> pnt;
		std::vector<unsigned int> indices;
		// Variables to keep track of current height and angle after each iteration
		float stackCounter = -this->height / 2.0f;
		float sliceAngle = 0.0f;

		// Slice angle increment
		const float sliceInc = (2 * PI) / this->slices;
		// Stack height increment
		const float stackInc = this->height / this->stacks;

		//int outerLoopCounter = 0;
		int loopCount = 0;

		// Build the bottom circle
		buildBotCircle();
		// Build the top circle
		buildTopCircle();
		// Loop over slices first, then build up stacks
		for (int i = 0; i < stacks; i++) {
			// Positions
			vec4 v0 = vec4(cos(sliceAngle) * radius, stackCounter + stackInc, sin(sliceAngle) * radius, 1.0f);
			vec4 v1 = vec4(cos(sliceAngle) * radius, stackCounter, sin(sliceAngle) * radius, 1.0f);
			// Normals
			vec3 normal = normalize(vec3(cos(sliceAngle), 0, sin(sliceAngle)));
			// Textures
			vec2 t0 = vec2(sliceAngle / (2 * PI), (stackCounter + stackInc + height / 2) / height);
			vec2 t1 = vec2(sliceAngle / (2 * PI), (stackCounter + height / 2) / height);
			// Define the vertex data objects
			pntVertexData pnt0(v0, normal, t0);
			pntVertexData pnt1(v1, normal, t1);
		
			for (int j = 0; j < slices; j++) {
				auto offset = pnt.size();
				// Update the slice angle and normal
				sliceAngle += sliceInc;
				normal = normalize(vec3(cos(sliceAngle), 0, sin(sliceAngle)));
				vec4 v2 = vec4(cos(sliceAngle) * radius, stackCounter, sin(sliceAngle) * radius, 1.0f);
				vec4 v3 = vec4(cos(sliceAngle) * radius, stackCounter + stackInc, sin(sliceAngle) * radius, 1.0f);
				// Textures
				vec2 t2 = vec2(sliceAngle / (2 * PI), (stackCounter + height / 2) / height);
				vec2 t3 = vec2(sliceAngle / (2 * PI), (stackCounter + stackInc + height / 2) / height);

				pntVertexData pnt2(v2, normal, t2);
				pntVertexData pnt3(v3, normal, t3);

				// Cylinder's side
				pnt.push_back(pnt0);
				pnt.push_back(pnt1);
				pnt.push_back(pnt2);
				pnt.push_back(pnt3);

				// Push indices
				indices.push_back(0 + 4 * loopCount);
				indices.push_back(3 + 4 * loopCount);
				indices.push_back(1 + 4 * loopCount);
				indices.push_back(1 + 4 * loopCount);
				indices.push_back(3 + 4 * loopCount);
				indices.push_back(2 + 4 * loopCount);
				

				// Update to the next slice before continuing
				pnt0 = pnt3;
				pnt1 = pnt2;
				loopCount++;
			}
			// Update the stack's height before continuing.
			stackCounter += stackInc;
		}
	
		//SubMesh cylinderMesh = MeshComponent::buildSubMesh(pnt, indices);
		SubMesh cylinderMesh = MeshComponent::buildSubMesh(pnt, indices);

		// Set the primitive mode for the vertex data
		cylinderMesh.primitiveMode = GL_TRIANGLES;

		// Set the material
		cylinderMesh.material = this->cylinderMat;

		// Push the submesh into vector of Submeshes to be rendered
		this->subMeshes.push_back(cylinderMesh);

		this->saveInitialLoad();
	}


}

void CylinderMeshComponent::buildTopCircle()
{
	// Storing vertex's data & indices
	std::vector<pntVertexData> pnt;
	std::vector<unsigned int> indices;
	float sliceAngle = 0.0f;
	// Slice angle increment
	const float sliceInc = (2 * PI) / this->slices;
	// Centers of top circle
	vec4 topCenter = vec4(0.0f, this->height / 2, 0.0f, 1.0f);
	// Normals for top center
	vec3 topNormal = vec3(0.0f, 1.0f, 0.0f);
	// Texture Coords for top center
	vec2 topTexture = vec2(0.5, 0.5);

	pntVertexData pntTop(topCenter, topNormal, topTexture);
	pnt.push_back(pntTop);

	for (int i = 0; i < this->slices + 1; i++) {
		vec4 v0Top = vec4(cos(sliceAngle) * radius, this->height / 2, sin(sliceAngle) * radius, 1.0f);
		vec3 normal = normalize(vec3(cos(sliceAngle), 0, sin(sliceAngle)));
		// Texture
		vec2 topTexture = vec2(0.5 * (1 - glm::cos(sliceAngle)), 0.5 * (1 - glm::sin(sliceAngle)));
		pntVertexData pnt0Top(v0Top, normal, topTexture);

		pnt.push_back(pnt0Top);

		indices.push_back(0);
		indices.push_back(i + 2);
		indices.push_back(i + 1);
		// Update the slice angle and normal
		sliceAngle += sliceInc;
	}

	SubMesh topMesh = MeshComponent::buildSubMesh(pnt, indices);

	// Set the primitive mode for the vertex data
	topMesh.primitiveMode = GL_TRIANGLES;

	// Set the material
	topMesh.material = this->cylinderMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(topMesh);

	this->saveInitialLoad();
}

void CylinderMeshComponent::buildBotCircle()
{
	// Storing vertex's data & indices
	std::vector<pntVertexData> pnt;
	std::vector<unsigned int> indices;
	float sliceAngle = 0.0f;
	// Slice angle increment
	const float sliceInc = (2 * PI) / this->slices;
	// Centers of bottom circle
	vec4 bottomCenter = vec4(0.0f, -this->height / 2, 0.0f, 1.0f);
	// Normals for bottom center
	vec3 botNormal = vec3(0.0f, -1.0f, 0.0f);
	// Texture Coords for bottom center
	vec2 botTexture = vec2(0.5, 0.5);

	pntVertexData pntBot(bottomCenter, botNormal, botTexture);
	pnt.push_back(pntBot);

	for (int i = 0; i < this->slices + 1; i++) {
		vec4 v0Bot = vec4(cos(sliceAngle) * radius, -this->height / 2, sin(sliceAngle) * radius, 1.0f);
		vec3 normal = normalize(vec3(cos(sliceAngle), 0, sin(sliceAngle)));
		// Texture
		vec2 botTexture = vec2(0.5 * (1 - glm::cos(sliceAngle)), 0.5 * (1 - glm::sin(sliceAngle)));
		pntVertexData pnt0Bot(v0Bot, normal, botTexture);

		pnt.push_back(pnt0Bot);

		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
		// Update the slice angle
		sliceAngle += sliceInc;
	}

	SubMesh botMesh = MeshComponent::buildSubMesh(pnt, indices);

	// Set the primitive mode for the vertex data
	botMesh.primitiveMode = GL_TRIANGLES;

	// Set the material
	botMesh.material = this->cylinderMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(botMesh);

	this->saveInitialLoad();
}
