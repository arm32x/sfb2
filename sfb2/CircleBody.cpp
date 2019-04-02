#include "CircleBody.hpp"

CircleBody::CircleBody(World& world, float x, float y, float radius, BodyType type) : Body(world, x, y, type), CircleFixture(*this, 0, 0, radius) { }
CircleBody::CircleBody(World& world, const Vector2f& position, float radius, BodyType type) : Body(world, position, type), CircleFixture(*this, Vector2f(0, 0), radius) { }
