#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int D_UP = 0;
const int D_DOWN = 1;
const int D_LEFT = 2;
const int D_RIGHT = 3;

const int WIDTH = 50;
const int HEIGHT = 20;

struct Food {
    int x;
    int y;
};

class Node {
    public:
        int x;
        int y;
        Node* next;

        Node(int x, int y) : x(x), y(y), next(nullptr) {}
        ~Node() {}
};

class Snake {
    private:
        int len;
        int dirt;
        Node* head;

        void move_head() {
            if (dirt < 2) {
                head->x += dirt == 0 ? -1 : 1;
            } else {
                head->y += dirt == 2 ? -1 : 1;
            }
        }

    public:
        Snake(int len) : len(len), dirt(D_RIGHT) {
            head = new Node(len, 1);
            Node* p = head;
            for (int i = 1; i < len; i++) {
                Node* node = new Node(len - i, i);
                p->next = node;
                p = p->next;
            }
        }

        ~Snake() {
            while (head != nullptr) {
                Node* n = head->next;
                delete head;
                head = n;
            }
        }

        bool hit_body() {
            Node* p = head->next;
            while (p != nullptr) {
                if (head->x == p->x && head->y == p->y) 
                    return true;
            }
            return false;
        }

        bool hit_wall() {
            return head->x > WIDTH || head->x < 1 || head->y > HEIGHT || head->y < 1;
        }

        bool hit_food(Food food) {
            return head->x == food.x && head->y == food.y;
        }

        void walk() {
            Node* p = head;
            Node front = *p;
            while (p->next != nullptr) {
                Node* n = p->next;
                Node tmp = *n;
                n->x = front.x;
                n->y = front.y;
                p = n;
                front = tmp;
            }
            move_head();
        }

        void eat() {
            Node* node = new Node(head->x, head->y);
            node->next = head;
            head = node;
            move_head();
            len++;
        }

        void chg_dirt(int ndirt) {
            dirt = ndirt;
        }

        void clear(WINDOW* win) {
            Node* p = head;
            while (p != nullptr) {
                mvwaddch(win, p->y, p->x, ' ');
                p = p->next;
            }
        }

        void draw(WINDOW* win) {
            Node* p = head;
            while (p != nullptr) {
                mvwaddch(win, p->y, p->x, '+');
                p = p->next;
            }
        }
};

Food rand_food() {
    Food food;
    food.x = rand() % WIDTH + 1;
    food.y = rand() % HEIGHT + 1;
    return food;
}

void draw_food(WINDOW* win, Food food) {
    mvwaddch(win, food.y, food.x, '*');
}

int main() {
    initscr(); cbreak(); noecho();
    WINDOW* win = newwin(HEIGHT+2, WIDTH+2, 5, 5);
    box(win, 0, 0);
    keypad(win, true);
    refresh();
    srand((unsigned)time(0));
    Snake* snake = new Snake(3);
    Food food = rand_food();
    bool alive = true;
    while(alive) {
        snake->clear(win);
        snake->draw(win);
        draw_food(win, food);
        wrefresh(win);
        wtimeout(win, 1);
        int key = wgetch(win);
        switch (key) {
            case KEY_UP:
                snake->chg_dirt(D_UP);
                break;
            case KEY_DOWN:
                snake->chg_dirt(D_DOWN);
                break;
            case KEY_LEFT:
                snake->chg_dirt(D_LEFT);
                break;
            case KEY_RIGHT:
                snake->chg_dirt(D_RIGHT);
                break;
            default:
                break;
        }
        snake->walk();
        if (snake->hit_food(food)) {
            snake->eat();
            food = rand_food();
        }
        if (snake->hit_body() || snake->hit_wall()) {
            alive = false;
        }
    }
    wtimeout(win, -1);
    wgetch(win);
    endwin();
    return 0;
}
