#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1024
#define MAX_PATH_LENGTH 200

//콘솔창 리셋
void clearScreen()
{
    system("cls"); // 콘솔창 리셋
}

//저자 폴더 만드는 함수
void make_dir_folder(const char* name)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    char* folderPath = NULL;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\"); // 독후감상문 폴더에 저자명으로 폴더 생성
    strcat(folderPath, name); // 원래있던 기본 주소와 저자명과 합침.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();
        printf("감상문 작성 완료.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
    }
    else 
    {
        DWORD error = GetLastError();

        if (error == ERROR_ALREADY_EXISTS) 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            clearScreen();
            printf("저자명 폴더가 존재합니다. \n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            clearScreen();
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        }
    }

    free(folderPath);
}

//감상문 파일을 만드는 함수
void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    char* folderPath = NULL;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\", folder_name); // 폴더 경로 생성

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "%s%s.txt", folderPath, input_title); // 파일 경로 생성

    
    DWORD attrib = GetFileAttributesA(folderPath);

    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        // 폴더 생성
        BOOL result = CreateDirectoryA(folderPath, NULL);

        if (!result)
        {
            DWORD error = GetLastError();
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
            return;
        }
    }

    FILE* filePointer = fopen(filePath, "r"); // 파일을 읽기 모드로 열기

    if (filePointer != NULL)
    {
        // 파일이 이미 존재하는 경우
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();
        printf("\n\n");
        printf("%s에 대한 감상문이 이미 존재합니다.\n", input_title);
        printf("\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        fclose(filePointer);
        return;
    }

    // 파일이 존재하지않을경우 입력
    filePointer = fopen(filePath, "w");
    if (filePointer == NULL)
    {
        DWORD error = GetLastError();
        printf("파일을 생성할 수 없습니다. 오류 코드: %lu\n", error);
        return;
    }

    // txt 파일에 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨

    clearScreen();
    printf("\n\n");
    printf("감상문이 성공적으로 작성되었습니다.\n");
    printf("\n\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값

    free(folderPath);
    free(filePath);
}

//감상문 파일를 출력 함수
void read_text(const char* folder_name, const char* input_title)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    FILE* filePointer = fopen(filePath, "r"); // "r" 모드로 파일 열기

    if (filePointer == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();
        printf("\n\n해당하는 감상문이 없습니다.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        return;
    }

    printf("==================감상문 내용=======================\n");

    // 파일에서 한 줄씩 읽어와 출력하기
    char*buffer = NULL;
    buffer = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));// 읽은 내용을 저장할 버퍼

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) 
    {
        printf("%s", buffer);
    }

    printf("\n======================================================\n");

    fclose(filePointer); // 파일 닫기
    free(filePath);
    free(buffer);
}

//감상문 내용을 수정 함수
void edit_text(const char* folder_name, const char* input_title, const char* input_content) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    FILE* filePointer = fopen(filePath, "w"); // "w" 쓰기 모드로 파일 열기

    if (filePointer == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();

        printf("\n\n해당하는 감상문이 없습니다.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        return;
    }

    // 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);
    clearScreen();
    printf("===================================================\n");
    printf("수정 후 정보\n");
    printf("저자명: %s\n", folder_name);
    printf("제목: %s\n", input_title);
    printf("내용: \n%s\n", input_content);
    printf("===================================================\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
    printf("\n\n파일이 성공적으로 덮어쓰기 되었습니다.\n\n\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
    free(filePath);
}

//감상문 text파일을 삭제 함수
void delete_text(const char* folder_name, const char* input_title) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성
    
    char check[4];
    int valid_input = 0; //입력값이 있는지 확인하는 변수

    while (!valid_input) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        printf("\n=========================================\n");
        printf("삭제하시겠습니까? (복구할 수 없습니다) \n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        printf("yes/no ==>> ");
        scanf("%3s", check);
        clearScreen();

        if (strcmp(check, "yes") == 0 || strcmp(check, "no") == 0) 
        {
            valid_input = 1; // 입력이 있는 경우 반복문 종료
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            printf("\n\n잘못된 입력입니다. 다시 입력해주세요.\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
            
            while (getchar() != '\n'); // 입력 버퍼를 비워줌
        }
    }

    if (strcmp(check, "yes") == 0)
    {
        // 파일 삭제
        if (remove(filePath) == 0)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            clearScreen();
            printf("\n\n파일이 성공적으로 삭제되었습니다.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            clearScreen();
            printf("\n해당하는 감상문이 없습니다.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        }
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();
        printf("\n\n삭제가 취소 되었습니다.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
    }
    free(filePath);
}

//책 추천해주는 함수
void recommend_book(const char* filename) 
{

    FILE* file = fopen(filename, "r");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드
    if (file == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        clearScreen();
        perror("파일 열기 실패");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        return;
    }

    // 파일에서 총 줄 수를 계산
    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch == '\n') 
        {
            lines++;
        }
    }
    rewind(file); // 파일 포인터를 다시 파일의 시작으로 이동

    // 랜덤 시드 설정
    srand((unsigned int)time(NULL));

    // 랜덤 줄 선택
    int random_line = rand() % lines;

    
    int current_line = 0;
    char buffer[1024];
    char* title = NULL;
    title = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char)); // 제목 문자 배열
    char* author = NULL;
    author = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char)); // 저자 문자 배열

    // 선택된 줄까지 이동 후 // 기준으로 제목과 저자를 나누어 출력
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        if (current_line == random_line) 
        {
            // 줄에서 "//"를 기준으로 제목과 저자 분리
            char* slash_pos = strstr(buffer, "//");
            if (slash_pos != NULL) 
            {
                *slash_pos = '\0'; // "//" 이전 내용은 제목
                strcpy(title, buffer);
                strcpy(author, slash_pos + 2); // "//" 이후 내용은 저자
            }
            break;
        }
        current_line++;
    }

    clearScreen();

    // 선택된 내용 출력
    printf("\n\n제목 : %s\n", title);
    printf("저자 : %s\n\n", author);

    free(title);
    free(author);

    fclose(file);
}

//책 추천 목록 추가 함수
void add_recommend_book(const char* filename, const char* new_data) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드
    FILE* file = fopen(filename, "a");
    if (file == NULL) 
    {
        clearScreen();
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        perror("파일 열기 실패");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        return;
    }

    // 데이터를 파일에 추가
    fprintf(file, "%s\n", new_data);
    fclose(file);
}


int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //글자색 변환 코드

    int set = -1;

    while (set != 0)
    {
        printf("======================================================\n");
        printf("1. 감상문 작성\n");
        printf("2. 감상문 출력\n");
        printf("3. 감상문 수정(재입력)\n");
        printf("4. 감상문 삭제\n");
        printf("5. 책 추천\n");
        printf("6. 책 추천 목록 추가 \n");
        printf("0. 종료\n");
        printf("======================================================\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
        printf("원하는 메뉴를 입력하세요 : ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값


        scanf("%d", &set);
        getchar();

        switch (set)
        {
        case 1:
        {
            clearScreen();

            char* input_folder = NULL;
            char* input_title = NULL;
            char* input_content = NULL;


            int valid_input = 0;

            while (!valid_input)
            {
                // 저자명 입력 받기
                printf("저자명을 입력하세요: ");
                input_folder = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));

                if (input_folder == NULL)
                {
                    printf("메모리 할당 실패\n");
                    return 1;
                }
                fgets(input_folder, MAX_TITLE_LENGTH, stdin);
                input_folder[strcspn(input_folder, "\n")] = '\0'; // 개행 문자 제거

                // 저자명이 입력되지 않은 경우
                if (strlen(input_folder) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("저자명이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_folder);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 초기화 후 다시 검색
            while (!valid_input)
            {
                // 제목 입력 받기
                printf("제목을 입력하세요: ");
                input_title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder); // 저자명 메모리 해제
                    return 1;
                }
                fgets(input_title, MAX_TITLE_LENGTH, stdin);
                input_title[strcspn(input_title, "\n")] = '\0'; // 개행 문자 제거

                // 제목이 입력되지 않은 경우
                if (strlen(input_title) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("제목이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_title);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 다시 초기화하여 다음 입력에 대해 검증 시작

            while (!valid_input)
            {
                
                printf("내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");
                input_content = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

                if (input_content == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder); // 저자명 메모리 해제
                    free(input_title);  // 제목 메모리 해제
                    return 1;
                }

                input_content[0] = '\0'; // 내용 배열 초기화
                // 내용 입력 받기

                while (1)
                {
                    fgets(input_content + strlen(input_content), MAX_CONTENT_LENGTH - strlen(input_content), stdin); // 사용자 입력 받기
                    // "//" 입력하면 종료
                    if (strncmp(input_content + strlen(input_content) - 3, "//", 2) == 0)
                    {
                        input_content[strlen(input_content) - 3] = '\0'; // "//" 제거
                        break;
                    }
                }

                // 내용이 입력되지 않은 경우
                if (strlen(input_content) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("내용이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_content);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
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
            clearScreen();
            char* input_folder_r = NULL;
            char* input_title_r = NULL;
            int valid_input = 0;

            // 저자명 입력 받기
            while (!valid_input)
            {
                printf("저자명을 입력하세요: ");
                input_folder_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));

                if (input_folder_r == NULL)
                {
                    printf("메모리 할당 실패\n");
                    return 1;
                }
                fgets(input_folder_r, MAX_PATH_LENGTH, stdin);
                input_folder_r[strcspn(input_folder_r, "\n")] = '\0'; // 개행 문자 제거

                // 저자명이 입력되지 않은 경우
                if (strlen(input_folder_r) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("저자명이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_folder_r);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 다시 초기화하여 다음 입력에 대해 검증 시작
            // 제목 입력 받기
            while (!valid_input)
            {
                printf("제목을 입력하세요: ");
                input_title_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
                if (input_title_r == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder_r); // 동적 할당 해제
                    return 1;
                }
                fgets(input_title_r, MAX_PATH_LENGTH, stdin);
                input_title_r[strcspn(input_title_r, "\n")] = '\0'; // 개행 문자 제거

                // 제목이 입력되지 않은 경우
                if (strlen(input_title_r) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("제목이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_title_r);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }
            // 파일 읽기 함수 호출
            read_text(input_folder_r, input_title_r);

            set = -1;
            free(input_folder_r);
            free(input_title_r);
            break;
        }
        case 3:
        {

            clearScreen();
            char* input_folder_e = NULL;
            char* input_title_e = NULL;
            char* input_content_e = NULL;
            int valid_input = 0;

            while (!valid_input)
            {
                // 저자명 입력 받기
                printf("저자명을 입력하세요: ");
                input_folder_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_folder_e == NULL)
                {
                    printf("메모리 할당 실패\n");
                    return 1;
                }
                fgets(input_folder_e, MAX_TITLE_LENGTH, stdin);
                input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // 개행 문자 제거

                // 저자명이 입력되지 않은 경우
                if (strlen(input_folder_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("저자명이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_folder_e);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 다시 초기화하여 다음 입력에 대해 검증 시작
            while (!valid_input)
            {
                // 제목 입력 받기
                printf("제목을 입력하세요: ");
                input_title_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title_e == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder_e); // 저자명 메모리 해제
                    return 1;
                }
                fgets(input_title_e, MAX_TITLE_LENGTH, stdin);
                input_title_e[strcspn(input_title_e, "\n")] = '\0'; // 개행 문자 제거

                // 제목이 입력되지 않은 경우
                if (strlen(input_title_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("제목이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_title_e);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 다시 초기화하여 다음 입력에 대해 검증 시작
            while (!valid_input)
            {
                // 내용 입력 받기
                printf("내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");
                input_content_e = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
                if (input_content_e == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder_e); // 저자명 메모리 해제
                    free(input_title_e);  // 제목 메모리 해제
                    return 1;
                }

                input_content_e[0] = '\0'; // 내용 배열 초기화
                while (1)
                {
                    fgets(input_content_e + strlen(input_content_e), MAX_CONTENT_LENGTH - strlen(input_content_e), stdin); // 사용자 입력 받기
                    // "//" 입력하면 종료
                    if (strncmp(input_content_e + strlen(input_content_e) - 3, "//", 2) == 0)
                    {
                        input_content_e[strlen(input_content_e) - 3] = '\0'; // "//" 제거
                        break;
                    }
                }

                // 내용이 입력되지 않은 경우
                if (strlen(input_content_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("내용이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_content_e);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            clearScreen();
            // 덮어쓰기 함수에 전달
            edit_text(input_folder_e, input_title_e, input_content_e);

            // 메모리 해제
            free(input_folder_e);
            free(input_title_e);
            free(input_content_e);
            break;
        }
        case 4:
        {
            clearScreen();
            char* input_folder_d = NULL;
            char* input_title_d = NULL;

            int valid_input = 0;

            while (!valid_input)
            {
                // 저자명 입력 받기
                printf("저자명을 입력하세요: ");
                input_folder_d = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_folder_d == NULL)
                {
                    printf("메모리 할당 실패\n");
                    return 1;
                }
                fgets(input_folder_d, MAX_TITLE_LENGTH, stdin);
                input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // 개행 문자 제거

                // 저자명이 입력되지 않은 경우
                if (strlen(input_folder_d) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("저자명이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_folder_d);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }

            valid_input = 0; // 다시 초기화하여 다음 입력에 대해 검증 시작
            while (!valid_input)
            {
                // 제목 입력 받기
                printf("제목을 입력하세요: ");
                input_title_d = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title_d == NULL)
                {
                    printf("메모리 할당 실패\n");
                    free(input_folder_d); // 저자명 메모리 해제
                    return 1;
                }
                fgets(input_title_d, MAX_TITLE_LENGTH, stdin);
                input_title_d[strcspn(input_title_d, "\n")] = '\0'; // 개행 문자 제거

                // 제목이 입력되지 않은 경우
                if (strlen(input_title_d) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
                    printf("제목이 입력되지 않았습니다. 다시 입력해주세요.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
                    free(input_title_d);
                }
                else
                {
                    valid_input = 1; // 입력이 있으면 반복문 종료
                }
            }
            clearScreen();
            // 파일 삭제 함수 호출
            delete_text(input_folder_d, input_title_d);

            free(input_folder_d);
            free(input_title_d);
            break;
        }
        case 5:
        {
            clearScreen();
            const char* re_filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt";
            recommend_book(re_filename);
            break;
        }
        case 6:
        {
            clearScreen();
            const char* add_filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt"; // 파일의 주소를 직접 지정

            char* add_data;// 입력 받을 문자열 배열 선언
            add_data = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

            // 사용자로부터 제목과 저자를 입력 받음
            printf("제목//저자 형태로 입력하세요: ");
            scanf(" %[^\n]", add_data); // 개행 문자를 제외한 문자열 입력 받기

            // 파일에 내용 추가
            add_recommend_book(add_filename, add_data);

            clearScreen();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            printf("\n\n성공적으로 추가되었습니다.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
            free(add_data);
            break;
        }
        case 0:
        {
            ///////////종료/////////////////
            printf("\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            printf("====================종료되었습니다.====================");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
            break;
        }
        default:
        {
            clearScreen();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 붉은색 글씨
            printf("\n======================================================\n");
            printf("menu 내에서 선택해주세요.\n");
            printf("======================================================\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 글자색 기본값
        }
        }
    }
}