#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class Body;
#include "Fixture.hpp"

class RectangleFixture : public Fixture, protected RectangleShape {
	
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
	
};
