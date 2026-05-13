#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"
#include "physicsConfig.hpp"

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

Particle::Particle(
    glm::vec2 center,
    float radius,
    glm::vec2 velocity,
    float mass,
    SDL_Color color
) :
    Object(center, radius, color, true),
    velocity(velocity),
    mass(mass)
{}

Particle::~Particle() {}

void Particle::calcNewVelocity(Particle* other) {
    float mRatio = ((1 + PhysicsConfig::Cr) * other->getMass()) / (mass + other->getMass());

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

        this->calcNewVelocity(other);
        other->calcNewVelocity(this);
    }
}

void Particle::update(Window* window, float deltaTime) {
    this->velocity += PhysicsConfig::gravity * deltaTime;
    glm::vec2 positionChanged = velocity * deltaTime;
    this->updatePosition(positionChanged);

    if (std::abs(this->velocity.x) < 0.1f) 
        this->velocity.x = 0;
    if (std::abs(this->velocity.y) < 0.1f)
        this->velocity.y = 0;

    SDL_FRect boundingBox = this->getBoundingBox();

    //floor
    if (boundingBox.y + boundingBox.h / 2.0f > window->logHeight()) {
        this->setCenter({ this->getCenter().x, window->logHeight() - boundingBox.h / 2.0f });
        this->velocity.y *= -PhysicsConfig::Cr;
    }

    //ceiling
    if (boundingBox.y - boundingBox.h / 2.0f < 0) {
        this->setCenter({ this->getCenter().x, boundingBox.h / 2.0f });
        this->velocity.y *= -PhysicsConfig::Cr;
    }

    //left wall
    if (boundingBox.x - boundingBox.w / 2.0f < 0) {
        this->setCenter({ boundingBox.w / 2.0f, this->getCenter().y });
        this->velocity.x *= -PhysicsConfig::Cr;
    }

    //right wall
    if (boundingBox.x + boundingBox.w / 2.0f > window->logWidth()) {
        this->setCenter({ (float) window->logWidth() - boundingBox.w / 2.0f, this->getCenter().y });
        this->velocity.x *= -PhysicsConfig::Cr;
    }
}

void Particle::drawCircle(SDL_Renderer* renderer) {

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
    //hit another particle
    if (other->getType() == ObjectType::PARTICLE) {
        Particle* otherParticle = static_cast<Particle*>(other);

        glm::vec2 vDiff = this->velocity - otherParticle->getVelocity();
        glm::vec2 xDiff = this->getCenter() - otherParticle->getCenter();

        if (glm::dot(vDiff, xDiff) >= 0)
            return;

        glm::vec2 v1 = velocity;
        glm::vec2 v2 = otherParticle->getVelocity();
        
        handleAABBCollision(otherParticle);
        
        this->calcNewVelocity(otherParticle);
        otherParticle->calcNewVelocity(this);
    }
}

void Particle::createNewParticle(Window* window, std::vector<std::unique_ptr<Object>> &objects, glm::vec2 launchVelocity, glm::vec2 launchPosition) {
    float mass = 1;
    float sizeX = 10;
    float sizeY = 10;

    glm::vec2 newSize = glm::vec2(sizeX, sizeY);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<Uint8> distr(0, 255);
    SDL_Color color = {distr(gen), distr(gen), distr(gen), distr(gen)};

    Particle particle(launchPosition, newSize, launchVelocity, mass, color);
    objects.push_back(std::make_unique<Particle>(particle));
}