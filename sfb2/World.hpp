#pragma once

#include <forward_list>
#include <functional>
#include <iostream>
#include <queue>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"
class CircleBody;
#include "CircleBody.hpp"
class RectangleBody;
#include "RectangleBody.hpp"

class World : public Drawable {

	public:
		float ppm; ///< The number of pixels per meter in this `World`.

		World(const Vector2f& gravity = Vector2f(0.0f, 9.807f), float pixelsPerMeter = 32.0f);
		World(float gravityDown, float pixelsPerMeter = 32.0f);

		RectangleBody& createRectangleBody(float x, float y, float width, float height, BodyType type);
		RectangleBody& createRectangleBody(const Vector2f& position, const Vector2f& size, BodyType type);
		RectangleBody& createRectangleBody(const FloatRect& rect, BodyType type);
		
		CircleBody& createCircleBody(float x, float y, float radius, BodyType type);
		CircleBody& createCircleBody(const Vector2f& position, float radius, BodyType type);
		
		void destroyBody(Body& body);

		void step(Time timeStep, int velocityIterations = 8, int positionIterations = 3);
		
		std::function<void(Body&, Body&)> onContactBegin;
		std::function<void(Body&, Body&)> onContactEnd;

	protected:
		b2World internalWorld; ///< The internal `b2World` represented by this `World`.  Use only if no other option exists.
		
		void draw(RenderTarget& target, RenderStates states) const;
		
	private:
		struct ContactListener : public b2ContactListener {
			std::queue<b2Contact*> queueBeginContact; 
			virtual void BeginContact(b2Contact* contact) {
				queueBeginContact.push(contact);
			}
			std::queue<b2Contact*> queueEndContact;
			virtual void EndContact(b2Contact* contact) {
				queueEndContact.push(contact);
			}
		} contactListener;

};