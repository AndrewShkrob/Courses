#include "test_runner.h"
#include "tests.h"

#include "bus_manager.h"

#include <iostream>

using namespace std;

void Tests() {
    TestRunner tr;
    RUN_TEST(tr, TestStopOperatorIn);
    RUN_TEST(tr, TestBusOperatorIn);
    RUN_TEST(tr, TestBusManagerGetBusDescription);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Tests();

    BusManager bm;

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        string type;
        cin >> type;
        if (type == "Stop") {
            Stop stop;
            cin >> stop;
            bm.AddStop(stop);
        } else if (type == "Bus") {
            Bus bus;
            cin >> bus;
            bm.AddBus(bus);
        }
    }

    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        string type;
        cin >> type;
        if (type == "Bus") {
            string bus_number;
            while (cin.peek() == ' ')
                cin.ignore();
            getline(cin, bus_number);
            cout << bm.GetBusDescription(bus_number) << endl;
        }
    }
}