#include "tests.h"

using namespace std;

void TestStopOperatorIn() {
    {
        istringstream is("Biryulyovo Passazhirskaya: 55.580999, 37.659164");
        Stop s;
        is >> s;
        ASSERT_EQUAL(s.name, "Biryulyovo Passazhirskaya");
        ASSERT_EQUAL(s.coords.latitude, 55.580999);
        ASSERT_EQUAL(s.coords.longitude, 37.659164);
    }
    {
        istringstream is("Universam: +55.587655, -37.645687");
        Stop s;
        is >> s;
        ASSERT_EQUAL(s.name, "Universam");
        ASSERT_EQUAL(s.coords.latitude, 55.587655);
        ASSERT_EQUAL(s.coords.longitude, -37.645687);
    }
}

void TestBusOperatorIn() {
    {
        istringstream is(
                "256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye");
        Bus bus;
        is >> bus;
        ASSERT_EQUAL(bus.GetNumber(), "256");
        auto stop_names = bus.GetStopNames();
        ASSERT_EQUAL(stop_names.size(), 6);
        vector<string_view> sn(begin(stop_names), end(stop_names));
        ASSERT_EQUAL(sn[0], "Biryulyovo Zapadnoye");
        ASSERT_EQUAL(sn[1], "Biryusinka");
        ASSERT_EQUAL(sn[2], "Universam");
        ASSERT_EQUAL(sn[3], "Biryulyovo Tovarnaya");
        ASSERT_EQUAL(sn[4], "Biryulyovo Passazhirskaya");
        ASSERT_EQUAL(sn[5], "Biryulyovo Zapadnoye");
    }
    {
        istringstream is("750: Tolstopaltsevo - Marushkino - Rasskazovka");
        Bus bus;
        is >> bus;
        ASSERT_EQUAL(bus.GetNumber(), "750");
        auto stop_names = bus.GetStopNames();
        ASSERT_EQUAL(stop_names.size(), 5);
        vector<string_view> sn(begin(stop_names), end(stop_names));
        ASSERT_EQUAL(sn[0], "Tolstopaltsevo");
        ASSERT_EQUAL(sn[1], "Marushkino");
        ASSERT_EQUAL(sn[2], "Rasskazovka");
        ASSERT_EQUAL(sn[3], "Marushkino");
        ASSERT_EQUAL(sn[4], "Tolstopaltsevo");
    }
}

void TestBusManagerGetBusDescription() {
    BusManager bm;
    {
        {
            istringstream is("Tolstopaltsevo: 55.611087, 37.20829");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Marushkino: 55.595884, 37.209755");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Rasskazovka: 55.632761, 37.333324");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Biryulyovo Zapadnoye: 55.574371, 37.6517");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Biryusinka: 55.581065, 37.64839");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Universam: 55.587655, 37.645687");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Biryulyovo Tovarnaya: 55.592028, 37.653656");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
        {
            istringstream is("Biryulyovo Passazhirskaya: 55.580999, 37.659164");
            Stop s;
            is >> s;
            bm.AddStop(s);
        }
    }
    {
        istringstream is(
                "256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye");
        Bus bus;
        is >> bus;
        bm.AddBus(bus);
        string bus_desc = bm.GetBusDescription("256");
        ASSERT_EQUAL(bus_desc, "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length");
    }
    {
        istringstream is("750: Tolstopaltsevo - Marushkino - Rasskazovka");
        Bus bus;
        is >> bus;
        bm.AddBus(bus);
        string bus_desc = bm.GetBusDescription("750");
        ASSERT_EQUAL(bus_desc, "Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length");
    }
    {
        string bus_desc = bm.GetBusDescription("751");
        ASSERT_EQUAL(bus_desc, "Bus 751: not found");
    }
}