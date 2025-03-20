#include "AtomEngine.hpp"

using namespace AtomEngine;

AtomError::AtomError(const LPCWSTR error)
{
	MessageBox(NULL, error, L"ATOM_ENGINE ERROR", MB_ICONERROR);
}