#include <ncurses.h>
#include <vector>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;

vector<vector<char>> screen(HEIGHT, vector<char>(WIDTH, '*'));

void game_loop() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddch(i, j, screen[i][j]);
        }
    }
    refresh();
    getch();
}

int main() {
    initscr(); cbreak(); noecho(); clear();

    game_loop();

    endwin();
    return 0;
}
