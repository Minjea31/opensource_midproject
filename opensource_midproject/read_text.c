#include <stdio.h>

int main() {
    FILE* filePointer; // 파일 포인터 선언
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\kim.txt"; // 파일 경로를 직접 지정합니다.

    // 파일 열기. "r" 모드는 읽기 모드로 파일을 엽니다.
    filePointer = fopen(filePath, "r");

    // 파일이 정상적으로 열렸는지 확인
    if (filePointer == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return -1; // 오류 코드 반환
    }

    // 파일에서 한 줄씩 읽어와 출력하기
    char buffer[100]; // 읽은 내용을 저장할 버퍼
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        printf("%s", buffer);
    }

    // 파일 닫기
    fclose(filePointer);

    return 0; // 프로그램 종료
}
