#include <stdio.h>
#include <string.h>

int main() {
    FILE* filePointer; // 파일 포인터 선언
    char fileName[100]; // 파일 이름을 저장할 배열
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // 파일이 저장 될 경로
    char content[1000]; // 입력 받을 내용을 저장할 배열

    printf("파일 이름을 입력하세요: ");
    scanf("%s", fileName); // 파일 이름 입력 받기

    printf("파일에 입력할 내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");

    //파일 경로 생성
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, fileName);

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
