#include "ini.h"

#include <algorithm>

using namespace std;

namespace Ini {
    Section &Document::AddSection(std::string name) {
        return sections[move(name)];
    }

    const Section &Document::GetSection(const std::string &name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream &input) {
        Document result;

        Section *current_section = nullptr;
        for (string line; getline(input, line);) {
            if (line.empty())
                continue;
            if (line[0] == '[') {
                current_section = &result.AddSection(line.substr(1, line.size() - 2));
            } else {
                size_t eq_pos = line.find('=');
                current_section->insert({
                    line.substr(0, eq_pos),
                    line.substr(eq_pos + 1)
                });
            }
        }

        return result;
    }
}