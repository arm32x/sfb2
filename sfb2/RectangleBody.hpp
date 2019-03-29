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
		[[deprecated("The constructor taking in a Body& has a cleaner interface.")]]
		RectangleBody(const Vector2f& size, b2Body* body, World& world);
		RectangleBody(Body& body);
		
	private:
		using Body::getFixtureList;
		using Body::createRectangleFixture;
    
};
