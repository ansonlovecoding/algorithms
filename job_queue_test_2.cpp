#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class Worker {
public:
    int id;
    long long start_time;

    Worker (int id){
        this->id = id;
        start_time = 0;
    }
};

struct WorkerCompare{
    bool operator() (Worker first, Worker second){
        //min-heap
        if (first.start_time == second.start_time){
            return first.id > second.id;
        } else{
            return first.start_time > second.start_time;
        }
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;
    priority_queue<Worker, vector<Worker>, WorkerCompare> job_pool;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        for (int i = num_workers_ - 1; i >= 0; --i) {
            job_pool.push(Worker(i));
        }
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        for (int i = 0; i < jobs_.size(); ++i) {
            int duration = jobs_[i];
            Worker next_worker = job_pool.top();
            assigned_workers_[i] = next_worker.id;
            start_times_[i] = next_worker.start_time;
            job_pool.pop();
            next_worker.start_time += duration;
            job_pool.push(next_worker);
        }
    }


public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
