#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
using namespace std;

int bord[10][10];
//黑子是1，白子是2，障碍是3

int mouse[2];

void printbord() {
	IMAGE qipan;
	loadimage(&qipan, _T("main.jpg"));
	putimage(0, 0, &qipan);
	IMAGE heizi, baizi, zhangai;
	loadimage(&heizi, _T("black.jpg"));
	loadimage(&baizi, _T("white.jpg"));
	loadimage(&zhangai, _T("barriar.jpg"));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (bord[i][j] == 1)
				putimage(50 * (j + 1) + 2, 50 * (i + 1) + 2, &heizi);
			if (bord[i][j] == 2)
				putimage(50 * (j + 1) + 2, 50 * (i + 1) + 2, &baizi);
			if (bord[i][j] == 3)
				putimage(50 * (j + 1) + 2, 50 * (i + 1) + 2, &zhangai);
		}
	}
}

bool canmove(int x, int y) {
    int flag = 0;
    if (x == 0)
        flag++;
    else {
        if (bord[x - 1][y]!=0)
            flag++;
    }
    if (y == 0)
        flag++;
    else {
        if (bord[x][y - 1]!=0)
            flag++;
    }
    if (x == 9)
        flag++;
    else {
        if (bord[x + 1][y]!=0)
            flag++;
    }
    if (y == 9)
        flag++;
    else {
        if (bord[x][y + 1]!=0)
            flag++;
    }
    if (x == 0 || y == 9)
        flag++;
    else {
        if (bord[x - 1][y + 1]!=0)
            flag++;
    }
    if (x == 0 || y == 0)
        flag++;
    else {
        if (bord[x - 1][y - 1]!=0)
            flag++;
    }
    if (x == 9 || y == 0)
        flag++;
    else {
        if (bord[x + 1][y - 1]!=0)
            flag++;
    }
    if (x == 9 || y == 9)
        flag++;
    else {
        if (bord[x + 1][y + 1]!=0)
            flag++;
    }
    if (flag == 8)
        return false;
    else
        return true;
}

void click() {
    MOUSEMSG m;
    while (1) {
        m = GetMouseMsg();
        if ((m.uMsg) == WM_LBUTTONDOWN) {
            mouse[0] = m.x;
            mouse[1] = m.y;
            break;
        }    
    }
}

void justclick() {
    IMAGE clicli;
    loadimage(&clicli, _T("click.jpg"));
    putimage(600, 50, &clicli);
    click();
}

void putbarrier(int x, int y) {
    IMAGE wrong;
    loadimage(&wrong, _T("error.jpg"));
    int barx, bary;
    click();
    barx = (mouse[1] / 10) / 5;
    bary = (mouse[0] / 10) / 5;
    if (barx < 1 || barx>10 || bary < 1 || bary>10) {
        putimage(600, 50, &wrong);
        putbarrier(x, y);
    }
    if (barx == x) {
        int minmin1 = min(y, bary);
        int maxmax1 = max(y, bary);
        int flagflag1 = 0;
        for (int wety1 = minmin1 + 1; wety1 < maxmax1; wety1++)
            if (bord[x - 1][wety1 - 1]!=0)
                flagflag1 = 1;
        if (bord[x - 1][bary - 1]!=0)
            flagflag1 = 1;
        if (flagflag1 == 0) {
            bord[x - 1][bary - 1]=3;
            printbord();
            return;
        }
        else {
            printbord();
            putimage(600, 50, &wrong);
            putbarrier(x, y);
            return;
        }
    }
    if (bary == y) {
        int minmin2 = min(x, barx);
        int maxmax2 = max(x, barx);
        int flagflag2 = 0;
        for (int wety2 = minmin2 + 1; wety2 < maxmax2; wety2++)
            if (bord[wety2 - 1][y - 1]!= 0)
                flagflag2 = 1;
        if (bord[barx - 1][y - 1]!= 0)
            flagflag2 = 1;
        if (flagflag2 == 0) {
            bord[barx - 1][y - 1]=3;
            printbord();
            return;
        }
        else {
            printbord();
            putimage(600, 50, &wrong);
            putbarrier(x, y);
            return;
        }
    }
    if (y - bary == x - barx) {
        int minmin3 = min(y, bary);
        int minmin33 = min(x, barx);
        int maxmax3 = max(y, bary);
        int maxmax33 = max(x, barx);
        int flagflag3 = 0;
        for (int wety3 = 1; minmin3 + wety3 < maxmax3; wety3++)
            if (bord[minmin33 + wety3 - 1][minmin3 + wety3 - 1] != 0)
                flagflag3 = 1;
        if (bord[barx - 1][bary - 1]!= 0)
            flagflag3 = 1;
        if (flagflag3 == 0) {
            bord[barx - 1][bary - 1]=3;
            printbord();
            return;
        }
        else {
            printbord();
            putimage(600, 50, &wrong);
            putbarrier(x, y);
            return;
        }
    }
    if (barx + bary == x + y) {
        int minmin4 = min(bary, y);
        int minmin44 = min(barx, x);
        int maxmax4 = max(bary, y);
        int maxmax44 = max(barx, x);
        int flagflag4 = 0;
        for (int wety4 = 1; minmin4 + wety4 < maxmax4; wety4++)
            if (bord[maxmax44 - wety4 - 1][minmin4 + wety4 - 1]!= 0)
                flagflag4 = 1;
        if (bord[barx - 1][bary - 1]!=0)
            flagflag4 = 1;
        if (flagflag4 == 0) {
            bord[barx - 1][bary - 1]=3;
            printbord();
            return;
        }
        else {
            printbord();
            putimage(600, 50, &wrong);
            putbarrier(x, y);
            return;
        }
    }
    printbord();
    putimage(600, 50, &wrong);
    putbarrier(x, y);
    return;
}

bool ifwin() {
    int fourmove = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (bord[i][j] == 1) {
                if (!canmove(i, j)) {
                    fourmove++;
                }
            }
        }
    }
    if (fourmove == 4)
        return false;
    else
        return true;
}

bool ifwin1() {
    int fourmove = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (bord[i][j] == 2) {
                if (!canmove(i, j)) {
                    fourmove++;
                }
            }
        }
    }
    if (fourmove == 4)
        return true;
    else
        return false;
}

int searchblank(int x, int y) {
    int sum = 0;
    if (x > 0 && bord[x - 1][y] == 0)
        sum++;
    if (y > 0 && bord[x][y - 1] == 0)
        sum++;
    if (x < 9 && bord[x + 1][y] == 0)
        sum++;
    if (y < 9 && bord[x][y + 1] == 0)
        sum++;
    if (x > 0 && y > 0 && bord[x - 1][y - 1] == 0)
        sum++;
    if (x < 9 && y < 9 && bord[x + 1][y + 1] == 0)
        sum++;
    if (x > 0 && y < 9 && bord[x - 1][y + 1] == 0)
        sum++;
    if (x < 9 && y > 0 && bord[x + 1][y - 1] == 0)
        sum++;
    return sum;
}

int searchnoblank(int x, int y) {
    int sum = 0;
    if (x > 0 && bord[x - 1][y] != 0)
        sum++;
    if (y > 0 && bord[x][y - 1] != 0)
        sum++;
    if (x < 9 && bord[x + 1][y] != 0)
        sum++;
    if (y < 9 && bord[x][y + 1] != 0)
        sum++;
    if (x > 0 && y > 0 && bord[x - 1][y - 1] != 0)
        sum++;
    if (x < 9 && y < 9 && bord[x + 1][y + 1] != 0)
        sum++;
    if (x > 0 && y < 9 && bord[x - 1][y + 1] != 0)
        sum++;
    if (x < 9 && y > 0 && bord[x + 1][y - 1] != 0)
        sum++;
    return sum;
}

int freedom(int piece) {
    int grossfree = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (bord[i][j] == piece) {
                for (int k = i - 1, l = j - 1; k >= 0 && l >= 0 && bord[k][l] == 0; k--, l--)
                    grossfree++;
                for (int k = j - 1; k >= 0 && bord[i][k] == 0; k--)
                    grossfree++;
                for (int k = i + 1, l = j - 1; k < 10 && l >= 0 && bord[k][l] == 0; k++, l--)
                    grossfree++;
                for (int k = i + 1; k < 10 && bord[k][j] == 0; k++)
                    grossfree++;
                for (int k = i + 1, l = j + 1; k < 10 && l < 10 && bord[k][l] == 0; k--, l--)
                    grossfree++;
                for (int k = j + 1; k < 10 && bord[i][k] == 0; k++)
                    grossfree++;
                for (int k = i - 1, l = j + 1; k >= 0 && l < 10 && bord[k][l] == 0; k--, l++)
                    grossfree++;
                for (int k = i - 1; k >= 0 && bord[k][j] == 0; k--)
                    grossfree++;
            }
        }
    }
    return grossfree;
}

int allsearchblank(int piece) {
    int sum = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (bord[i][j] == piece) {
                sum += searchblank(i, j);
            }
        }
    }
    return sum;
}

int main() {
allnew:  initgraph(1000, 600);
    setorigin(0, 0);
    IMAGE wrong;
    loadimage(&wrong, _T("error.jpg"));
    IMAGE begin;
    loadimage(&begin, _T("start.jpg"));
    putimage(0, 0, &begin);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            bord[i][j] = 0;
    int round = 0;
    bord[0][3] = 1;
    bord[0][6] = 1;
    bord[3][0] = 1;
    bord[3][9] = 1;
    bord[6][0] = 2;
    bord[6][9] = 2;
    bord[9][3] = 2;
    bord[9][6] = 2;
blank:  click();
    if (!(mouse[0] >= 363 && mouse[0] <= 617 && mouse[1] >= 264 && mouse[1] <= 343))
        goto blank;
    printbord();
    while (1) {
        int choosex, choosey;
        if (!ifwin()) {
            IMAGE loser;
            loadimage(&loser, _T("lose.jpg"));
            putimage(600, 50, &loser);
            IMAGE re;
            loadimage(&re, _T("rebegin.jpg"));
            putimage(570, 100, &re);
            click();
            if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 350 && mouse[1] <= 400)
                goto end;
            goto allnew;
        }
    newblack:  click();
        if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 450 && mouse[1] <= 500) {
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    bord[i][j] = 0;
            bord[0][3] = 1;
            bord[0][6] = 1;
            bord[3][0] = 1;
            bord[3][9] = 1;
            bord[6][0] = 2;
            bord[6][9] = 2;
            bord[9][3] = 2;
            bord[9][6] = 2;
            printbord();
            goto newblack;
        }
        if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 150 && mouse[1] <= 200) {
            ofstream savefile("lastgame");
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    savefile << bord[i][j] << ' ';
            savefile.close();
            IMAGE save;
            loadimage(&save, _T("saved.jpg"));
            putimage(600, 50, &save);
            goto newblack;
        }
        if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 250 && mouse[1] <= 300) {
            ifstream savedfile("lastgame");
            if (!savedfile) {
                putimage(600, 50, &wrong);
                goto newblack;
            }
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    savedfile >> bord[i][j];
            savedfile.close();
            printbord();
            goto newblack;
        }
        if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 350 && mouse[1] <= 400)
            goto end;
        choosex = ((mouse[1]) / 10) / 5;
        choosey = ((mouse[0]) / 10) / 5;
        if (choosex < 1 || choosex>10 || choosey < 1 || choosey>10) {
            putimage(600, 50, &wrong);
            goto newblack;
        }
        if (!canmove(choosex - 1, choosey - 1)) {
            putimage(600, 50, &wrong);
            goto newblack;
        }
        if (bord[choosex - 1][choosey - 1] == 1) {
            printbord();
            int newx, newy;
            click();
            newx = ((mouse[1]) / 10) / 5;
            newy = ((mouse[0]) / 10) / 5;
            if (newx == choosex) {
                int min1 = min(choosey, newy);
                int max1 = max(choosey, newy);
                int flag1 = 0;
                for (int k = min1 + 1; k < max1; k++)
                    if (bord[newx - 1][k - 1] != 0)
                        flag1 = 1;
                if (bord[newx - 1][newy - 1] != 0)
                    flag1 = 1;
                if (flag1 == 0) {
                    bord[newx - 1][newy - 1] = 1;
                    bord[choosex - 1][choosey - 1] = 0;
                    printbord();
                }
                else {
                    printbord();
                    putimage(600, 50, &wrong);
                    goto newblack;
                }
            }
            if (newy == choosey) {
                int min2 = min(choosex, newx);
                int max2 = max(choosex, newx);
                int flag2 = 0;
                for (int k = min2 + 1; k < max2; k++)
                    if (bord[k - 1][newy - 1] != 0)
                        flag2 = 1;
                if (bord[newx - 1][newy - 1] != 0)
                    flag2 = 1;
                if (flag2 == 0) {
                    bord[newx - 1][newy - 1] = 1;
                    bord[choosex - 1][choosey - 1] = 0;
                    printbord();
                }
                else {
                    printbord();
                    putimage(600, 50, &wrong);
                    goto newblack;
                }
            }
            if (newy - choosey == newx - choosex) {
                int min3 = min(choosey, newy);
                int min33 = min(choosex, newx);
                int max3 = max(choosey, newy);
                int max33 = max(choosex, newx);
                int flag3 = 0;
                for (int k = 1; min3 + k < max3; k++)
                    if (bord[min33 + k - 1][min3 + k - 1] != 0)
                        flag3 = 1;
                if (bord[newx - 1][newy - 1] != 0)
                    flag3 = 1;
                if (flag3 == 0) {
                    bord[newx - 1][newy - 1] = 1;
                    bord[choosex - 1][choosey - 1] = 0;
                    printbord();
                }
                else {
                    printbord();
                    putimage(600, 50, &wrong);
                    goto newblack;
                }
            }
            if (newx + newy == choosex + choosey) {
                int min4 = min(choosey, newy);
                int min44 = min(choosex, newx);
                int max4 = max(choosey, newy);
                int max44 = max(choosex, newx);
                int flag4 = 0;
                for (int k = 1; min4 + k < max4; k++) {
                    if (bord[max44 - k - 1][min4 + k - 1] != 0)
                        flag4 = 1;
                }
                if (bord[newx - 1][newy - 1] != 0)
                    flag4 = 1;
                if (flag4 == 0) {
                    bord[newx - 1][newy - 1] = 1;
                    bord[choosex - 1][choosey - 1] = 0;
                    printbord();
                }
                else {
                    printbord();
                    putimage(600, 50, &wrong);
                    goto newblack;
                }
            }
            if (choosex != newx && choosey != newy && newx + newy != choosex + choosey && newy - choosey != newx - choosex) {
                putimage(600, 50, &wrong);
                goto newblack;
            }
            putbarrier(newx, newy);
        }
        else {
            printbord();
            putimage(600, 50, &wrong);
            goto newblack;
        }
        if (ifwin1()) {
            IMAGE winner;
            loadimage(&winner, _T("win.jpg"));
            putimage(600, 50, &winner);
            IMAGE re;
            loadimage(&re, _T("rebegin.jpg"));
            putimage(570, 100, &re);
            click();
            if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 350 && mouse[1] <= 400)
                goto end;
            goto allnew;
        }
        if (!ifwin()) {
            IMAGE loser;
            loadimage(&loser, _T("lose.jpg"));
            putimage(600, 50, &loser);
            IMAGE re;
            loadimage(&re, _T("rebegin.jpg"));
            putimage(570, 100, &re);
            click();
            if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 350 && mouse[1] <= 400)
                goto end;
            goto allnew;
        }
        struct piece {
            int x1;
            int y1;
            int test1[8];
            int sum1;
        }white1[4], bestwhite1;
        int turn1 = 0, max1 = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (bord[i][j] == 2) {
                    white1[turn1].x1 = i;
                    white1[turn1].y1 = j;
                    for (int k = 0; k < 8; k++)
                        white1[turn1].test1[k] = 0;
                    white1[turn1].sum1 = 0;
                    for (int k = i - 1, l = j - 1; k >= 0 && l >= 0 && bord[k][l] == 0; k--, l--)
                        white1[turn1].test1[0] += searchblank(k, l) + 1;
                    for (int k = j - 1; k >= 0 && bord[i][k] == 0; k--)
                        white1[turn1].test1[1] += searchblank(i, k) + 1;
                    for (int k = i + 1, l = j - 1; k < 10 && l >= 0 && bord[k][l] == 0; k++, l--)
                        white1[turn1].test1[2] += searchblank(k, l) + 1;
                    for (int k = i + 1; k < 10 && bord[k][j] == 0; k++)
                        white1[turn1].test1[3] += searchblank(k, j) + 1;
                    for (int k = i + 1, l = j + 1; k < 10 && l < 10 && bord[k][l] == 0; k--, l--)
                        white1[turn1].test1[4] += searchblank(k, l) + 1;
                    for (int k = j + 1; k < 10 && bord[i][k] == 0; k++)
                        white1[turn1].test1[5] += searchblank(i, k) + 1;
                    for (int k = i - 1, l = j + 1; k >= 0 && l < 10 && bord[k][l] == 0; k--, l++)
                        white1[turn1].test1[6] += searchblank(k, l) + 1;
                    for (int k = i - 1; k >= 0 && bord[k][j] == 0; k--)
                        white1[turn1].test1[7] += searchblank(k, j) + 1;
                    for (int k = 0; k < 8; k++)
                        white1[turn1].sum1 += white1[turn1].test1[k];
                    if(white1[turn1].sum1 > 0)
                        white1[turn1].sum1 += 50 * searchnoblank(i, j);
                    if (white1[turn1].sum1 >= max1) {
                        max1 = white1[turn1].sum1;
                        bestwhite1 = white1[turn1];
                    }
                    turn1++;
                }
            }
        }
        int pos1, max2 = 0;
        int chosenx, choseny;
        for (int i = 0; i < 8; i++) {
            if (bestwhite1.test1[i] >= max2) {
                max2 = bestwhite1.test1[i];
                pos1 = i;
            }
        }
        int x2 = bestwhite1.x1;
        int y2 = bestwhite1.y1;
        if (pos1 == 0) {
            int max3 = -100000;
            int posx1, posy1;
            for (int k = x2 - 1, l = y2 - 1; k >= 0 && l >= 0 && bord[k][l] == 0; k--, l--) {
                bord[x2][y2] = 0;
                bord[k][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max3) {
                        posx1 = k;
                        posy1 = l;
                        max3 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2)*20 - allsearchblank(1)*20 >= max3){
                        posx1 = k;
                        posy1 = l;
                        max3 = freedom(2) - freedom(1) + allsearchblank(2)*20 - allsearchblank(1)*20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx1][posy1] = 2;
            chosenx = posx1;
            choseny = posy1;
        }
        if (pos1 == 1) {
            int max4 = -100000;
            int posy2;
            for (int l = y2 - 1; l >= 0 && bord[x2][l] == 0; l--) {
                bord[x2][y2] = 0;
                bord[x2][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max4) {
                        posy2 = l;
                        max4 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max4) {
                        posy2 = l;
                        max4 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[x2][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[x2][posy2] = 2;
            chosenx = x2;
            choseny = posy2;
        }
        if (pos1 == 2) {
            int max5 = -100000;
            int posx3, posy3;
            for (int k = x2 + 1, l = y2 - 1; k < 10 && l >= 0 && bord[k][l] == 0; k--, l--) {
                bord[x2][y2] = 0;
                bord[k][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max5) {
                        posx3 = k;
                        posy3 = l;
                        max5 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max5) {
                        posx3 = k;
                        posy3 = l;
                        max5 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx3][posy3] = 2;
            chosenx = posx3;
            choseny = posy3;
        }
        if (pos1 == 3) {
            int max6 = -100000;
            int posx4;
            for (int k = x2 + 1; k < 10 && bord[k][y2] == 0; k++) {
                bord[x2][y2] = 0;
                bord[k][y2] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max6) {
                        posx4 = k;
                        max6 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max6) {
                        posx4 = k;
                        max6 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][y2] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx4][y2] = 2;
            chosenx = posx4;
            choseny = y2;
        }
        if (pos1 == 4) {
            int max7 = -100000;
            int posx5, posy5;
            for (int k = x2 + 1, l = y2 + 1; k < 10 && l < 10 && bord[k][l] == 0; k++, l++) {
                bord[x2][y2] = 0;
                bord[k][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max7) {
                        posx5 = k;
                        posy5 = l;
                        max7 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max7) {
                        posx5 = k;
                        posy5 = l;
                        max7 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx5][posy5] = 2;
            chosenx = posx5;
            choseny = posy5;
        }
        if (pos1 == 5) {
            int max8 = -100000;
            int posy6;
            for (int l = y2 + 1; l < 10 && bord[x2][l] == 0; l++) {
                bord[x2][y2] = 0;
                bord[x2][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max8) {
                        posy6 = l;
                        max8 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max8) {
                        posy6 = l;
                        max8 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[x2][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[x2][posy6] = 2;
            chosenx = x2;
            choseny = posy6;
        }
        if (pos1 == 6) {
            int max9 = -100000;
            int posx7, posy7;
            for (int k = x2 - 1, l = y2 + 1; k >= 0 && l < 10 && bord[k][l] == 0; k--, l++) {
                bord[x2][y2] = 0;
                bord[k][l] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max9) {
                        posx7 = k;
                        posy7 = l;
                        max9 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max9) {
                        posx7 = k;
                        posy7 = l;
                        max9 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][l] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx7][posy7] = 2;
            chosenx = posx7;
            choseny = posy7;
        }
        if (pos1 == 7) {
            int max10 = -100000;
            int posx8;
            for (int k = x2 - 1; k >= 0 && bord[k][y2] == 0; k--) {
                bord[x2][y2] = 0;
                bord[k][y2] = 2;
                if (round <= 20) {
                    if (freedom(2) - freedom(1) >= max10) {
                        posx8 = k;
                        max10 = freedom(2) - freedom(1);
                    }
                }
                else {
                    if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max10) {
                        posx8 = k;
                        max10 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    }
                }
                bord[x2][y2] = 2;
                bord[k][y2] = 0;
            }
            bord[x2][y2] = 0;
            bord[posx8][y2] = 2;
            chosenx = posx8;
            choseny = y2;
        }
        justclick();
        printbord();
        int max0 = -100000;
        int barrierx, barriery;
        for (int i = chosenx - 1, j = choseny - 1; i >= 0 && j >= 0 && bord[i][j] == 0; i--, j--) {
            bord[i][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1) >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = i;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    barrierx = i;
                    barriery = j;
                }
            }
            bord[i][j] = 0;
        }
        for (int j = choseny - 1;j >= 0 && bord[chosenx][j] == 0; j--) {
            bord[chosenx][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1) >= max0) {
                    max0 = freedom(2) - freedom(1) * 20;
                    barrierx = chosenx;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = chosenx;
                    barriery = j;
                }
            }
            bord[chosenx][j] = 0;
        }
        for (int i = chosenx + 1, j = choseny - 1; i < 10 && j >= 0 && bord[i][j] == 0; i++, j--) {
            bord[i][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1)  >= max0) {
                    max0 = freedom(2) - freedom(1);
                    barrierx = i;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = i;
                    barriery = j;
                }
            }
            bord[i][j] = 0;
        }
        for (int i = chosenx + 1; i < 10 && bord[i][choseny] == 0; i++) {
            bord[i][choseny] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1) >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = i;
                    barriery = choseny;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = i;
                    barriery = choseny;
                }
            }
            bord[i][choseny] = 0;
        }
        for (int i = chosenx + 1, j = choseny + 1; i < 10 && j < 10 && bord[i][j] == 0; i++, j++) {
            bord[i][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1)  >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = i;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20  >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20;
                    barrierx = i;
                    barriery = j;
                }
            }
            bord[i][j] = 0;
        }
        for (int j = choseny + 1; j < 10 && bord[chosenx][j] == 0; j++) {
            bord[chosenx][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1)  >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = chosenx;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20  >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = chosenx;
                    barriery = j;
                }
            }
            bord[chosenx][j] = 0;
        }
        for (int i = chosenx - 1, j = choseny + 1; i >= 0 && j < 10 && bord[i][j] == 0; i--, j++) {
            bord[i][j] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1)  >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = i;
                    barriery = j;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = i;
                    barriery = j;
                }
            }
            bord[i][j] = 0;
        }
        for (int i = chosenx - 1; i >= 0 && bord[i][choseny] == 0; i--) {
            bord[i][choseny] = 3;
            if (round <= 20) {
                if (freedom(2) - freedom(1)  >= max0) {
                    max0 = freedom(2) - freedom(1) ;
                    barrierx = i;
                    barriery = choseny;
                }
            }
            else {
                if (freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20  >= max0) {
                    max0 = freedom(2) - freedom(1) + allsearchblank(2) * 20 - allsearchblank(1) * 20 ;
                    barrierx = i;
                    barriery = choseny;
                }
            }
            bord[i][choseny] = 0;
        }
        bord[barrierx][barriery] = 3;
        justclick();
        printbord();
        round++;
        if (ifwin1()) {
            IMAGE winner;
            loadimage(&winner, _T("win.jpg"));
            putimage(600, 50, &winner);
            IMAGE re;
            loadimage(&re, _T("rebegin.jpg"));
            putimage(570, 100, &re);
            click();
            if (mouse[0] >= 650 && mouse[0] <= 800 && mouse[1] >= 350 && mouse[1] <= 400)
                goto end;
            goto allnew;
        }
    }
end:return 0;
}