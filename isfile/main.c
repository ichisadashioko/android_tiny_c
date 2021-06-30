#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "no input argument\n");
        return -1;
    }

    char *input_filepath = argv[1];

    struct stat input_file_stats;

    int c_return_value = stat(input_filepath, &input_file_stats);
    if (c_return_value != 0)
    {
        if (errno == EACCES)
        {
            fprintf(stderr, "EACCES - %d - Search permission is denied for one of the directories in the path prefix of %s.\n", EACCES, input_filepath);
        }
        else if (errno == EFAULT)
        {
            fprintf(stderr, "EFAULT - %d - Bad address.\n", EFAULT);
        }
        else if (errno == ENAMETOOLONG)
        {
            fprintf(stderr, "ENAMETOOLONG - %d - %s is too long.\n", ENAMETOOLONG, input_filepath);
        }
        else if (errno == ENOENT)
        {
            fprintf(stderr, "ENOENT - %d - A component of %s does not exist or is a dangling symbolic link.\n", ENOENT, input_filepath);
        }
        else if (errno == ENOMEM)
        {
            fprintf(stderr, "ENOMEM - %d - Out of memory (i.e., kernel memory).\n", ENOMEM);
        }
        else if (errno == ENOTDIR)
        {
            fprintf(stderr, "ENOTDIR - %d - A component of the path prefix of %s is not a directory.\n", ENOTDIR, input_filepath);
        }
        else if (errno == EOVERFLOW)
        {
            fprintf(stderr, "EOVERFLOW - %d - %s refers to a file whose size, inode number, or number of blocks cannot be represented in, respectively, the types off_t, ino_t, or blkcnt_t. This error can occur when, for example, and application compiled on a 32-bit platform without -D_FILE_OFFSET_BITS=64 calls stat() on a file whose size exceeds (1<<31)-1 bytes.\n", EOVERFLOW, input_filepath);
        }
        else
        {
            fprintf(stderr, "%d - stat() failed with unknown errno.\n", errno);
        }

        return -1;
    }

    if (S_ISREG(input_file_stats.st_mode))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    return 0;
}
