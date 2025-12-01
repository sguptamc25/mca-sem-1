#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "[Reverse Program] Array in reverse order: ";
    for (int i = argc - 1; i > 0; i--) {
        cout << argv[i] << " ";
    }
    cout << endl;
    return 0;
}
