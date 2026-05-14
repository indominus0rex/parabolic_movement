#include <variant>

#include "collisionManager.hpp"
#include "particle.hpp"
#include "object.hpp"

bool collisionManager::checkCircleRect(const CircleData& circle, const RectData& rect) {
    return false;
}

bool collisionManager::checkAABB(Object* a, Object* b) {
    return a->applyVisitor([&](auto&& shapeA) {
        using T = std::decay_t<decltype(shapeA)>;
        
        return b->applyVisitor([&](auto&& shapeB) {
            using U = std::decay_t<decltype(shapeB)>;
            
            if constexpr (std::is_same_v<T, RectData> && std::is_same_v<U, RectData>) {
                SDL_FRect rectA = a->getBoundingBox();
                SDL_FRect rectB = b->getBoundingBox();
                return SDL_HasRectIntersectionFloat(&rectA, &rectB);
            }
            else if constexpr (std::is_same_v<T, CircleData> && std::is_same_v<U, CircleData>) {
                float distSq = glm::distance(a->getCenter(), b->getCenter());
                float combinedRadius = shapeA.radius + shapeB.radius;
                return distSq <= combinedRadius;
            }
            else if constexpr (std::is_same_v<T, RectData> && std::is_same_v<U, CircleData>) {
                return checkCircleRect(shapeB, shapeA);
            }
            else if constexpr (std::is_same_v<T, CircleData> && std::is_same_v<U, RectData>) {
                return checkCircleRect(shapeA, shapeB);
            }

            return false;
        });
    });
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