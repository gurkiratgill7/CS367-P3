/* This is the only file you will be editing and submit.
 * - Copyright of Starter Code: Profs. Ivan Avramovic, Yutao Zhong, and Hamza Mughal 
 *                              of George Mason University.  All Rights Reserved
 * - Copyright of Student Code: You!  
 * - Restrictions on Student Code: Do not post your code on any public site (eg. Github).
 * -- Use of a PRIVATE Git repository (e.g. GMU's GitLab server) is strongly recommended!
 * -- You may post your code on a PRIVATE repository to give interviewers access to it.
 * -- You are liable for the protection of your code from others.
 * - Date: Mar 2025
 */

/* CS367 Project 3, Spring 2025
 * Fill in your Name, GNumber, and Section Number in the following comment fields
 * Name:
 * GNumber:
 * Section Number: CS367-00_             (Replace the _ with your section number)
 */

#include <sys/wait.h>
#include "hiy.h"
#include "parse.h"
#include "util.h"
#include "logging.h"

/* Constants */
#define DEBUG 1 /* You can set this to 0 to turn off the debug parse information */
#define STOP_SHELL  0
#define RUN_SHELL   1

/*.===============================================.
 *| Uncomment the lines below if you would like to use them:
 *+===============================================*/

/*

static const char *task_path[] = { "./", "/usr/bin/", NULL };
static const char *instructions[] = { "quit", "help", "list", "delete", "start", "startbg", "kill", "suspend", "fg", "bg", "pipe", NULL};

#define NUM_PATHS        ( sizeof(task_path)/sizeof(const char*) - 1 )
#define NUM_INSTRUCTIONS ( sizeof(instructions)/sizeof(const char*) - 1 )

*/

/*-------------------------------------------*/
/*  The entry of your task manager program   */
/*-------------------------------------------*/

int main() {
    char *cmd = NULL;
    int do_run_shell = RUN_SHELL;

    /* Intial Prompt and Welcome */
    log_hiy_intro();
    log_hiy_help();

    /* Shell looping here to accept user command and execute */
    while (do_run_shell == RUN_SHELL) {
        char *argv[MAXARGS+1] = {0};        /* Argument list */
        Instruction inst = {0};           /* Instruction structure: check parse.h */

        /* Print prompt */
        log_hiy_prompt();
        
        /* Get Input - Allocates memory for the cmd copy */
        cmd = get_input(); 
        /* If the input is whitespace/invalid, get new input from the user. */
        if(cmd == NULL) {
          continue;
        }
        
        /* Parse the Command and Populate the Instruction and Arguments */
        initialize_command(&inst, argv);    /* initialize arg lists and instruction */
        parse(cmd, &inst, argv);            /* call provided parse() */

        if (DEBUG) {  /* display parse result, redefine DEBUG to turn it off */
          debug_print_parse(cmd, &inst, argv, "Main, after parse");
        }

        /* After parsing: your code to continue from here */
        /*.===============================================.
         *| - The command has been parsed and you have cmd, inst, and argv filled with data
         *| - Very highly recommended to start calling your own functions after this point.
         *+===============================================*/
            

        /*==BUILT_IN: quit===*/

        if (strcmp(inst.instruct, "quit") == 0){
          do_run_shell = STOP_SHELL;  /*set the main loop to exit when you finish processing it */

          /*.===============================================.
           *| You will need to print a message when quit is entered, based on the instructions
           *| in the project spec. You can do that here; in your functions; or at the end of main.
           *+===============================================*/

        }


        /*.===============================================.
         *| After your code: We cleanup before Looping to the next command.
         *| free_command WILL free the cmd, inst and argv data.
         *| Make sure you've COPIED ANY INFORMATION YOU NEED first.
         *| Hint: You can use the util.c functions for copying this information.
         *+===============================================*/

        free_command(cmd, &inst, argv);
        cmd = NULL;
    }  // end while

    return 0;
}  // end main()

