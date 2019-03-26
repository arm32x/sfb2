#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"
#include "CircleFixture.hpp"
class World;

class CircleBody : public Body, public CircleFixture {
	friend class World;
	
	public:
		using Body::getPosition;
		using Body::setPosition;
		using Body::getRotation;
		using Body::setRotation;

	protected:
		CircleBody(float radius, b2Body* body, World& world);
		
	private:
		using Body::getFixtureList;
		using Body::createRectangleFixture;
    
};
