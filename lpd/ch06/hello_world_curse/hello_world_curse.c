#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
    initscr();

    move(5, 15);
    printw("hello world\n");
    refresh();

    sleep(2);

    endwin();
    return 0;
}
