#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "object.hpp"

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
    std::vector<Object*> particles;
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

    void insert(Object* particle) {
        if (!bound.contains(particle->getPosition()))    
            return;

        if (particles.size() < capacity) {
            particles.push_back(particle);
        }
        else {
            if (!divided) {
                subDivide();
            }
            bound1->insert(particle);
            bound2->insert(particle);
            bound3->insert(particle);
            bound4->insert(particle);
        }
    }

    void query(Bound range, std::vector<Object*>& found) {
        if (!(range.x < bound.x + bound.w && range.x + range.w > bound.x &&
              range.y < bound.y + bound.h && range.y + range.h > bound.y)) 
            return;
        
        for (auto particle : particles) {
            if (range.contains(particle->getPosition()))
                found.push_back(particle);
        }

        if (divided) {
            bound1->query(range, found);
            bound2->query(range, found);
            bound3->query(range, found);
            bound4->query(range, found);
        }
    }
};