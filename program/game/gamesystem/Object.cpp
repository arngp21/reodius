#include"Object.h"
#include"GameManager.h"

extern GameManager* gamemanager_;

void Object::initialize() {
	gamemanager_->objects_.emplace_back(shared_from_this());
}