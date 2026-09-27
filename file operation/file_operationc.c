#include <stdio.h>
#include <stdlib.h>


// 1. Create File Only
void createFile()
{
    char filename[100];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }

    fclose(fp);

    printf("File created successfully.\n");
}
void writeFile()
{
    char filename[100];
    char ch;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "a");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    getchar(); // Remove newline from input buffer

    printf("Enter text: ");

    while ((ch = getchar()) != '\n')
    {
        fputc(ch, fp);
    }

    fclose(fp);

    printf("Data written successfully.\n");
}

void readFile()
{
    char filename[100];
    char ch;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\nFile Content \n");

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    printf("\n\n");

    fclose(fp);
}


void copyFile()
{
    char source[100], destination[100];
    char ch;
    FILE *src, *dest;

    printf("Enter source file: ");
    scanf("%s", source);

    printf("Enter destination file: ");
    scanf("%s", destination);

    src = fopen(source, "r");
    dest = fopen(destination, "w");

    if (src == NULL || dest == NULL)
    {
        printf("Copy failed!\n");

        if (src != NULL)
            fclose(src);

        if (dest != NULL)
            fclose(dest);

        return;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
}

void moveFile()
{
    char source[100], destination[100];

    printf("Enter source file: ");
    scanf("%s", source);

    printf("Enter destination file: ");
    scanf("%s", destination);

    if (rename(source, destination) == 0)
        printf("File moved successfully.\n");
    else
        printf("Move failed!\n");
}
void renameFile()
{
    char oldname[100], newname[100];

    printf("Enter current file name: ");
    scanf("%s", oldname);

    printf("Enter new file name: ");
    scanf("%s", newname);

    if (rename(oldname, newname) == 0)
        printf("File renamed successfully.\n");
    else
        printf("Rename failed!\n");
}


void deleteFile()
{
    char filename[100];

    printf("Enter file name: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        printf("Delete failed!\n");
}
void updateFile()
{
    char filename[100];
    char ch;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    getchar();   // Remove newline from input buffer

    printf("Enter new text: ");

    while ((ch = getchar()) != '\n')
    {
        fputc(ch, fp);
    }

    fclose(fp);

    printf("File updated successfully.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf(" FILE MANAGEMENT SYSTEM\n");
        printf("\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Copy File\n");
        printf("5. Rename File\n");
        printf("6. Delete File\n");
        printf("7. Move File\n");
        printf("8. Update File\n");
        printf("9. Exit\n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createFile();
            break;

        case 2:
            writeFile();
            break;

        case 3:
            readFile();
            break;

        case 4:
            copyFile();
            break;

        case 5:
            renameFile();
            break;

        case 6:
            deleteFile();
            break;

        case 7:
            moveFile();
            break;

        case 8:
            updateFile();
            break;

        case 9:
            printf("Program terminated.\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}