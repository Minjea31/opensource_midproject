#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LENGTH 200

void delete_text(const char* folder_name, const char* input_title) {
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����

    // ���� ����
    if (remove(filePath) == 0) {
        printf("������ ���������� �����Ǿ����ϴ�.\n");
    }
    else {
        printf("���� ������ �����߽��ϴ�.\n");
    }
}

int main() {
    char input_folder_d[MAX_PATH_LENGTH]; // ���ڸ��� �Է¹��� �迭
    char input_title_d[MAX_PATH_LENGTH]; // ������ �Է¹��� �迭

    printf("���ڸ��� �Է��ϼ���: ");
    fgets(input_folder_d, MAX_PATH_LENGTH, stdin); // ���ڸ� �Է� �ޱ�
    input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // ���� ���� ����

    printf("������ �Է��ϼ���: ");
    fgets(input_title_d, MAX_PATH_LENGTH, stdin); // ���� �Է� �ޱ�
    input_title_d[strcspn(input_title_d, "\n")] = '\0'; // ���� ���� ����

    // ���� ���� �Լ� ȣ��
    delete_text(input_folder_d, input_title_d);

    return 0;
}
