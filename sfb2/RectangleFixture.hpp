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
		RectangleFixture(const Vector2f& size, b2Fixture* fixture, Body& body);
		
		void update();
		void draw(RenderTarget& target, RenderStates states) const;
		
};
