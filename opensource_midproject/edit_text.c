#include <stdio.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_PATH_LENGTH 200

void edit_text(const char* folder_name, const char* input_title, const char* input_content) {
    char filePath[MAX_PATH_LENGTH];
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\%s\\%s.txt", folder_name, input_title); // ���� ���

    FILE* filePointer = fopen(filePath, "w"); // "w" ���� ���� ���� ����

    if (filePointer == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("������ ���������� ����� �Ǿ����ϴ�.\n");
}

int main() {
    char input_folder_e[MAX_TITLE_LENGTH]; // ���ڸ��� �Է¹��� �迭
    char input_title_e[MAX_TITLE_LENGTH]; // ������ �Է¹��� �迭
    char input_content_e[MAX_CONTENT_LENGTH]; // ������ �Է¹��� �迭

    printf("���ڸ��� �Է��ϼ���: ");
    fgets(input_folder_e, MAX_TITLE_LENGTH, stdin); // ���ڸ� �Է� �ޱ�
    input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // ���� ���� ���Ÿ� ���� �ڵ�

    printf("������ �Է��ϼ���: ");
    fgets(input_title_e, MAX_TITLE_LENGTH, stdin); // ���� �Է� �ޱ�
    input_title_e[strcspn(input_title_e, "\n")] = '\0'; // ���� ���� ���Ÿ� ���� �ڵ�

    printf("������ �Է��ϼ���: ");
    fgets(input_content_e, MAX_CONTENT_LENGTH, stdin); // ���� �Է� �ޱ�

    // ���� ���� �����
    edit_text(input_folder_e, input_title_e, input_content_e);

    return 0;
}