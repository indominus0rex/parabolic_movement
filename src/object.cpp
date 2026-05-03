#include "object.hpp"

Object::Object(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

bool Object::checkCollision(float otherX, float otherY, float otherW, float otherH) const {
    return otherX < x && x < otherX + otherW && otherY < y && y < otherY + otherH;
}