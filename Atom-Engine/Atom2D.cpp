#include "AtomEngine.hpp"

using namespace AtomEngine;
using namespace AtomMath;


Atom2D::Atom2D()
{
	this->Position = Vector2(0, 0);
	this->Scale = Vector2(0, 0);
	this->Rotation = 0.0f;
}

void Atom2D::SetPosition(Vector2 position)
{
	this->Position = position;
}

void Atom2D::SetScale(Vector2 scale)
{
	this->Scale = scale;
}

void Atom2D::SetRotation(float rotation)
{
	this->Rotation = rotation;
}

Vector2 Atom2D::GetPosition()
{
	return this->Position;
}

Vector2 Atom2D::GetScale()
{
	return this->Scale;
}

float Atom2D::GetRotation()
{
	return this->Rotation;
}