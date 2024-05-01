#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1024
#define MAX_PATH_LENGTH 200

//�ܼ�â ����
void clearScreen()
{
    system("cls"); // �ܼ�â ����
}

//���� ���� ����� �Լ�
void make_dir_folder(const char* name)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

    char* folderPath = NULL;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    strcpy(folderPath, "C:\\Users\\kimmi\\Desktop\\���İ���\\"); // ���İ��� ������ ���ڸ����� ���� ����
    strcat(folderPath, name); // �����ִ� �⺻ �ּҿ� ���ڸ�� ��ħ.

    BOOL result = CreateDirectoryA(folderPath, NULL);

    if (result) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();
        printf("���� �ۼ� �Ϸ�.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
    }
    else 
    {
        DWORD error = GetLastError();

        if (error == ERROR_ALREADY_EXISTS) 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            clearScreen();
            printf("���ڸ� ������ �����մϴ�. \n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            clearScreen();
            printf("������ ����� �� �����߽��ϴ�. ���� �ڵ�: %lu\n", error);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        }
    }

    free(folderPath);
}

//���� ������ ����� �Լ�
void make_write_text(const char* folder_name, const char* input_title, const char* input_content)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

    char* folderPath = NULL;
    folderPath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(folderPath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\", folder_name); // ���� ��� ����

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "%s%s.txt", folderPath, input_title); // ���� ��� ����

    
    DWORD attrib = GetFileAttributesA(folderPath);

    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
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

    FILE* filePointer = fopen(filePath, "r"); // ������ �б� ���� ����

    if (filePointer != NULL)
    {
        // ������ �̹� �����ϴ� ���
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();
        printf("\n\n");
        printf("%s�� ���� ������ �̹� �����մϴ�.\n", input_title);
        printf("\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        fclose(filePointer);
        return;
    }

    // ������ ��������������� �Է�
    filePointer = fopen(filePath, "w");
    if (filePointer == NULL)
    {
        DWORD error = GetLastError();
        printf("������ ������ �� �����ϴ�. ���� �ڵ�: %lu\n", error);
        return;
    }

    // txt ���Ͽ� ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�

    clearScreen();
    printf("\n\n");
    printf("������ ���������� �ۼ��Ǿ����ϴ�.\n");
    printf("\n\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��

    free(folderPath);
    free(filePath);
}

//���� ���ϸ� ��� �Լ�
void read_text(const char* folder_name, const char* input_title)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����

    FILE* filePointer = fopen(filePath, "r"); // "r" ���� ���� ����

    if (filePointer == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();
        printf("\n\n�ش��ϴ� ������ �����ϴ�.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        return;
    }

    printf("==================���� ����=======================\n");

    // ���Ͽ��� �� �پ� �о�� ����ϱ�
    char*buffer = NULL;
    buffer = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));// ���� ������ ������ ����

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) 
    {
        printf("%s", buffer);
    }

    printf("\n======================================================\n");

    fclose(filePointer); // ���� �ݱ�
    free(filePath);
    free(buffer);
}

//���� ������ ���� �Լ�
void edit_text(const char* folder_name, const char* input_title, const char* input_content) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����

    FILE* filePointer = fopen(filePath, "w"); // "w" ���� ���� ���� ����

    if (filePointer == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();

        printf("\n\n�ش��ϴ� ������ �����ϴ�.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        return;
    }

    // ���� �Է�
    fprintf(filePointer, "%s", input_content);

    fclose(filePointer);
    clearScreen();
    printf("===================================================\n");
    printf("���� �� ����\n");
    printf("���ڸ�: %s\n", folder_name);
    printf("����: %s\n", input_title);
    printf("����: \n%s\n", input_content);
    printf("===================================================\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
    printf("\n\n������ ���������� ����� �Ǿ����ϴ�.\n\n\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
    free(filePath);
}

//���� text������ ���� �Լ�
void delete_text(const char* folder_name, const char* input_title) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

    char* filePath = NULL;
    filePath = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
    sprintf(filePath, "C:\\Users\\kimmi\\Desktop\\���İ���\\%s\\%s.txt", folder_name, input_title); // ���� ��� ����
    
    char check[4];
    int valid_input = 0; //�Է°��� �ִ��� Ȯ���ϴ� ����

    while (!valid_input) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        printf("\n=========================================\n");
        printf("�����Ͻðڽ��ϱ�? (������ �� �����ϴ�) \n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        printf("yes/no ==>> ");
        scanf("%3s", check);
        clearScreen();

        if (strcmp(check, "yes") == 0 || strcmp(check, "no") == 0) 
        {
            valid_input = 1; // �Է��� �ִ� ��� �ݺ��� ����
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            printf("\n\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
            
            while (getchar() != '\n'); // �Է� ���۸� �����
        }
    }

    if (strcmp(check, "yes") == 0)
    {
        // ���� ����
        if (remove(filePath) == 0)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            clearScreen();
            printf("\n\n������ ���������� �����Ǿ����ϴ�.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        }
        else 
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            clearScreen();
            printf("\n�ش��ϴ� ������ �����ϴ�.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        }
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();
        printf("\n\n������ ��� �Ǿ����ϴ�.\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
    }
    free(filePath);
}

//å ��õ���ִ� �Լ�
void recommend_book(const char* filename) 
{

    FILE* file = fopen(filename, "r");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�
    if (file == NULL) 
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        clearScreen();
        perror("���� ���� ����");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
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
    srand((unsigned int)time(NULL));

    // ���� �� ����
    int random_line = rand() % lines;

    
    int current_line = 0;
    char buffer[1024];
    char* title = NULL;
    title = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char)); // ���� ���� �迭
    char* author = NULL;
    author = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char)); // ���� ���� �迭

    // ���õ� �ٱ��� �̵� �� // �������� ����� ���ڸ� ������ ���
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

    clearScreen();

    // ���õ� ���� ���
    printf("\n\n���� : %s\n", title);
    printf("���� : %s\n\n", author);

    free(title);
    free(author);

    fclose(file);
}

//å ��õ ��� �߰� �Լ�
void add_recommend_book(const char* filename, const char* new_data) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�
    FILE* file = fopen(filename, "a");
    if (file == NULL) 
    {
        clearScreen();
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        perror("���� ���� ����");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        return;
    }

    // �����͸� ���Ͽ� �߰�
    fprintf(file, "%s\n", new_data);
    fclose(file);
}


int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڻ� ��ȯ �ڵ�

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
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
        printf("���ϴ� �޴��� �Է��ϼ��� : ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��


        scanf("%d", &set);
        getchar();

        switch (set)
        {
        case 1:
        {
            clearScreen();

            char* input_folder = NULL;
            char* input_title = NULL;
            char* input_content = NULL;


            int valid_input = 0;

            while (!valid_input)
            {
                // ���ڸ� �Է� �ޱ�
                printf("���ڸ��� �Է��ϼ���: ");
                input_folder = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));

                if (input_folder == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    return 1;
                }
                fgets(input_folder, MAX_TITLE_LENGTH, stdin);
                input_folder[strcspn(input_folder, "\n")] = '\0'; // ���� ���� ����

                // ���ڸ��� �Էµ��� ���� ���
                if (strlen(input_folder) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("���ڸ��� �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_folder);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ʱ�ȭ �� �ٽ� �˻�
            while (!valid_input)
            {
                // ���� �Է� �ޱ�
                printf("������ �Է��ϼ���: ");
                input_title = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder); // ���ڸ� �޸� ����
                    return 1;
                }
                fgets(input_title, MAX_TITLE_LENGTH, stdin);
                input_title[strcspn(input_title, "\n")] = '\0'; // ���� ���� ����

                // ������ �Էµ��� ���� ���
                if (strlen(input_title) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_title);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ٽ� �ʱ�ȭ�Ͽ� ���� �Է¿� ���� ���� ����

            while (!valid_input)
            {
                
                printf("������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");
                input_content = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

                if (input_content == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder); // ���ڸ� �޸� ����
                    free(input_title);  // ���� �޸� ����
                    return 1;
                }

                input_content[0] = '\0'; // ���� �迭 �ʱ�ȭ
                // ���� �Է� �ޱ�

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

                // ������ �Էµ��� ���� ���
                if (strlen(input_content) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_content);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
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
            clearScreen();
            char* input_folder_r = NULL;
            char* input_title_r = NULL;
            int valid_input = 0;

            // ���ڸ� �Է� �ޱ�
            while (!valid_input)
            {
                printf("���ڸ��� �Է��ϼ���: ");
                input_folder_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));

                if (input_folder_r == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    return 1;
                }
                fgets(input_folder_r, MAX_PATH_LENGTH, stdin);
                input_folder_r[strcspn(input_folder_r, "\n")] = '\0'; // ���� ���� ����

                // ���ڸ��� �Էµ��� ���� ���
                if (strlen(input_folder_r) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("���ڸ��� �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_folder_r);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ٽ� �ʱ�ȭ�Ͽ� ���� �Է¿� ���� ���� ����
            // ���� �Է� �ޱ�
            while (!valid_input)
            {
                printf("������ �Է��ϼ���: ");
                input_title_r = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));
                if (input_title_r == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder_r); // ���� �Ҵ� ����
                    return 1;
                }
                fgets(input_title_r, MAX_PATH_LENGTH, stdin);
                input_title_r[strcspn(input_title_r, "\n")] = '\0'; // ���� ���� ����

                // ������ �Էµ��� ���� ���
                if (strlen(input_title_r) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_title_r);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }
            // ���� �б� �Լ� ȣ��
            read_text(input_folder_r, input_title_r);

            set = -1;
            free(input_folder_r);
            free(input_title_r);
            break;
        }
        case 3:
        {

            clearScreen();
            char* input_folder_e = NULL;
            char* input_title_e = NULL;
            char* input_content_e = NULL;
            int valid_input = 0;

            while (!valid_input)
            {
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

                // ���ڸ��� �Էµ��� ���� ���
                if (strlen(input_folder_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("���ڸ��� �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_folder_e);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ٽ� �ʱ�ȭ�Ͽ� ���� �Է¿� ���� ���� ����
            while (!valid_input)
            {
                // ���� �Է� �ޱ�
                printf("������ �Է��ϼ���: ");
                input_title_e = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title_e == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder_e); // ���ڸ� �޸� ����
                    return 1;
                }
                fgets(input_title_e, MAX_TITLE_LENGTH, stdin);
                input_title_e[strcspn(input_title_e, "\n")] = '\0'; // ���� ���� ����

                // ������ �Էµ��� ���� ���
                if (strlen(input_title_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_title_e);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ٽ� �ʱ�ȭ�Ͽ� ���� �Է¿� ���� ���� ����
            while (!valid_input)
            {
                // ���� �Է� �ޱ�
                printf("������ �Է��ϼ���. �Է��� �����Ϸ��� '// '�� �Է��ϼ���.\n");
                input_content_e = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));
                if (input_content_e == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder_e); // ���ڸ� �޸� ����
                    free(input_title_e);  // ���� �޸� ����
                    return 1;
                }

                input_content_e[0] = '\0'; // ���� �迭 �ʱ�ȭ
                while (1)
                {
                    fgets(input_content_e + strlen(input_content_e), MAX_CONTENT_LENGTH - strlen(input_content_e), stdin); // ����� �Է� �ޱ�
                    // "//" �Է��ϸ� ����
                    if (strncmp(input_content_e + strlen(input_content_e) - 3, "//", 2) == 0)
                    {
                        input_content_e[strlen(input_content_e) - 3] = '\0'; // "//" ����
                        break;
                    }
                }

                // ������ �Էµ��� ���� ���
                if (strlen(input_content_e) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_content_e);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            clearScreen();
            // ����� �Լ��� ����
            edit_text(input_folder_e, input_title_e, input_content_e);

            // �޸� ����
            free(input_folder_e);
            free(input_title_e);
            free(input_content_e);
            break;
        }
        case 4:
        {
            clearScreen();
            char* input_folder_d = NULL;
            char* input_title_d = NULL;

            int valid_input = 0;

            while (!valid_input)
            {
                // ���ڸ� �Է� �ޱ�
                printf("���ڸ��� �Է��ϼ���: ");
                input_folder_d = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_folder_d == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    return 1;
                }
                fgets(input_folder_d, MAX_TITLE_LENGTH, stdin);
                input_folder_d[strcspn(input_folder_d, "\n")] = '\0'; // ���� ���� ����

                // ���ڸ��� �Էµ��� ���� ���
                if (strlen(input_folder_d) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("���ڸ��� �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_folder_d);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }

            valid_input = 0; // �ٽ� �ʱ�ȭ�Ͽ� ���� �Է¿� ���� ���� ����
            while (!valid_input)
            {
                // ���� �Է� �ޱ�
                printf("������ �Է��ϼ���: ");
                input_title_d = (char*)malloc(MAX_TITLE_LENGTH * sizeof(char));
                if (input_title_d == NULL)
                {
                    printf("�޸� �Ҵ� ����\n");
                    free(input_folder_d); // ���ڸ� �޸� ����
                    return 1;
                }
                fgets(input_title_d, MAX_TITLE_LENGTH, stdin);
                input_title_d[strcspn(input_title_d, "\n")] = '\0'; // ���� ���� ����

                // ������ �Էµ��� ���� ���
                if (strlen(input_title_d) == 0)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
                    printf("������ �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
                    free(input_title_d);
                }
                else
                {
                    valid_input = 1; // �Է��� ������ �ݺ��� ����
                }
            }
            clearScreen();
            // ���� ���� �Լ� ȣ��
            delete_text(input_folder_d, input_title_d);

            free(input_folder_d);
            free(input_title_d);
            break;
        }
        case 5:
        {
            clearScreen();
            const char* re_filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt";
            recommend_book(re_filename);
            break;
        }
        case 6:
        {
            clearScreen();
            const char* add_filename = "C:\\Users\\kimmi\\Desktop\\���İ���\\�������.txt"; // ������ �ּҸ� ���� ����

            char* add_data;// �Է� ���� ���ڿ� �迭 ����
            add_data = (char*)malloc(MAX_CONTENT_LENGTH * sizeof(char));

            // ����ڷκ��� ����� ���ڸ� �Է� ����
            printf("����//���� ���·� �Է��ϼ���: ");
            scanf(" %[^\n]", add_data); // ���� ���ڸ� ������ ���ڿ� �Է� �ޱ�

            // ���Ͽ� ���� �߰�
            add_recommend_book(add_filename, add_data);

            clearScreen();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            printf("\n\n���������� �߰��Ǿ����ϴ�.\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
            free(add_data);
            break;
        }
        case 0:
        {
            ///////////����/////////////////
            printf("\n\n\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            printf("====================����Ǿ����ϴ�.====================");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
            break;
        }
        default:
        {
            clearScreen();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // ������ �۾�
            printf("\n======================================================\n");
            printf("menu ������ �������ּ���.\n");
            printf("======================================================\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���ڻ� �⺻��
        }
        }
    }
}