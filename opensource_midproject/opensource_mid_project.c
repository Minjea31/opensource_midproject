#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1024
#define MAX_PATH_LENGTH 200


//저자 폴더 만드는 함수
void make_dir_folder(const char* name)
{
    char* folderPath;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\"); // 독후감상문 폴더에 저자명으로 폴더 생성
    strcat(folderPath, name); // 원래있던 기본 주소와 저자명과 합침.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) 
    {
        printf("감상문 작성 완료.\n");
    }
    else 
    {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("저자명 폴더가 존재합니다. \n");
        }
        else {
            printf("폴더를 만드는 데 실패했습니다. 오류 코드: %lu\n", error);
        }
    }
    free(folderPath);
}

//감상문 파일을 만드는 함수
void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    char* folderPath;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\", folder_name); // 폴더 경로 생성

    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "%s%s.txt", folderPath, input_title); // 파일 경로 생성

    // 폴더가 이미 존재하는지 확인
    DWORD attrib = GetFileAttributesA(folderPath);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) 
    {
        printf("폴더가 이미 존재합니다.\n");
    }
    else 
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

    FILE* filePointer = fopen(filePath, "w"); // "w" 쓰기 모드로 파일 열기

    if (filePointer == NULL) 
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // txt 파일에 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("파일이 성공적으로 생성되었습니다.\n");
    free(folderPath);
    free(filePath);
}

//감상문 파일를 출력 함수
void read_text(const char* folder_name, const char* input_title)
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    FILE* filePointer = fopen(filePath, "r"); // "r" 모드로 파일 열기

    if (filePointer == NULL) 
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일에서 한 줄씩 읽어와 출력하기
    char*buffer;
    buffer = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));// 읽은 내용을 저장할 버퍼
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) 
    {
        printf("%s", buffer);
    }

    fclose(filePointer); // 파일 닫기
    free(filePath);
    free(buffer);
}

//감상문 내용을 수정 함수
void edit_text(const char* folder_name, const char* input_title, const char* input_content) 
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성

    FILE* filePointer = fopen(filePath, "w"); // "w" 쓰기 모드로 파일 열기

    if (filePointer == NULL) 
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 내용 입력
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("파일이 성공적으로 덮어쓰기 되었습니다.\n");
    free(filePath);
}

//감상문 text파일을 삭제 함수
void delete_text(const char* folder_name, const char* input_title) 
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\독후감상문\\%s\\%s.txt", folder_name, input_title); // 파일 경로 생성
    
    char check[4];
    printf("삭제하시겠습니까? (복구할 수 없습니다) \n");
    printf("yes/no ==>>");
    scanf("%3s", check);

    if (strcmp(check, "yes") == 0)
    {
        // 파일 삭제
        if (remove(filePath) == 0) 
        {
            printf("\n 파일이 성공적으로 삭제되었습니다.\n");
        }
        else {
            printf("파일 삭제에 실패했습니다.\n");
        }
    }
    free(filePath);
}

//책 추천해주는 함수
void recommend_book(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("파일 열기 실패");
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
    srand(time(NULL));

    // 랜덤 줄 선택
    int random_line = rand() % lines;

    // 선택된 줄까지 이동
    int current_line = 0;
    char buffer[MAX_CONTENT_LENGTH]; // 문자 배열
    char title[MAX_CONTENT_LENGTH]; // 제목 문자 배열
    char author[MAX_CONTENT_LENGTH]; // 저자 문자 배열
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

    // 선택된 내용 출력
    printf("제목 : %s\n", title);
    printf("저자 : %s\n", author);

    fclose(file);
}

//책 추천 목록 추가 함수
void add_recommend_book(const char* filename, const char* new_data) 
{
    FILE* file = fopen(filename, "a");
    if (file == NULL) 
    {
        perror("파일 열기 실패");
        return;
    }

    // 데이터를 파일에 추가
    fprintf(file, "%s\n", new_data);
    fclose(file);
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
        printf("5. 책 추천\n");
        printf("6. 책 추천 목록 추가 \n");
        printf("0. 종료\n");
        printf("======================================================\n");
        printf("원하는 메뉴를 입력하세요 : ");


        scanf("%d", &set);
        getchar();
        printf("\n======================================================\n");

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
            if (input_folder == NULL) 
            {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder, MAX_TITLE_LENGTH, stdin);
            input_folder[strcspn(input_folder, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요 : ");
            input_title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title == NULL) 
            {
                printf("메모리 할당 실패\n");
                free(input_folder); // 폴더명 메모리 해제
                return 1;
            }
            fgets(input_title, MAX_TITLE_LENGTH, stdin);
            input_title[strcspn(input_title, "\n")] = '\0'; // 개행 문자 제거

            // 내용 입력 받기
            printf("내용을 입력하세요. 입력을 종료하려면 '// '을 입력하세요.\n");
            input_content = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content == NULL) 
            {
                printf("메모리 할당 실패\n");
                free(input_folder); // 폴더명 메모리 해제
                free(input_title);  // 제목 메모리 해제
                return 1;
            }
            input_content[0] = '\0'; // 내용 배열 초기화
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
            if (input_folder_r == NULL) 
            {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_r, MAX_PATH_LENGTH, stdin);
            input_folder_r[strcspn(input_folder_r, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요 : ");
            input_title_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_r == NULL) 
            {
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
            if (input_folder_e == NULL) 
            {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_e, MAX_TITLE_LENGTH, stdin);
            input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요: ");
            input_title_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title_e == NULL) 
            {
                printf("메모리 할당 실패\n");
                free(input_folder_e); // 동적 할당 해제
                return 1;
            }
            fgets(input_title_e, MAX_TITLE_LENGTH, stdin);
            input_title_e[strcspn(input_title_e, "\n")] = '\0'; // 개행 문자 제거

            // 내용 입력 받기
            printf("내용을 입력하세요: ");
            input_content_e = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content_e == NULL) 
            {
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
            if (input_folder_d == NULL) 
            {
                printf("메모리 할당 실패\n");
                return 1;
            }
            fgets(input_folder_d, MAX_PATH_LENGTH, stdin);
            input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // 개행 문자 제거

            // 제목 입력 받기
            printf("제목을 입력하세요: ");
            input_title_d = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_d == NULL) 
            {
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
            break;
        }
        case 5:
        {
            const char* re_filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt"; // 파일의 주소를 직접 지정
            recommend_book(re_filename);
            break;
        }
        case 6:
        {
            const char* add_filename = "C:\\Users\\kimmi\\Desktop\\독후감상문\\도서목록.txt"; // 파일의 주소를 직접 지정

            char add_data[1024]; // 입력 받을 문자열 배열 선언

            // 사용자로부터 제목과 저자를 입력 받음
            printf("제목//저자 형태로 입력하세요: ");
            scanf(" %[^\n]", add_data); // 개행 문자를 제외한 문자열 입력 받기

            // 파일에 내용 추가
            add_recommend_book(add_filename, add_data);

            printf("성공적으로 추가되었습니다.\n");
            break;
        }
        case 0:
        {
            ///////////종료/////////////////
            printf("====================종료 되었습니다.=====================");
            break;
        }
        }
    }
}