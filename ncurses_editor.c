#include <curses.h>
#include <stdlib.h>

#define MAX_LINES 1000
#define MAX_COLS  256

char buffer[MAX_LINES][MAX_COLS];
int line_lengths[MAX_LINES] = {0};

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int x = 0, y = 0;
    int ch;

    while (1) {
        clear();
        // Display buffer
        for (int i = 0; i < MAX_LINES; ++i) {
            if (line_lengths[i] > 0) {
                mvprintw(i, 0, "%.*s", line_lengths[i], buffer[i]);
            }
        }
        move(y, x);
        refresh();

        ch = getch();
        if (ch == 'Q' || ch == 'q') {
            break;
        } else if (ch == KEY_UP) {
            if (y > 0) y--;
            if (x > line_lengths[y]) x = line_lengths[y];
        } else if (ch == KEY_DOWN) {
            if (y < MAX_LINES - 1) y++;
            if (x > line_lengths[y]) x = line_lengths[y];
        } else if (ch == KEY_LEFT) {
            if (x > 0) x--;
        } else if (ch == KEY_RIGHT) {
            if (x < line_lengths[y]) x++;
        } else if (ch == '\n' || ch == '\r') { // Enter
            if (y < MAX_LINES - 1) {
                y++;
                x = 0;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (x > 0) {
                for (int i = x - 1; i < line_lengths[y] - 1; ++i) {
                    buffer[y][i] = buffer[y][i + 1];
                }
                line_lengths[y]--;
                x--;
            }
        } else if (ch >= 32 && ch <= 126) { // Printable characters
            if (line_lengths[y] < MAX_COLS - 1) {
                for (int i = line_lengths[y]; i > x; --i) {
                    buffer[y][i] = buffer[y][i - 1];
                }
                buffer[y][x] = ch;
                line_lengths[y]++;
                x++;
            }
        }
    }

    endwin();
    return 0;
} 