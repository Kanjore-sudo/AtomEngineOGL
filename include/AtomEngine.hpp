#ifndef ATOM_ENGINE_HPP
#define ATOM_ENGINE_HPP
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "AtomMath.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AtomEngine
{
	class AtomError
	{
	public:
		AtomError(const std::string& error, const char* file = __FILE__, int line = __LINE__, const char* func = __FUNCTION__);
	};

	class Shader
	{
	public:
		GLuint ID;
		Shader(const char* vertexPath, const char* fragmentPath);
		void use();
		void setMat4(const std::string& name, const float* value);
	};


	class GameObject;
	class Texture;
	

	class Window {
	protected:
		GLFWwindow* window;
	public:
		int width, height;
		Window(const std::string& title, int w, int h);
		~Window();
		bool Create();
		void Show();
		int Run(GameObject* scene);
	};

	//Objeto Textura

	//migrar a smart pointers

	class Game;

	class GameObject
	{
	protected:
		Window* wnd = nullptr;
		std::string name;
		GameObject* parent;
		std::vector<GameObject*> childs;

	public:
		GameObject() {}

		virtual GameObject* GetParent() = 0;
		virtual std::vector<GameObject*> GetChilds() = 0;

		virtual void SetParent(GameObject* parent) = 0;
		virtual void AddChild(GameObject* child) = 0;

		virtual void Process(Window* window) = 0;
	};

	class Texture
	{
	protected:
		std::string path;
		int width, height, channels;
		unsigned char* data = nullptr;

	public:
		GLuint textureID = 0;
		Texture() {}
		Texture(const std::string& path);

		bool Load();
		void Bind();
		std::string GetPath() { return path; }
		int GetWidth() { return width; }
		int GetHeight() { return height; }
	};

	class TextureManager
	{
	protected:
		std::vector<Texture> textureQueue;
		std::vector<std::string> textureNamesQueue;
		std::string name;
		std::map<std::string, Texture> Data;
		Game* game = nullptr;
	
	public:
		TextureManager(); 
		TextureManager(std::string _name);
		TextureManager(std::string _name, Game* _game);
		~TextureManager() {};

		void NewTexture(std::string _name, const std::string& _path);
		std::vector<Texture> GetTextureQueue();
		std::vector<std::string> GetTextureNamesQueue();

		std::map<std::string, Texture>* GetDataDictionary();
		Texture* GetTexture(std::string _name);
	};


	class Game
	{
	protected:
		std::string name;
		int width, height;
		Window* wnd = nullptr;
		bool isLoading = false;

	public:
		TextureManager* tm = nullptr;
		Game(const std::string& name, int w, int h);
		~Game();

		void SetTextureManager(TextureManager* tm);
		void LoadTextures();
		void Run(GameObject* scene);
		bool IsLoading();
		Window* GetWindow();
	};

	class Atom : public GameObject
	{
	public:
		Atom();

		virtual GameObject* GetParent() override;
		virtual std::vector<GameObject*> GetChilds() override;

		virtual void SetParent(GameObject* parent) override;

		virtual void AddChild(GameObject* child) override;

		virtual void Process(Window* window) override;
	};


	class Atom2D : public Atom
	{
	protected:
		AtomMath::Vector2 Position;
		AtomMath::Vector2 Scale;
		float Rotation{ 0.0 };

	public:
		Atom2D();

		virtual void SetPosition(AtomMath::Vector2 position);

		virtual void SetScale(AtomMath::Vector2 position);

		virtual void SetRotation(float rotation);

		virtual AtomMath::Vector2 GetPosition();
		virtual AtomMath::Vector2 GetScale();
		virtual float GetRotation();
	};

	class Sprite : public Atom2D
	{
	protected:
		Texture* texture = nullptr;

	public:
		Sprite(Texture* _texture);
		~Sprite();
		virtual void Process(Window* window) override;
	};

}
#endif // !ATOM_ENGINE_HPP
