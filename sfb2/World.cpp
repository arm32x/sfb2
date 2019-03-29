#include "World.hpp"

World::World(const Vector2f& gravity, float pixelsPerMeter) : ppm(pixelsPerMeter), internalWorld(b2Vec2(gravity.x, gravity.y)) {
	internalWorld.SetContactListener(&contactListener);
}
World::World(float gravityDown, float pixelsPerMeter) : World(Vector2f(0.0f, gravityDown), pixelsPerMeter) { }

RectangleBody& World::createRectangleBody(float x, float y, float width, float height, BodyType type) {
	Body& body = createBody(x, y, type);
	body.createRectangleFixture(0, 0, width, height);
	RectangleBody* ptr = new RectangleBody(body);
	return *ptr;
}
RectangleBody& World::createRectangleBody(const Vector2f& position, const Vector2f& size, BodyType type) {
	return createRectangleBody(position.x, position.y, size.x, size.y, type);
}
RectangleBody& World::createRectangleBody(const FloatRect& rect, BodyType type) {
	// TODO: Replace this with a version that sets the origin of the fixture.
	return createRectangleBody(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f, rect.width, rect.height, type);
}

/*CircleBody& World::createCircleBody(float x, float y, float radius, BodyType type) {
	b2BodyDef bodyDef;
	bodyDef.position.Set(x / ppm, y / ppm);
	bodyDef.type = static_cast<b2BodyType>(type);
	bodyDef.linearDamping = 0.05f;
	
	b2CircleShape bodyShape;
	bodyShape.m_radius = radius / ppm;
	
	b2FixtureDef fixDef;
	fixDef.density = 1.0f;
	fixDef.friction = 0.4f;
	fixDef.restitution = 0.5f;
	
	fixDef.shape = &bodyShape;
	b2Body* body = internalWorld.CreateBody(&bodyDef);
	body->CreateFixture(&fixDef);
	
	CircleBody* wrapper = new CircleBody(radius, body, *this);
	return *wrapper;
}
CircleBody& World::createCircleBody(const Vector2f& position, float radius, BodyType type) {
	return createCircleBody(position.x, position.y, radius, type);
}*/

Body& World::createBody(float x, float y, BodyType type) {
	// TODO: Implement this.
}
Body& World::createBody(const Vector2f& position, BodyType type) {
	return createBody(position.x, position.y, type);
}

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