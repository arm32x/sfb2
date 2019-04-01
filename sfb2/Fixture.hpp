#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class Body;

class Fixture : public Drawable {
	friend class Body;
	
	public:
		void* userPointer;
		Body& body;
		b2Fixture* internalFixture; ///< A pointer to the fixture that this class represents.  Use only if no other option exists.
		
		bool isTouching(const Vector2f& point) const;
		std::function<void(Fixture&)> onContactBegin;
		std::function<void(Fixture&)> onContactEnd;
		
		bool isSensor() const;
		void setSensor(bool value);
		
		bool isVisible() const;
		void setVisible(bool visible);
		
	protected:
		Fixture(Body& body);
		
		virtual void update() { }
	
	private:
		bool visible = true;
		
};