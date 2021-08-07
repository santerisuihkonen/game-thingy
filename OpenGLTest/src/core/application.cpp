#include "application.h"
#include "camera.h"

#include <iostream>
#include <vector>
#include "input.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "time.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "common/primitives/cube.h"
#include "renderer/renderableObject.h"
#include "common/gameObject.h"
#include "common/lights/directionalLight.h"

namespace Core
{
    Application* Application::_instance = nullptr;

    Application::Application()
    {
	    if (this->_instance) {
		    std::cout << "Application instance already running, this will probably cause some issues, I don't know though, I'm just an idiot coding" << std::endl;
	    }

	    if (!this->_instance) {
		    this->_instance = this;
	    }

	    this->_window = std::unique_ptr<Window>(Window::create());
	    Renderer::init();
    }

    Application::~Application()
    {

    }

    void Application::run()
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::unique_ptr<Camera> mainCamera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(mainCamera->getFov()), (float)this->getWindow().getWidth() / (float)this->getWindow().getHeight(), 0.1f, 100.0f);
        

        glm::vec3 lightPosition(0.0f, 1.0f, 0.0f);

        DirectionalLight* dirLight = new DirectionalLight(glm::vec3(0.0f, 1.0f, 0.0f));

        // Create default cube gameobject
        Texture cubeTexture("res/textures/container2.png");
        Texture cubeSpecular("res/textures/container2_specular.png");
        Texture cubeEmission("res/textures/container2_emission.png");
        Texture cubeTextures[] = { cubeTexture, cubeSpecular, cubeEmission };

        Shader cubeShader("res/shaders/basic-material.glsl");
        cubeShader.set();
        cubeShader.setUniform1i("material.diffuse", cubeTexture.getTextureId());
        cubeShader.setUniform1i("material.specular", cubeSpecular.getTextureId());
        cubeShader.setUniform1i("material.emission", cubeEmission.getTextureId());
        cubeShader.setUniform1f("material.shininess", 32.0f);

        cubeShader.setUniformVec3("pointLights[0].ambient", 0.4f, 0.4f, 0.4f);
        cubeShader.setUniformVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        cubeShader.setUniformVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setUniformVec3("pointLights[0].position", lightPosition);
        cubeShader.setUniform1f("pointLights[0].constant", 1.0f);
        cubeShader.setUniform1f("pointLights[0].linear", 0.09);
        cubeShader.setUniform1f("pointLights[0].quadratic", 0.032);

        cubeShader.setUniformVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        cubeShader.setUniformVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setUniformVec3("dirLight.diffuse", 0.0f, 0.0f, 1.0f);
        cubeShader.setUniformVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


        cubeShader.setUniformMat4("projection", projection);

        //Texture texture("res/textures/shekelman.jpg");
        //cubeShader->setUniform1i("u_texture", 0);

        Cube cubePrimitive = Cube();
        
        RenderableObject cubeRender(cubeShader, *cubePrimitive.getVao(), cubeTextures, 36);

        GameObject* cube = new GameObject();
        cube->setRendererData(cubeRender);

        cubeShader.unset();

        // create test light gameobject (also cube lol)
        Shader lightShader("res/shaders/light.glsl");
        lightShader.set();
        lightShader.setUniformMat4("projection", projection);

        RenderableObject lightRender(lightShader, *cubePrimitive.getVao(), nullptr, 36);


        GameObject* light = new GameObject();
        light->setPosition(lightPosition);
        light->setScale(glm::vec3(0.2f));
        light->setRendererData(lightRender);
        
        lightShader.unset();

        glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        // main game lööp
        while (this->_running) {
            if (Input::keyPressed(Key::Escape)) {
                this->close();
            }

            TimeManager::update();
            
		    mainCamera->update();
            
            Renderer::clear();
            
            glm::mat4 view = mainCamera->getViewMatrix();

            lightPosition = light->getPosition();
            float time = TimeManager::getTime();
            glm::vec3 newLightPosition(glm::sin(time) * 2, lightPosition.y, glm::cos(time) * 2);
            light->setPosition(newLightPosition);
            
            cubeShader.set();
            cubeShader.setUniformVec3("pointLights[0].position", newLightPosition);
            cubeShader.unset();
            
            cube->render(*mainCamera);
            light->render(*mainCamera);
            
		    this->_window->update();
	    }
        
        delete cube;
    }
    
    void Application::close()
    {
    	this->_running = false;
    }
    
}
