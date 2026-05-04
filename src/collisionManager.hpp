#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <SDL3/SDL.h>

#include "object.hpp"
#include "particle.hpp"

class collisionManager {
private:

    static bool checkAABB(Object* a, Object* b) {
        return SDL_HasRectIntersectionFloat(&a->rect, &b->rect);
    }

public:

    static void handleCollision(std::vector<std::unique_ptr<Object>>& objects) {
        for (size_t i = 0; i < objects.size(); i++) {
            Object* a = objects[i].get();

            if (!a->canCollide)
                continue;

            for (size_t j = i + 1; j < objects.size(); j++) {
                Object* b = objects[j].get();

                if (!b->canCollide)
                    continue;

                if (checkAABB(a, b)) {
                    std::cout << "collided" << '\n';
                    a->onCollision(b);
                    b->onCollision(a);
                }
            }
        }
    }
};