#include "MasterRenderer.h"
#include "DisplayManager.h"
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

const float MasterRenderer::FOV = 60.0f;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000.0f;

MasterRenderer::MasterRenderer() : shader(), terrainShader() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    createProjectionMatrix();
    renderer.emplace(shader, projectionMatrix);
    terrainRenderer.emplace(terrainShader, projectionMatrix);
}

void MasterRenderer::render(Light sun, Camera camera)
{
	prepare();
	shader.start();
	shader.loadLight(sun);
	shader.loadViewMatrix(camera);
    if (renderer) {
        renderer->render(entities);
    }
	shader.stop();

    terrainShader.start();
    terrainShader.loadLight(sun);
    terrainShader.loadViewMatrix(camera);
    if (terrainRenderer) {
        terrainRenderer->render(terrains);
    }
    terrainShader.stop();
    terrains.clear();
	entities.clear();
}

void MasterRenderer::cleanUp()
{
	shader.cleanUp();
    terrainShader.cleanUp();
}

void MasterRenderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.349f, 0.569f, 1.0f);
}

void MasterRenderer::createProjectionMatrix()
{
    float aspectRatio = static_cast<float>(DisplayManager::getWidth()) / static_cast<float>(DisplayManager::getHeight());
    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void MasterRenderer::processEntity(Entity entity)
{
    TexturedModel entityModel = entity.getModel();

    auto it = entities.find(entityModel);

    if (it != entities.end()) {
        it->second.push_back(entity);
    }
    else {
        std::vector<Entity> newBatch = { entity };
        entities[entityModel] = newBatch;
    }
}

void MasterRenderer::processTerrain(Terrain terrain)
{
    terrains.push_back(terrain);
}
