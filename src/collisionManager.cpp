#include "collisionManager.hpp"

bool collisionManager::checkAABB(Object* a, Object* b) {
    SDL_FRect rectA = a->getBoundingBox();
    SDL_FRect rectB = b->getBoundingBox();
    return SDL_HasRectIntersectionFloat(&rectA, &rectB);
}

void collisionManager::handleCollision(Window* window, std::vector<std::unique_ptr<Object>>& objects) {
    Bound bound = {0, 0, (float) window->Width(), (float) window->Height()};
    Quadtree quadtree(bound);

    for (auto& object : objects) {
        if (object->getCanCollide())
            quadtree.insert(object.get());
    }

    for (int i = 0; i < 4; i++) {
        for (auto& object : objects) {
            std::vector<Object*> neighbors;

            SDL_FRect boundingBox = object->getBoundingBox();

            Bound seachArea = {
                boundingBox.x - 10,
                boundingBox.y - 10,
                boundingBox.w + 20,
                boundingBox.h + 20
            };
            
            quadtree.query(seachArea, neighbors);
            for (Object* other : neighbors) {
                if (object.get() != other && checkAABB(object.get(), other)) {
                    object->onCollision(window, other);
                }
            }
        }
    }
}