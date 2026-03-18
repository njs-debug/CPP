//1번
#include <iostream>
#include <string>

using namespace std;

int main() {
    int input;
    cin >> input;

    int units[] = {10000, 1000, 100, 10, 1};
    string unit_names[] = {"만", "천", "백", "십", ""};
    
    bool started = false;

    for (int i = 0; i < 5; i++) {
        int digit = (input / units[i]) % 10;

        if (digit == 0 && !started && i < 4) continue;
        
        if (started) cout << " ";
        
        cout << digit << unit_names[i];
        started = true;
    }

    cout << endl;
    return 0;
}

//2번
#include <iostream>
#include <string>

using namespace std;

int main() {
    int input;
    cin >> input;

    if (input == 0) {
        cout << "0" << endl;
        return 0;
    }

    int units[] = {10000, 1000, 100, 10, 1};
    string unit_names[] = {"만", "천", "백", "십", ""};
    
    bool first_print = true;

    for (int i = 0; i < 5; i++) {
        int digit = (input / units[i]) % 10;

        if (digit == 0) continue;

        if (!first_print) cout << " ";
        
        cout << digit << unit_names[i];
        first_print = false;
    }

    cout << endl;
    return 0;
}

//3번
#include <iostream>
#include <string>

using namespace std;

int main() {
    int input;
    cin >> input;

    if (input == 0) {
        cout << "0" << endl;
        return 0;
    }

    int units[] = {10000, 1000, 100, 10, 1};
    string unit_names[] = {"만", "천", "백", "십", ""};
    
    bool first_print = true;

    for (int i = 0; i < 5; i++) {
        int digit = (input / units[i]) % 10;

        if (digit == 0) continue;

        if (!first_print) cout << " ";
        
        if (digit == 1 && units[i] >= 10) {
            cout << unit_names[i];
        } else {
            cout << digit << unit_names[i];
        }
        
        first_print = false;
    }

    cout << endl;
    return 0;
}