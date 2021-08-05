#include "renderableObject.h"

Core::RenderableObject::RenderableObject(Shader* shader, VertexArray* vao, Texture* textures, int vertexArrayCount)
    : shader(shader), vao(vao), textures(textures), vertexArrayCount(vertexArrayCount)
{
}

void Core::RenderableObject::set()
{
    this->shader->set();
    this->vao->set();

    if (this->textures) {
        this->textures[0].set(1);
        this->textures[1].set(2);
        this->textures[2].set(3);

        // jotain vitun paskaa taas oli std::vector :n kanssa ei helvetti
        /*
        for (const auto& tex: *this->textures) {
            tex.set(tex.getTextureId());
        }*/
    }
}

