#include "AtomEngine.hpp"

using namespace AtomEngine;

Game::Game(const std::string& name, int w, int h) : name(name), width(w), height(h)
{
    wnd = new Window(name, width, height);
    if (!wnd->Create()) {
        AtomError("Error creando ventana");
    }
}

Game::~Game() { delete wnd; }

bool Game::IsLoading() { return isLoading; }

void Game::SetTextureManager(TextureManager* tm) { this->tm = tm; }

void Game::LoadTextures()
{
    isLoading = true;
    int cont = 0;
    for (auto& texture : tm->GetTextureQueue()) {
        if (!texture.Load()) {
            AtomError("Error cargando textura: " + texture.GetPath());
        }
        tm->GetDataDictionary()->insert(std::make_pair(tm->GetTextureNamesQueue()[cont], texture));
        cont++;
    }
    isLoading = false;
}

void Game::Run(GameObject* scene)
{
    wnd->Show();
    wnd->Run(scene);
}

Window* Game::GetWindow() { return wnd; }
