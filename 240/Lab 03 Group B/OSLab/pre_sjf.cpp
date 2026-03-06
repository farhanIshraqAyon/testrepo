#include <iostream>
#include <vector>

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
    int remaining; // Remaining Burst Time (Crucial for Preemptive SJF)
};

// Preemptive SJF (Shortest Remaining Time First) function
void preemptiveSJF(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    // Initialize remaining time for all processes to their full burst time
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining = processes[i].bt;
    }

    double totalTAT = 0, totalWT = 0;

    // Keep running until all processes are fully completed
    while (completed < n)
    {
        int idx = -1;
        int minRemaining = 1e9; // Initialize to a very large number

        // Find the arrived process with the absolute shortest REMAINING time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currentTime && processes[i].remaining > 0)
            {
                if (processes[i].remaining < minRemaining)
                {
                    minRemaining = processes[i].remaining;
                    idx = i;
                }
            }
        }

        // If no process is ready, CPU is idle; advance time by 1
        if (idx == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the selected process for exactly 1 unit of time
        processes[idx].remaining--;
        currentTime++;

        // If the process just finished its very last unit of time
        if (processes[idx].remaining == 0)
        {
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
    // ct, tat, wt, and remaining are initialized to 0 and handled by the function
    vector<Process> processes = {
        {1, 1, 3, 0, 0, 0, 0},
        {2, 2, 4, 0, 0, 0, 0},
        {3, 1, 2, 0, 0, 0, 0},
        {4, 4, 4, 0, 0, 0, 0}};

    cout << "--- Preemptive Shortest Job First (SRTF) Scheduling ---";
    preemptiveSJF(processes);

    return 0;
}