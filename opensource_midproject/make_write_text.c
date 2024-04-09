#include <stdio.h>
#include <string.h>

int make_write_text(char* input_title) {
    FILE* filePointer; // ���� ������ ����
    char filePath[] = "C:\\Users\\kimmi\\Desktop\\"; // ������ ���� �� ���
    char content[1000]; // �Է� ���� ������ ������ �迭

    printf("���Ͽ� �Է��� ������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");

    //���� ��� ����
    char fullPath[200];
    sprintf(fullPath, "%s%s.txt", filePath, input_title);

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

int main()
{
    char* input_title = NULL;
    char temp_title[100]; // �ӽ� ����
    printf("������ �Է��ϼ��� : ");
    scanf("%s", temp_title); // ���ڿ� �Է� �ޱ�

    // ���� �޸� �Ҵ�
    input_title = (char*)malloc(strlen(temp_title) + 1);
    if (input_title == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return 1;
    }

    // �Է¹��� ���ڿ� ����
    strcpy(input_title, temp_title);

    make_write_text(input_title);

    // �޸� ����
    free(input_title);
}