#include "RectangleFixture.hpp"
#include "Body.hpp"

// TODO: Add support for offset/origin.
CircleFixture::CircleFixture(float radius, b2Fixture* fixture, Body& body) : Fixture(fixture, body), CircleShape(radius) {
	setOrigin(radius, radius);
	update();
}

void RectangleFixture::update() {
	setPosition(body.getPosition());
}
void RectangleFixture::draw(RenderTarget& target, RenderStates states) const {
	target.draw(static_cast<CircleShape>(*this));
}