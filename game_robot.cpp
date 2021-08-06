#include <bits/stdc++.h>
typedef enum {EMPTY = 0, MINE = 1 , ENEMY = -1} Cell;

void scanb(Cell b[8][8]) {
    int ms;
    char s[65];
    std::cin >> ms >> s;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            switch (s[i * 8 + j]) {
            case 'E': b[i][j] = EMPTY; break;
            case 'W': b[i][j] = MINE;  break;
            case 'B': b[i][j] = ENEMY; break;
            }
        }
    }
}

int get_flips_line(Cell b[8][8], int y, int x, int dy, int dx) {
    if (b[y][x] != EMPTY) return 0;
    if (dy == 0 && dx == 0) return 0;
    int flips = 0;
    for (int i = y + dy, j = x + dx; i >= 0 && i < 8 && j >= 0 && j < 8; i += dy, j += dx) {
        switch (b[i][j]) {
        case EMPTY: return 0;
        case MINE:  return flips;
        case ENEMY: ++flips; break;
        }
    }
    return 0;

}

int get_flips(Cell b[8][8], int y, int x) {
    int flips = 0;
    for (int dy = -1; dy <= 1; ++dy)
        for (int dx = -1; dx <= 1; ++dx)
            flips += get_flips_line(b, y, x, dy, dx);
    if (flips) ++flips;
    return flips;
}

int do_flips_line(Cell b[8][8], int y, int x, int dy, int dx) {
    int flips = get_flips_line(b, y, x, dy, dx);
    for (int i = 0; i < flips; ++i) {
        y += dy;
        x += dx;
        b[y][x] = MINE;
    }
    return flips;
}

int do_flips(Cell b[8][8], int y, int x) {
    int flips = 0;
    for (int dy = -1; dy <= 1; ++dy)
        for (int dx = -1; dx <= 1; ++dx) {
            flips += do_flips_line(b, y, x, dy, dx);
        }
    if (flips) b[y][x] = MINE;
    return flips;
}

void copyb(Cell dst[8][8], Cell src[8][8]) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            dst[i][j] = src[i][j];
}

void invertb(Cell dst[8][8]) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            switch (dst[i][j]) {
            case EMPTY: break;
            case ENEMY: dst[i][j] = MINE; break;
            case MINE: dst[i][j] = ENEMY; break;
            }
}

int get_moves(Cell b[8][8]) {
    int moves = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (get_flips(b, i, j))
                ++moves;
    return moves;
}

void printb(Cell b[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            switch (b[i][j]) {
            case EMPTY: std::cerr << " "; break;
            case MINE:  std::cerr << "-"; break;
            case ENEMY: std::cerr << "#"; break;
            }
        }
        std::cerr << std::endl;
    }
}
float weights[8][8] = {
    {4, 1, 3, 3, 3, 3, 1, 4},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {3, 1, 2, 2, 2, 2, 1, 3},
    {3, 1, 2, 1, 1, 2, 1, 3},
    {3, 1, 2, 1, 1, 2, 1, 3},
    {3, 1, 2, 2, 2, 2, 1, 3},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {4, 1, 3, 3, 3, 3, 1, 4},
};

float ones[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

int rateb(Cell b[8][8]) {
    int rating = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            //switch(b[i][j]) {
            //case MINE: rating++; break;
            //}
            switch(b[i][j]) {
            case MINE: rating++; break;
            case ENEMY: rating--; break;
            }
    return rating;
}

float rateb_weights(Cell b[8][8], float w[8][8]) {
    float rating = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            //switch(b[i][j]) {
            //case MINE: rating++; break;
            //}
            switch(b[i][j]) {
            case MINE: rating += w[i][j]; break;
            case ENEMY: rating -= w[i][j]; break;
            }
    return rating;
}

std::pair<int, int> minmax(Cell b[8][8], int depth, float w[8][8]) {
    if (depth == 0) {
        return {rateb_weights(b, w), -1};
    }
    depth--;

    float max_rating = -999;
    int max_move = -1;

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (get_flips(b, i, j)) {
                Cell bb[8][8];
                copyb(bb, b);
                do_flips(bb, i, j);
                invertb(bb);
                int cur_rating = -minmax(bb, depth, w).first;
                if (cur_rating > max_rating) {
                    max_rating = cur_rating;
                    max_move = i * 8 + j;
                }
            }

    if (max_move < 0) {
        Cell bb[8][8];
        copyb(bb, b);
        invertb(bb);
        max_rating = -minmax(bb, depth, w).first;
    }

    return {max_rating, max_move};
}

int greedy(Cell b[8][8]) {
    int max_move = -1;
    int max_flips = -999;

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            int flips = get_flips(b, i, j);
            if (flips > 0) {
                if (flips > max_flips) {
                    max_move = i * 8 + j;
                    max_flips = flips;
                }
            }
        }
    return max_move;
}

int play(Cell b[8][8]) {
    printb(b);
    std::pair<int, int> res = minmax(b, 1, weights);
    std::cout << res.first << ' ' << res.second << std::endl;
    return res.second;
}

int weedy(Cell b[8][8], float w[8][8]) {
    int best_move = -1;
    float best_rating = -999999;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (get_flips(b, i, j)) {
                Cell bb[8][8];
                copyb(bb, b);
                do_flips(bb, i, j);
                float rating = rateb_weights(bb, w);
                if (rating > best_rating) {
                    best_rating = rating;
                    best_move = i * 8 + j;
                }
            }

    return best_move;
}

void game() {
    Cell b[8][8];
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            b[i][j] = EMPTY;
    b[3][3] = MINE;
    b[3][4] = ENEMY;
    b[4][3] = ENEMY;
    b[4][4] = MINE;


    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            int move = minmax(b, 6, ones).second;
            if (move >= 0)
                do_flips(b, move / 8, move % 8);
            printb(b);
            std::cout << std::endl;
            invertb(b);
        } else {
            int move = minmax(b, 3, weights).second;
            if (move >= 0)
                do_flips(b, move / 8, move % 8);
            invertb(b);
            printb(b);
            std::cout << std::endl;
        }
    }

    int score = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            switch (b[i][j]) {
            case MINE: score++; break;
            case ENEMY: score--; break;
            }

    std::cout << "Score is " << score << std::endl;
}
int main() {
    //while (1) {
    //    Cell b[8][8];
    //    scanb(b);
    //    int move = play(b);
    //    std::cout << move << std::endl;
    //}
    game();
return 0;
}
/**
5000

EEEEEEEE
EEEEEEEE
EEEEEEEE
EEEBWEEE
EEEWBEEE
EEEEEEEE
EEEEEEEE
EEEEEEEE


**/
