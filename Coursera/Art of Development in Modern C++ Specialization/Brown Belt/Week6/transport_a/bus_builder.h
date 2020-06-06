#include <string>
#include <string_view>
#include <list>
#include <algorithm>
#include "bus.h"
#include "parse.h"

#ifndef BROWN_BELT_BUS_BUILDER_H
#define BROWN_BELT_BUS_BUILDER_H


class BusBuilder {
public:
    BusBuilder &SetBusNumber(std::string &number);

    BusBuilder &ConfigureStops(std::string &stops_config);

    Bus Build();

private:
    enum class RouteType {
        RING = '>',
        ROUND = '-',
        NONE = '\0'
    };

    static inline RouteType GetRouteType(const std::string &stops_config);

    std::string bus_number;
    std::string stops_config;
    std::vector<std::string_view> stop_names;
    RouteType route_type;
};


#endif //BROWN_BELT_BUS_BUILDER_H
