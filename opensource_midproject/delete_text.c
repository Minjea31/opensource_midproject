#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LENGTH 200

void delete_text(const char* folder_name, const char* input_title) {
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    // 파일 삭제
    if (remove(filePath) == 0) {
        printf("파일이 성공적으로 삭제되었습니다.\n");
    }
    else {
        printf("파일 삭제에 실패했습니다.\n");
    }
}

int main() {
    char input_folder_d[MAX_PATH_LENGTH]; // 저자명을 입력받을 배열
    char input_title_d[MAX_PATH_LENGTH]; // 제목을 입력받을 배열

    printf("저자명을 입력하세요: ");
    fgets(input_folder_d, MAX_PATH_LENGTH, stdin); // 저자명 입력 받기
    input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // 개행 문자 제거

    printf("제목을 입력하세요: ");
    fgets(input_title_d, MAX_PATH_LENGTH, stdin); // 제목 입력 받기
    input_title_d[strcspn(input_title_d, "\n")] = '\0'; // 개행 문자 제거

    // 파일 삭제 함수 호출
    delete_text(input_folder_d, input_title_d);

    return 0;
}
