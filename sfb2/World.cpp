#include "World.hpp"

World::World(const Vector2f& gravity, float pixelsPerMeter) : ppm(pixelsPerMeter), internalWorld(b2Vec2(gravity.x, gravity.y)) {
	internalWorld.SetContactListener(&contactListener);
}
World::World(float gravityDown, float pixelsPerMeter) : World(Vector2f(0.0f, gravityDown), pixelsPerMeter) { }

RectangleBody& World::createRectangleBody(float x, float y, float width, float height, BodyType type) {
	return *new RectangleBody(*this, x, y, width, height, type);
}
RectangleBody& World::createRectangleBody(const Vector2f& position, const Vector2f& size, BodyType type) {
	return *new RectangleBody(*this, position, size, type);
}
RectangleBody& World::createRectangleBody(const FloatRect& rect, BodyType type) {
	return *new RectangleBody(*this, rect, type);
}

Body& World::createBody(float x, float y, BodyType type) { return *new Body(*this, x, y, type); }
Body& World::createBody(const Vector2f& position, BodyType type) { return *new Body(*this, position, type); }

void World::destroyBody(Body& body) {
	internalWorld.DestroyBody(body.internalBody);
	delete &body;
}

void World::step(Time timeStep, int velocityIterations, int positionIterations) {
	internalWorld.Step(timeStep.asSeconds(), velocityIterations, positionIterations);
	std::queue<b2Contact*>* queue;
	queue = &contactListener.queueBeginContact;
	for (b2Contact* contact = queue->front(); !queue->empty(); queue->pop(), contact = queue->front()) {
		Fixture& fixtureA = *static_cast<Fixture*>(contact->GetFixtureA()->GetUserData());
		Fixture& fixtureB = *static_cast<Fixture*>(contact->GetFixtureB()->GetUserData());
		if (fixtureA.onContactEnd != nullptr) fixtureA.onContactEnd(fixtureB);
		if (fixtureB.onContactEnd != nullptr) fixtureB.onContactEnd(fixtureA);
		if (this->onContactEnd != nullptr) this->onContactEnd(fixtureA, fixtureB);
	}
	queue = &contactListener.queueEndContact;
	for (b2Contact* contact = queue->front(); !queue->empty(); queue->pop(), contact = queue->front()) {
		Fixture& fixtureA = *static_cast<Fixture*>(contact->GetFixtureA()->GetUserData());
		Fixture& fixtureB = *static_cast<Fixture*>(contact->GetFixtureB()->GetUserData());
		if (fixtureA.onContactEnd != nullptr) fixtureA.onContactEnd(fixtureB);
		if (fixtureB.onContactEnd != nullptr) fixtureB.onContactEnd(fixtureA);
		if (this->onContactEnd != nullptr) this->onContactEnd(fixtureA, fixtureB);
	}
	for (b2Body* internalBody = internalWorld.GetBodyList(); internalBody != nullptr; internalBody = internalBody->GetNext()) {
		Body& body = *static_cast<Body*>(internalBody->GetUserData());
		body.update();
	}
}
void World::draw(RenderTarget& target, RenderStates states) const {
	for (const b2Body* internalBody = internalWorld.GetBodyList(); internalBody != nullptr; internalBody = internalBody->GetNext()) {
		Body& body = *static_cast<Body*>(internalBody->GetUserData());
		target.draw(body);
	}
}