#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

void display()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);

    int y = 0, x = 0;
    int ch;
    int idx;

    int node_indices[MAX_LINES];
    int total_lines = 0;
    idx = inuse_head;
    while (idx != -1 && total_lines < MAX_LINES) {
        node_indices[total_lines++] = idx;
        idx = textbuffer[idx].next;
    }

    while (1) {
        clear();
        for (int row = 0; row < total_lines && row < max_rows - 2; ++row) {
            int node_idx = node_indices[row];
            int len = strlen(textbuffer[node_idx].statement);
            if (row == y) {
                if (x < len) {
                    if (x > 0) mvprintw(row, 0, "%.*s", x, textbuffer[node_idx].statement);
                    attron(A_REVERSE);
                    mvprintw(row, x, "%c", textbuffer[node_idx].statement[x]);
                    attroff(A_REVERSE);
                    if (x < len - 1) mvprintw(row, x + 1, "%s", &textbuffer[node_idx].statement[x + 1]);
                } else {
                    mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
                    attron(A_REVERSE);
                    mvprintw(row, x, " ");
                    attroff(A_REVERSE);
                }
            } else {
                mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
            }
        }
        move(y, x);
        mvprintw(max_rows - 1, 0, "Edit mode: Arrow keys to move, Enter=newline, Backspace=del, Q=quit");
        refresh();

        ch = getch();
        if (ch == 'Q' || ch == 'q') {
            break;
        } else if (ch == KEY_UP) {
            if (y > 0) {
                y--;
                int node_idx = node_indices[y];
                int len = strlen(textbuffer[node_idx].statement);
                if (x > len) x = len;
            }
        } else if (ch == KEY_DOWN) {
            if (y < total_lines - 1) {
                y++;
                int node_idx = node_indices[y];
                int len = strlen(textbuffer[node_idx].statement);
                if (x > len) x = len;
            }
        } else if (ch == KEY_LEFT) {
            if (x > 0) x--;
        } else if (ch == KEY_RIGHT) {
            int node_idx = node_indices[y];
            int len = strlen(textbuffer[node_idx].statement);
            if (x < len) x++;
        } else if (ch == '\n' || ch == '\r') {
            if (total_lines < MAX_LINES) {
                int node_idx = node_indices[y];
                int new_idx = -1;
        
                for (int i = 0; i < MAX_LINES; ++i) {
                    if (textbuffer[i].statement[0] == '\0' && i != inuse_head) {
                        new_idx = i;
                        break;
                    }
                }
                if (new_idx != -1) {
            
                    strcpy(textbuffer[new_idx].statement, textbuffer[node_idx].statement + x);
                    textbuffer[node_idx].statement[x] = '\0';
                   
                    textbuffer[new_idx].next = textbuffer[node_idx].next;
                    textbuffer[new_idx].prev = node_idx;
                    if (textbuffer[node_idx].next != -1)
                        textbuffer[textbuffer[node_idx].next].prev = new_idx;
                    textbuffer[node_idx].next = new_idx;
                
                    for (int i = total_lines; i > y + 1; --i) node_indices[i] = node_indices[i-1];
                    node_indices[y+1] = new_idx;
                    total_lines++;
                    y++;
                    x = 0;
                }
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            int node_idx = node_indices[y];
            if (x > 0) {
                int len = strlen(textbuffer[node_idx].statement);
                memmove(&textbuffer[node_idx].statement[x-1], &textbuffer[node_idx].statement[x], len - x + 1);
                x--;
            } else if (y > 0) {
                int prev_idx = node_indices[y-1];
                int prev_len = strlen(textbuffer[prev_idx].statement);
                int curr_len = strlen(textbuffer[node_idx].statement);
                if (prev_len + curr_len < MAX_LEN - 1) {
                    strcat(textbuffer[prev_idx].statement, textbuffer[node_idx].statement);
                    
                    textbuffer[prev_idx].next = textbuffer[node_idx].next;
                    if (textbuffer[node_idx].next != -1)
                        textbuffer[textbuffer[node_idx].next].prev = prev_idx;
                    textbuffer[node_idx].statement[0] = '\0';
                    
                    for (int i = y; i < total_lines - 1; ++i) node_indices[i] = node_indices[i+1];
                    total_lines--;
                    y--;
                    x = prev_len;
                }
            }
        } else if (ch >= 32 && ch <= 126) {
            int node_idx = node_indices[y];
            int len = strlen(textbuffer[node_idx].statement);
            if (len < MAX_LEN - 1) {
                memmove(&textbuffer[node_idx].statement[x+1], &textbuffer[node_idx].statement[x], len - x + 1);
                textbuffer[node_idx].statement[x] = ch;
                x++;
            }
        }
    }

    endwin();
}