#pragma once

#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Fixture.hpp"
#include "RectangleFixture.hpp"
class World;

enum BodyType {
    StaticBody = 0,
    KinematicBody = 1,
    DynamicBody = 2
};

class Body : public Drawable {
	friend class World;
	friend bool operator==(Body&, Body&);
	friend bool operator!=(Body&, Body&);

	public:
		void* userPointer = nullptr;
		World& world; ///< The `World` that this `Body` exists in.
		
		RectangleFixture& createRectangleFixture(float x, float y, float width, float height, BodyType type);
		RectangleFixture& createRectangleFixture(const Vector2f& position, const Vector2f& size, BodyType type);
		RectangleFixture& createRectangleFixture(const FloatRect& rect, BodyType type);
		
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
		
		std::vector<std::reference_wrapper<Fixture>> getFixtureList() const;

	protected:
		Body(b2Body* body, World& world);
		b2Body* internalBody; ///< A pointer to the `b2Body` represented by this `Body`.  Use only if no other option exists.
		
		virtual void update() { }
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	
};

bool operator==(const Body& lhs, const Body& rhs);
bool operator!=(const Body& lhs, const Body& rhs);

#include "World.hpp"