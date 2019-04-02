#include "Body.hpp"

Body::Body(World& world, float x, float y, BodyType type) : world(world) {
	b2BodyDef def;
	def.position.Set(x / world.ppm, y / world.ppm);
	def.type = static_cast<b2BodyType>(type);
	def.linearDamping = 0.05f;
	
	internalBody = world.internalWorld.CreateBody(&def);
	internalBody->SetUserData(this);
}
Body::Body(World& world, const Vector2f& position, BodyType type) : Body(world, position.x, position.y, type) { }

RectangleFixture& Body::createRectangleFixture(float x, float y, float width, float height) { return *new RectangleFixture(*this, x, y, width, height); }
RectangleFixture& Body::createRectangleFixture(const Vector2f& position, const Vector2f& size) { return *new RectangleFixture(*this, position, size); }
RectangleFixture& Body::createRectangleFixture(const FloatRect& rect) { return *new RectangleFixture(*this, rect); }
CircleFixture& Body::createCircleFixture(float x, float y, float radius) { return *new CircleFixture(*this, x, y, radius); }
CircleFixture& Body::createCircleFixture(const Vector2f& position, float radius) { return *new CircleFixture(*this, position.x, position.y, radius); }

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
	for (Fixture& fixture : getFixtureList()) {
		if (fixture.internalFixture->TestPoint(b2Vec2(point.x / world.ppm, point.y / world.ppm))) return true;
	}
	return false;
}

float Body::getLinearDamping() const { return internalBody->GetLinearDamping(); }
void Body::setLinearDamping(float linearDamping) { internalBody->SetLinearDamping(linearDamping); }
float Body::getAngularDamping() const { return internalBody->GetAngularDamping(); }
void Body::setAngularDamping(float angularDamping) { internalBody->SetAngularDamping(angularDamping); }

bool Body::isActive() const { return internalBody->IsActive(); }
void Body::setActive(bool active) { internalBody->SetActive(active); }

FixtureList Body::getFixtureList() const {
	return FixtureList(internalBody->GetFixtureList());
}

void Body::update() {
	for (Fixture& fixture : getFixtureList()) {
		fixture.update();
	}
}
void Body::draw(RenderTarget& target, RenderStates states) const {
	for (Fixture& fixture : getFixtureList()) {
		if (fixture.isVisible()) target.draw(fixture);
	}
}

bool operator==(const Body& lhs, const Body& rhs) { return lhs.internalBody == rhs.internalBody; }
bool operator!=(const Body& lhs, const Body& rhs) { return !(lhs == rhs); }
