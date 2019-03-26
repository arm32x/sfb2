#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"
#include "Utilities.hpp"
#include "World.hpp"

class World;

class RectangleBody : public Body {
	friend class World;
	
public:
	const Color& getFillColor() const;
	void setFillColor(const Color& color);
	const Color& getOutlineColor() const;
	void setOutlineColor(const Color& color);
	float getOutlineThickness() const;
	void setOutlineThickness(float thickness);
	
	const Vector2f& getSize() const;

protected:
	RectangleShape internalShape;

    RectangleBody(const Vector2f& size, b2Body* body, World& world);
    
    void update();
    void draw(RenderTarget& target, RenderStates states) const;
    
};
