#include <tuple>

using namespace std;

using CoordType = int;

struct Point3D {
    CoordType x;
    CoordType y;
    CoordType z;

    bool operator==(const Point3D &other) const {
        return tuple(x, y, z) == tuple(other.x, other.y, other.z);
    }
};

struct Hasher {
    size_t operator()(const Point3D point3D) const {
        size_t x_hash = coord_hash(point3D.x);
        size_t y_hash = coord_hash(point3D.y);
        size_t z_hash = coord_hash(point3D.z);
        size_t t = 211;
        return x_hash * t * t + y_hash * t + z_hash;
    }

    hash<CoordType> coord_hash;
};
