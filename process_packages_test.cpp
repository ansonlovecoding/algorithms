#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
            arrival_time(arrival_time),
            process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
            dropped(dropped),
            start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
            size_(size),
            finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here
        Request new_req = Request(request.arrival_time, request.process_time);
        int previous_arrive_time = store.empty() ? -1 : store.back().arrival_time;
        int previous_process_time = store.empty() ? -1 : store.back().process_time;

        int tmp_time = previous_arrive_time + previous_process_time;
        while (!store.empty() && new_req.arrival_time >= store.front().arrival_time + store.front().process_time){
            store.pop();
        }
        new_req.arrival_time = request.arrival_time > tmp_time ? request.arrival_time : tmp_time;

        if (store.size() >= size_){
            Response rsp = Response(true, -1);
            return rsp;
        }
        store.push(new_req);
        Response rsp = Response(false, new_req.arrival_time);
        return rsp;
    }
private:
    int size_;
    std::queue <int> finish_time_;
    std::queue <Request> store;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
