#include <bits/stdc++.h>

using namespace std;

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            LastFetchedTime = AskTimeServer();
        } catch (system_error &) {
        }
        return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};