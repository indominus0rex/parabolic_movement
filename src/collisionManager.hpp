#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <SDL3/SDL.h>
#include <stack>
#include <algorithm>

#include "window.hpp"
#include "object.hpp"
#include "particle.hpp"
#include "quadtree.hpp"

class collisionManager {
private:

    static bool checkAABB(Object* a, Object* b) {
        SDL_FRect rectA = a->getRect();
        SDL_FRect rectB = b->getRect();
        return SDL_HasRectIntersectionFloat(&rectA, &rectB);
    }

    static bool checkCircular(Object* a, Object* b) {
        
    }

public:

    static void handleCollision(Window* window, std::vector<std::unique_ptr<Object>>& objects) {
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
};