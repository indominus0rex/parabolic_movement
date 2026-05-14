#include "object.hpp"

Object::Object(glm::vec2 position, glm::vec2 size, SDL_Color color, bool canCollide) : 
    canCollide(canCollide), 
    color(color),
    shapeData(RectData{position, size})
{}
    
Object::Object(glm::vec2 center, float radius, SDL_Color color, bool canCollide) :
    canCollide(canCollide),
    color(color),
    shapeData(CircleData{center, radius})
{}

SDL_FRect Object::getBoundingBox() const {
    return std::visit([](auto&& arg) -> SDL_FRect {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RectData>) {
            return { arg.position.x, arg.position.y, arg.size.x, arg.size.y };
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            return { arg.center.x - arg.radius, arg.center.y - arg.radius, arg.radius * 2, arg.radius * 2 }; 
        }
    }, shapeData);
}

float Object::getRadius() const {
    if (const auto* data = std::get_if<CircleData>(&shapeData)) {
        return data->radius;
    }

    return 0.0f;
}

void Object::setCenter(glm::vec2 newCenter) {
    std::visit([newCenter](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RectData>) {
            arg.position = newCenter;
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            arg.center = newCenter;
        }
    }, shapeData);
}

void Object::setRadius(float newRadius) {
    if (auto* circle = std::get_if<CircleData>(&shapeData)) {
        circle->radius = newRadius;
    }
}

glm::vec2 Object::getCenter() const {
    return std::visit([](auto&& arg) -> glm::vec2 {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RectData>) {
            return arg.position; 
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            return arg.center;
        }
    }, shapeData);
}

SDL_FRect Object::getRect() const {
    if (auto* rect = std::get_if<RectData>(&shapeData)) {
        SDL_FRect newRect = {
            rect->position.x - rect->size.x / 2.0f,
            rect->position.y - rect->size.y / 2.0f,
            rect->size.x,
            rect->size.y
        };
        return newRect;
    }
}

void Object::updatePosition(glm::vec2 positionChanged) {
    std::visit([positionChanged](auto&& arg){
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RectData>) {
            arg.position += positionChanged;
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            arg.center += positionChanged;
        }
    }, shapeData);
}

void Object::setCanCollide(bool canCollide) {
    this->canCollide = canCollide;
}