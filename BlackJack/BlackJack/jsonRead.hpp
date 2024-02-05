#pragma once
#include "nlohmann/json.hpp"
#include <string>

nlohmann::json readJson(const std::string& fileName);