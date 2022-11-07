#pragma once
#include "MeshComponent.h"

class CylinderMeshComponent : public MeshComponent
{
public:
	CylinderMeshComponent(GLuint shaderProgram, Material mat,
		float radius = 1.0f, float height = 2.0f, int stacks = 12,
		int slices = 16, int updateOrder = 100);


protected:

	virtual void buildMesh();

	/**
	* @fn void buildTopCircle();
	* 
	* @brief a helper method for building top circle of the cylinder
	*
	*/
	void buildTopCircle();
	/**
	* @fn void buildBottomCircle();
	*
	* @brief a helper method for building bottom circle of the cylinder
	*
	*/
	void buildBotCircle();

	float radius, height;
	int slices, stacks;
	Material cylinderMat;

};
