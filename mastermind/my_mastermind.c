#include "my_mastermind.h"



//Generate a random code
void generate_random_code(struct s_option* option) {

    int lower = 0, upper = 7, count = 4;
    char secret_code;
    
    srand(time(0));

    printf("Generate random code\n");
    for (int i = 0; i < count; i++) {
        secret_code = '0' + (rand() % (upper - lower + 1)) + lower;
        option->secret_code[i] = secret_code;
    }
}

//Initalize the struct by giving vairbles values
void init_option(struct s_option* option) {
    option->nbr_attempt = 10;
}
//Read over command line use argc and argv
void parse_option(struct s_option* option, int ac, char **av) {
    init_option(option);
    //Start at index 1 to skip over filename
    int index = 1;
    //parse over command line to check for c and t flags
    while (index < ac) {
          if (strcmp(av[index], "-c") == 0 && av[index + 1] != NULL && strlen(av[index + 1]) == 4)
        {
            strncpy(option->secret_code, av[index + 1], MM_SIZE_CODE);

        } else if (strcmp(av[index], "-t") == 0 && av[index + 1] != NULL)
        {
            option->nbr_attempt = atoi(av[index + 1]);
        } else if(strcmp(av[index], "-c") == 0 && av[index + 1] == NULL)
        {
            
            generate_random_code(option);
        } else if(strcmp(av[index], "-c") == 0 && strlen(av[index + 1]) != 4)
        {
            printf("This is an invalid code\n");
            exit(0);
        }
        index += 1;
    }
}
//Compare secret code to user entries
char compare_code(char* secret_code, char* user_code) {


    int index = 0;
    int count = 0;

    
    if (strlen(user_code) > MM_SIZE_CODE) {
           printf("Input too long, max 4 digits\n");
           return 0;
    }
    if (strlen(user_code) < MM_SIZE_CODE) {
           printf("Input too sort, need 4 digits\n");
           return 0;
    }
 

    //Check for well placed pieces in code comparisons
    while(index < MM_SIZE_CODE) {
        if(secret_code[index] == user_code[index]) {
            count++;
             if (strncmp(secret_code, user_code, MM_SIZE_CODE) == 0)
            {
                printf("It is a match\n");
                exit(0);
            }
            
        }
        index++;
    }
    printf("Well placed pieces %d\n", count);


    int found = 0;
    int k = 0;
    int l = 0;
    //Check for misplaced pieces in code comparisons
    for(k = 0; k < MM_SIZE_CODE; k++) {
        for(l = 0; l < MM_SIZE_CODE; l++){
            if((secret_code[k] == user_code[l]) && (k != l)) {
                found++;
            } 
        }
    }
        printf("Misplaced pieces: %d\n", found);

        if (strlen(user_code) != MM_SIZE_CODE) { 
            printf("You need 4 digits\n"); 
        } else if(isalpha(*user_code)) {
            printf("This is not a digit!\n"); 
        }
        return 0;
}
    
//Show number of attempts
void print_option(struct s_option* option) {
    printf("\n<Print Option>\n");
    printf("Number attempt %d\n", option->nbr_attempt);
    printf("This is the secret code %c%c%c%c\n", option->secret_code[0],option->secret_code[1],option->secret_code[2],option->secret_code[3]);
    printf("\n");
    
}

//Start game
void play_game(struct s_option* option) {
    //Add +1 to size to account for Null terminator("\0")
    char user_code[256 + 1];
    int temp = 0;
    //Current attempts start at 0
    int current_nbr_attempt = 0;
    //Keeping count of current attempts vs total number of allowed
    while (current_nbr_attempt < option->nbr_attempt) {
        printf("Enter your code:\n");
        //Use read to get user code
        temp = read(STDIN_FILENO, &user_code[0], 256);
        user_code[temp - 1] = '\0';
        //Compare secret code against user code to see if they match
        if (compare_code(option->secret_code, &user_code[0]) == true) {
            break;
        }
        //Current attempt counter increases by 1 with each 
        //attempt until it reaches the max allowed
        current_nbr_attempt += 1;
        printf("Number attempt %d\n", current_nbr_attempt);
    }
}

int main(int ac, char **av) {
    //Call struct
    struct s_option option;
    //Call other functions with parameters
    parse_option(&option, ac, av);
    print_option(&option);
    play_game(&option);
    return EXIT_SUCCESS;
}
