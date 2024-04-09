#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000


void make_dir_folder(const char* name)
{
    char folderPath[MAX_PATH];
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\"); // ����ȭ�鿡 �Է��� �̸����� ���� ����
    strcat(folderPath, name); // �����ִ� �⺻ �ּҿ� �Է��� ���� ���� �̸��� ��ħ.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) {
        printf("������ ���������� �����Ǿ����ϴ�.\n");
    }
    else {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("�̹� ���� ������ �����ϱ⶧���� �� �ȿ� ��������ϴ�. \n");
        }
        else {
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
        }
    }
}

void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    char folderPath[MAX_PATH];
    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\%s\\", folder_name); // ���� ��� ����

    char filePath[MAX_PATH];
    sprintf(filePath, "%s%s.txt", folderPath, input_title); // ���� ��� ����

    // ������ �̹� �����ϴ��� Ȯ��
    DWORD attrib = GetFileAttributesA(folderPath);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("������ �̹� �����մϴ�.\n");
    }
    else {
        // ���� ����
        BOOL result = CreateDirectoryA(folderPath, NULL);
        if (!result) {
            DWORD error = GetLastError();
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
            return;
        }
    }

    FILE* filePointer = fopen(filePath, "w"); // "w" ���� ���� ���� ����

    if (filePointer == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("������ ���������� �����Ǿ����ϴ�.\n");
}

int main()
{
    ///////////////////////���� ����///////////////////////////////////////
    char input_folder[MAX_TITLE_LENGTH]; // �������� �Է¹��� �迭
    printf("������� �������� �Է��ϼ��� : ");
    fgets(input_folder, MAX_TITLE_LENGTH, stdin); // ������ �Է� �ޱ�
    input_folder[strcspn(input_folder, "\n")] = '\0'; // fgets�� �Է¹��� ���ڿ��� ���� ���� ����

    ///////////////////////////////////////////////////////////////////////

    ///////////////////////���� �Է�///////////////////////////////////////
    char input_title[MAX_TITLE_LENGTH]; // ������ �Է¹��� �迭
    printf("������ �Է��ϼ��� : ");
    fgets(input_title, MAX_TITLE_LENGTH, stdin); // ���� �Է� �ޱ�
    input_title[strcspn(input_title, "\n")] = '\0'; // fgets�� �Է¹��� ���ڿ��� ���� ���� ����

    ///////////////////////���� �Է�///////////////////////////////////////
    char input_content[MAX_CONTENT_LENGTH]; // ������ �Է¹��� �迭

    printf("������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");
    input_content[0] = '\0'; // ���� �迭 �ʱ�ȭ

    while (1) {
        fgets(input_content + strlen(input_content), MAX_CONTENT_LENGTH - strlen(input_content), stdin); // ����� �Է� �ޱ�
        // "//" �Է��ϸ� ����
        if (strncmp(input_content + strlen(input_content) - 3, "//", 2) == 0)
        {
            break;
        }
    }

    // �Էµ� ����� ������ �Լ��� ����
    make_write_text(input_folder, input_title, input_content);

    return 0;
}

//read_text(); //������ �Է��ϸ� .txt������ ������ �������.