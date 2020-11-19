#include <stdio.h>
#include <stdlib.h>

/* program to read in text files in "%d %d\n" format and write each line out
to a binary file which will then be read as the input file for the main program */

struct cmdls {
 int cmd_no;
 int cmd_arg;
 struct cmdls* next;
};

int main(int argc, char const *argv[]){

    if (argc != 3){//expects name of executable, text file, and output file name
    printf("Wrong number of arguments, expected 2, got %d\n", argc-1);
    return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];

    FILE* in_ptr;
    FILE* out_ptr;

    in_ptr = fopen(input_path, "r");
    out_ptr = fopen(output_path, "wb");

    if (in_ptr == NULL || out_ptr == NULL){
        return 1;
    }
    struct cmdls first_cmd;
    struct cmdls* current = &first_cmd;
    struct cmdls* next;

    char output[2];

    while (fscanf(in_ptr, "%d %d\n", &current->cmd_no, &current->cmd_arg) != -1){
        output[0] = current->cmd_no;
        output[1] = current->cmd_arg;
        fwrite(output, sizeof(char), 2, out_ptr);
        next = calloc(1, sizeof(struct cmdls));
        current->next = next;  
        current = next;
    }

    fclose(in_ptr);
    fclose(out_ptr);

    return 0;
}
