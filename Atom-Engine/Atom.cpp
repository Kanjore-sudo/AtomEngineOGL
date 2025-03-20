#include "AtomEngine.hpp"

using namespace AtomEngine;

Atom::Atom(){}

GameObject* Atom::GetParent() 
{
	return this->parent;
}

std::vector<GameObject*> Atom::GetChilds()
{
	return this->childs;
}

void Atom::SetParent(GameObject* parent)
{
	this->parent = parent;
}

void Atom::AddChild(GameObject* child)
{
	this->childs.push_back(child);
}

void Atom::Process(Window* window)
{
	for (auto child : this->childs)
	{
		child->Process(window);
	}
}

