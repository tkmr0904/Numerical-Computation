#include <ncurses.h>
#include <unistd.h>

/* --------------------------------------------------------------
  viewheart -- 座標を指定してハートマークを描く
   -------------------------------------------------------------- */
void viewheart(int x, int y)
{
    int i;
    char heart[8][32 + 1] = {
        " ****      ****",
        "******    ******",
        "*******  *******",
        " **************",
        "   **********",
        "    ********",
        "      ****",
        "       **"};

    for (i = 0; i < 8; i++)
    {
        mvprintw(y + i, x, heart[i]);
    }
}

/* --------------------------------------------------------------
  clrheart -- 座標を指定してハートマークを消す
   -------------------------------------------------------------- */
void clrheart(int x, int y)
{
    int i;
    /* 他の形にも対応できるよう矩形領域をスペースで消す */
    char clr[8][32 + 1] = {
        "                ",
        "                ",
        "                ",
        "                ",
        "                ",
        "                ",
        "                ",
        "                ",
    };

    for (i = 0; i < 8; i++)
    {
        mvprintw(y + i, x, clr[i]);
    }

    /* 
  clr[] = "                ";
    と宣言しておいて
  for (i = 0; i < 8; i++) {
    mvprintw(y+i, x, clr);
  }
    のようにしてもOK。
 */
}

/* --------------------------------------------------------------
  moveheart -- 矢印キーでハートマークを動かす
   -------------------------------------------------------------- */




void moveheart(int x, int y)
{
    int key;
    int oldx = x, oldy = y;

    /* [BACKSPACE]キーが押されるまで繰り返す */
    while ((key = getch()) != KEY_BACKSPACE)
    {
        switch (key)
        {
        case KEY_UP:
            oldx = x;
            oldy = y;
            y--;
            if (y < 0)
                y = 0;
            break;
        case KEY_DOWN:
            oldx = x;
            oldy = y;
            y++;
            if (y > 17)
                y = 17;
            break;
        case KEY_LEFT:
            oldx = x;
            oldy = y;
            x--;
            if (x < 0)
                x = 0;
            break;
        case KEY_RIGHT:
            oldx = x;
            oldy = y;
            x++;
            if (x > 63)
                x = 63;
            break;
        }
        /* ハートを描く */
        clrheart(oldx, oldy);
        viewheart(x, y);
    }
}

/* --------------------------------------------------------------
  main
   -------------------------------------------------------------- */
int main(void)
{
    int i;
    int key;
    int x, y;
    int oldx, oldy;

    initscr();

    /* 特殊キーを受け取る */
    noecho();
    cbreak();
    keypad(stdscr, TRUE);






    

    /* 初期座標 */
    x = 32;
    y = 8;

    mvprintw(y, x, "123456\n");

    refresh();


    #if 0
    viewheart(x, y); /* ハートを表示 */
    moveheart(x, y);     /* キーでハートを動かす */
    #endif


    endwin();
    return (0);
}