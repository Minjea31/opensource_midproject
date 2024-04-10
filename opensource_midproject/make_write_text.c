#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000



int make_write_text(char* input_title, char* input_content) {
    FILE* filePointer; // 파일 포인터 선언
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // 파일이 저장 될 경로

    //파일 경로 생성
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, input_title);

    // "w" 쓰기 모드로 열기
    filePointer = fopen(fullPath, "w");

    // 파일이 정상적으로 열렸는지 확인
    if (filePointer == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return -1; // 오류 코드 반환
    }

    // 내용 입력
    fprintf(filePointer, "%s", input_content); // 파일에 입력한 내용 쓰기

    fclose(filePointer);

    printf("파일이 성공적으로 생성되었습니다.\n");

    return 0;
}

int main()
{
    char input_title[MAX_TITLE_LENGTH]; // 제목을 입력받을 배열
    char input_content[MAX_CONTENT_LENGTH]; // 내용을 입력받을 배열


    printf("제목을 입력하세요 : ");
    fgets(input_title, MAX_TITLE_LENGTH, stdin); // 제목 입력 받기
    input_title[strcspn(input_title, "\n")] = '\0'; // 개행문자 제거

    printf("내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");
    input_content[0] = '\0'; // 내용 배열 초기화

    while (1) {
        fgets(input_content + strlen(input_content), MAX_CONTENT_LENGTH - strlen(input_content), stdin); // 사용자 입력 받기
        // "//" 입력하면 종료
        if (strncmp(input_content + strlen(input_content) - 3, "//", 2) == 0)
        {
            break;
        }
    }

    // 입력된 제목과 내용을 함수에 전달
    make_write_text(input_title, input_content);

    return 0;
}