#include <iostream>
#include <math.h>
#include <algorithm>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color) : 
    Object(x, y, w, h, true), vx(ux), vy(uy), color(color), mass(mass) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100.0f;
    vy += gravity * deltaTime;

    x += vx * deltaTime;
    y += vy * deltaTime;
    rect.x = x;
    rect.y = y;

    //floor
    if (y > window->logHeight() - rect.h) {
        const float velocityYLoss = -0.5f;
        y = window->logHeight() - rect.h;
        rect.y = y;
        vy *= velocityYLoss;
        
        const float velocityXLoss = 2.0f;
        if (vx > 0) 
            vx = std::max(0.0f, vx - velocityXLoss);
        else 
            vx = std::min(0.0f, vx + velocityXLoss);
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::onCollision(Object* other) {
    //hit another particle  
    if (Particle* p = dynamic_cast<Particle*>(other)) {
        if (!p->canCollide || !this->canCollide)
            return;
            
        SDL_FRect c;
        
        SDL_GetRectIntersectionFloat(&rect, &p->rect, &c);
    
        if (c.w < c.h) {
            std::swap(vx, p->vx);
            if (x < p->x) {
                x -= c.w;
            }
            else if (x > p->x) {
                x += c.w;
            }
        }
        else if (c.w > c.h) {
            if (y > p->y) {
                y += c.h;
            }
            else if (y < p->y) {
                y -= c.h;
            }
            
            const float velocityYLoss = -0.5f;
            vy *= velocityYLoss;
            
            const float velocityXLoss = 0.95f;
            vx *= velocityXLoss;
        }
    }
}