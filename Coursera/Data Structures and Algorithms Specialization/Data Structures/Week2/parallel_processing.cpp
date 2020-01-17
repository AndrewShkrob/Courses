#include <bits/stdc++.h>

using namespace std;

struct Thread {
    int id;
    long long free_time;

    bool operator<(const Thread &worker) const {
        if (free_time == worker.free_time)
            return id > worker.id;
        return free_time > worker.free_time;
    }
};

class JobQueue {
private:
    int num_workers_{};
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;
    priority_queue<Thread> pq;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        for (int i = 0; i < num_workers_; ++i) {
            pq.push({i, 0});
        }
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        for (int i = 0; i < jobs_.size(); ++i) {
            int duration = jobs_[i];
            assigned_workers_[i] = pq.top().id;
            start_times_[i] = pq.top().free_time;
            pq.pop();
            pq.push({assigned_workers_[i], start_times_[i] + duration});
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
