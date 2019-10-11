#include <bits/stdc++.h>

using namespace std;

struct Event {
    string hotel_name;
    int64_t time;
    size_t client_id;
    size_t room_count;
};

struct Hotel {
    size_t booked_rooms = 0;
    map<size_t, size_t> clients;

    void addEvent(const Event &event) {
        booked_rooms += event.room_count;
        clients[event.client_id] += event.room_count;
    }
};

class HotelManager {
public:
    size_t Clients(const string &hotel_name) {
        return hotels[hotel_name].clients.size();
    }

    size_t Rooms(const string &hotel_name) {
        return hotels[hotel_name].booked_rooms;
    }

    void Book(const Event &event) {
        adjust(event.time);
        hotels[event.hotel_name].addEvent(event);
        events.push(event);
    }

private:
    static const int64_t day_time = 86400;
    map<string, Hotel> hotels;
    queue<Event> events;

    void adjust(int64_t current_time) {
        while (!events.empty() && current_time - events.front().time >= day_time) {
            auto &event = events.front();
            auto &hotel = hotels[event.hotel_name];
            hotel.booked_rooms -= event.room_count;
            hotel.clients[event.client_id] -= event.room_count;
            if (hotel.clients[event.client_id] == 0)
                hotel.clients.erase(event.client_id);
            events.pop();
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    HotelManager m;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int64_t time;
        uint client_id;
        size_t room_count;
        string command, hotel_name;
        cin >> command;
        if (command == "CLIENTS") {
            cin >> hotel_name;
            cout << m.Clients(hotel_name) << '\n';
        } else if (command == "ROOMS") {
            cin >> hotel_name;
            cout << m.Rooms(hotel_name) << '\n';
        } else {
            cin >> time >> hotel_name >> client_id >> room_count;
            m.Book({hotel_name, time, client_id, room_count});
        }
    }
}