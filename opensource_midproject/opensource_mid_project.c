#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000


void make_dir_folder(const char* name)
{
    char folderPath[MAX_PATH];
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\"); // 바탕화면에 입력한 이름으로 폴더 생성
    strcat(folderPath, name); // 원래있던 기본 주소와 입력한 만들 폴더 이름과 합침.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) {
        printf("폴더가 성공적으로 생성되었습니다.\n");
    }
    else {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("이미 저자 폴더가 존재하기때문에 그 안에 만들었습니다. \n");
        }
        else {
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
        }
    }
}

void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    char folderPath[MAX_PATH];
    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\%s\\", folder_name); // 폴더 경로 생성

    char filePath[MAX_PATH];
    sprintf(filePath, "%s%s.txt", folderPath, input_title); // 파일 경로 생성

    // 폴더가 이미 존재하는지 확인
    DWORD attrib = GetFileAttributesA(folderPath);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("폴더가 이미 존재합니다.\n");
    }
    else {
        // 폴더 생성
        BOOL result = CreateDirectoryA(folderPath, NULL);
        if (!result) {
            DWORD error = GetLastError();
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
            return;
        }
    }

    FILE* filePointer = fopen(filePath, "w"); // "w" 쓰기 모드로 파일 열기

    if (filePointer == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("파일이 성공적으로 생성되었습니다.\n");
}

int main()
{
    ///////////////////////폴더 생성///////////////////////////////////////
    char input_folder[MAX_TITLE_LENGTH]; // 폴더명을 입력받을 배열
    printf("만들려는 폴더명을 입력하세요 : ");
    fgets(input_folder, MAX_TITLE_LENGTH, stdin); // 폴더명 입력 받기
    input_folder[strcspn(input_folder, "\n")] = '\0'; // fgets로 입력받은 문자열의 개행 문자 제거

    ///////////////////////////////////////////////////////////////////////

    ///////////////////////제목 입력///////////////////////////////////////
    char input_title[MAX_TITLE_LENGTH]; // 제목을 입력받을 배열
    printf("제목을 입력하세요 : ");
    fgets(input_title, MAX_TITLE_LENGTH, stdin); // 제목 입력 받기
    input_title[strcspn(input_title, "\n")] = '\0'; // fgets로 입력받은 문자열의 개행 문자 제거

    ///////////////////////내용 입력///////////////////////////////////////
    char input_content[MAX_CONTENT_LENGTH]; // 내용을 입력받을 배열

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
    make_write_text(input_folder, input_title, input_content);

    return 0;
}

//read_text(); //제목을 입력하면 .txt파일의 내용을 출력해줌.