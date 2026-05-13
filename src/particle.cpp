#include <iostream>
#include <math.h>
#include <algorithm>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(
    glm::vec2 position, 
    glm::vec2 size, 
    glm::vec2 velocity, 
    float mass, 
    SDL_Color color
) : 
    Object(position, size, color, true), 
    velocity(velocity), 
    mass(mass)
{}

Particle::~Particle() {}

void Particle::calcNewVelocity(Particle* other) {
    float mRatio = ((1 + Cr) * other->getMass()) / (mass + other->getMass());

    glm::vec2 vDiff = velocity - other->getVelocity();
    glm::vec2 xDiff = this->getCenter() - other->getCenter();

    float dotProduct = glm::dot(vDiff, xDiff);
    float sqLength = glm::dot(xDiff, xDiff);

    glm::vec2 newVelocity = velocity - mRatio * (dotProduct / sqLength) * xDiff;
    velocity = newVelocity;
}

void Particle::handleAABBCollision(Particle* other) {
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
    }
}

void Particle::handleCircularCollision(Particle* other) {
    
}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100;
    // this->velocity.y += gravity * deltaTime;
    glm::vec2 positionChanged = velocity * deltaTime;
    this->updatePosition(positionChanged);

    SDL_FRect boundingBox = this->getBoundingBox();

    //floor
    if (boundingBox.y + boundingBox.h > window->logHeight()) {
        glm::vec2 newCenter = { this->getCenter().x, window->logHeight() - boundingBox.h };
        this->setCenter(newCenter);
        if (this->velocity.y)
            this->velocity.y *= -Cr;
    }

    //ceiling
    if (boundingBox.y - boundingBox.h < 0) {
        glm::vec2 newCenter = { this->getCenter().x, 0 };
        this->setCenter(newCenter);
        if (this->velocity.y)
            this->velocity.y *= -Cr;
    }

    //left wall
    if (boundingBox.x - boundingBox.w < 0) {
        glm::vec2 newCenter = { 0, this->getCenter().y };
        this->setCenter(newCenter);
        if (this->velocity.x)
            this->velocity.x *= -Cr;
    }

    //right wall
    if (boundingBox.x + boundingBox.w > window->logWidth()) {
        glm::vec2 newCenter = { window->logWidth() - boundingBox.w, this->getCenter().y }; 
        this->setCenter(newCenter);
        if (this->velocity.x)
            this->velocity.x *= -Cr;
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (this->isCircle()) {

    }
    else if (this->isRect()) {
        SDL_FRect currentRect = this->getRect();
        SDL_RenderFillRect(renderer, &currentRect);
    }
}

void Particle::onCollision(Window* window, Object* other) {
    //hit another particle
    if (other->getType() == ObjectType::PARTICLE) {
        Particle* otherParticle = static_cast<Particle*>(other);

        glm::vec2 vDiff = this->velocity - otherParticle->getVelocity();
        glm::vec2 xDiff = this->getCenter() - otherParticle->getCenter();

        if (glm::dot(vDiff, xDiff) >= 0)
            return;

        glm::vec2 v1 = velocity;
        glm::vec2 v2 = otherParticle->getVelocity();
        
        if (this->isRect()) {
            handleAABBCollision(otherParticle);
        }
        else if (this->isCircle()) {
            handleCircularCollision(otherParticle);
        }
        
        this->calcNewVelocity(otherParticle);
        otherParticle->calcNewVelocity(this);
    }
}