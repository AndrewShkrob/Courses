#pragma once

#include <vector>
#include <string>
#include <string_view>

void LeftStrip(std::string_view &sv);

std::string_view ReadToken(std::string_view &sv);

std::vector<std::string_view> SplitIntoWords(std::string_view line);