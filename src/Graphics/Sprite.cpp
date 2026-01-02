#include "AtomEngine.hpp"

using namespace AtomEngine;
using namespace AtomMath;

static Shader* shader = nullptr;
static GLuint VAO, VBO;

Sprite::Sprite(Texture* _texture) : texture(_texture)
{
    if (!shader) {
        shader = new Shader("assets/simple.vert", "assets/simple.frag");
    }
    if (!VAO) {
        float vertices[] = {
            0.5f,  0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
           -0.5f, -0.5f, 0.0f, 0.0f,
           -0.5f,  0.5f, 0.0f, 1.0f
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}

Sprite::~Sprite() {}

void Sprite::Process(Window* window)
{
    if (!texture) return;

    Matrix4 model = Matrix4(1.0f);
    model = Translate(model, Vector3(Position.x, Position.y, 0.0f));
    model = Rotate(model, ToRadians(Rotation), Vector3(0.0f, 0.0f, 1.0f));
    model = ScaleMatrix(model, Vector3(Scale.x * texture->GetWidth(), Scale.y * texture->GetHeight(), 1.0f));

    Matrix4 projection = Ortho(0.0f, (float)window->width, (float)window->height, 0.0f, -1.0f, 1.0f);

    shader->use();
    shader->setMat4("model", glm::value_ptr(model));
    shader->setMat4("projection", glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
