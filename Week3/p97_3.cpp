#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    double sum = 0.0;
    int sign = 1;

    for (int i = 1; i <= n; i++) {
        sum += sign * (1.0 / (2 * i - 1));
        sign *= -1;
    }

    double pi = 4.0 * sum;
    
    cout.precision(10);
    cout << fixed << pi << endl;

    return 0;
}