#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_SIZE 5
#define MAX_HISTORY 2000

#define Sleep(ms) usleep((ms) * 1000)

// --- 데이터 구조체 정의 ---
struct GameState {
    int size;                   // 3, 4, 5 (퍼즐 크기)
    int board[MAX_SIZE][MAX_SIZE];
    int init_board[MAX_SIZE][MAX_SIZE]; // 리플레이용 초기 상태
    int empty_r, empty_c;       // 빈칸(0)의 위치
    int move_count;             // 이동 횟수
    time_t start_time;          // 시작 시간
    int elapsed_time;           // 누적 진행 시간(초)
    char history[MAX_HISTORY];  // 이동 기록 (U, D, L, R)
    int is_ascii_mode;          // 0: 숫자, 1: 문자(그림) 모드
};

struct Record {
    char name[20];
    int size;
    int moves;
    int time;
};

// --- 전역 변수 ---
GameState game;
const char* save_file = "puzzle_save.txt";
const char* rank_file = "puzzle_rank.bin";

// 그림 퍼즐을 위한 아스키 문자 배열 (인덱스 1~24를 A~X에 매핑)
const char ascii_art[] = " ABCDEFGHIJKLMNOPQRSTUVWXY";

// --- 함수 선언 ---
void initGame(int size, int ascii_mode);
void printBoard(int current_board[MAX_SIZE][MAX_SIZE]);
int moveDirection(char dir);
int checkWin();
void playReplay();
void saveGame();
int loadGame();
void saveRanking();
void printRanking();

// --- 유틸리티 함수 ---
void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

// --- 1. 및 5. 게임 초기화 (크기 확장 및 아스키 모드) ---
void initGame(int size, int ascii_mode) {
    game.size = size;
    game.is_ascii_mode = ascii_mode;
    game.move_count = 0;
    game.elapsed_time = 0;
    memset(game.history, 0, sizeof(game.history));

    int num = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            game.board[i][j] = num++;
        }
    }
    game.board[size - 1][size - 1] = 0; // 마지막은 빈칸
    game.empty_r = size - 1;
    game.empty_c = size - 1;

    // 무작위로 섞기 (역연산 가능한 유효한 퍼즐을 만들기 위해 직접 움직임)
    srand((unsigned int)time(NULL));
    char dirs[] = { 'U', 'D', 'L', 'R' };
    for (int i = 0; i < 200; i++) {
        char rand_dir = dirs[rand() % 4];
        moveDirection(rand_dir);
    }

    // 섞인 후의 상태를 리플레이용으로 저장 및 초기화
    memcpy(game.init_board, game.board, sizeof(game.board));
    game.move_count = 0;
    memset(game.history, 0, sizeof(game.history));
    game.start_time = time(NULL);
}

// 화면 출력 함수
void printBoard(int b[MAX_SIZE][MAX_SIZE]) {
    system("clear"); // 화면 지우기
    printf("===== %dx%d 퍼즐 게임 =====\n", game.size, game.size);
    printf("[이동: 방향키] [S: 저장] [Q: 종료]\n");
    printf("이동 횟수: %d\n\n", game.move_count);

    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (b[i][j] == 0) {
                printf("  [ ] ");
            } else {
                if (game.is_ascii_mode)
                    printf("  [%c] ", ascii_art[b[i][j]]);
                else
                    printf(" [%2d] ", b[i][j]);
            }
        }
        printf("\n\n");
    }
}

// 이동 처리 (U, D, L, R)
int moveDirection(char dir) {
    int dr = 0, dc = 0;
    if (dir == 'U') dr = -1;
    else if (dir == 'D') dr = 1;
    else if (dir == 'L') dc = -1;
    else if (dir == 'R') dc = 1;
    else return 0;

    int nr = game.empty_r + dr;
    int nc = game.empty_c + dc;

    if (nr >= 0 && nr < game.size && nc >= 0 && nc < game.size) {
        swap(&game.board[game.empty_r][game.empty_c], &game.board[nr][nc]);
        game.empty_r = nr;
        game.empty_c = nc;
        return 1;
    }
    return 0;
}

// 승리 조건 확인
int checkWin() {
    int num = 1;
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (i == game.size - 1 && j == game.size - 1) {
                if (game.board[i][j] != 0) return 0;
            } else {
                if (game.board[i][j] != num++) return 0;
            }
        }
    }
    return 1;
}

// --- 3. 게임 저장 기능 (텍스트 모드) ---
void saveGame() {
    FILE* fp = fopen(save_file, "w");
    if (fp == NULL) return;

    // 현재 시간 계산하여 누적 시간에 더함
    int current_play = (int)(time(NULL) - game.start_time);
    game.elapsed_time += current_play;

    fprintf(fp, "%d %d %d %d %d %d\n", game.size, game.is_ascii_mode, game.move_count, game.elapsed_time, game.empty_r, game.empty_c);

    for(int i=0; i<game.size; i++)
        for(int j=0; j<game.size; j++)
            fprintf(fp, "%d ", game.board[i][j]);

    for(int i=0; i<game.size; i++)
        for(int j=0; j<game.size; j++)
            fprintf(fp, "%d ", game.init_board[i][j]);

    fprintf(fp, "\n%s\n", game.history);
    fclose(fp);
    printf("\n게임을 저장했습니다!\n");
    Sleep(1000);
}

// --- 4. 게임 로드 기능 (텍스트 모드) ---
int loadGame() {
    FILE* fp = fopen(save_file, "r");
    if (fp == NULL) return 0;

    fscanf(fp, "%d %d %d %d %d %d", &game.size, &game.is_ascii_mode, &game.move_count, &game.elapsed_time, &game.empty_r, &game.empty_c);

    for(int i=0; i<game.size; i++)
        for(int j=0; j<game.size; j++)
            fscanf(fp, "%d", &game.board[i][j]);

    for(int i=0; i<game.size; i++)
        for(int j=0; j<game.size; j++)
            fscanf(fp, "%d", &game.init_board[i][j]);

    fscanf(fp, "%s", game.history);
    fclose(fp);

    game.start_time = time(NULL); // 이어하기 시작 시간 리셋
    return 1;
}

// --- 2. 리플레이 기능 ---
void playReplay() {
    printf("\n--- 리플레이를 시작합니다! ---\n");
    Sleep(1000);

    int temp_board[MAX_SIZE][MAX_SIZE];
    memcpy(temp_board, game.init_board, sizeof(game.init_board));

    // 리플레이용 임시 빈칸 위치 찾기
    int temp_er = 0, temp_ec = 0;
    for(int i=0; i<game.size; i++)
        for(int j=0; j<game.size; j++)
            if(temp_board[i][j] == 0) { temp_er = i; temp_ec = j; }

    int original_er = game.empty_r, original_ec = game.empty_c;
    game.empty_r = temp_er; game.empty_c = temp_ec;

    for (int i = 0; i < game.move_count; i++) {
        memcpy(game.board, temp_board, sizeof(temp_board));
        printBoard(game.board);
        printf("\n리플레이 진행 중... (%d / %d)\n", i+1, game.move_count);

        moveDirection(game.history[i]);
        memcpy(temp_board, game.board, sizeof(game.board));
        Sleep(300); // 0.3초 대기
    }

    printf("\n리플레이 종료!\n");
    system("pause");
}

// --- 6. 랭킹 보드 (이진 파일 입출력) ---
void saveRanking() {
    Record records[11];
    int count = 0;
    FILE* fp = fopen(rank_file, "rb");
    if (fp != NULL) {
        count = fread(records, sizeof(Record), 10, fp);
        fclose(fp);
    }

    printf("\n축하합니다! 이름을 입력하세요: ");
    scanf("%19s", records[count].name);
    records[count].size = game.size;
    records[count].moves = game.move_count;
    records[count].time = game.elapsed_time + (int)(time(NULL) - game.start_time);
    count++;

    // 단순 정렬 (이동 횟수 기준 오름차순)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (records[i].moves > records[j].moves) {
                Record temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
    if (count > 10) count = 10; // 상위 10개만 유지

    fp = fopen(rank_file, "wb");
    fwrite(records, sizeof(Record), count, fp);
    fclose(fp);
}

void printRanking() {
    Record records[10];
    FILE* fp = fopen(rank_file, "rb");
    if (fp == NULL) {
        printf("등록된 랭킹이 없습니다.\n");
        system("pause");
        return;
    }
    int count = fread(records, sizeof(Record), 10, fp);
    fclose(fp);

    system("cls");
    printf("===== 명예의 전당 (Top 10) =====\n");
    printf("순위\t이름\t퍼즐\t이동\t시간(초)\n");
    printf("--------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%dx%d\t%d\t%d\n", i+1, records[i].name, records[i].size, records[i].size, records[i].moves, records[i].time);
    }
    printf("--------------------------------\n");
    system("pause");
}

// --- 메인 함수 ---
int main() {
    int choice;
    while (1) {
        system("cls");
        printf("1. 새 게임 (3x3)\n");
        printf("2. 새 게임 (4x4)\n");
        printf("3. 새 게임 (5x5)\n");
        printf("4. 이어하기\n");
        printf("5. 랭킹 보기\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        if (choice == 0) break;
        if (choice == 5) { printRanking(); continue; }

        if (choice >= 1 && choice <= 3) {
            int size = (choice == 1) ? 3 : (choice == 2) ? 4 : 5;
            int mode;
            printf("모드 선택 (0: 숫자, 1: 그림(알파벳)): ");
            scanf("%d", &mode);
            initGame(size, mode);
        } else if (choice == 4) {
            if (!loadGame()) {
                printf("저장된 게임이 없습니다!\n");
                Sleep(1000);
                continue;
            }
        } else continue;

        // 게임 루프
        while (1) {
            printBoard(game.board);
            if (checkWin()) {
                printf("\n*** 퍼즐 완성! ***\n");
                saveRanking();
                printf("리플레이를 보시겠습니까? (Y/N): ");
                char ans = _getch();
                if (ans == 'y' || ans == 'Y') playReplay();
                break;
            }

            int key = _getch();
            if (key == 224) { // 방향키
                key = _getch();
                char dir = 0;
                // 빈칸 이동: 위 화살표(72) -> 빈칸이 아래로(D), 등등
                if (key == 72) dir = 'D';      
                else if (key == 80) dir = 'U';
                else if (key == 75) dir = 'R';
                else if (key == 77) dir = 'L';

                if (dir && moveDirection(dir)) {
                    game.history[game.move_count++] = dir;
                }
            } else if (key == 's' || key == 'S') {
                saveGame();
                break; // 저장 후 메인 메뉴로
            } else if (key == 'q' || key == 'Q') {
                break; // 종료
            }
        }
    }
    return 0;
}