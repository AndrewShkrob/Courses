#include <tuple>

using namespace std;

struct Address {
    string city, street;
    int building;

    bool operator==(const Address &other) const {
        return tuple(city, street, building) ==
               tuple(other.city, other.street, other.building);
    }
};

struct Person {
    string name;
    int height;
    double weight;
    Address address;

    bool operator==(const Person &other) const {
        return tuple(name, height, weight, address) ==
               tuple(other.name, other.height, other.weight, other.address);
    }
};

struct AddressHasher {
    size_t operator()(const Address &address) const {
        size_t city_hash = string_hash(address.city);
        size_t street_hash = string_hash(address.street);
        size_t building_hash = int_hash(address.building);
        return city_hash * t * t + street_hash * t + building_hash;
    }

    hash<std::string> string_hash;
    hash<int> int_hash;
    static const size_t t = 115'249;
};

struct PersonHasher {
    size_t operator()(const Person &person) const {
        size_t name_hash = string_hash(person.name);
        size_t height_hash = int_hash(person.height);
        size_t weight_hash = double_hash(person.weight);
        size_t addr_hash = address_hash(person.address);
        return name_hash * t * t * t + height_hash * t * t + weight_hash * t + addr_hash;
    }

    hash<string> string_hash;
    hash<int> int_hash;
    hash<double> double_hash;
    AddressHasher address_hash;
    static const size_t t = 6'328'548;
};
