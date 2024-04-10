#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000



int make_write_text(char* input_title, char* input_content) {
    FILE* filePointer; // ���� ������ ����
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // ������ ���� �� ���

    //���� ��� ����
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, input_title);

    // "w" ���� ���� ����
    filePointer = fopen(fullPath, "w");

    // ������ ���������� ���ȴ��� Ȯ��
    if (filePointer == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return -1; // ���� �ڵ� ��ȯ
    }

    // ���� �Է�
    fprintf(filePointer, "%s", input_content); // ���Ͽ� �Է��� ���� ����

    fclose(filePointer);

    printf("������ ���������� �����Ǿ����ϴ�.\n");

    return 0;
}

int main()
{
    char input_title[MAX_TITLE_LENGTH]; // ������ �Է¹��� �迭
    char input_content[MAX_CONTENT_LENGTH]; // ������ �Է¹��� �迭


    printf("������ �Է��ϼ��� : ");
    fgets(input_title, MAX_TITLE_LENGTH, stdin); // ���� �Է� �ޱ�
    input_title[strcspn(input_title, "\n")] = '\0'; // ���๮�� ����

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
    make_write_text(input_title, input_content);

    return 0;
}