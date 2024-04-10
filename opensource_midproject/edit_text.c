#include <stdio.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_PATH_LENGTH 200

void edit_text(const char* folder_name, const char* input_title, const char* input_content) {
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // 파일 경로

    FILE* filePointer = fopen(filePath, "w"); // "w" 쓰기 모드로 파일 열기

    if (filePointer == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("파일이 성공적으로 덮어쓰기 되었습니다.\n");
}

int main() {
    char input_folder_e[MAX_TITLE_LENGTH]; // 저자명을 입력받을 배열
    char input_title_e[MAX_TITLE_LENGTH]; // 제목을 입력받을 배열
    char input_content_e[MAX_CONTENT_LENGTH]; // 내용을 입력받을 배열

    printf("저자명을 입력하세요: ");
    fgets(input_folder_e, MAX_TITLE_LENGTH, stdin); // 저자명 입력 받기
    input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // 개행 문자 제거를 위한 코드

    printf("제목을 입력하세요: ");
    fgets(input_title_e, MAX_TITLE_LENGTH, stdin); // 제목 입력 받기
    input_title_e[strcspn(input_title_e, "\n")] = '\0'; // 개행 문자 제거를 위한 코드

    printf("내용을 입력하세요: ");
    fgets(input_content_e, MAX_CONTENT_LENGTH, stdin); // 내용 입력 받기

    // 파일 내용 덮어쓰기
    edit_text(input_folder_e, input_title_e, input_content_e);

    return 0;
}