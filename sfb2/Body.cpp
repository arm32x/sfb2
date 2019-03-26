#include "Body.hpp"

Body::Body(b2Body* body, World& world) : world(world), internalBody(body) {
	body->SetUserData(this);
}

Vector2f Body::getPosition() const {
	return Vector2f(internalBody->GetPosition().x * world.ppm, internalBody->GetPosition().y * world.ppm);
}
void Body::setPosition(float x, float y) {
	internalBody->SetTransform(b2Vec2(x / world.ppm, y / world.ppm), internalBody->GetAngle());
}
void Body::setPosition(const Vector2f& position) {
	setPosition(position.x, position.y);
}
float Body::getRotation() const {
	return internalBody->GetAngle() * (180 / PI);
}
void Body::setRotation(float angle)  {
	internalBody->SetTransform(internalBody->GetPosition(), angle * (PI / 180));
}

Vector2f Body::getLocalCenter() const {
	return Vector2f(internalBody->GetLocalCenter().x * world.ppm, internalBody->GetLocalCenter().y * world.ppm);
}
Vector2f Body::getGlobalCenter() const {
	return Vector2f(internalBody->GetWorldCenter().x * world.ppm, internalBody->GetWorldCenter().y * world.ppm);
}

Vector2f Body::getVelocity() const {
	return Vector2f(internalBody->GetLinearVelocity().x * world.ppm, internalBody->GetLinearVelocity().y * world.ppm);
}
void Body::setVelocity(float x, float y) {
	internalBody->SetLinearVelocity(b2Vec2(x / world.ppm, y / world.ppm));
}
void Body::setVelocity(const Vector2f& velocity) {
	setVelocity(velocity.x, velocity.y);
}
float Body::getAngularVelocity() const {
	return internalBody->GetAngularVelocity() * (180 / PI);
}
void Body::setAngularVelocity(float velocity) {
	internalBody->SetAngularVelocity(velocity * (PI / 180));
}
Vector2f Body::getVelocityAtLocalPoint(const Vector2f& point) const {
	return Vector2f(internalBody->GetLinearVelocityFromLocalPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm)).x * world.ppm, internalBody->GetLinearVelocityFromLocalPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm)).y * world.ppm);
}
Vector2f Body::getVelocityAtGlobalPoint(const Vector2f& point) const {
	return Vector2f(internalBody->GetLinearVelocityFromWorldPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm)).x * world.ppm, internalBody->GetLinearVelocityFromWorldPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm)).y * world.ppm);
}

void Body::applyForceToGlobalPoint(const Vector2f& force, const Vector2f& point, bool wake) {
	internalBody->ApplyForce(b2Vec2(force.x / world.ppm, force.y / world.ppm), b2Vec2(point.x / world.ppm, point.y / world.ppm), wake);
}
void Body::applyForceToLocalPoint(const Vector2f& force, const Vector2f& point, bool wake) {
	applyForceToGlobalPoint(force, Utilities::localToGlobalPoint(point, *this), wake);
}
void Body::applyForceToCenter(const Vector2f& force, bool wake) {
	applyForceToLocalPoint(force, Vector2f(0.0f, 0.0f), wake);
}
void Body::applyTorque(float torque, bool wake) {
	internalBody->ApplyTorque(torque * (PI / 180), wake);
}

void Body::applyLinearImpulseToGlobalPoint(const Vector2f& impulse, const Vector2f& point, bool wake) {
	internalBody->ApplyLinearImpulse(b2Vec2(impulse.x / world.ppm, impulse.y / world.ppm), b2Vec2(point.x / world.ppm, point.y / world.ppm), wake);
}
void Body::applyLinearImpulseToLocalPoint(const Vector2f& impulse, const Vector2f& point, bool wake) {
	applyLinearImpulseToGlobalPoint(impulse, Utilities::localToGlobalPoint(point, *this), wake);
}
void Body::applyLinearImpulseToCenter(const Vector2f& impulse, bool wake) {
	applyLinearImpulseToLocalPoint(impulse, Vector2f(0.0f, 0.0f), wake);
}
void Body::applyAngularImpulse(float impulse, bool wake) {
	internalBody->ApplyAngularImpulse(impulse * (PI / 180), wake);
}

bool Body::isTouching() const {
	for (b2ContactEdge* edge = internalBody->GetContactList(); edge != nullptr; edge = edge->next) {
		if (edge->contact->IsTouching()) return true;
	}
	return false;
}
bool Body::isTouching(Body& other) const {
	for (b2ContactEdge* edge = internalBody->GetContactList(); edge != nullptr; edge = edge->next) {
		if (edge->other == other.internalBody && edge->contact->IsTouching()) return true;
	}
	return false;
}
bool Body::isTouching(const Vector2f& point) const {
	for (b2Fixture* internalFixture = internalBody->GetFixtureList(); internalFixture != nullptr; internalFixture = internalFixture->GetNext()) {
		if (internalFixture->TestPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm))) return true;
	}
	return false;
}

float Body::getLinearDamping() const { return internalBody->GetLinearDamping(); }
void Body::setLinearDamping(float linearDamping) { internalBody->SetLinearDamping(linearDamping); }
float Body::getAngularDamping() const { return internalBody->GetAngularDamping(); }
void Body::setAngularDamping(float angularDamping) { internalBody->SetAngularDamping(angularDamping); }

bool Body::isSensor() const {
	for (b2Fixture* internalFixture = internalBody->GetFixtureList(); internalFixture != nullptr; internalFixture = internalFixture->GetNext()) {
		if (!internalFixture->IsSensor()) return false;
	}
	return true;
}
void Body::setSensor(bool value) {
	for (b2Fixture* internalFixture = internalBody->GetFixtureList(); internalFixture != nullptr; internalFixture = internalFixture->GetNext()) {
		internalFixture->SetSensor(value);
	}
}

bool Body::isActive() const { return internalBody->IsActive(); }
void Body::setActive(bool active) { internalBody->SetActive(active); }
bool Body::isVisible() const { return visible; }
void Body::setVisible(bool visible) { this->visible = visible; }

bool operator==(const Body& lhs, const Body& rhs) { return lhs.internalBody == rhs.internalBody; }
bool operator!=(const Body& lhs, const Body& rhs) { return !(lhs == rhs); }
