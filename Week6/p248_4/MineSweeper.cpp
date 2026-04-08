#include "MineSweeper.h"

enum LavelType {Empty = 0, bomb = 9};
enum MaskType {Hide = 0, Open, Flag};

// 1. 맵의 최대 크기를 80x40으로 정적 할당
static int MineMapMask[40][80];   // Hide, Open, Flag
static int MineMapLabel[40][80];  // 0~8, 9(bomb)

// 동적으로 사용할 맵의 크기와 지뢰 개수 변수
static int nx, ny;
static int nBomb;

// 여러 가지 작은 함수들
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y) {         // (x,y)를 파는 함수
    if (isValid(x, y) && mask(x, y) != Open) {
        mask(x, y) = Open;
        if (label(x, y) == 0) {
            dig(x - 1, y - 1);
            dig(x - 1, y);
            dig(x - 1, y + 1);
            dig(x, y - 1);
            dig(x, y + 1);
            dig(x + 1, y - 1);
            dig(x + 1, y);
            dig(x + 1, y + 1);
        }
    }
}

static void mark(int x, int y) {        // (x,y)를 깃발로 표시하는 함수
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;    
}

static int getBombCount() {             // 깃발의 수를 계산하는 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag)
                count++;
    return count;
}

static void print() {                   // 지뢰 맵의 화면 출력 함수
    system("cls");
    printf(" 발견:%2d 전체:%2d\n", getBombCount(), nBomb);

    // 3. 열 번호 출력 (두 자리 수를 고려해 간격 조정)
    printf("   ");
    for (int x = 0; x < nx; x++) {
        printf("%2d ", x + 1);
    }
    printf("\n");

    // 3. 행 번호 출력 및 맵 표시 (원본 코드의 nx, ny 반복 범위 오류 수정)
    for (int y = 0; y < ny; y++) {
        printf("%2d ", y + 1);           // 행 번호
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == Hide)      // 파지 않은 곳
                printf(".  ");            
            else if (mask(x, y) == Flag) // 지뢰 예상 자리
                printf("P  ");
            else {                       // 판 자리        
                if (isBomb(x, y))        // 9: 폭발!
                    printf("* ");        
                else if (isEmpty(x, y))  // 0: 빈칸 표시
                    printf("   ");
                else
                    printf("%-3d", label(x, y)); // 1~8: 숫자 표시
            }
        }
        printf("\n");
    }
}

static int countNbrBombs(int x, int y) { // 인접한 지뢰의 수 계산 함수
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == bomb)
                count++;
    return count;
}

static void init(int width, int height, int total) {
    srand((unsigned)time(NULL));
    nx = width;
    ny = height;
    nBomb = total;

    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {   // 지뢰 맵, 마스크 초기화
            mask(x, y) = Hide;
            label(x, y) = 0;
        }

    for (int i = 0; i < nBomb; i++) {    // 지뢰 매설 (total 개)
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);  
        label(x, y) = bomb;
    }

    for (int y = 0; y < ny; y++)         // 인접한 지뢰의 수 계산
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}

static bool getPos(int& x, int& y) {     // 키보드 좌표 입력 함수
    printf("\n지뢰(P) 열(1-%d) 행(1-%d)\n 입력 --> ", nx, ny);

    char first[10];
    int c, r;
    bool isBomb = false;

    // 4. "열 행" 또는 "P 열 행" 방식의 입력을 모두 처리
    scanf("%s", first);

    // 첫 입력이 'P' 또는 'p'인 경우
    if (tolower(first[0]) == 'p') {
        isBomb = true;
        scanf("%d %d", &c, &r);
    }
    // 첫 입력이 숫자인 경우 (바로 열 번호로 사용)
    else {
        c = atoi(first);
        scanf("%d", &r);
    }

    // 사용자는 1-based index를 입력하므로 0-based로 변환
    x = c - 1;              
    y = r - 1;
    return isBomb;
}

static int checkDone() {                 // 게임 종료 여부 체크 함수
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open)
                count++;
            else if (isBomb(x, y))
                return -1;  
        }
    return (count == nBomb) ? 1 : 0;  
}

void playMinSweeper(int width, int height, int total) {
    int x, y, status;
    init(width, height, total);
    do {
        print();
        bool isBomb = getPos(x, y);
        if (isBomb) mark(x, y);
        else        dig(x, y);
        status = checkDone();
    } while (status == 0);

    print();
    if (status < 0)
        printf("\n실패: 지뢰 폭발!!!\n\n");
    else
        printf("\n성공: 탐색 성공!!!\n\n");
}

int main()
{
    int width, height, total;
    printf(" <Mine Sweeper>\n");

    // 1 & 2. 맵의 크기 및 매설할 지뢰 개수 입력받기
    printf(" 맵의 가로 크기 입력 (최대 80) : ");
    scanf("%d", &width);
    printf(" 맵의 세로 크기 입력 (최대 40) : ");
    scanf("%d", &height);
    printf(" 매설할 총 지뢰의 개수 입력 : ");
    scanf("%d", &total);

    // 사용자가 최대 크기를 넘기거나 지뢰 개수를 맵 크기보다 많이 입력했을 경우 방어
    if (width > 80) width = 80;
    if (height > 40) height = 40;
    if (total >= width * height) total = width * height - 1;

    playMinSweeper(width, height, total);

    return 0;
}
