#include "collide/geo2d.h"
#include "collide/game_object.h"

using namespace std;

class Unit : public GameObject {
public:
    explicit Unit(geo2d::Point position);

    bool Collide(const GameObject &that) const override;

    geo2d::Point GetPosition() const;

    virtual bool CollideWith(const Unit &that) const;

    virtual bool CollideWith(const Building &that) const;

    virtual bool CollideWith(const Tower &that) const;

    virtual bool CollideWith(const Fence &that) const;

private:
    geo2d::Point position;
};

class Building : public GameObject {
public:
    explicit Building(geo2d::Rectangle geometry);

    bool Collide(const GameObject &that) const override;

    geo2d::Rectangle GetGeometry() const;

    virtual bool CollideWith(const Unit &that) const;

    virtual bool CollideWith(const Building &that) const;

    virtual bool CollideWith(const Tower &that) const;

    virtual bool CollideWith(const Fence &that) const;

private:
    geo2d::Rectangle geometry;
};

class Tower : public GameObject {
public:
    explicit Tower(geo2d::Circle geometry);

    bool Collide(const GameObject &that) const override;

    geo2d::Circle GetGeometry() const;

    virtual bool CollideWith(const Unit &that) const;

    virtual bool CollideWith(const Building &that) const;

    virtual bool CollideWith(const Tower &that) const;

    virtual bool CollideWith(const Fence &that) const;

private:
    geo2d::Circle geometry;
};

class Fence : public GameObject {
public:
    explicit Fence(geo2d::Segment geometry);

    bool Collide(const GameObject &that) const override;

    geo2d::Segment GetGeometry() const;

    virtual bool CollideWith(const Unit &that) const;

    virtual bool CollideWith(const Building &that) const;

    virtual bool CollideWith(const Tower &that) const;

    virtual bool CollideWith(const Fence &that) const;

private:
    geo2d::Segment geometry;
};

Unit::Unit(geo2d::Point position) : position(position) {}

bool Unit::Collide(const GameObject &that) const {
    return that.CollideWith(*this);
}

geo2d::Point Unit::GetPosition() const {
    return position;
}

bool Unit::CollideWith(const Unit &that) const {
    return geo2d::Collide(position, that.GetPosition());
}

bool Unit::CollideWith(const Building &that) const {
    return geo2d::Collide(position, that.GetGeometry());
}

bool Unit::CollideWith(const Tower &that) const {
    return geo2d::Collide(position, that.GetGeometry());
}

bool Unit::CollideWith(const Fence &that) const {
    return geo2d::Collide(position, that.GetGeometry());
}

Building::Building(geo2d::Rectangle geometry) : geometry(geometry) {}

bool Building::Collide(const GameObject &that) const {
    return that.CollideWith(*this);
}

geo2d::Rectangle Building::GetGeometry() const {
    return geometry;
}

bool Building::CollideWith(const Unit &that) const {
    return geo2d::Collide(geometry, that.GetPosition());
}

bool Building::CollideWith(const Building &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Building::CollideWith(const Tower &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Building::CollideWith(const Fence &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

Tower::Tower(geo2d::Circle geometry) : geometry(geometry) {}

bool Tower::Collide(const GameObject &that) const {
    return that.CollideWith(*this);
}

geo2d::Circle Tower::GetGeometry() const {
    return geometry;
}

bool Tower::CollideWith(const Unit &that) const {
    return geo2d::Collide(geometry, that.GetPosition());
}

bool Tower::CollideWith(const Building &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Tower::CollideWith(const Tower &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Tower::CollideWith(const Fence &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

Fence::Fence(geo2d::Segment geometry) : geometry(geometry) {}

bool Fence::Collide(const GameObject &that) const {
    return that.CollideWith(*this);
}

geo2d::Segment Fence::GetGeometry() const {
    return geometry;
}

bool Fence::CollideWith(const Unit &that) const {
    return geo2d::Collide(geometry, that.GetPosition());
}

bool Fence::CollideWith(const Building &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Fence::CollideWith(const Tower &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Fence::CollideWith(const Fence &that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Collide(const GameObject &first, const GameObject &second) {
    return first.Collide(second);
}
