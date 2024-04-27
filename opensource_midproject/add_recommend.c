#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void append_to_file(const char* filename, const char* new_data) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    // �����͸� ���Ͽ� �߰�
    fprintf(file, "%s\n", new_data);

    // ���õ� �� ���
    srand(time(NULL));
    int random_line = rand() % 2;
    if (random_line == 0) {
        printf("���� : %s\n", strtok((char*)new_data, "//"));
        printf("���� : %s\n", strtok(NULL, "//"));
    }

    fclose(file);
}

int main() {
    const char* filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt"; // ������ �ּҸ� ���� ����

    char new_data[1024];
    printf("����//���� ���·� �Է��ϼ���: ");
    fgets(new_data, sizeof(new_data), stdin);
    // fgets�� ���� ���ڵ� �����ϱ� ������ ���� ���� ����
    new_data[strcspn(new_data, "\n")] = '\0';

    append_to_file(filename, new_data);

    printf("���������� �߰��Ǿ����ϴ�.\n");

    return 0;
}
