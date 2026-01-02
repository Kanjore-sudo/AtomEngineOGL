#include "AtomEngine.hpp"

using namespace AtomEngine;

TextureManager::TextureManager() : name("AtomEngineTextureManager") {}

TextureManager::TextureManager(std::string _name) : name(_name) {}

TextureManager::TextureManager(std::string _name, Game* _game) : name(_name), game(_game) {}

void TextureManager::NewTexture(std::string _name, const std::string& _path)
{
    Texture texture(_path);
    textureQueue.push_back(texture);
    textureNamesQueue.push_back(_name);
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
	auto i = Data.find(name);

	if (i != Data.end())
	{
		return &i->second;
	}

	AtomError("No se encontro la textura");
	return nullptr;
}
