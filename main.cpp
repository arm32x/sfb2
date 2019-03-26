#include <algorithm>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;

#include <libconfig.h++>
using namespace libconfig;

#include "sfb2/World.hpp"
#include "sfb2/Utilities.hpp"

#include "util/Options.hpp"
#include "util/Random.hpp"

int main() {
	Options options("options.cfg");
	if (!options.load()) return EXIT_FAILURE;
	// Seed the random number generator in a MinGW-compatible way.
	Random::seedGenerator((time(nullptr) & 0xFFFF) | (getpid() << 16));
	
	ContextSettings ctxSettings;
	ctxSettings.antialiasingLevel = (int)options["display.antialiasingLevel"];
	RenderWindow window(VideoMode((unsigned int)options["display.resolution.x"], (unsigned int)options["display.resolution.y"]), "SFML Window", (bool)options["display.fullscreen"] ? Style::Fullscreen : Style::Close, ctxSettings);
	window.setVerticalSyncEnabled(true);
	
	World world(9.807f); // Create the world.
	
	world.createRectangleBody(FloatRect(0.0f, window.getSize().y - 10.0f, window.getSize().x, 10.0f), BodyType::KinematicBody);
	
	RectangleBody& demoRect = world.createRectangleBody(Vector2f(window.getSize()) / 2.0f, Vector2f(100.0f, 100.0f), BodyType::DynamicBody);
	demoRect.setFillColor(Color::Red);
	demoRect.setRotation(15.0f);
	
	Clock frameClock; ///< Responsible for calculating the timestep for physics calculations.
	while (window.isOpen()) {
		// Handle events.
		Event e;
		while (window.pollEvent(e)) {
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wswitch"
			switch (e.type) {
				case Event::Closed:
					window.close();
					break;
			}
			#pragma GCC diagnostic pop
		}
		
		Time frameTime = frameClock.restart();
		world.step(frameTime); // Update the game physics.
		
		window.clear(Color::Black); // Clear the screen.
		window.draw(world); // Draw everything contained in the world (all physics objects).
		// Draw additional objects here.
		window.display(); // Output the graphics to the screen.
	}

    return EXIT_SUCCESS;
}
