#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id) : textureID(id), shineDamper(1), reflectivity(0) {}

unsigned int ModelTexture::getID()
{
	return textureID;
}

float ModelTexture::getShineDamper()
{
	return shineDamper;
}

void ModelTexture::setShineDamper(float shineDamper)
{
	this->shineDamper = shineDamper;
}

float ModelTexture::getReflectivity()
{
	return reflectivity;
}

void ModelTexture::setReflectivity(float reflectivity)
{
	this->reflectivity = reflectivity;
}
