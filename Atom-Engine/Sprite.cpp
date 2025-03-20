#include "AtomEngine.hpp"

using namespace AtomEngine;
using namespace AtomMath;

Sprite::Sprite(Texture* _texture)
{
	this->texture = _texture;
}

Sprite::~Sprite(){}


void Sprite::Process(Window* window) 
{
	

	if (!this->texture)
	{
		AtomError(L"Error en Sprite::Process: Puntero a textura es nulo");
		return;
	}

	if (!this->texture->bitmap)
	{
		AtomError(L"Error en Sprite::Process: Bitmap de la textura es nulo");
		return;
	}

	if (!window)
	{
		AtomError(L"Error en Sprite::Process: Puntero a ventana es nulo");
		return;
	}

	if (!window->pRenderTarget)
	{
		AtomError(L"Error en Sprite::Process: Render Target de la ventana es nulo");
		return;
	}

	ID2D1Bitmap* btmp = this->texture->bitmap;
	ID2D1RenderTarget* renderTarget = window->pRenderTarget; // Usar el window pasado como argumento

	
	D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();

	//traslacion
	transform = transform * D2D1::Matrix3x2F::Translation(this->Position.x, this->Position.y);

	//rotacion
	D2D1_SIZE_F bitmapSize = btmp->GetSize();
	//pivote
	D2D1_POINT_2F pivot = D2D1::Point2F(bitmapSize.width / 2.0f, bitmapSize.height / 2.0f);

	transform = transform * D2D1::Matrix3x2F::Rotation(this->Rotation, pivot);

	//escalado
	transform = transform * D2D1::Matrix3x2F::Scale(this->Scale.x, this->Scale.y, pivot);

	renderTarget->SetTransform(transform);

	if (btmp)
	{
		renderTarget->DrawBitmap(btmp, D2D1::RectF(0, 0, btmp->GetSize().width, btmp->GetSize().height));
	}


	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	
}
