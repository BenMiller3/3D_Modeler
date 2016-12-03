#ifndef __SCENEOBJECT_H__	//guard against cyclic dependancy
#define __SCENEOBJECT_H__

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

class SceneObject
{
	public:
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetMaterial(float x, float y, float z, float w);
		void SetMinBound(float x, float y, float z);
		void SetMaxBound(float x, float y, float z);
		bool selected = false;
		void Draw();
		bool Select(double posX, double posY, double posZ, double x2, double y2, double z2, double camX, double camY, double camZ);
		//void CheckSide(posX, posY, PozZ, dirX, dirY, dirZ);
		bool RayPLaneIntersection(double camX, double camY, double camZ, double dirX, double dirY, double dirZ, bool useMinAsPoint, char direction);
		std::vector<float> position;
		std::vector<float> rotation;
		std::vector<float> scale;
		std::vector<float> minBound;
		std::vector<float> maxBound;
		SceneObject();
};

#endif