#include <stdio.h>

int main() {
    FILE* file;
    char filename[] = "C:\\Users\\kimmi\\Desktop\\����\\qwer.txt."; // ���� ��θ� ���� �߰��ϼ���.

    // ���� ���� �õ�
    file = fopen(filename, "w");

    // ������ ���������� ���ȴ��� Ȯ��
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ���� ���� �о����
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); // ȭ�鿡 �� ���ھ� ���
    }

    // ���� �ݱ�
    fclose(file);

    return 0;
}
