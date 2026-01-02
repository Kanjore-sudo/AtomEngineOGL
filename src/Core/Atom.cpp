#include "AtomEngine.hpp"

using namespace AtomEngine;

Atom::Atom() {}

GameObject* Atom::GetParent() { return parent; }
std::vector<GameObject*> Atom::GetChilds() { return childs; }

void Atom::SetParent(GameObject* parent) { this->parent = parent; }
void Atom::AddChild(GameObject* child) { childs.push_back(child); }

void Atom::Process(Window* window)
{
	for (auto& child : childs) child->Process(window);
}
