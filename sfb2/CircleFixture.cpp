#include "CircleFixture.hpp"

CircleFixture::CircleFixture(Body& body, float x, float y, float radius) : Fixture(body), CircleShape(radius) {
	b2FixtureDef def;
	def.density = 1.0f;
	def.friction = 1.0f;
	def.restitution = 0.5f;
	
	b2CircleShape shape;
	shape.m_radius = radius / body.world.ppm;
	shape.m_p.Set(x / body.world.ppm, y / body.world.ppm);
	def.shape = &shape;
	
	internalFixture = body.internalBody->CreateFixture(&def);
	internalFixture->SetUserData(this);
	setOrigin(radius - x, radius - y);
}
CircleFixture::CircleFixture(Body& body, const Vector2f& position, float radius) : CircleFixture(body, position.x, position.y, radius) { }

void CircleFixture::update() {
	setPosition(body.getPosition());
	setRotation(body.getRotation());
}
void CircleFixture::draw(RenderTarget& target, RenderStates states) const {
	target.draw(static_cast<CircleShape>(*this));
}
