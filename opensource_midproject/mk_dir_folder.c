#include <windows.h> //�����쿡 ������ ����� ���� �������
#include <stdio.h>
#include <string.h> //�Է��� �ּҿ� �⺻ �ּҸ� ��ġ�� ���� ������� - strcpy, strcat ���

int main() {
    char* name = (char*)malloc(100 * sizeof(char)); //�����Ҵ����� ���� ������ �̸��� �Է¹ޱ� ->���⿡ �����̸��� ���� �ɰ�.
    printf("������� ���� �̸��� �Է��Ͻÿ� : ");
    scanf("%s", name);

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

    return 0;
}