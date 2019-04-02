#include "RectangleFixture.hpp"
#include "Body.hpp"

RectangleFixture::RectangleFixture(Body& body, float x, float y, float width, float height) : Fixture(body), RectangleShape(Vector2f(width, height)) {
	b2FixtureDef def;
	def.density = 1.0f;
	def.friction = 0.4f;
	def.restitution = 0.5f;
	
	b2PolygonShape shape;
	shape.SetAsBox(width / body.world.ppm / 2.0f, height / body.world.ppm / 2.0f, b2Vec2(x / body.world.ppm, y / body.world.ppm), 0.0f);
	def.shape = &shape;
	
	internalFixture = body.internalBody->CreateFixture(&def);
	internalFixture->SetUserData(this);
	setOrigin(width / 2.0f - x, height / 2.0f - y);
}
RectangleFixture::RectangleFixture(Body& body, const Vector2f& position, const Vector2f& size) : RectangleFixture(body, position.x, position.y, size.x, size.y) { }
RectangleFixture::RectangleFixture(Body& body, const FloatRect& rect) : RectangleFixture(body, rect.left + rect.width / 2.0f, rect.left + rect.width / 2.0f, rect.width, rect.height) {
	setOrigin(rect.left, rect.top);
}

void RectangleFixture::update() {
	setPosition(body.getPosition());
	setRotation(body.getRotation());
}
void RectangleFixture::draw(RenderTarget& target, RenderStates states) const {
	target.draw(static_cast<RectangleShape>(*this));
}