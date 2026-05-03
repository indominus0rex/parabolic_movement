#include "object.hpp"

Object::Object(float x, float y, float w, float h, bool dynamic, bool canCollide) : 
    x(x), y(y), w(w), h(h), dynamic(dynamic), canCollide(canCollide) {}

bool Object::checkCollision(float otherX, float otherY, float otherW, float otherH) const {
    return otherX < x && x < otherX + otherW && otherY < y && y < otherY + otherH && canCollide;
}