#include "AtomEngine.hpp"

using namespace AtomEngine;

TextureManager::TextureManager()
{
	this->name = "AtomEngineTextureManager";
}

TextureManager::TextureManager(std::string _name)
{
	this->name = _name;
}

TextureManager::TextureManager(std::string _name, Game* _game)
{
	this->name = _name;
	this->game = _game;
}

void TextureManager::NewTexture(std::string _name, LPCWSTR _path)
{
	
	// Crear Textura
	Texture texture(_path);

	// Llamar a AtomLoadImage directamente con texture.GetBitMap()
	HRESULT hr = this->game->GetWindow()->AtomLoadImage(
		this->game->GetWindow()->pRenderTarget,
		texture.GetPath(),
		texture.GetBitMap() // texture.GetBitMap() devuelve ID2D1Bitmap**
	);

	if (FAILED(hr))
	{
		AtomError(L"Fallo al crear la textura");
		return;
	}

	// Meterlo al diccionario
	this->Data.insert(std::make_pair(_name, texture));
}

std::vector<Texture> AtomEngine::TextureManager::GetTextureQueue()
{
	return this->textureQueue;
}

std::vector<std::string> AtomEngine::TextureManager::GetTextureNamesQueue()
{
	return this->textureNamesQueue;
}



std::map<std::string, Texture>* AtomEngine::TextureManager::GetDataDictionary()
{
	return &this->Data;
}

Texture* TextureManager::GetTexture(std::string name)
{
	auto i = this->Data.find(name);
	
	if (i != this->Data.end())
	{
		return &i->second;
	}

	AtomError(L"No se encontro la textura");
	 
}