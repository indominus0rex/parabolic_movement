#include "object.hpp"

Object::Object(float x, float y, float w, float h, bool canCollide) : 
    x(x), y(y), w(w), h(h), rect({x, y, w, h}), canCollide(canCollide) {}   