#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

int make_dir_folder() 
{
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
}

int make_write_text() 
{
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


int read_text()
{
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
}



int main()
{
    make_dir_folder(); //저자를 입력받아서 저자명의 폴더을 만듬.
    make_write_text(); //제목을 입력 받아서 제목명의 .txt파일을 만듦 // 감상문을 입력받아서 내용을 넣을것임.
    read_text(); //제목을 입력하면 .txt파일의 내용을 출력해줌.
}