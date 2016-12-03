#include "SceneObject.h"

SceneObject::SceneObject()
{
	position.push_back(0.0f); position.push_back(0.0f); position.push_back(0.0f);
	rotation.push_back(0.0f); rotation.push_back(0.0f); rotation.push_back(0.0f);
	scale.push_back(1.0f); scale.push_back(1.0f); scale.push_back(1.0f);
	minBound.push_back(-0.5f); minBound.push_back(-0.5f); minBound.push_back(-0.5f);
	maxBound.push_back(0.5f); maxBound.push_back(0.5f); maxBound.push_back(0.5f);
}


void SceneObject::Translate(float x, float y, float z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;

	minBound[0] += x;
	minBound[1] += y;
	minBound[2] += z;

	maxBound[0] += x;
	maxBound[1] += y;
	maxBound[2] += z;
}

void SceneObject::Rotate(float x, float y, float z)
{
	rotation[0] += x;
	rotation[1] += y;
	rotation[2] += z;
}
void SceneObject::Scale(float x, float y, float z)
{
	scale[0] += x;
	scale[1] += y;
	scale[2] += z;

	printf("%f",scale[0]);

	if(scale[0] < 0.1f)
		{
			scale[0] = 0.1f;
			return;
		}
	if(scale[1] < 0.1f)
		{
			scale[1] = 0.1f;
			return;
		}
	if(scale[2] < 0.1f)
		{
			scale[2] = 0.1f;
			return;
		}

	minBound[0] -= x;
	minBound[1] -= y;
	minBound[2] -= z;

	maxBound[0] += x;
	maxBound[1] += y;
	maxBound[2] += z;

}
/*
void SceneObject::SetMaterial(float x, float y, float z, float w)
{
	material = {x, y, z, w};
}
void SceneObject::SetMinBound(float x, float y, float z)
{
	minBound = { x, y, z };
}
void SceneObject::SetMaxBound(float x, float y, float z)
{
	maxBound = { x, y, z };
}*/

bool SceneObject::RayPLaneIntersection(double camX, double camY, double camZ, double dirX, double dirY, double dirZ, bool useMinAsPoint, char direction)
{
	std::vector<float> camPos (3, 0); 
	camPos[0] = camX;
	camPos[1] = camY;
	camPos[2] = camZ;

	std::vector<float> dirVec (3, 0); 
	dirVec[0] = dirX;
	dirVec[1] = dirY;
	dirVec[2] = dirZ;

	std::vector<float> planeNorm (3, 0);  
	if(direction == 'x')
	{
		planeNorm[0] = 1;
	}
	else if(direction == 'y')
	{
		planeNorm[1] = 1;
		//printf("Got To Y CHAR");
	}
	else if(direction == 'z')
	{
		planeNorm[2] = 1;
		//printf("Got To Z CHAR");
	}

	std::vector<float> pointOnPlane (3, 0); 
	pointOnPlane = minBound;
	if(useMinAsPoint)
	{
		pointOnPlane = minBound;
	}
	else
	{
		pointOnPlane = maxBound;
	}

	float D = -(planeNorm[0]*pointOnPlane[0] + planeNorm[1]*pointOnPlane[1] + planeNorm[2]*pointOnPlane[2]);

	float part1 = -(std::inner_product(planeNorm.begin(), planeNorm.end(), camPos.begin(), 0.0) + D);
	float t = part1/(std::inner_product(planeNorm.begin(), planeNorm.end(), dirVec.begin(), 0.0));


	dirVec[0] *= t;
	dirVec[1] *= t;
	dirVec[2] *= t;

	dirVec[0] += camPos[0];
	dirVec[1] += camPos[1];
	dirVec[2] += camPos[2];

	float distX = dirVec[0]-camPos[0];
	float distY = dirVec[1]-camPos[1];
	float distZ = dirVec[2]-camPos[2];

	distanceToIntersect = sqrt(distX*distX + distY*distY + distZ*distZ);

	if(direction == 'x')
	{
		if(dirVec[1] > minBound[1] && dirVec[1] < maxBound[1] && dirVec[2] > minBound[2] && dirVec[2] < maxBound[2])
		{
			//printf("HIT ON X\n");
			return  true;
		}
	}
	else if(direction == 'y')
	{
		//printf("Got To Y\n");
		if(dirVec[0] > minBound[0] && dirVec[0] < maxBound[0] && dirVec[2] > minBound[2] && dirVec[2] < maxBound[2])
		{
			//printf("HIT ON Y\n");
			return true;
		}
	}
	else if(direction == 'z')
	{
		//printf("Got To Z\n");
		if(dirVec[1] > minBound[1] && dirVec[1] < maxBound[1] && dirVec[0] > minBound[0] && dirVec[0] < maxBound[0])
		{
			//printf("HIT ON Z\n");
			return true;
		}
	}

	return false;
	//printf("MISS");
	//-((Normal Dot Ray Origin) + Direction)/(Norm dot Ray Direction)

}

bool SceneObject::Select(double posX, double posY, double posZ, double x2, double y2, double z2, double camX, double camY, double camZ)
{	
	//std::vector<double> dir (x2- posX, y2- posY, z2 - posZ); 
  	std::vector<float> dir (3, 9999);                       // four ints with value 100
	dir[0] = x2-posX;
	dir[1] = y2-posY;
	dir[2] = z2-posZ;
	float length = sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);
	dir[0] = dir[0]/length;
	dir[1] = dir[1]/length;
	dir[2] = dir[2]/length;
	//printf("NEW CLICK\n");

	if(RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], true,  'x')
	|| RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], true,  'y')
	|| RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], true,  'z')
	|| RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], false,  'x')
	|| RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], false,  'y')
	|| RayPLaneIntersection(camX, camY, camZ, dir[0], dir[1], dir[2], false,  'z'))
	{
		return true;
	}
	return false;
}

void SceneObject::Draw()  
{
	glPushMatrix();
	glScalef(scale[0], scale[1], scale[2]);
	glTranslatef(position[0], position[1], position[2]);	
	glRotatef(rotation[0], 1, 0, 0);		
	glRotatef(rotation[1], 0, 1, 0);	
	glRotatef(rotation[2], 0, 0, 1);	
	//glMaterialfv(GL_FRONT, GL_SPECULAR, m_amb);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, m_amb);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, m_amb);
	float m_amb[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float m_dif[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float m_spec[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
	glutSolidTeapot(0.4f);

	if(selected)
	{
		//glutSolidCube(0.1f);
		//glTranslatef(0, 0, 0);
		//glutWireCube(0.5f);
		glutWireCube(1.0f);
		//glutWireCube(2.0f);

		//glPushMatrix();
		//glTranslatef(minBound[0], minBound[1], minBound[2]);
		//glutSolidCube(0.1f);
		//glPopMatrix();

		//glTranslatef(maxBound[0], maxBound[1], maxBound[2]);
		//glutSolidCube(0.1f);
	}
	glPopMatrix();
}

