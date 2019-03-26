#include "RectangleBody.hpp"

////////////////////////////////////////////////////////////////////////////////
/// Creates a RectangleBody using already-initialized Box2D objects.
/// @param size The size of the fixture.
/// @param body The pre-initialized Box2D body.  Must have exactly one fixture.
/// @param world The sfb2 World that this body was created in.
////////////////////////////////////////////////////////////////////////////////
RectangleBody::RectangleBody(const Vector2f& size, b2Body* body, World& world) : Body(body, world), RectangleFixture(size, body->GetFixtureList(), *this) { }