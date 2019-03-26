#include "Options.hpp"

Options::Options(const std::string& filename) : cfg(), cfgFilename(filename) {
	cfg.setOptions(Config::OptionAutoConvert | Config::OptionSemicolonSeparators | Config::OptionFsync);
	cfg.setTabWidth(0);
}

bool Options::load() {
	std::cout << "Loading options..." << std::endl;
	try {
		cfg.readFile("options.cfg");
	} catch (const FileIOException& ex) {
		std::cerr << "FileIOException occurred while reading 'options.cfg'." << std::endl;
		std::cout << "Attempting to write the default configuration file." << std::endl;
		{
			std::string str = defaultCfgString;
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) -> bool { return !std::isspace(ch); }));
			str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) -> bool { return !std::isspace(ch); }).base(), str.end());
			std::ofstream out("options.cfg");
			out << str;
		}
	} catch (const ParseException& ex) {
		std::cerr << "ParseException (" << ex.getError() << ") occurred on line " << ex.getLine() << " while reading 'options.cfg'." << std::endl;
		return false;
	}
	defaultCfg.readString(defaultCfgString);
	std::cout << "Done." << std::endl;
	return true;
}

Setting& Options::operator[](const std::string& name) const {
	try {
		return cfg.lookup(name);
	} catch (const SettingNotFoundException& ex) {
		return defaultCfg.lookup(name);
	}
}
Setting& Options::operator[](const char* name) const {
	try {
		return cfg.lookup(name);
	} catch (const SettingNotFoundException& ex) {
		return defaultCfg.lookup(name);
	}
}
