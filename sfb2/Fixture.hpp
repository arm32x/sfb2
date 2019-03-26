#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Body.hpp"

class Fixture : public Drawable {
	
	public:
		void* userPointer;
		Body& body;
		
		bool isTouching(const Vector2f& point) const;
		std::function<void(Fixture&)> onContactBegin;
		std::function<void(Fixture&)> onContactEnd;
		
		bool isSensor() const;
		void setSensor(bool value);
		
		bool isVisible() const;
		void setVisible(bool visible);
		
	protected:
		Fixture(b2Fixture* fixture, Body& body);
		b2Fixture* internalFixture; ///< A pointer to the fixture that this class represents.  Use only if no other option exists.
		
		virtual void update() { }
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	
	private:
		bool visible = true;
		
};