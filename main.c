#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse232editor.h"

struct node textbuffer[MAX_LINES];
int free_head = 0;
int inuse_head = -1;

void initialize_buffer() {
    for (int i = 0; i < MAX_LINES; i++) {
        textbuffer[i].prev = -1;
        textbuffer[i].next = i + 1;
        strcpy(textbuffer[i].statement, "");
    }
    textbuffer[MAX_LINES - 1].next = -1;
    inuse_head = -1;
    free_head = 0;
}

void print_help() {
    printf("\nAvailable commands:\n");
    printf("  E <filename>    - Edit file\n");
    printf("  I <line> <text> - Insert text at line\n");
    printf("  D <line>        - Delete line\n");
    printf("  U              - Undo last command\n");
    printf("  R              - Redo last command\n");
    printf("  P              - Display text\n");
    printf("  S <filename>    - Save to file\n");
    printf("  H              - Show this help\n");
    printf("  Q              - Quit\n\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./cse232editor filename\n");
        return 1;
    }

    initialize_buffer();
    edit(argv[1]);

    printf("Editor started. Type 'H' for help.\n");

    char command[256];
    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) break;

        
        command[strcspn(command, "\n")] = 0;

        switch (command[0]) {
            case 'Q':
            case 'q':
                return 0;

            case 'H':
            case 'h':
                print_help();
                break;

            case 'I':
            case 'i': {
                int line;
                char text[MAX_LEN];
                if (sscanf(command + 1, "%d %[^\n]", &line, text) == 2) {
                    insert_line(line, text);
                } else {
                    printf("Usage: I <line> <text>\n");
                }
                break;
            }

            case 'E':
            case 'e': {
                char filename[256];
                if (sscanf(command + 1, "%s", filename) == 1) {
                    edit(filename);
                } else {
                    printf("Usage: E <filename>\n");
                }
                break;
            }

            case 'D':
            case 'd': {
                int line;
                if (sscanf(command + 1, "%d", &line) == 1) {
                    delete(line);
                } else {
                    printf("Usage: D <line>\n");
                }
                break;
            }


            case 'U':
            case 'u':
                printf("Undo command is not implemented yet.\n");
                break;

            case 'R':
            case 'r':
                printf("Redo command is not implemented yet.\n");
                break;

            case 'P':
            case 'p':
                display();
                

                break;

            case 'S':
            case 's':
                {
                    char filename[256];
                    if (sscanf(command + 1, "%s", filename) == 1) {
                        save(filename);
                    } else {
                        printf("Usage: S <filename>\n");
                    }
                    
                }
                break;

            default:
                printf("Unknown command. Type 'H' for help.\n");
        }
    }

    return 0;
}