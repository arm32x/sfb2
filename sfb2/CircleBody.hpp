#pragma once

#include <Box2d/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"
#include "World.hpp"

class CircleBody : public Body {
	friend class World;
	
public:
	const Color& getFillColor() const;
	void setFillColor(const Color& color);
	const Color& getOutlineColor() const;
	void setOutlineColor(const Color& color);
	float getOutlineThickness() const;
	void setOutlineThickness(float thickness);
	
	float getRadius() const;
	
protected:
	CircleShape internalShape;
	
	CircleBody(float radius, b2Body* body, World& world);
	
	void update();
	void draw(RenderTarget& target, RenderStates states) const;
	
};
