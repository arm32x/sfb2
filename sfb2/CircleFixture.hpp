#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class Fixture;
#include "Fixture.hpp"

class CircleFixture : public Fixture, private CircleShape {
	friend class Body;
	
	public:
		using CircleShape::getFillColor;
		using CircleShape::setFillColor;
		using CircleShape::getOutlineColor;
		using CircleShape::setOutlineColor;
		using CircleShape::getOutlineThickness;
		using CircleShape::setOutlineThickness;
		
		using CircleShape::getRadius;
		using CircleShape::getTransform;
		
		using CircleShape::getTexture;
		using CircleShape::setTexture;
		using CircleShape::getTextureRect;
		using CircleShape::setTextureRect;
		
	protected:
		CircleFixture(float radius, b2Fixture* fixture, Body& body);
		
		void update();
		void draw(RenderTarget& target, RenderStates states) const;
		
};
