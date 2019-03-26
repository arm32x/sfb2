#pragma once

#include <bitset>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
using namespace sf;

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
	
	float getLinearDamping() const;
	void setLinearDamping(float linearDamping);
	float getAngularDamping() const;
	void setAngularDamping(float angularDamping);
	
	bool isTouching() const;
	bool isTouching(Body& other) const;
	bool isTouching(const Vector2f& point) const;
	
	// TODO: Move these to an additional Fixture class and support fixtures in the library.
	bool isSensor() const;
	void setSensor(bool value);
	
	bool isActive() const;
	void setActive(bool active);
	bool isVisible() const;
	void setVisible(bool visible);
	
	std::function<void(Body&)> onContactBegin;
	std::function<void(Body&)> onContactEnd;
	
	virtual ~Body() = default;

protected:
	Body(b2Body* body, World& world);
	
	virtual void update() { };
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	
private:
	bool visible = true;
	
};

bool operator==(const Body& lhs, const Body& rhs);
bool operator!=(const Body& lhs, const Body& rhs);

#include "World.hpp"