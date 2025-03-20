#include "AtomEngine.hpp"

using namespace AtomEngine;

Texture::Texture(LPCWSTR path)
{
	this->path = path;
}


void Texture::SetBitmap(ID2D1Bitmap* bitmap)
{
	this->bitmap = bitmap;
}

LPCWSTR Texture::GetPath()
{
	return this->path;
}

ID2D1Bitmap** Texture::GetBitMap()
{
	return &this->bitmap;
}
