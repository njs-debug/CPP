#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int people, n, bullets;
    
    cout << "사람 수 입력: ";
    cin >> people;
    cout << "탄창 칸 수(n연발) 입력: ";
    cin >> n;
    cout << "총알 수 입력: ";
    cin >> bullets;

    if (bullets > n) {
        cout << "오류: 총알 수는 탄창 칸 수보다 많을 수 없습니다." << endl;
        return 0;
    }
    if (bullets >= people) {
        cout << "오류: 총알 수가 사람 수와 같거나 많으면 모두가 죽거나 생존자가 없습니다." << endl;
        return 0;
    }

    vector<int> gun(n, 0);
    vector<bool> alive(people, true);

    int loaded = 0;
    while (loaded < bullets) {
        int pos = rand() % n;
        if (gun[pos] == 0) {
            gun[pos] = 1;
            loaded++;
        }
    }

    cout << "\n=== 러시안 룰렛 게임 시작 ===\n";

    int current_chamber = 0;
    int current_person = 0;
    int fired_bullets = 0;

    while (fired_bullets < bullets) {
        if (alive[current_person]) {
            cout << current_person + 1 << "번 사람이 방아쇠를 당깁니다... ";

            if (gun[current_chamber] == 1) {
                cout << "빵! 탈락했습니다." << endl;
                alive[current_person] = false;
                fired_bullets++;
            } else {
                cout << "철컥! 생존했습니다." << endl;
            }

            current_chamber++;
            if (current_chamber >= n) {
                current_chamber = 0;
            }
        }

        current_person++;
        if (current_person >= people) {
            current_person = 0;
        }
    }

    cout << "\n=== 게임 종료 ===\n";
    cout << "총알 " << bullets << "발이 모두 발사되었습니다.\n";
    cout << "최종 생존자: ";
    for (int i = 0; i < people; i++) {
        if (alive[i]) {
            cout << i + 1 << "번 ";
        }
    }
    cout << endl;

    return 0;
}