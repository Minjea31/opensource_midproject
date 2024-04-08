#include <stdio.h>

int main() {
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

    return 0; // ���α׷� ����
}
