#include "object.hpp"

Object::Object(glm::vec2 position, glm::vec2 size, SDL_Color color, bool canCollide) : 
    canCollide(canCollide), position(position), size(size), color(color) {}   