#include "Fixture.hpp"
#include "Body.hpp"

Fixture::Fixture(Body& body) : body(body) {
	
}

bool Fixture::isTouching(const Vector2f& point) const {
	return internalFixture->TestPoint(b2Vec2(point.x / body.world.ppm, point.y / body.world.ppm));
}

bool Fixture::isSensor() const { return internalFixture->IsSensor(); }
void Fixture::setSensor(bool value) { internalFixture->SetSensor(value); }

bool Fixture::isVisible() const { return visible; }
void Fixture::setVisible(bool value) { visible = value; }
