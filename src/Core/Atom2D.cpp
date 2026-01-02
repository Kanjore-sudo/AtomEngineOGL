#include "AtomEngine.hpp"

using namespace AtomEngine;
using namespace AtomMath;

Atom2D::Atom2D() : Position(0, 0), Scale(1, 1), Rotation(0.0f) {}

void Atom2D::SetPosition(Vector2 position) { Position = position; }
void Atom2D::SetScale(Vector2 scale) { Scale = scale; }
void Atom2D::SetRotation(float rotation) { Rotation = rotation; }

Vector2 Atom2D::GetPosition() { return Position; }
Vector2 Atom2D::GetScale() { return Scale; }
float Atom2D::GetRotation() { return Rotation; }
