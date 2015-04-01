#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

int main()
{
    const char witch_one[] = "First witch: ";
    const char witch_two[] = "Second witch: ";

    initscr();

    move(5, 15);
    attron(A_BOLD);
    printw("Macbeth");
    attroff(A_BOLD);
    refresh();
    sleep(1);

    move(8, 15);
    attron(A_STANDOUT);
    printw("Thunder and lightning");
    attroff(A_STANDOUT);
    refresh();
    sleep(1);

    move(10, 10);
    printw("when shall we three meet again");
    move(13, 10);
    printw("in thunder, or in rain ?");

    move(17, 10);
    printw("when the hurlyburly'done,");
    move(20, 10);
    printw("when the battle's lost or win");
    refresh();
    sleep(1);

    move(10, 10);
    attron(A_DIM);
    char *scan_ptr = (char *)(witch_one + strlen(witch_one) - 1);
    while (scan_ptr >= witch_one)
    {
        move(10, 10);
        insch(*scan_ptr);
        scan_ptr--;

        refresh();
        sleep(1);
    }

    move(17, 10);
    scan_ptr = (char *)(witch_two + strlen(witch_two) - 1);
    while(scan_ptr >= witch_two)
    {
        move(17, 10);
        insch(*scan_ptr);
        scan_ptr--;

        refresh();
        sleep(1);
    }
    attroff(A_DIM);
    refresh();
    sleep(3);

    move(LINES - 1, COLS - 1);
    refresh();
    sleep(1);

    endwin();
    return 0;
}
