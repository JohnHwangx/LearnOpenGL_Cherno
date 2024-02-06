#pragma once
#include "Shader.h"
#include "Texture.h"

namespace Breakout {
    class SpriteRenderer
    {
    public:
        // Constructor (inits shaders/shapes)
        SpriteRenderer(const Shader& shader);
        // Destructor
        ~SpriteRenderer();
        // Renders a defined quad textured with given sprite
        void DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    private:
        // Render state
        Shader       shader;
        unsigned int quadVAO;
        // Initializes and configures the quad's buffer and vertex attributes
        void initRenderData();
    };
}