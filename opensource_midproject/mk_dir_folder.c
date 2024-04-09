#include <windows.h> //윈도우에 폴더를 만들기 위한 헤더파일
#include <stdio.h>
#include <string.h> //입력한 주소와 기본 주소를 합치기 위한 헤더파일 - strcpy, strcat 사용


void make_dir_folder(char* name)
{
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

}


int main()
{
    char* input_string = NULL;
    char temp_buffer[100]; // 임시 버퍼
    printf("만들려는 폴더명을 입력하세요 : ");
    scanf("%s", temp_buffer); // 문자열 입력 받기

    // 동적 메모리 할당
    input_string = (char*)malloc(strlen(temp_buffer) + 1);
    if (input_string == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 입력받은 문자열 복사
    strcpy(input_string, temp_buffer);

    make_dir_folder(input_string);

    // 메모리 해제
    free(input_string);
}