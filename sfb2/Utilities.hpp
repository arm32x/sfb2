#pragma once

#include <functional>

#include <SFML/System/Vector2.hpp>
using namespace sf;

#include "Body.hpp"

constexpr float PIf = 3.14159265359f;
constexpr double PI = 3.14159265358979323846;
constexpr long double PIL = 3.141592653589793238462643383279502884L;

namespace Utilities {
	
	Vector2f localToGlobalPoint(const Vector2f& localPoint, const Body& body);
	Vector2f globalToLocalPoint(const Vector2f& globalPoint, const Body& body);
	
}