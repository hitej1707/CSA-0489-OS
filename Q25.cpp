#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    // Open a directory
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Print file name
        printf("File: %s\n", entry->d_name);

        // Get file information
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Print file size
        printf("\tSize: %ld bytes\n", file_stat.st_size);

        // Open the file
        int fd = open(entry->d_name, O_RDONLY);
        if (fd == -1) {
            perror("open");
            continue;
        }

        // Perform seek operation
        off_t offset = lseek(fd, 0, SEEK_END);
        if (offset == -1) {
            perror("lseek");
            close(fd);
            continue;
        }
        printf("\tSeek offset: %ld\n", offset);

        // Perform fcntl operation
        int flags = fcntl(fd, F_GETFL);
        if (flags == -1) {
            perror("fcntl");
            close(fd);
            continue;
        }
        printf("\tFile flags: %d\n", flags);

        // Close the file
        close(fd);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
