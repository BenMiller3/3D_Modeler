#ifndef __SCENEOBJECT_H__	//guard against cyclic dependancy
#define __SCENEOBJECT_H__

#include "header.h"

class SceneObject
{
	public:
		void Translate(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void Scale(float x, float y, float z);
		void SetMaterial(float x, float y, float z, float w);
		void SetMinBound(float x, float y, float z);
		void SetMaxBound(float x, float y, float z);
		bool selected = false;
		void Draw(int selection,int colourOption);
		float distanceToIntersect;
		bool Select(double posX, double posY, double posZ, double x2, double y2, double z2, double camX, double camY, double camZ);
		bool RayPLaneIntersection(double camX, double camY, double camZ, double dirX, double dirY, double dirZ, bool useMinAsPoint, char direction);
		std::vector<float> position;
		std::vector<float> rotation;
		std::vector<float> scale;
		std::vector<float> minBound;
		std::vector<float> maxBound;
		SceneObject();
};

#endif