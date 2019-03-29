#include "RectangleBody.hpp"

////////////////////////////////////////////////////////////////////////////////
/// Creates a RectangleBody using already-initialized Box2D objects.
/// @param size The size of the fixture.
/// @param body The pre-initialized Box2D body.  Must have exactly one fixture.
/// @param world The sfb2 World that this body was created in.
/// @deprecated
////////////////////////////////////////////////////////////////////////////////
RectangleBody::RectangleBody(const Vector2f& size, b2Body* body, World& world) : Body(body, world), RectangleFixture(size, body->GetFixtureList(), *this) { }

////////////////////////////////////////////////////////////////////////////////
/// Creates a RectangleBody using the properties of the Body& passed in.
/// @warning This will throw an std::bad_cast exception if the body’s first
/// fixture is not a RectangleFixture.
/// @param body The body to create the RectangleBody out of.
////////////////////////////////////////////////////////////////////////////////
RectangleBody::RectangleBody(Body& body) : Body(body), RectangleFixture(dynamic_cast<RectangleFixture&>(body.getFixtureList()[0])) { }