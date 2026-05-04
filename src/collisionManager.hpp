#pragma once

#include <vector>
#include <memory>
#include <SDL3/SDL.h>

#include "object.hpp"

class collisionManager {
private:

    static bool checkAABB(Object* a, Object* b) {
        return SDL_HasRectIntersectionFloat(&a->getRect(), &b->getRect());
    }

public:

    static void handleCollision(std::vector<std::unique_ptr<Object>> objects) {
        for (size_t i = 0; i < objects.size(); i++) {
            for (size_t j = i + 1; j < objects.size(); j++) {
                Object* a = objects[i].get();
                Object* b = objects[j].get();

                if (checkAABB(a, b)) {
                    a->onCollision(b);
                    b->onCollision(a);
                }
            }
        }
    }
};