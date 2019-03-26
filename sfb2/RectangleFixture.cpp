#include "RectangleFixture.hpp"
#include "Body.hpp"

// TODO: Add support for offset/origin.
RectangleFixture::RectangleFixture(const Vector2f& size, b2Fixture* fixture, Body& body) : Fixture(fixture, body), RectangleShape(size) {
	setOrigin(size / 2.0f);
	update();
}

void RectangleFixture::update() {
	setPosition(body.getPosition());
	setRotation(body.getRotation());
}
void RectangleFixture::draw(RenderTarget& target, RenderStates states) const {
	target.draw(static_cast<RectangleShape>(*this));
}