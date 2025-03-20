#ifndef ATOM_ENGINE_HPP
#define ATOM_ENGINE_HPP
#pragma once

#include <iostream>
#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <string>
#include <vector>
#include <map>
#include "AtomMath.hpp"


namespace AtomEngine
{
	class AtomError
	{
	public:
		AtomError(const LPCWSTR error);
	};


	class GameObject;
	class Texture;
	

	class Window {
	protected:
		std::wstring className;
		std::wstring title;
		int width;
		int height;

		HINSTANCE hInstance;
		HWND hWnd;

		ID2D1Factory* pFactory = nullptr;
		

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	public:
		ID2D1HwndRenderTarget* pRenderTarget = nullptr;
		Window(std::wstring className, std::wstring title, int w, int h);
		~Window();

		bool Create();

		HRESULT InitDirect2D();

		HRESULT AtomLoadImage(ID2D1HwndRenderTarget* renderTarget, const wchar_t* ruta, ID2D1Bitmap** ppBitmap);
	

		void showWindow();

		int ProcesInit(GameObject* scene);

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
		
		LPCWSTR path = L"";

	public:
		ID2D1Bitmap* bitmap = nullptr;
		Texture() {}
		Texture(LPCWSTR path);

		void SetBitmap(ID2D1Bitmap* bitmap);

		LPCWSTR GetPath();
		ID2D1Bitmap** GetBitMap();
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

		void NewTexture(std::string _name, LPCWSTR _path);
		std::vector<Texture> GetTextureQueue();
		std::vector<std::string> GetTextureNamesQueue();

		std::map<std::string, Texture>* GetDataDictionary();
		Texture* GetTexture(std::string _name);
	};


	class Game
	{
	protected:
		std::wstring name;
		int width;
		int height;
		Window* wnd = nullptr;
		bool isLoading;


	public:
		TextureManager* tm;
		Game(std::wstring, int w, int h);
		~Game() {};

		//Game(std::wstring name, int w, int h);
		void SetTextureManager(TextureManager* tm);
		void LoadBitmaps();
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
		Window* window = nullptr;
		Texture* texture = nullptr;
		LPCWSTR path;

	public:
		Sprite(Texture* _texture);
		~Sprite();
		virtual void Process(Window* window) override;
	};

}
#endif // !ATOM_ENGINE_HPP
