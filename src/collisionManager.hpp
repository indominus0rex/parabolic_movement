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

class collisionManager : public Object {
private:

    static bool checkAABB(Object* a, Object* b);
    static bool checkCircleRect(const CircleData& circle, const RectData& rect);

public:

    static void handleCollision(Window* window, std::vector<std::unique_ptr<Object>>& objects);
};