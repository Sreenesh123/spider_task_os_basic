#include <iostream>
#include <vector>
#include <cstring>

#define P 4 
#define R 3 

using namespace std;
bool is_available(int process_id, int allocated[][R], int need[][R], int available[]) {
    for (int i = 0; i < R; i++) {
        if (need[process_id][i] > available[i]) {
            return false;
        }
    }
    return true;
}


bool find_safe_sequence(bool marked[], int allocated[][R], int need[][R], int available[], vector<int>& safe) {
    bool found = false;
    for (int i = 0; i < P; i++) {
        if (!marked[i] && is_available(i, allocated, need, available)) {
            marked[i] = true;
            for (int j = 0; j < R; j++) {
                available[j] += allocated[i][j];
            }

            safe.push_back(i);
            if (safe.size() == P) {
                return true;
            }

            if (find_safe_sequence(marked, allocated, need, available, safe)) {
                found = true;
            }

            safe.pop_back();
            marked[i] = false;
            for (int j = 0; j < R; j++) {
                available[j] -= allocated[i][j];
            }
        }
    }
    return found;
}

int main() {
    int allocated[P][R] = {
        { 0, 1, 0 },
        { 2, 0, 0 },
        { 3, 0, 2 },
        { 2, 1, 1 }
    };

    int max[P][R] = {
        { 7, 5, 3 },
        { 3, 2, 2 },
        { 9, 0, 2 },
        { 2, 2, 2 }
    };

    int resources[R] = { 10, 5, 7 };

    int available[R];

    for (int i = 0; i < R; i++) {
        int sum = 0;
        for (int j = 0; j < P; j++) {
            sum += allocated[j][i];
        }
        available[i] = resources[i] - sum;
    }

    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    vector<int> safe;
    bool marked[P];
    memset(marked, false, sizeof(marked));

    if (find_safe_sequence(marked, allocated, need, available, safe)) {
        cout << "Safe sequence exists: ";
        for (int i = 0; i < safe.size(); i++) {
            cout << "P" << safe[i] + 1;
            if (i != safe.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "No safe sequence. Deadlock is possible." << endl;
    }

    return 0;
}

