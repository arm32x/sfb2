#include "Fixture.hpp"

Fixture::Fixture(b2Fixture* fixture, Body& body) : body(body), internalFixture(fixture) {
	internalFixture->SetUserData(this);
}

bool Body::isTouching(const Vector2f& point) const {
	for (b2Fixture* internalFixture = internalBody->GetFixtureList(); internalFixture != nullptr; internalFixture = internalFixture->GetNext()) {
		if (internalFixture->TestPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm))) return true;
	}
	return false;
}

bool Fixture::isSensor() const { return internalFixture->IsSensor(); }
bool Fixture::setSensor(bool value) { internalFixture->SetSensor(value); }
