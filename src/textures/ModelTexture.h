#pragma once

class ModelTexture {
private:
	unsigned int textureID;
	float shineDamper;
	float reflectivity;

public:
	ModelTexture(unsigned int id);
	unsigned int getID();
	float getShineDamper();
	void setShineDamper(float shineDamper);
	float getReflectivity();
	void setReflectivity(float reflectivity);
};