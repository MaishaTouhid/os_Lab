
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 1024   

void getName(char *name) {
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';  
}

void printBinary(unsigned char byte) {
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (byte >> bit) & 1);
    }
}

void readFile() {
    char name[100];
    unsigned char buf[SIZE];
    int mode;

    printf("Enter file name: ");
    getName(name);

    printf("View as: 1. Hex   2. Binary (0/1)\nChoice: ");
    scanf("%d", &mode);
    getchar();

    int fd = open(name, O_RDONLY);
    if (fd < 0) {
        printf("Could not open the file.\n");
        return;
    }

    int n;
    long totalBytes = 0;
    long offset = 0;

    if (mode == 2)
        printf("\n--- Binary Dump (up to first 128 bytes) ---\n");
    else
        printf("\n--- Hex Dump (up to first 512 bytes) ---\n");

    long limit = (mode == 2) ? 128 : 512;   
    int perLine = (mode == 2) ? 8 : 16;

    while ((n = read(fd, buf, SIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if (offset % perLine == 0)
                printf("\n%06lx: ", offset);   
            if (mode == 2) {
                printBinary(buf[i]);
                printf(" ");
            } else {
                printf("%02x ", buf[i]);      
            }
            offset++;
        }
        totalBytes += n;
        if (offset >= limit) break;   
    }
    printf("\n\n");
    printf("Total bytes read so far: %ld bytes\n", totalBytes);

    close(fd);
}


void copyFile() {
    char src[100], dest[100];
    unsigned char buf[SIZE];
    printf("Enter source file name (with extension): ");
    getName(src);
    printf("Enter destination file name (with extension): ");
    getName(dest);

    int fd1 = open(src, O_RDONLY);
    if (fd1 < 0) {
        printf("Could not open the source file.\n");
        return;
    }

    int fd2 = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd2 < 0) {
        printf("Could not create the destination file.\n");
        close(fd1);
        return;
    }

    int n;
    long total = 0;
    while ((n = read(fd1, buf, SIZE)) > 0) {
        write(fd2, buf, n);   
        total += n;
    }

    close(fd1);
    close(fd2);
    printf("File copied successfully. Total bytes copied: %ld\n", total);
}


int main() {
    int choice;

    while (1) {
        printf("\n===== FILE OPERATIONS (Any File Type) =====\n");
        printf("1. Read (Hex Dump)\n2. Copy\n3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();  
        if (choice == 1) readFile();
        else if (choice == 2) copyFile();
        else if (choice == 3) break;
        else printf("Invalid choice.\n");
    }

    printf("Program terminated.\n");
    return 0;
}