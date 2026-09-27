/*
 * File Operations Program - OS Lab
 * -----------------------------------------
 * This program works with ANY file type: .txt, .jpg, .png,
 * .pdf, .mp3, .exe -- any file at all!
 *
 * Reason: The open/read/write system calls operate on raw
 * BYTES, they don't distinguish between text and binary
 * (that's the default behavior on Linux). So Create, Delete,
 * Copy, and Rename already work with any file type.
 *
 * The only function that needed a change is "Read": printing
 * raw binary content (like an image) as text would garble the
 * terminal output. So now it shows a HEX DUMP instead, which
 * is a safe way to view any file type.
 *
 * Compile: gcc file_ops.c -o file_ops
 * Run    : ./file_ops
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 1024   // buffer size (bytes)

/* small helper to read a filename from the user */
void getName(char *name) {
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';   // remove trailing newline
}

/* -------- 1. CREATE -------- */
void createFile() {
    char name[100];
    printf("Enter file name (with extension, e.g. pic.jpg): ");
    getName(name);

    int fd = open(name, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        printf("Could not create the file.\n");
        return;
    }
    close(fd);
    printf("File created successfully.\n");
}

/* -------- 2. DELETE -------- */
void deleteFile() {
    char name[100];
    printf("Enter file name: ");
    getName(name);

    if (unlink(name) == 0)
        printf("File deleted successfully.\n");
    else
        printf("Could not delete the file.\n");
}

/* prints one byte as 8 binary bits, e.g. 65 -> 01000001 */
void printBinary(unsigned char byte) {
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (byte >> bit) & 1);
    }
}

/* -------- 3. READ (HEX or BINARY dump - safe for any file type) -------- */
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

    long limit = (mode == 2) ? 128 : 512;   // binary output is long, so show fewer bytes
    int perLine = (mode == 2) ? 8 : 16;

    while ((n = read(fd, buf, SIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if (offset % perLine == 0)
                printf("\n%06lx: ", offset);   // address column

            if (mode == 2) {
                printBinary(buf[i]);
                printf(" ");
            } else {
                printf("%02x ", buf[i]);       // hex value
            }
            offset++;
        }
        totalBytes += n;
        if (offset >= limit) break;   // stop early for large files
    }
    printf("\n------------------------------------------\n");
    printf("Total bytes read so far: %ld bytes\n", totalBytes);

    close(fd);
}

/* -------- 4. COPY (byte-for-byte, works for any file type) -------- */
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
        write(fd2, buf, n);   // write exactly as many bytes as read
        total += n;
    }

    close(fd1);
    close(fd2);
    printf("File copied successfully. Total bytes copied: %ld\n", total);
}

/* -------- 5. WRITE (append text data, meant for .txt/.log files) -------- */
void writeFile() {
    char name[100], data[SIZE];
    printf("Enter file name: ");
    getName(name);

    printf("Enter text to write: ");
    fgets(data, SIZE, stdin);

    int fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0) {
        printf("Could not open the file.\n");
        return;
    }

    write(fd, data, strlen(data));
    close(fd);
    printf("Data written successfully.\n");
}

/* -------- 6. RENAME (works for any file type) -------- */
void renameFile() {
    char oldName[100], newName[100];
    printf("Enter current file name (with extension): ");
    getName(oldName);
    printf("Enter new file name (with extension): ");
    getName(newName);

    if (rename(oldName, newName) == 0)
        printf("File renamed successfully.\n");
    else
        printf("Could not rename the file.\n");
}

/* -------- MAIN MENU -------- */
int main() {
    int choice;

    while (1) {
        printf("\n===== FILE OPERATIONS (Any File Type) =====\n");
        printf("1. Create\n2. Delete\n3. Read (Hex Dump)\n4. Copy\n5. Write (text)\n6. Rename\n7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();  // clear leftover newline left by scanf

        if (choice == 1) createFile();
        else if (choice == 2) deleteFile();
        else if (choice == 3) readFile();
        else if (choice == 4) copyFile();
        else if (choice == 5) writeFile();
        else if (choice == 6) renameFile();
        else if (choice == 7) break;
        else printf("Invalid choice.\n");
    }

    printf("Program terminated.\n");
    return 0;
}