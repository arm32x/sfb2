#pragma once

#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class CircleFixture;
#include "CircleFixture.hpp"
#include "Fixture.hpp"
#include "FixtureList.hpp"
#include "RectangleFixture.hpp"
#include "Utilities.hpp"
class World;

enum class BodyType {
    StaticBody = 0,
    KinematicBody = 1,
    DynamicBody = 2
};

class Body : public Drawable {
	friend class World;

	public:
		void* userPointer = nullptr;
		World& world; ///< The `World` that this `Body` exists in.
		b2Body* internalBody; ///< A pointer to the `b2Body` represented by this `Body`.  Use only if no other option exists.
		
		RectangleFixture& createRectangleFixture(float x, float y, float width, float height);
		RectangleFixture& createRectangleFixture(const Vector2f& position, const Vector2f& size);
		RectangleFixture& createRectangleFixture(const FloatRect& rect);
		CircleFixture& createCircleFixture(float x, float y, float radius);
		CircleFixture& createCircleFixture(const Vector2f& position, float radius);
		
		Vector2f getPosition() const;
		void setPosition(float x, float y);
		void setPosition(const Vector2f& position);
		float getRotation() const;
		void setRotation(float angle);
		
		Vector2f getLocalCenter() const;
		Vector2f getGlobalCenter() const;
		
		Vector2f getVelocity() const;
		void setVelocity(float x, float y);
		void setVelocity(const Vector2f& velocity);
		float getAngularVelocity() const;
		void setAngularVelocity(float velocity);
		Vector2f getVelocityAtLocalPoint(const Vector2f& point) const;
		Vector2f getVelocityAtGlobalPoint(const Vector2f& point) const;
		
		void applyForceToGlobalPoint(const Vector2f& force, const Vector2f& point, bool wake = true);
		void applyForceToLocalPoint(const Vector2f& force, const Vector2f& point, bool wake = true);
		void applyForceToCenter(const Vector2f& force, bool wake = true);
		void applyTorque(float torque, bool wake = true);
		
		void applyLinearImpulseToGlobalPoint(const Vector2f& impulse, const Vector2f& point, bool wake = true);
		void applyLinearImpulseToLocalPoint(const Vector2f& impulse, const Vector2f& point, bool wake = true);
		void applyLinearImpulseToCenter(const Vector2f& impulse, bool wake = true);
		void applyAngularImpulse(float angularImpulse, bool wake = true);
		
		bool isTouching() const;
		bool isTouching(Body& other) const;
		bool isTouching(const Vector2f& point) const;
		
		float getLinearDamping() const;
		void setLinearDamping(float linearDamping);
		float getAngularDamping() const;
		void setAngularDamping(float angularDamping);
		
		bool isActive() const;
		void setActive(bool active);
		
		virtual ~Body() = default;
		
		FixtureList getFixtureList() const;

	protected:
		Body(World& world, float x, float y, BodyType type);
		Body(World& world, const Vector2f& position, BodyType type);
		
		void update();
		void draw(RenderTarget& target, RenderStates states) const;
	
};

bool operator==(const Body& lhs, const Body& rhs);
bool operator!=(const Body& lhs, const Body& rhs);

#include "World.hpp"