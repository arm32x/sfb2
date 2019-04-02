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
		CircleBody(World& world, float x, float y, float radius, BodyType type);
		CircleBody(World& world, const Vector2f& position, float radius, BodyType type);
		
	private:
		using Body::createRectangleFixture;
		using Body::createCircleFixture;
		using Body::getFixtureList;
	
};