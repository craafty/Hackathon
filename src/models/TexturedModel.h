#pragma once
#include "RawModel.h"
#include "textures/ModelTexture.h"

class TexturedModel {
private:
	RawModel rawModel;
	ModelTexture texture;
public:
	TexturedModel(RawModel model, ModelTexture texture);
	RawModel getRawModel() const { return rawModel; }
	ModelTexture getTexture() const { return texture; };

	bool operator<(const TexturedModel& other) const {
		// Compare VAO IDs or another unique identifier
		if (getRawModel().getVaoID() != other.getRawModel().getVaoID()) {
			return getRawModel().getVaoID() < other.getRawModel().getVaoID();
		}
		// Optionally compare other attributes if needed
		return getTexture().getID() < other.getTexture().getID();
	}
};