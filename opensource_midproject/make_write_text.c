#include <stdio.h>
#include <string.h>

int make_write_text(char* input_title) {
    FILE* filePointer; // 파일 포인터 선언
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // 파일이 저장 될 경로
    char content[1000]; // 입력 받을 내용을 저장할 배열

    printf("파일에 입력할 내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");

    //파일 경로 생성
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, input_title);

    // "w" 쓰기 모드로 열기
    filePointer = fopen(fullPath, "w");

    // 파일이 정상적으로 열렸는지 확인
    if (filePointer == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return -1; // 오류 코드 반환
    }

    // 내용 입력
    while (1) {
        fgets(content, sizeof(content), stdin); // 사용자 입력 받기
        // "//" 입력하면 종료
        if (strncmp(content, "//", 2) == 0) {
            break;
        }
        fprintf(filePointer, "%s", content); // 파일에 입력한 내용 쓰기
    }

    fclose(filePointer);

    printf("파일이 성공적으로 생성되었습니다.\n");

    return 0;
}

int main()
{
    char* input_title = NULL;
    char temp_title[100]; // 임시 버퍼
    printf("제목을 입력하세요 : ");
    scanf("%s", temp_title); // 문자열 입력 받기

    // 동적 메모리 할당
    input_title = (char*)malloc(strlen(temp_title) + 1);
    if (input_title == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 입력받은 문자열 복사
    strcpy(input_title, temp_title);

    make_write_text(input_title);

    // 메모리 해제
    free(input_title);
}