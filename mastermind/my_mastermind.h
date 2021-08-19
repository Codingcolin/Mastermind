#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define MM_SIZE_CODE 4

struct s_option {
    int  nbr_attempt;
    char secret_code[MM_SIZE_CODE];
};

void generate_random_code(struct s_option* option);
void init_option(struct s_option* option);
void parse_option(struct s_option* option, int ac, char **av);
char compare_code(char* secret_code, char* user_code);
void print_option(struct s_option* option);
void play_game(struct s_option* option);
int is_string_digit(char* user_code);
int is_number_len(char* user_code);