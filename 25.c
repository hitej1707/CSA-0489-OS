#include <stdio.h>
#include <sys/stat.h>

void printPermissions(const char *filename) {
    struct stat fileStat;

    // Use stat system call to get file information
    if (stat(filename, &fileStat) == 0) {
        // Print owner's permissions
        printf("Owner permissions: ");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf("\n");

        // Print group's permissions
        printf("Group permissions: ");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf("\n");

        // Print others' permissions
        printf("Others permissions: ");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
    } else {
        perror("Error in stat");
    }
}

int main() {
    const char *filename = "txt2.txt"; // Replace with your file name

    // Print file permissions
    printf("File Permissions for %s:\n", filename);
    printPermissions(filename);

    return 0;
}
