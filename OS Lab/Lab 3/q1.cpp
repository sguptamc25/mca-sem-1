#include <iostream>
#include <vector>
#include <unistd.h>     // for fork(), getpid(), getppid(), sleep()
#include <sys/wait.h>   // for wait()
#include <cstdlib>      // for exit()
using namespace std;

// Insertion Sort (child’s algorithm)
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    else if (pid == 0) {
        // ---------------- CHILD PROCESS ----------------
        cout << "\n[Child] Started." << endl;
        cout << "[Child] PID: " << getpid() 
             << ", PPID: " << getppid() << endl;
        cout << "[Child] Sleeping for 10 seconds..." << endl;
        sleep(10);  // Keeps child alive after parent exits
        cout << "\n[Child] Woke up!" << endl;
        cout << "[Child] New PPID (after parent exit): " << getppid() << endl;
        cout << "[Child] Sorting using Insertion Sort..." << endl;
        insertionSort(arr);
        cout << "[Child] Sorted array: ";
        for (int num : arr) cout << num << " ";
        cout << endl;
        cout << "[Child] Exiting now." << endl;
        exit(0);
    }
    else {
        // ---------------- PARENT PROCESS ----------------
        cout << "\n[Parent] PID: " << getpid()
             << ", Child PID: " << pid << endl;
        cout << "[Parent] Exiting immediately (will not wait for child)." << endl;
        exit(0);  // Parent exits early → child becomes orphan
    }

    return 0;
}
