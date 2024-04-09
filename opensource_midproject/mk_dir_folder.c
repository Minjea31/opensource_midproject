#include <windows.h> //�����쿡 ������ ����� ���� �������
#include <stdio.h>
#include <string.h> //�Է��� �ּҿ� �⺻ �ּҸ� ��ġ�� ���� ������� - strcpy, strcat ���


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


int main()
{
    char* input_string = NULL;
    char temp_buffer[100]; // �ӽ� ����
    printf("������� �������� �Է��ϼ��� : ");
    scanf("%s", temp_buffer); // ���ڿ� �Է� �ޱ�

    // ���� �޸� �Ҵ�
    input_string = (char*)malloc(strlen(temp_buffer) + 1);
    if (input_string == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return 1;
    }

    // �Է¹��� ���ڿ� ����
    strcpy(input_string, temp_buffer);

    make_dir_folder(input_string);

    // �޸� ����
    free(input_string);
}