#include "renderer.h"
#include <iostream>
#include "../application.h"

namespace Core
{
    void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        fprintf(stderr, "EL GL_PANICO: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }

    void Renderer::init()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to init GLAD" << std::endl;
        }

        glViewport(0, 0, Application::getWindow().getWidth(), Application::getWindow().getHeight());
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debugMessageCallback, 0);
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void Renderer::draw(RenderableObject& object, Camera& camera, glm::mat4 modelMatrix)
    {
        object.set();

        object.shader->setUniformMat4("view", camera.getViewMatrix());
        object.shader->setUniformMat4("model", modelMatrix);
        object.shader->setUniformVec3("viewPos", camera.getPosition());

        glDrawArrays(GL_TRIANGLES, 0, object.vertexArrayCount);
    }
    /*
    void Renderer::drawIndexed(RenderableObject& object, glm::mat4 viewMatrix)
    {
        object.shader->setUniformMat4("view", viewMatrix);
        object.set();

        //glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);
    }*/
    void Renderer::updateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    
}
