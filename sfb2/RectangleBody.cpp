#include "RectangleBody.hpp"

RectangleBody::RectangleBody(const Vector2f& size, b2Body* body, World& world) : Body(body, world), internalShape(size) {
	internalShape.setOrigin(size.x / 2.0f, size.y / 2.0f);
	update();
}

const Color& RectangleBody::getFillColor() const { return internalShape.getFillColor(); }
void RectangleBody::setFillColor(const Color& color) { internalShape.setFillColor(color); }
const Color& RectangleBody::getOutlineColor() const { return internalShape.getOutlineColor(); }
void RectangleBody::setOutlineColor(const Color& color) { internalShape.setOutlineColor(color); }
float RectangleBody::getOutlineThickness() const { return internalShape.getOutlineThickness(); }
void RectangleBody::setOutlineThickness(float thickness) { internalShape.setOutlineThickness(thickness); }

const Vector2f& RectangleBody::getSize() const { return internalShape.getSize(); }

void RectangleBody::update() {
	internalShape.setPosition(getPosition());
	internalShape.setRotation(getRotation());
}
void RectangleBody::draw(RenderTarget& target, RenderStates states) const {
	target.draw(internalShape);
}