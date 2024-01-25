#include "jsonRead.hpp"

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>

nlohmann::json readJson(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) throw("Failed to open JSON file!");
	nlohmann::json jsonData;
	file >> jsonData;
	return jsonData;
}