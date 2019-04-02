#include "RectangleBody.hpp"

RectangleBody::RectangleBody(World& world, float x, float y, float width, float height, BodyType type) : Body(world, x, y, type), RectangleFixture(*this, 0, 0, width, height) { }
RectangleBody::RectangleBody(World& world, const Vector2f& position, const Vector2f& size, BodyType type) : Body(world, position, type), RectangleFixture(*this, Vector2f(0, 0), size) { }
RectangleBody::RectangleBody(World& world, const FloatRect& rect, BodyType type) : Body(world, rect.left, rect.top, type), RectangleFixture(*this, rect.width / 2.0f, rect.height / 2.0f, rect.width, rect.height) { }
