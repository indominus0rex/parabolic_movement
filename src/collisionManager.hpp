#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <SDL3/SDL.h>

#include "window.hpp"
#include "object.hpp"
#include "particle.hpp"

class collisionManager {
private:

    static bool checkAABB(Object* a, Object* b) {
        SDL_FRect rectA = a->getRect();
        SDL_FRect rectB = b->getRect();
        return SDL_HasRectIntersectionFloat(&rectA, &rectB);
    }

public:

    static void handleCollision(Window* window, std::vector<std::unique_ptr<Object>>& objects) {
        for (size_t i = 0; i < objects.size(); i++) {
            Object* a = objects[i].get();

            if (!a->getCanCollide())
                continue;

            for (size_t j = i + 1; j < objects.size(); j++) {
                Object* b = objects[j].get();

                if (!b->getCanCollide())
                    continue;

                if (checkAABB(a, b)) {
                    a->onCollision(window, b);
                    b->onCollision(window, a);
                }
            }
        }
    }
};