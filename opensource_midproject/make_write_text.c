#include <stdio.h>
#include <string.h>

int main() {
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
