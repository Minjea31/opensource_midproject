#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>



void make_dir_folder(char* name)
{
    char folderPath[MAX_PATH];
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\"); //����ȭ�鿡 �Է��� �̸����� ���� ����
    strcat(folderPath, name); // �����ִ� �⺻ �ּҿ� �Է��� ���� ���� �̸��� ��ħ.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) {
        printf("������ ���������� �����Ǿ����ϴ�.\n");
    }
    else {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("������ �̹� �����մϴ�.\n");
        }
        else {
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
        }
    }

}


int make_write_text() 
{
    FILE* filePointer; // ���� ������ ����
    char fileName[100]; // ���� �̸��� ������ �迭
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // ������ ���� �� ���
    char content[1000]; // �Է� ���� ������ ������ �迭

    printf("���� �̸��� �Է��ϼ���: ");
    scanf("%s", fileName); // ���� �̸� �Է� �ޱ�

    printf("���Ͽ� �Է��� ������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");

    //���� ��� ����
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, fileName);

    // "w" ���� ���� ����
    filePointer = fopen(fullPath, "w");

    // ������ ���������� ���ȴ��� Ȯ��
    if (filePointer == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return -1; // ���� �ڵ� ��ȯ
    }

    // ���� �Է�
    while (1) {
        fgets(content, sizeof(content), stdin); // ����� �Է� �ޱ�
        // "//" �Է��ϸ� ����
        if (strncmp(content, "//", 2) == 0) {
            break;
        }
        fprintf(filePointer, "%s", content); // ���Ͽ� �Է��� ���� ����
    }

    fclose(filePointer);

    printf("������ ���������� �����Ǿ����ϴ�.\n");

    return 0;
}


int read_text()
{
    FILE* filePointer; // ���� ������ ����
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\kim.txt"; // ���� ��θ� ���� �����մϴ�.

    // ���� ����. "r" ���� �б� ���� ������ ���ϴ�.
    filePointer = fopen(filePath, "r");

    // ������ ���������� ���ȴ��� Ȯ��
    if (filePointer == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return -1; // ���� �ڵ� ��ȯ
    }

    // ���Ͽ��� �� �پ� �о�� ����ϱ�
    char buffer[100]; // ���� ������ ������ ����
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        printf("%s", buffer);
    }

    // ���� �ݱ�
    fclose(filePointer);
}



int main()
{
    char* input_folder = NULL;
    char temp_folder[100]; // �ӽ� ����
    printf("������� �������� �Է��ϼ��� : ");
    scanf("%s", temp_folder); // ���ڿ� �Է� �ޱ�

    // ���� �޸� �Ҵ�
    input_folder = (char*)malloc(strlen(temp_folder) + 1);
    if (input_folder == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return 1;
    }

    // �Է¹��� ���ڿ� ����
    strcpy(input_folder, temp_folder);

    make_dir_folder(input_folder);

    // �޸� ����
    free(input_folder);

    ///////////////////////////////////////////////////////////////////////




    //make_write_text(); //������ �Է� �޾Ƽ� ������� .txt������ ���� // ������ �Է¹޾Ƽ� ������ ��������.
    //read_text(); //������ �Է��ϸ� .txt������ ������ �������.
}