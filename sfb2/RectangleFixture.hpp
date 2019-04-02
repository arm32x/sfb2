#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class Fixture;
#include "Fixture.hpp"

class RectangleFixture : public Fixture, private RectangleShape {
	friend class Body;
	
	public:
		using RectangleShape::getFillColor;
		using RectangleShape::setFillColor;
		using RectangleShape::getOutlineColor;
		using RectangleShape::setOutlineColor;
		using RectangleShape::getOutlineThickness;
		using RectangleShape::setOutlineThickness;
		
		using RectangleShape::getSize;
		using RectangleShape::getTransform;
		
		using RectangleShape::getTexture;
		using RectangleShape::setTexture;
		using RectangleShape::getTextureRect;
		using RectangleShape::setTextureRect;
		
	protected:
		RectangleFixture(Body& body, float x, float y, float width, float height);
		RectangleFixture(Body& body, const Vector2f& position, const Vector2f& size);
		RectangleFixture(Body& body, const FloatRect& rect);
		
		virtual void update();
		void draw(RenderTarget& target, RenderStates states) const;
		
};
