#include "object.hpp"

Object::Object(float x, float y, float w, float h, SDL_Color color, bool canCollide) : canCollide(canCollide) {
        this->position = glm::vec2(x, y);
        this->size = glm::vec2(w, h);
        this->color = color;
    }   