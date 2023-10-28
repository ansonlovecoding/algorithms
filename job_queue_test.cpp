#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;
    vector< std::pair<int, long long > > job_pool;

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
        build_heap_first();
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        for (int i = 0; i < jobs_.size(); ++i) {
            int duration = jobs_[i];
            std::pair<int, long long> next_worker = extract_max(duration);
            assigned_workers_[i] = next_worker.first;
            start_times_[i] = next_worker.second;
        }
    }

    void build_heap_first(){
        for (int i = num_workers_ - 1; i >= 0; --i) {
            job_pool.push_back(std::make_pair(i, 0));
        }
    }

    void shift_up(int n){
        if (n <= 0){
            return;
        }
        int mod = n % 2;
        int k;
        if (mod != 0){
            //left
            k = n / 2;
        } else{
            //right
            k = (n - 1) / 2;
        }
        if (job_pool[n].second > job_pool[k].second){
            std::swap(job_pool[n], job_pool[k]);
            shift_up(k);
        } else if (
                job_pool[n].second == job_pool[k].second &&
                        job_pool[n].first > job_pool[k].first){
            std::swap(job_pool[n], job_pool[k]);
            shift_up(k);
        }
    }

    void shift_down(int i){
        int left_index = 2 * i + 1;
        int right_index = 2 * i + 2;

        if (i >= job_pool.size()){
            return;
        }

        std::pair<int, long long > inert_point = job_pool[i];
        std::pair<int, long long > left;
        int largest = i;
        int sec_largest = i;
        if (left_index < job_pool.size()){
            left = job_pool[left_index];
            if (left.second > inert_point.second){
                largest = left_index;
            } else if (left.second == inert_point.second && left.first > inert_point.first){
                sec_largest = left_index;
            }
        }
        if (right_index < job_pool.size()){
            std::pair<int, long long > right = job_pool[right_index];
            if (right.second > left.second && right.second > inert_point.second){
                largest = right_index;
            } else if (right.second == inert_point.second && right.first > inert_point.first){
                sec_largest = right_index;
            }
        }
        if (largest == i && sec_largest != i){
            largest = sec_largest;
        }
        if (largest != i){
            swap(job_pool[i], job_pool[largest]);
            shift_down(largest);
        }
    }

    std::pair<int, long long> extract_max(int duration)
    {
        std::pair<int, long long> max_priority_job = job_pool.back();
        job_pool.pop_back();
//        job_pool.push_back(std::make_pair(max_priority_job.first, max_priority_job.second + duration));
//        shift_up(num_workers_ - 1);
        job_pool.insert(job_pool.begin(), std::make_pair(max_priority_job.first, max_priority_job.second + duration));
        shift_down(0);
        return max_priority_job;
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
