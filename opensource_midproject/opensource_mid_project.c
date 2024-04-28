#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1024
#define MAX_PATH_LENGTH 200


//���� ���� ����� �Լ�
void make_dir_folder(const char* name)
{
    char* folderPath;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\���İ���\\"); // ���İ��� ������ ���ڸ����� ���� ����
    strcat(folderPath, name); // �����ִ� �⺻ �ּҿ� ���ڸ�� ��ħ.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) 
    {
        printf("���� �ۼ� �Ϸ�.\n");
    }
    else 
    {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            printf("���ڸ� ������ �����մϴ�. \n");
        }
        else {
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
        }
    }
    free(folderPath);
}

//���� ������ ����� �Լ�
void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    char* folderPath;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\", folder_name); // ���� ��� ����

    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "%s%s.txt", folderPath, input_title); // ���� ��� ����

    // ������ �̹� �����ϴ��� Ȯ��
    DWORD attrib = GetFileAttributesA(folderPath);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) 
    {
        printf("������ �̹� �����մϴ�.\n");
    }
    else 
    {
        // ���� ����
        BOOL result = CreateDirectoryA(folderPath, NULL);
        if (!result) 
        {
            DWORD error = GetLastError();
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
            return;
        }
    }

    FILE* filePointer = fopen(filePath, "w"); // "w" ���� ���� ���� ����

    if (filePointer == NULL) 
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // txt ���Ͽ� ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("������ ���������� �����Ǿ����ϴ�.\n");
    free(folderPath);
    free(filePath);
}

//���� ���ϸ� ��� �Լ�
void read_text(const char* folder_name, const char* input_title)
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����

    FILE* filePointer = fopen(filePath, "r"); // "r" ���� ���� ����

    if (filePointer == NULL) 
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���Ͽ��� �� �پ� �о�� ����ϱ�
    char*buffer;
    buffer = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));// ���� ������ ������ ����
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) 
    {
        printf("%s", buffer);
    }

    fclose(filePointer); // ���� �ݱ�
    free(filePath);
    free(buffer);
}

//���� ������ ���� �Լ�
void edit_text(const char* folder_name, const char* input_title, const char* input_content) 
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����

    FILE* filePointer = fopen(filePath, "w"); // "w" ���� ���� ���� ����

    if (filePointer == NULL) 
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);

    printf("������ ���������� ����� �Ǿ����ϴ�.\n");
    free(filePath);
}

//���� text������ ���� �Լ�
void delete_text(const char* folder_name, const char* input_title) 
{
    char* filePath;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����
    
    char check[4];
    printf("�����Ͻðڽ��ϱ�? (������ �� �����ϴ�) \n");
    printf("yes/no ==>>");
    scanf("%3s", check);

    if (strcmp(check, "yes") == 0)
    {
        // ���� ����
        if (remove(filePath) == 0) 
        {
            printf("\n ������ ���������� �����Ǿ����ϴ�.\n");
        }
        else {
            printf("���� ������ �����߽��ϴ�.\n");
        }
    }
    free(filePath);
}

//å ��õ���ִ� �Լ�
void recommend_book(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("���� ���� ����");
        return;
    }

    // ���Ͽ��� �� �� ���� ���
    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch == '\n') 
        {
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
    char buffer[MAX_CONTENT_LENGTH]; // ���� �迭
    char title[MAX_CONTENT_LENGTH]; // ���� ���� �迭
    char author[MAX_CONTENT_LENGTH]; // ���� ���� �迭
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        if (current_line == random_line) 
        {
            // �ٿ��� "//"�� �������� ����� ���� �и�
            char* slash_pos = strstr(buffer, "//");
            if (slash_pos != NULL) 
            {
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

    fclose(file);
}

//å ��õ ��� �߰� �Լ�
void add_recommend_book(const char* filename, const char* new_data) 
{
    FILE* file = fopen(filename, "a");
    if (file == NULL) 
    {
        perror("���� ���� ����");
        return;
    }

    // �����͸� ���Ͽ� �߰�
    fprintf(file, "%s\n", new_data);
    fclose(file);
}


int main()
{
    int set = -1;

    while (set != 0)
    {
        printf("======================================================\n");
        printf("1. ���� �ۼ�\n");
        printf("2. ���� ���\n");
        printf("3. ���� ����(���Է�)\n");
        printf("4. ���� ����\n");
        printf("5. å ��õ\n");
        printf("6. å ��õ ��� �߰� \n");
        printf("0. ����\n");
        printf("======================================================\n");
        printf("���ϴ� �޴��� �Է��ϼ��� : ");


        scanf("%d", &set);
        getchar();
        printf("\n======================================================\n");

        switch (set)
        {
        case 1:
        {
            char* input_folder = NULL;
            char* input_title = NULL;
            char* input_content = NULL;

            // ������ �Է� �ޱ�
            printf("���ڸ��� �Է��ϼ��� : ");
            input_folder = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_folder == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                return 1;
            }
            fgets(input_folder, MAX_TITLE_LENGTH, stdin);
            input_folder[strcspn(input_folder, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ��� : ");
            input_title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder); // ������ �޸� ����
                return 1;
            }
            fgets(input_title, MAX_TITLE_LENGTH, stdin);
            input_title[strcspn(input_title, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");
            input_content = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder); // ������ �޸� ����
                free(input_title);  // ���� �޸� ����
                return 1;
            }
            input_content[0] = '\0'; // ���� �迭 �ʱ�ȭ
            while (1) 
            {
                fgets(input_content + strlen(input_content), MAX_CONTENT_LENGTH - strlen(input_content), stdin); // ����� �Է� �ޱ�
                // "//" �Է��ϸ� ����
                if (strncmp(input_content + strlen(input_content) - 3, "//", 2) == 0) 
                {
                    input_content[strlen(input_content) - 3] = '\0'; // "//" ����
                    break;
                }
            }

            make_write_text(input_folder, input_title, input_content);
            set = -1;
            //�޸� ����
            free(input_folder);
            free(input_title);
            free(input_content);
            break;
        }
        case 2:
        {
            char* input_folder_r = NULL;
            char* input_title_r = NULL;

            // ���ڸ� �Է� �ޱ�
            printf("���ڸ��� �Է��ϼ��� : ");
            input_folder_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_folder_r == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                return 1;
            }
            fgets(input_folder_r, MAX_PATH_LENGTH, stdin);
            input_folder_r[strcspn(input_folder_r, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ��� : ");
            input_title_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_r == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder_r); // ���� �Ҵ� ����
                return 1;
            }
            fgets(input_title_r, MAX_PATH_LENGTH, stdin);
            input_title_r[strcspn(input_title_r, "\n")] = '\0';

            // ���� �б� �Լ� ȣ��
            read_text(input_folder_r, input_title_r);

            set = -1;
            free(input_folder_r);
            free(input_title_r);
            break;
        }
        case 3:
        {
            char* input_folder_e = NULL;
            char* input_title_e = NULL;
            char* input_content_e = NULL;

            // ���ڸ� �Է� �ޱ�
            printf("���ڸ��� �Է��ϼ���: ");
            input_folder_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_folder_e == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                return 1;
            }
            fgets(input_folder_e, MAX_TITLE_LENGTH, stdin);
            input_folder_e[strcspn(input_folder_e, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ���: ");
            input_title_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
            if (input_title_e == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder_e); // ���� �Ҵ� ����
                return 1;
            }
            fgets(input_title_e, MAX_TITLE_LENGTH, stdin);
            input_title_e[strcspn(input_title_e, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ���: ");
            input_content_e = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
            if (input_content_e == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder_e); // ���� �Ҵ� ����
                free(input_title_e); // ���� �Ҵ� ����
                return 1;
            }
            fgets(input_content_e, MAX_CONTENT_LENGTH, stdin);

            // ����� �Լ��� ����
            edit_text(input_folder_e, input_title_e, input_content_e);

            set = -1;
            //�޸� ����
            free(input_folder_e);
            free(input_title_e);
            free(input_content_e);
            break;
        }
        case 4:
        {
            char* input_folder_d = NULL;
            char* input_title_d = NULL;

            // ���ڸ� �Է� �ޱ�
            printf("���ڸ��� �Է��ϼ���: ");
            input_folder_d = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_folder_d == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                return 1;
            }
            fgets(input_folder_d, MAX_PATH_LENGTH, stdin);
            input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // ���� ���� ����

            // ���� �Է� �ޱ�
            printf("������ �Է��ϼ���: ");
            input_title_d = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
            if (input_title_d == NULL) 
            {
                printf("�޸� �Ҵ� ����\n");
                free(input_folder_d); // ���� �Ҵ� ����
                return 1;
            }
            fgets(input_title_d, MAX_PATH_LENGTH, stdin);
            input_title_d[strcspn(input_title_d, "\n")] = '\0';

            // ���� ���� �Լ� ȣ��
            delete_text(input_folder_d, input_title_d);
            free(input_folder_d);
            free(input_title_d);
            break;
        }
        case 5:
        {
            const char* re_filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt"; // ������ �ּҸ� ���� ����
            recommend_book(re_filename);
            break;
        }
        case 6:
        {
            const char* add_filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt"; // ������ �ּҸ� ���� ����

            char add_data[1024]; // �Է� ���� ���ڿ� �迭 ����

            // ����ڷκ��� ����� ���ڸ� �Է� ����
            printf("����//���� ���·� �Է��ϼ���: ");
            scanf(" %[^\n]", add_data); // ���� ���ڸ� ������ ���ڿ� �Է� �ޱ�

            // ���Ͽ� ���� �߰�
            add_recommend_book(add_filename, add_data);

            printf("���������� �߰��Ǿ����ϴ�.\n");
            break;
        }
        case 0:
        {
            ///////////����/////////////////
            printf("====================���� �Ǿ����ϴ�.=====================");
            break;
        }
        }
    }
}