#include "GameObject.hpp"


GameObject::GameObject(const Vector3& _position, const Vector3& _size, const Color& _color) 
	: position(_position), size(_size), color(_color) {
}

GameObject::~GameObject() {

}
