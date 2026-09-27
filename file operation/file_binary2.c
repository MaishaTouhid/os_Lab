#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CREATE FILE 
void createFile()
{
    char filename[100];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }

    fclose(fp);

    printf("Binary file created successfully.\n");
}

//WRITE FILE
void writeFile()
{
    char filename[100];
    char text[1000];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "ab");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    getchar();

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    fwrite(text, sizeof(char), strlen(text), fp);

    fclose(fp);

    printf("Data written successfully.\n");
}

// READ FILE 
void readFile()
{
    char filename[100];
    char buffer[1024];
    size_t bytes;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\nFile Content\n");

    while ((bytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0)
    {
        fwrite(buffer, sizeof(char), bytes, stdout);
    }

    printf("\n\n");

    fclose(fp);
}
// COPY FILE
void copyFile()
{
    char source[100], destination[100];
    char buffer[1024];
    size_t bytes;
    FILE *src, *dest;

    printf("Enter source file: ");
    scanf("%s", source);

    printf("Enter destination file: ");
    scanf("%s", destination);

    src = fopen(source, "rb");
    dest = fopen(destination, "wb");

    if (src == NULL || dest == NULL)
    {
        printf("Copy failed!\n");

        if (src != NULL)
            fclose(src);

        if (dest != NULL)
            fclose(dest);

        return;
    }

    while ((bytes = fread(buffer, sizeof(char), sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, sizeof(char), bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
}


// UPDATE FILE
void updateFile()
{
    char filename[100];
    char text[1000];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    getchar();

    printf("Enter new text: ");
    fgets(text, sizeof(text), stdin);

    fwrite(text, sizeof(char), strlen(text), fp);

    fclose(fp);

    printf("File updated successfully.\n");
} 
//MAIN FUNCTION

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("      BINARY FILE MANAGEMENT\n");
        printf("\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Copy File\n");
        printf("5. Update File\n");
        printf("6. Exit\n");
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
            updateFile();
            break;

        case 6:
            printf("Program terminated.\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}