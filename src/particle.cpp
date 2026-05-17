#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"
#include "physicsConfig.hpp"
#include "config.hpp"

Particle::Particle(const ParticleConfig& particleConfig) : Object(particleConfig) {
    this->mass = particleConfig.mass;
    this->velocity = particleConfig.velocity;
}


Particle::~Particle() {}

void Particle::resolveCollision(Window* window, Particle* other) {
    glm::vec2 relativeVelocity = this->getVelocity() - other->getVelocity();
    glm::vec2 relativePosition = this->getCenter() - other->getCenter();

    if (glm::dot(relativeVelocity, relativePosition) >= 0) {
        return;
    }
}

void Particle::calcNewVelocity(Particle* other) {
    float mRatio = ((1 + PhysicsConfig::Cr) * other->getMass()) / (mass + other->getMass());

    glm::vec2 vDiff = velocity - other->getVelocity();
    glm::vec2 xDiff = this->getCenter() - other->getCenter();

    float dotProduct = glm::dot(vDiff, xDiff);
    float sqLength = glm::dot(xDiff, xDiff);

    glm::vec2 newVelocity = velocity - mRatio * (dotProduct / sqLength) * xDiff;
    velocity = newVelocity;
}

void Particle::handleAABBCollision(Window* window, Particle* other) {
    std::visit(Overload{
        [&](const RectData& rect) {
            float centerAX = this->getCenter().x;
            float centerAY = this->getCenter().y;
            float centerBX = other->getCenter().x;
            float centerBY = other->getCenter().y;

            float dx = centerAX - centerBX;
            float dy = centerAY - centerBY;

            float combinedHalfW = (this->getRect().w + other->getRect().w) / 2.0f;
            float combinedHalfH = (this->getRect().h + other->getRect().h) / 2.0f;

            float overlapX = combinedHalfW - std::abs(dx);
            float overlapY = combinedHalfH - std::abs(dy);

            if (overlapX > 0 && overlapY > 0) {
                if (overlapX < overlapY) {
                    if (dx > 0) {
                        glm::vec2 positionChanged = { overlapX, 0 };
                        this->updatePosition(positionChanged);
                    }
                    else {
                        glm::vec2 positionChanged = { -overlapX, 0 };
                        this->updatePosition(positionChanged);
                    }        
                } else {
                    if (dy > 0) {
                        glm::vec2 positionChanged = { 0, overlapY };
                        this->updatePosition(positionChanged);
                    }
                    else {
                        glm::vec2 positionChanged = { 0, -overlapY };
                        this->updatePosition(positionChanged);
                    }
                }

                this->calcNewVelocity(other);
                other->calcNewVelocity(this);
            }
        },
        [&](const CircleData& circle) {
            glm::vec2 centerA = this->getCenter();
            glm::vec2 centerB = other->getCenter();
            
            float distAB = glm::distance(centerA, centerB);
            float combinedRadius = this->getRadius() + other->getRadius();
            
            float overlap = combinedRadius - distAB;

            glm::vec2 unitVec = (centerA - centerB) / distAB;
            glm::vec2 pushForce = unitVec * (overlap / 2.0f);

            this->updatePosition(pushForce);
            other->updatePosition(-pushForce);

            this->calcNewVelocity(other);
            other->calcNewVelocity(this);
        }
    }, shapeData);
}

void Particle::update(Window* window, float deltaTime) {
    this->velocity += PhysicsConfig::gravity * deltaTime;
    glm::vec2 positionChanged = velocity * deltaTime;
    this->updatePosition(positionChanged);

    std::visit(Overload{
        [&](const RectData& rect) {
            SDL_FRect boundingBox = this->getBoundingBox();

            //floor
            if (boundingBox.y + boundingBox.h / 2.0f > window->logHeight()) {
                this->setCenter({ this->getCenter().x, window->logHeight() - boundingBox.h / 2.0f });
                if (this->velocity.y > 0) {
                    this->velocity.y *= -PhysicsConfig::Cr;
                }
            }

            //ceiling
            if (boundingBox.y - boundingBox.h / 2.0f < 0) {
                this->setCenter({ this->getCenter().x, boundingBox.h / 2.0f });
                if (this->velocity.y < 0) {
                    this->velocity.y *= -PhysicsConfig::Cr;
                } 
            }

            //left wall
            if (boundingBox.x - boundingBox.w / 2.0f < 0) {
                this->setCenter({ boundingBox.w / 2.0f, this->getCenter().y });
                if (this->velocity.x < 0) {
                    this->velocity.x *= -PhysicsConfig::Cr;
                }
            }

            //right wall
            if (boundingBox.x + boundingBox.w / 2.0f > window->logWidth()) {
                this->setCenter({ (float) window->logWidth() - boundingBox.w / 2.0f, this->getCenter().y });
                if (this->velocity.x > 0) {
                    this->velocity.x *= -PhysicsConfig::Cr;
                }
            }
        },
        [&](const CircleData& circle) {
            //left wall
            if (circle.center.x - circle.radius < 0) {
                this->setCenter({ circle.radius, circle.center.y });
                if (this->velocity.x < 0) {
                    this->velocity.x *= -PhysicsConfig::Cr;
                }
            }

            //right wall
            if (circle.center.x + circle.radius > window->logWidth()) {
                this->setCenter({ (float) window->logWidth() - circle.radius, circle.center.y });
                if (this->velocity.x > 0) {
                    this->velocity.x *= -PhysicsConfig::Cr;
                }
            }

            //ceiling
            if (circle.center.y - circle.radius < 0) {
                this->setCenter({ circle.center.x, circle.radius });
                if (this->velocity.y < 0) {
                    this->velocity.y *= -PhysicsConfig::Cr;
                }
            }

            //floor
            if (circle.center.y + circle.radius > window->logHeight()) {
                this->setCenter({ circle.center.x, (float) window->logHeight() - circle.radius });
                if (this->velocity.y > 0) {
                    this->velocity.y *= -PhysicsConfig::Cr;
                }
            }
        }
    }, shapeData);
}

void Particle::drawCircle(SDL_Renderer* renderer) {
    if (!this->isCircle())
        return;

    int x = (int) this->getRadius();
    int y = 0;
    int error = 1 - x;
    float centerX = this->getCenter().x;
    float centerY = this->getCenter().y;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
    while (x >= y) {
        
        SDL_RenderLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        SDL_RenderPoint(renderer, centerX + x, centerY + y);
        SDL_RenderPoint(renderer, centerX + x, centerY - y);
        SDL_RenderPoint(renderer, centerX - x, centerY + y);
        SDL_RenderPoint(renderer, centerX - x, centerY - y);
        SDL_RenderPoint(renderer, centerX + y, centerY + x);
        SDL_RenderPoint(renderer, centerX + y, centerY - x);
        SDL_RenderPoint(renderer, centerX - y, centerY + x);
        SDL_RenderPoint(renderer, centerX - y, centerY - x);
    
        y++;

        if (error < 0) {
            error += 2 * y + 1;
        }
        else {
            x--;
            error += 2 * (y - x) + 1;
        }
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    std::visit(Overload{
        [&](const RectData& rect) {
            SDL_FRect r = getRect();
            SDL_RenderFillRect(renderer, &r);
        },
        [&](const CircleData& circle) {
            drawCircle(renderer);
        }
    }, shapeData);
}

void Particle::onCollision(Window* window, Object* other) {
    if (other->getType() == ObjectType::PARTICLE) {
        Particle* otherParticle = static_cast<Particle*>(other);

        glm::vec2 vDiff = this->velocity - otherParticle->getVelocity();
        glm::vec2 xDiff = this->getCenter() - otherParticle->getCenter();

        if (glm::dot(vDiff, xDiff) >= 0)
            return;

        glm::vec2 v1 = velocity;
        glm::vec2 v2 = otherParticle->getVelocity();
        
        handleAABBCollision(window, otherParticle);
        resolveCollision(window, otherParticle);
        
        this->calcNewVelocity(otherParticle);
        otherParticle->calcNewVelocity(this);
    }
}

float Particle::getRadius() const {
    if (auto* circle = std::get_if<CircleData>(&shapeData)) {
        return circle->radius;
    }

    return 0.0f;
}

void Particle::setRadius(float radius) {
    if (auto* circle = std::get_if<CircleData>(&shapeData)) {
        circle->radius = radius; 
    }
}