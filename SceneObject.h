#ifndef __SCENEOBJECT_H__	//guard against cyclic dependancy
#define __SCENEOBJECT_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

class SceneObject
{
	public:
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetMaterial(float x, float y, float z, float w);
		void SetMinBound(float x, float y, float z);
		void SetMaxBound(float x, float y, float z);
		void Draw();
		/*std::vector<float> position = {0.0f, 0.0f, 0.0f};
		std::vector<float> rotation = {0.0f, 0.0f, 0.0f};
		std::vector<float> scale = {1.0f, 1.0f, 1.0f};
		std::vector<float> material = {0.5f, 0.5f, 0.5f, 0.5f};
		std::vector<float> minBound = {0.0f, 0.0f, 0.0f};
		std::vector<float> maxBound = {1.0f, 1.0f, 1.0f};*/
};

#endif