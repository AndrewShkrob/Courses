#pragma once

#include <string>
#include <string_view>
#include <vector>

std::string_view Strip(std::string_view s);

std::string_view LeftStrip(std::string_view s);

std::vector<std::string_view> SplitBy(std::string_view s, char sep);