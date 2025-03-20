#include "AtomEngine.hpp"

using namespace AtomEngine;

Game::Game(std::wstring name, int w, int h)
{
	this->name = name;
	this->width = w;
	this->height = h;
	this->wnd = new Window(L"ventana", this->name, this->width, this->height);


	if (!this->wnd->Create())
	{
		AtomError(L"Error al crear la ventana");
	}
}

bool Game::IsLoading() { return this->isLoading; }

void AtomEngine::Game::SetTextureManager(TextureManager* tm)
{
	this->tm = tm;
}

void Game::LoadBitmaps()
{
	this->isLoading = true;
	int cont = 0;
	for (auto texture : this->tm->GetTextureQueue())
	{
		AtomError(L"Creando texturas");
		HRESULT hr = this->wnd->AtomLoadImage(
			
			this->wnd->pRenderTarget,
			texture.GetPath(),
			texture.GetBitMap()
		);
		
		if (FAILED(hr))
		{
			AtomError(L"Fallo al crear la textura");
		}
		else 
		{
			AtomError(L"No falla");
		}

		this->tm->GetDataDictionary()->insert(std::make_pair(this->tm->GetTextureNamesQueue()[cont], texture));
		cont++;
	}
	this->isLoading = false;
	AtomError(L"Texturas creadas");
}

void Game::Run(GameObject* scene)
{

	this->wnd->showWindow();

	this->wnd->ProcesInit(scene);
}

Window* Game::GetWindow()
{
	return this->wnd;
}

