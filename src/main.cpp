#include "AtomEngine.hpp"

using namespace AtomEngine;

int main() {
    Game game("Mi Juego", 800, 600);
    TextureManager tm;
    game.SetTextureManager(&tm);

    // Cargar textura del cubo
    tm.NewTexture("cube", "../assets/cube_texture.png");

    // Cargar texturas
    game.LoadTextures();

    // Crear escena
    Atom* scene = new Atom();

    // Crear sprite con la textura del cubo
    Texture* cubeTex = tm.GetTexture("cube");
    if (cubeTex) {
        Sprite* cubeSprite = new Sprite(cubeTex);
        cubeSprite->SetPosition(AtomMath::Vector2(400, 300)); // Centro de la pantalla
        cubeSprite->SetScale(AtomMath::Vector2(0.5f, 0.5f));  // Escala a la mitad
        scene->AddChild(cubeSprite);
    }

    game.Run(scene);

    delete scene;
    return 0;
}
