#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time) :
            arrival_time(arrival_time),
            process_time(process_time) {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time) :
            dropped(dropped),
            start_time(start_time) {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    explicit Buffer(int size) :
            size_(size),
            finish_time_() {}

    Response Process(const Request &request) {
        int start_time = finish_time_.empty() ? request.arrival_time : std::max(finish_time_.back(),
                                                                                request.arrival_time);
        int request_finish_time = start_time + request.process_time;
        if (finish_time_.size() >= size_ && finish_time_.front() > request.arrival_time)
            return {true, start_time};
        else {
            if (!finish_time_.empty() && request.arrival_time >= finish_time_.front())
                finish_time_.pop();
            finish_time_.push(request_finish_time);
        }
        return {false, start_time};
    }

private:
    int size_;
    std::queue<int> finish_time_;
};

std::vector<Request> ReadRequests() {
    std::vector<Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.emplace_back(arrival_time, process_time);
    }
    return requests;
}

std::vector<Response> ProcessRequests(const std::vector<Request> &requests, Buffer *buffer) {
    std::vector<Response> responses;
    responses.reserve(requests.size());
    for (auto request : requests)
        responses.push_back(buffer->Process(request));
    return responses;
}

void PrintResponses(const std::vector<Response> &responses) {
    for (auto response : responses)
        std::cout << (response.dropped ? -1 : response.start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector<Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector<Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
