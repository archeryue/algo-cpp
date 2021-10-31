#include <ncurses.h>
#include <vector>

using namespace std;

class Node {
    public:
        int x;
        int y;
        Node* next;

        Node(int x, int y) : x(x), y(y), next(nullptr) {}
        ~Node() {}
};

const int D_UP = 0;
const int D_DOWN = 1;
const int D_LEFT = 2;
const int D_RIGHT = 3;

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
            head = new Node(1, len);
            Node* p = head;
            for (int i = 1; i < len; i++) {
                Node* node = new Node(1, len - i);
                p->next = node;
            }
        }

        void walk() {
            Node* p = head;
            while (p->next != nullptr) {
                Node* n = p->next;
                n->x = p->x;
                n->y = p->y;
                p = n;
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

int main() {
    initscr(); cbreak(); noecho();
    endwin();
    return 0;
}
