#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void append_to_file(const char* filename, const char* new_data) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 데이터를 파일에 추가
    fprintf(file, "%s\n", new_data);

    // 선택된 줄 출력
    srand(time(NULL));
    int random_line = rand() % 2;
    if (random_line == 0) {
        printf("제목 : %s\n", strtok((char*)new_data, "//"));
        printf("저자 : %s\n", strtok(NULL, "//"));
    }

    fclose(file);
}

int main() {
    const char* filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt"; // 파일의 주소를 직접 지정

    char new_data[1024];
    printf("제목//저자 형태로 입력하세요: ");
    fgets(new_data, sizeof(new_data), stdin);
    // fgets는 개행 문자도 포함하기 때문에 개행 문자 제거
    new_data[strcspn(new_data, "\n")] = '\0';

    append_to_file(filename, new_data);

    printf("성공적으로 추가되었습니다.\n");

    return 0;
}
