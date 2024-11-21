#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "models/RawModel.h"
#include "renderEngine/EntityRenderer.h"
#include "shaders/StaticShader.h"
#include "models/TexturedModel.h"
#include "textures/ModelTexture.h"
#include "entities/Entity.h"
#include "renderEngine/ModelLoader.h"
#include "entities/Light.h"
#include "renderEngine/MasterRenderer.h"
#include "terrains/Terrain.h"
#include "entities/Player.h"
#include <glm/gtc/random.hpp>

int main() {
    DisplayManager::createDisplay();
    Loader loader;

	RawModel model = ModelLoader::loadModel(ASSETS_PATH "ChristmasTree/ChristmasTree.obj", loader);
    TexturedModel stallModel(model, ModelTexture(loader.loadTexture(ASSETS_PATH "ChristmasTree/Handle1Tex.png")));

    Entity entity(stallModel, glm::vec3(0.0f, 0.0f, -25.0f), 0.0f, 0.0f, 0.0f, 1.0f);
    Light light(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(1, 1, 1));

    Terrain terrain(0, 0, loader, ModelTexture(loader.loadTexture(ASSETS_PATH "snow.png")));

    std::vector<Entity> allStalls;
    for (int i = 0; i < 300; i++)
    {
        float x = glm::linearRand(0, 800);
        float z = glm::linearRand(0, 800);
        if ((x < 350 || x > 450) || (z < 350 || z > 450)) {
            allStalls.push_back(Entity(stallModel, glm::vec3(x, 0, z), 0, 0, 0, 10.0f));
        }
        else {
            i--;
        }
    }

    MasterRenderer renderer;

    RawModel elfModel = ModelLoader::loadModel(ASSETS_PATH "Elf/AnnoyingElfKeith.obj", loader);
    TexturedModel elf(elfModel, ModelTexture(loader.loadTexture(ASSETS_PATH "Elf/Handle1Tex.png")));

    RawModel cabinModel = ModelLoader::loadModel(ASSETS_PATH "christmasfireplace/christmasfireplace.obj", loader);
    TexturedModel cabin(cabinModel, ModelTexture(loader.loadTexture(ASSETS_PATH "christmasfireplace/fireplace02.png")));
    Entity fireplace(cabin, glm::vec3(400.0f, 0.0f, 400.0f), 0.0f, 180.0f, 0.0f, 8.0f);

    RawModel hatModel = ModelLoader::loadModel(ASSETS_PATH "Santa/santa hat.obj", loader);
    TexturedModel hat(hatModel, ModelTexture(loader.loadTexture(ASSETS_PATH "Santa/lambert2.png")));
    Entity santa(hat, glm::vec3(403.0f, 0.0f, 400.0f), 0.0f, 180.0f, 0.0f, 3.0f);

    Player player(elf, glm::vec3(400, 0, 390), 0, 0, 0, 3);
    Camera camera(player);

    while (!DisplayManager::isCloseRequested()) {
        entity.increaseRotation(0.0f, 1.0f, 0.0f);
        camera.move();
        player.move();
        renderer.processEntity(player);
        renderer.processEntity(santa);
        renderer.processEntity(fireplace);
        renderer.processTerrain(terrain);
        for (const Entity& stall : allStalls)
        {
            renderer.processEntity(stall);
        }
        renderer.render(light, camera);
        DisplayManager::updateDisplay();
    }

    renderer.cleanUp();
    loader.cleanUp();
    DisplayManager::closeDisplay();
    return 0;
}