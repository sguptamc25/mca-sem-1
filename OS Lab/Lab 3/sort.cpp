#include <iostream>
#include <vector>
#include <unistd.h>     
#include <sys/wait.h>    
#include <cstring>       
#include <cstdlib>       

using namespace std;
// Bubble Sort function (for parent)
void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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
    bubbleSort(arr);
    cout << "[Parent] Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    else if (pid == 0) {
        // ---------- CHILD PROCESS ----------
        cout << "[Child] Executing reverse program using execve()...\n";
        vector<char*> args;
        args.push_back(strdup("./reverse")); 
        for (int num : arr) {
            string s = to_string(num);
            args.push_back(strdup(s.c_str()));
        }
        args.push_back(NULL); 
        execve("./reverse", args.data(), NULL);
        perror("execve failed");
        exit(1);
    }
    else {
        // ---------- PARENT PROCESS ----------
        wait(NULL);
        cout << "[Parent] Child executed reverse successfully.\n";
    }

    return 0;
}
