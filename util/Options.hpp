#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include <SFML/System/Vector2.hpp>
using namespace sf;

#include "libconfig.h++"
using namespace libconfig;

class Options {
	
	public:
		Options(const std::string& filename);
		bool load();
		
		Setting& operator[](const std::string& name) const;
		Setting& operator[](const char* name) const;
		
	protected:
		Config cfg;
		Config defaultCfg;
		
		const std::string cfgFilename;
		const std::string defaultCfgString = R"CFG(
display = {
	resolution = { x = 1280; y = 720 };
	fullscreen = false;
	antialiasingLevel = 0;
};
		)CFG";
	
};