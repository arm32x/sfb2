#include "Utilities.hpp"

Vector2f Utilities::localToGlobalPoint(const Vector2f& localPoint, const Body& body) {
	const b2Vec2& result = body.internalBody->GetWorldPoint(b2Vec2(localPoint.x / body.world.ppm, localPoint.y / body.world.ppm));
	return Vector2f(result.x * body.world.ppm, result.y * body.world.ppm);
}
Vector2f Utilities::globalToLocalPoint(const Vector2f& globalPoint, const Body& body) {
	const b2Vec2& result = body.internalBody->GetLocalPoint(b2Vec2(globalPoint.x / body.world.ppm, globalPoint.y / body.world.ppm));
	return Vector2f(result.x * body.world.ppm, result.y * body.world.ppm);
}
