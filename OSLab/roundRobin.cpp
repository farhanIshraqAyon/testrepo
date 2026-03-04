#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Define the Process structure
struct Process
{
    int id;        // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int remaining; // Remaining Burst Time
};

// Round Robin Scheduling Function
void roundRobin(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    queue<int> q; // Queue to hold the index of processes
    int currentTime = 0, completed = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining = processes[i].bt;
    }

    // Track if a process is already in the ready queue
    vector<bool> inQueue(n, false);
    double totalTAT = 0, totalWT = 0;

    // Keep running until all processes are fully completed
    while (completed < n)
    {
        // 1. Check for any newly arrived processes and add them to the queue
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currentTime && !inQueue[i] && processes[i].remaining > 0)
            {
                q.push(i);
                inQueue[i] = true; // Mark as added to queue
            }
        }

        // If no process is ready, CPU is idle; advance time by 1
        if (q.empty())
        {
            currentTime++;
            continue;
        }

        // 2. Take the first process from the queue
        int idx = q.front();
        q.pop();

        // 3. Execute it for either the Time Quantum or its remaining time (whichever is smaller)
        int execTime = min(quantum, processes[idx].remaining);
        processes[idx].remaining -= execTime;
        currentTime += execTime;

        // 4. Check for newly arrived processes again WHILE this process was executing
        // This ensures new arrivals get in line BEFORE the current process loops back
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currentTime && !inQueue[i] && processes[i].remaining > 0)
            {
                q.push(i);
                inQueue[i] = true;
            }
        }

        // 5. If the current process still needs more time, put it back at the end of the line
        if (processes[idx].remaining > 0)
        {
            q.push(idx);
        }
        else
        {
            // Process is completely finished
            processes[idx].ct = currentTime;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;

            totalTAT += processes[idx].tat;
            totalWT += processes[idx].wt;

            completed++;
        }
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
    // Format: {id, at, bt, ct, tat, wt, remaining}
    vector<Process> processes = {
        {1, 0, 5, 0, 0, 0, 0},
        {2, 1, 4, 0, 0, 0, 0},
        {3, 2, 2, 0, 0, 0, 0},
        {4, 4, 1, 0, 0, 0, 0}};

    int time_quantum = 2; // Time limits for each turn

    cout << "--- Round Robin (RR) Scheduling | Quantum = " << time_quantum << " ---";
    roundRobin(processes, time_quantum);

    return 0;
}