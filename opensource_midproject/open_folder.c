#include <stdio.h>

int main() {
    FILE* file;
    char filename[] = "C:\\Users\\kimmi\\Desktop\\도구\\qwer.txt."; // 파일 경로를 직접 추가하세요.

    // 파일 열기 시도
    file = fopen(filename, "w");

    // 파일이 성공적으로 열렸는지 확인
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 파일 내용 읽어오기
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); // 화면에 한 글자씩 출력
    }

    // 파일 닫기
    fclose(file);

    return 0;
}


// 경로를 입력할때 \\ 두개 가 필요함.
//C:\\Users\\kimmi\\Desktop\\도구 여기 폴더에 qwer이라는 .txt 파일 생성.
