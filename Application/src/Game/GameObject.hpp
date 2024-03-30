#pragma once

#include <raylib.h>

struct GameObject {
public:
	GameObject(const Vector3& _position, const Vector3& _size, const Color& _color);
	~GameObject();
public:
	Vector3 position;
	Vector3 size;
	Color color;
};