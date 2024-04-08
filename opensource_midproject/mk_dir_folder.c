#include <windows.h> //윈도우에 폴더를 만들기 위한 헤더파일
#include <stdio.h>
#include <string.h> //입력한 주소와 기본 주소를 합치기 위한 헤더파일 - strcpy, strcat 사용

int main() {
    char* name = (char*)malloc(100 * sizeof(char)); //동적할당으로 만들 파일의 이름을 입력받기 ->여기에 저자이름이 들어가게 될것.
    printf("만들려는 폴더 이름을 입력하시오 : ");
    scanf("%s", name);

    char folderPath[MAX_PATH];
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\"); //바탕화면에 입력한 이름으로 폴더 생성
    strcat(folderPath, name); // 원래있던 기본 주소와 입력한 만들 폴더 이름과 합침.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) {
        printf("폴더가 성공적으로 생성되었습니다.\n");
    }
    else {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("폴더가 이미 존재합니다.\n");
        }
        else {
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
        }
    }

    return 0;
}