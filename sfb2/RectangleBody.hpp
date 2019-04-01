#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"
#include "RectangleFixture.hpp"
class World;

class RectangleBody : public Body, public RectangleFixture {
	friend class World;
	
	public:
		using Body::getPosition;
		using Body::setPosition;
		using Body::getRotation;
		using Body::setRotation;

	protected:
		RectangleBody(World& world, float x, float y, float width, float height, BodyType type);
		RectangleBody(World& world, const Vector2f& position, const Vector2f& size, BodyType type);
		RectangleBody(World& world, const FloatRect& rect, BodyType type);
		
	private:
		using Body::getFixtureList;
		using Body::createRectangleFixture;
    
};
