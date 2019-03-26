#include "CircleBody.hpp"

CircleBody::CircleBody(float radius, b2Body* body, World& world) : Body(body, world), internalShape(radius) {
	internalShape.setOrigin(radius, radius);
	update();
}

const Color& CircleBody::getFillColor() const { return internalShape.getFillColor(); }
void CircleBody::setFillColor(const Color& color) { internalShape.setFillColor(color); }
const Color& CircleBody::getOutlineColor() const { return internalShape.getOutlineColor(); }
void CircleBody::setOutlineColor(const Color& color) { internalShape.setOutlineColor(color); }
float CircleBody::getOutlineThickness() const { return internalShape.getOutlineThickness(); }
void CircleBody::setOutlineThickness(float thickness) { internalShape.setOutlineThickness(thickness); }

float CircleBody::getRadius() const { return internalShape.getRadius(); }

void CircleBody::update() {
	internalShape.setPosition(getPosition());
	internalShape.setRotation(getRotation());
}
void CircleBody::draw(RenderTarget& target, RenderStates states) const {
	target.draw(internalShape);
}
