#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//å ��õ���ִ� �Լ�
void recommend_book(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("���� ���� ����");
        return;
    }

    // ���Ͽ��� �� �� ���� ���
    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(file); // ���� �����͸� �ٽ� ������ �������� �̵�

    // ���� �õ� ����
    srand(time(NULL));

    // ���� �� ����
    int random_line = rand() % lines;

    // ���õ� �ٱ��� �̵�
    int current_line = 0;
    char buffer[1024];
    char* title = NULL;
    title = (char*)malloc(1024 * sizeof(char)); // ���� ���� �����Ҵ�
    char* author = NULL;
    author = (char*)malloc(1024 * sizeof(char));// ���� ���� �����Ҵ�
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (current_line == random_line) {
            // �ٿ��� "//"�� �������� ����� ���� �и�
            char* slash_pos = strstr(buffer, "//");
            if (slash_pos != NULL) {
                *slash_pos = '\0'; // "//" ���� ������ ����
                strcpy(title, buffer);
                strcpy(author, slash_pos + 2); // "//" ���� ������ ����
            }
            break;
        }
        current_line++;
    }

    // ���õ� ���� ���
    printf("���� : %s\n", title);
    printf("���� : %s\n", author);

    free(title);
    free(author);

    fclose(file);
}


int main() 
{
    const char* filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt"; // ������ �ּҸ� ���� ����
    recommend_book(filename);
    return 0;
}
