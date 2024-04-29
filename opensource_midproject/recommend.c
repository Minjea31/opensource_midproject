#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//책 추천해주는 함수
void recommend_book(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 파일에서 총 줄 수를 계산
    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(file); // 파일 포인터를 다시 파일의 시작으로 이동

    // 랜덤 시드 설정
    srand(time(NULL));

    // 랜덤 줄 선택
    int random_line = rand() % lines;

    // 선택된 줄까지 이동
    int current_line = 0;
    char buffer[1024];
    char* title = NULL;
    title = (char*)malloc(1024 * sizeof(char)); // 제목 공간 동적할당
    char* author = NULL;
    author = (char*)malloc(1024 * sizeof(char));// 저자 공간 동적할당
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (current_line == random_line) {
            // 줄에서 "//"를 기준으로 제목과 저자 분리
            char* slash_pos = strstr(buffer, "//");
            if (slash_pos != NULL) {
                *slash_pos = '\0'; // "//" 이전 내용은 제목
                strcpy(title, buffer);
                strcpy(author, slash_pos + 2); // "//" 이후 내용은 저자
            }
            break;
        }
        current_line++;
    }

    // 선택된 내용 출력
    printf("제목 : %s\n", title);
    printf("저자 : %s\n", author);

    free(title);
    free(author);

    fclose(file);
}


int main() 
{
    const char* filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt"; // 파일의 주소를 직접 지정
    recommend_book(filename);
    return 0;
}
