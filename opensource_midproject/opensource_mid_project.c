#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_PATH_LENGTH 200


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

void read_text(const char* folder_name, const char* input_title)
{
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    FILE* filePointer = fopen(filePath, "r"); // "r" 모드로 파일 열기

    if (filePointer == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일에서 한 줄씩 읽어와 출력하기
    char buffer[100]; // 읽은 내용을 저장할 버퍼
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        printf("%s", buffer);
    }

    fclose(filePointer); // 파일 닫기
}

void edit_text(const char* folder_name, const char* input_title, const char* input_content) {
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

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

int main()
{
    int set = -1;

    while (set != 0)
    {
        printf("======================================================\n");
        printf("1. 감상문 작성\n");
        printf("2. 감상문 출력\n");
        printf("3. 감상문 수정(재입력)\n");
        printf("4. 감상문 삭제\n");
        printf("0. 종료\n");
        printf("======================================================\n");
        printf("원하는 메뉴를 입력하세요 : ");


        scanf("%d", &set);
        getchar();

        switch (set)
        {
        case 1:
        {
            char* input_folder = NULL;
            char* input_title = NULL;
            char* input_content = NULL;

            // 폴더명 입력 받기
            printf("저자명을 입력하세요 : ");
            input_folder = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_folder == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder, MAX_TITLE_LENGTH, stdin);
            input_folder[strcspn(input_folder, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요 : ");
            input_title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder); // 폴더명 메모리 해제
                return 1;
            }
            fgets(input_title, MAX_TITLE_LENGTH, stdin);
            input_title[strcspn(input_title, "\n")] = '\0'; // 개행 문자 제거

            // 내용 입력 받기
            printf("내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");
            input_content = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder); // 폴더명 메모리 해제
                free(input_title);  // 제목 메모리 해제
                return 1;
            }
            input_content[0] = '\0'; // 내용 배열 초기화
            while (1) {
                fgets(input_content + strlen(input_content), MAX_CONTENT_LENGTH - strlen(input_content), stdin); // 사용자 입력 받기
                // "//" 입력하면 종료
                if (strncmp(input_content + strlen(input_content) - 3, "//", 2) == 0) {
                    break;
                }
            }

            make_write_text(input_folder, input_title, input_content);
            set = -1;
            //메모리 해제
            free(input_folder);
            free(input_title);
            free(input_content);
            break;
        }
        case 2:
        {
            char* input_folder_r = NULL;
            char* input_title_r = NULL;

            // 저자명 입력 받기
            printf("저자명을 입력하세요 : ");
            input_folder_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_folder_r == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_r, MAX_PATH_LENGTH, stdin);
            input_folder_r[strcspn(input_folder_r, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요 : ");
            input_title_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_r == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder_r); // 동적 할당 해제
                return 1;
            }
            fgets(input_title_r, MAX_PATH_LENGTH, stdin);
            input_title_r[strcspn(input_title_r, "\n")] = '\0';

            // 파일 읽기 함수 호출
            read_text(input_folder_r, input_title_r);

            set = -1;
            free(input_folder_r);
            free(input_title_r);
            break;
        }
        case 3:
        {
            char* input_folder_e = NULL;
            char* input_title_e = NULL;
            char* input_content_e = NULL;

            // 저자명 입력 받기
            printf("저자명을 입력하세요: ");
            input_folder_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_folder_e == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_e, MAX_TITLE_LENGTH, stdin);
            input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요: ");
            input_title_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title_e == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder_e); // 동적 할당 해제
                return 1;
            }
            fgets(input_title_e, MAX_TITLE_LENGTH, stdin);
            input_title_e[strcspn(input_title_e, "\n")] = '\0'; // 개행 문자 제거

            // 내용 입력 받기
            printf("내용을 입력하세요: ");
            input_content_e = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content_e == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder_e); // 동적 할당 해제
                free(input_title_e); // 동적 할당 해제
                return 1;
            }
            fgets(input_content_e, MAX_CONTENT_LENGTH, stdin);

            // 덮어쓰기 함수에 전달
            edit_text(input_folder_e, input_title_e, input_content_e);

            set = -1;
            //메모리 해제
            free(input_folder_e);
            free(input_title_e);
            free(input_content_e);
            break;
        }
        case 4:
        {
            char* input_folder_d = NULL;
            char* input_title_d = NULL;

            // 저자명 입력 받기
            printf("저자명을 입력하세요: ");
            input_folder_d = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_folder_d == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_d, MAX_PATH_LENGTH, stdin);
            input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요: ");
            input_title_d = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_d == NULL) {
                printf("메모리 할당 실패\n");
                free(input_folder_d); // 동적 할당 해제
                return 1;
            }
            fgets(input_title_d, MAX_PATH_LENGTH, stdin);
            input_title_d[strcspn(input_title_d, "\n")] = '\0';

            // 파일 삭제 함수 호출
            delete_text(input_folder_d, input_title_d);
            free(input_folder_d);
            free(input_title_d);
        }
        case 0:
        {
            ///////////종료/////////////////
            break;
        }
        }
    }
}