#include <iostream>
#include <vector>

using namespace std;

// Define the Process structure
struct Process
{
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Non-Preemptive SJF function
void sjf(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    // Track which processes have finished executing
    vector<bool> done(n, false);

    double totalTAT = 0, totalWT = 0;

    // Keep running until all processes are completed
    while (completed < n)
    {
        int idx = -1;
        int minBT = 1e9; // Initialize with a very large number

        // Find the process with the shortest burst time that has already arrived
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && processes[i].at <= currentTime)
            {
                if (processes[i].bt < minBT)
                {
                    minBT = processes[i].bt;
                    idx = i;
                }
            }
        }

        // If no process has arrived yet, just advance the CPU time
        if (idx == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the selected process
        currentTime += processes[idx].bt;
        processes[idx].ct = currentTime;

        // Calculate TAT and WT
        processes[idx].tat = processes[idx].ct - processes[idx].at;
        processes[idx].wt = processes[idx].tat - processes[idx].bt;

        totalTAT += processes[idx].tat;
        totalWT += processes[idx].wt;

        // Mark process as completed
        done[idx] = true;
        completed++;
    }

    // Print results
    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto p : processes)
    {
        cout << p.id << "\t" << p.at << "\t" << p.bt << "\t"
             << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage WT = " << totalWT / n << endl;
}

int main()
{
    // Initialize a vector of processes
    // Format: {id, arrival_time, burst_time, ct, tat, wt}
    vector<Process> processes = {
        {1, 1, 3, 0, 0, 0},
        {2, 2, 4, 0, 0, 0},
        {3, 1, 2, 0, 0, 0},
        {4, 4, 4, 0, 0, 0}};

    cout << "--- Non-Preemptive Shortest Job First (SJF) Scheduling ---";
    sjf(processes);

    return 0;
}