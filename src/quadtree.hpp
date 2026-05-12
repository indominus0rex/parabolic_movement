#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "particle.hpp"

struct Bound {
    float x;
    float y;
    float w;
    float h;

    bool contains(const glm::vec2& point) const { 
        return (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h); 
    }
};

class Quadtree {
private:

    Bound bound;
    int capacity = 4;
    std::vector<Particle*> particles;
    std::unique_ptr<Quadtree> bound1;
    std::unique_ptr<Quadtree> bound2;
    std::unique_ptr<Quadtree> bound3;
    std::unique_ptr<Quadtree> bound4;
    bool divided = false;

public:

    Quadtree(Bound bound) : bound(bound) {}

    void subDivide() {
        float hW = bound.w / 2;
        float hH = bound.h / 2;
        bound1 = std::make_unique<Quadtree>(Bound{bound.x, bound.y, hW, hH});
        bound2 = std::make_unique<Quadtree>(Bound{bound.x + hW, bound.y, hW, hH});
        bound3 = std::make_unique<Quadtree>(Bound{bound.x, bound.y + hH, hW, hH});
        bound4 = std::make_unique<Quadtree>(Bound{bound.x + hW, bound.y + hH, hW, hH});
        divided = true;
    }

    void insert(Particle* particle) {
        if (!bound.contains(particle->getPosition()))    
            return;

        
    }
};