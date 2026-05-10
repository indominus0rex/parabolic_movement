#include "object.hpp"

Object::Object(float x, float y, float w, float h, bool canCollide) : canCollide(canCollide) {
        this->setPosition(x, y);
        this->setSize(w, h);
    }   