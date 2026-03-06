#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the Process structure expected by the FCFS function
struct Process {
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Your FCFS function
void fcfs(vector<Process>& processes) {
    // Sort processes by Arrival Time (AT)
    sort(processes.begin(), processes.end(),
         [](Process a, Process b) {
             return a.at < b.at;
         });

    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    for (auto &p : processes) {
        // If the CPU is idle before the process arrives, fast-forward time
        if (currentTime < p.at) {
            currentTime = p.at;
        }

        // Process executes
        currentTime += p.bt;
        p.ct = currentTime;

        // Calculate Turnaround Time (TAT) and Waiting Time (WT)
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;

        totalTAT += p.tat;
        totalWT += p.wt;
    }

    // Print results
    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto p : processes) {
        cout << p.id << "\t" << p.at << "\t" << p.bt << "\t"
             << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    cout << "\nAverage TAT = " << totalTAT / processes.size();
    cout << "\nAverage WT = " << totalWT / processes.size() << endl;
}

int main() {
    // Initialize a vector of processes
    // Format: {id, arrival_time, burst_time, ct, tat, wt}
    // We initialize ct, tat, and wt to 0 as they are calculated later
    vector<Process> processes = {
        {1, 0, 5, 0, 0, 0},
        {2, 1, 3, 0, 0, 0},
        {3, 2, 8, 0, 0, 0},
        {4, 4, 6, 0, 0, 0} 
    };

    cout << "--- First-Come, First-Served (FCFS) Scheduling ---";
    fcfs(processes);

    return 0;
}