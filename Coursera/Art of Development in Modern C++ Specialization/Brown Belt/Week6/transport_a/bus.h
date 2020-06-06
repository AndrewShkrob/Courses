#include <string>
#include <string_view>
#include <vector>
#include <istream>
#include <sstream>
#include <unordered_map>

#ifndef BROWN_BELT_BUS_H
#define BROWN_BELT_BUS_H

class Bus {
    friend class BusBuilder;

public:
    Bus() = default;

    const std::string &GetNumber() const;

    size_t GetStopsCount() const;

    size_t GetUniqueStopsCount() const;

    const std::vector<std::string_view> &GetStopNames() const;

private:
    Bus(std::string &number,
        std::string &stops_config,
        std::vector<std::string_view> &stop_names);

    std::string number;
    std::string stops_config;
    std::vector<std::string_view> stop_names;
};

std::istream &operator>>(std::istream &is, Bus &bus);

#endif //BROWN_BELT_BUS_H
