#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if(argc < 1){
        fprintf(stderr, "no input argument\n");
        return -1;
    }

    char* input_filepath = argv[0];

    struct stat input_file_stats;

    int c_return_value = stat(input_filepath, &input_file_stats);
    if ( c_return_value != 0)
    return 0;
}
