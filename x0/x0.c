#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
char field[17][17];
int spawnx = 1, spawny = 1, flag = 0, q = 0, lastx = 0, lasty = 0, ret = 0, stop = 0;
void walls(int x, int y) {
	for (int i = 0; i <= x + 1; i++) {
		for (int j = 0; j <= y + 1; j++) {
			if (i == 0 || j == 0 || i == x+1 || j == y+1) {
				field[i][j] = '#';
			}
			else {
				if (field[i][j] != 'X' && field[i][j] != '0') {
					field[i][j] = '.';
				}
			}
		}
	}
}
void printwalls(int x, int y) {
	for (int i = 0; i <= x + 1; i++) {
		for (int j = 0; j <= y + 1; j++) {
			_putch(field[i][j]);
		}
		_putch('\n');
	}
}
void move(deltax, deltay, x, y) {
	int x1 = spawnx + deltax;
	int y1 = spawny + deltay;
	if (x1 == 0 || y1 == 0 || x1 == y + 1 || y1 == x + 1) {
		spawnx += 0;
		spawny += 0;
	}
	else {
		spawnx += deltax;
		spawny += deltay;
	}
}
void printstart() {
	if (field[spawny][spawnx] != 'X' && field[spawny][spawnx] != '0') {
		field[spawny][spawnx] = '+';
	}
}
void decision(int lasty, int lastx, int r, int x, int y) {
	char str[15];
	memset(str, 0, sizeof(str));
	// влево и вправо
	if (spawnx - (r - 1) >= 1) {
		int l = r-1;
		while (l != 0) {
			if (ret != 0) { break; }
			else {
				int i = 0, k = -l, fl = 0;
				while (i != r) {
					str[i] = field[lasty][lastx + k];
					i++;
					k++;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { ret = q + 1; }
				l--;
			}
		}
	}
	if ((spawnx + (r - 1) <= x + 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, k = l, fl = 0;
				while (i != r) {
					str[i] = field[lasty][lastx + k];
					i++;
					k--;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("2 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	// вверх и вниз
	if ((spawny - (r - 1) >= 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, k = -l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + k][lastx];
					i++;
					k++;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("3 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	if ((spawny + (r - 1) <= y + 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, k = l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + k][lastx];
					i++;
					k--;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("4 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	// диагональ влево и вниз и вправо вверх 
	if (spawnx - (r - 1) >= 1 && (spawny + (r - 1) <= y + 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, kx = -l, ky = l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + ky][lastx + kx];
					i++;
					kx++;
					ky--;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("2 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	if ((spawnx + (r - 1) <= x + 1) && (spawny - (r - 1) >= 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, kx = l, ky = -l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + ky][lastx + kx];
					i++;
					kx--;
					ky++;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("2 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	// диагональ влево вверх и вправо вниз
	if (spawnx - (r - 1) >= 1 && (spawny - (r - 1) >= 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, k = -l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + k][lastx + k];
					i++;
					k++;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("2 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
	if ((spawnx + (r - 1) <= x + 1) && (spawny + (r - 1) <= y + 1) && ret == 0) {
		int l = r - 1;
		while (l != 0) {
			memset(str, 0, sizeof(str));
			if (ret != 0) { break; }
			else {
				int i = 0, k = l, fl = 0;
				while (i != r) {
					str[i] = field[lasty + k][lastx + k];
					i++;
					k--;
				}
				for (int j = 0; j < r - 1; j++) {
					if (str[j] == str[j + 1]) {
						fl = 0;
					}
					else {
						fl = 1;
						break;
					}
				}
				if (fl == 1) { ret = 0; }
				else { printf("2 %s", str); ret = q + 1; }
				l--;
			}
		}
	}
}
void printX0(spawny, spawnx) {
	if (q == 0) {
		if (field[spawny][spawnx] == '0') { q = 0; }
		else { field[spawny][spawnx] = 'X'; q = 1; }
	}
	else {
		if (field[spawny][spawnx] == 'X') { q = 1; }
		else { field[spawny][spawnx] = '0'; q = 0; }
	}
}
void findwin(x, y, r) {
	char str[16];
	int win = 0;
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			if (field[i][j] != '+') {
				if (i - (r - 1) >= 1) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = -l;
						while (o != r) {
							str[o] = field[j + k][i];
							o++;
							k++;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if ((i + (r - 1) <= x + 2)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = l;
						while (o != r) {
							str[o] = field[j + k][i];
							o++;
							k--;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if ((j - (r - 1) >= 1)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = -l;
						while (o != r) {
							str[o] = field[j][i + k];
							o++;
							k++;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if ((j + (r - 1) <= y + 2)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = l;
						while (o != r) {
							str[o] = field[j][i + k];
							o++;
							k--;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if (i - (r - 1) >= 1 && (j + (r - 1) <= y + 2)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, kx = -l, ky = l;
						while (o != r) {
							str[o] = field[j + ky][i + kx];
							o++;
							kx++;
							ky--;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if ((i + (r - 1) <= x + 2) && (j - (r - 1) >= 1)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, kx = l, ky = -l;
						while (o != r) {
							str[o] = field[j + ky][i + kx];
							o++;
							kx--;
							ky++;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if (i - (r - 1) >= 1 && (j - (r - 1) >= 1)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = -l;
						while (o != r) {
							str[o] = field[j + k][i + k];
							o++;
							k++;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}
				if ((i + (r - 1) <= x + 1) && (j + (r - 1) <= y + 1)) {
					int l = r - 1;
					while (l != 0) {
						memset(str, 0, sizeof(str));
						int o = 0, k = l;
						while (o != r) {
							str[o] = field[j + k][i + k];
							o++;
							k--;
						}
						if ((strchr(str, '.') && strchr(str, '0') && !strchr(str, 'X') && !strchr(str, '#')) || (!strchr(str, '#') && strchr(str, '.') && strchr(str, 'X') && !strchr(str, '0')) || (strchr(str, '.') && !strchr(str, '0') && !strchr(str, '#') && !strchr(str, 'X'))) { win++; }
						l--;
					}
				}


			}
		}
	}
	if (win == 0 && lastx != 0 && lasty != 0) { stop = 1; }
}
void keyboard(x, y, r) {
	int ch = _getch();
	switch (ch) {
	case 72: move(0, -1, x, y); break;
	case 80: move(0, 1, x, y); break;
	case 75: move(-1, 0, x, y); break;
	case 77: move(1, 0, x, y); break;
	case 27: flag = 1; break;
	case 13: printX0(spawny, spawnx); decision(spawny, spawnx, r, x, y); lastx = spawnx; lasty = spawny; break;
	}
}
void game(int x, int y, int r) {
	walls(x, y);
	printstart();
	printwalls(x, y);
	findwin(x, y, r);
}
int input() {
	char xx[100];
	int flag = 0, x1 = 0;
	gets(xx);
	for (int i = 0; i < strlen(xx); i++) {
		if (isdigit(xx[i])) {
			flag = 0;
			continue;
		}
		else {
			flag = 1;
			break;
		}
	}
	if (flag == 0 && strlen(xx) <= 2 && strlen(xx) > 0) {
		sscanf_s(xx, "%d", &x1);
		if (x1 <= 15 && x1 >= 3) { return x1; }
		else { return -1; }
	}
	else { return -1; }
}
int main() {
	setlocale(LC_ALL, "Rus");
	int x = 3, y = 3, r = 3, ch = 0, k1 = 1;
	printf("Размер поля (мин. 3х3, макс. 15х15): \n \n");
	printf("> 1) Ширина: %d\n", x);
	printf("2) Высота: %d \n", y);
	printf("3) Клеток для победы: %d\n", r);
	printf("4) Продолжить \n");
	printf("\nДля выхода назад нажмите ESC");
	while (ch != 27) {
		ch = getch();
		if (ch == 49 || (ch == 13 && k1 == 1)) {
			k1 = 1;
			system("cls");
			memset(field, 0, sizeof(field));
			spawnx = 1, spawny = 1, flag = 0, q = 0, lastx = 0, lasty = 0;
			printf("Введите ширину от 3 до 15 включительно: ");
			x = input();
		}
		else if (ch == 50 || (ch == 13 && k1 == 2)) {
			k1 = 2;
			system("cls");
			memset(field, 0, sizeof(field));
			spawnx = 1, spawny = 1, flag = 0, q = 0, lastx = 0, lasty = 0;
			printf("Введите длину от 3 до 15 включительно: ");
			y = input();
		}
		else if (ch == 51 || (ch == 13 && k1 == 3)) {
			k1 = 3;
			system("cls");
			memset(field, 0, sizeof(field));
			spawnx = 1, spawny = 1, flag = 0, q = 0, lastx = 0, lasty = 0;
			printf("Введите количетсво клеток для победы от 3 до 15 включительно: ");
			r = input();
		}
		else if (ch == 52 || (ch == 13 && k1 == 4)) {
			k1 = 4;
			if (x == -1 || y == -1 || r == -1) {
				int chp = 0;
				system("cls");
				printf("Были введены не все значения!\n");
				printf("\nДля выхода назад нажмите ESC");
				while (chp != 27) {
					chp = getch();
					system("cls");
					printf("Были введены не все значения!\n");
					printf("\nДля выхода назад нажмите ESC");
				}
			}
			else {
				while (flag != 1) {
					system("cls");
					printf("Приятной игры! \n \n");
					printf("Передвигаться на стрелочки! \n");
					printf("Сделать ход - Enter!\n");
					printf("Клеток для победы - %d!\n \n", r);
					printf("\nДля выхода назад нажмите ESC\n\n");
					game(x, y, r);
					if (stop == 0) {
						if (ret == 1) { printf(" \nПобеда игрока %d!", 2); flag = 1; }
						else if (ret == 2) { printf(" \nПобеда игрока %d!", 1); flag = 1; }
						else { printf("\nХод игрока номер %d", q + 1); }
					}
					else {
						printf(" \nНичья!"); flag = 1;
					}
					keyboard(x, y, r);
				}
				flag = 0; ret = 0; stop = 0;
				memset(field, 0, sizeof(field));
				spawnx = 1, spawny = 1, flag = 0, q = 0, lastx = 0, lasty = 0;

			}
		}
		else if (ch == 80) {
			if (k1 == 4) { continue; }
			else { k1++; }
		}
		else if (ch == 72) {
			if (k1 == 1) { continue; }
			else { k1--; }
		}
		system("cls");
		printf("Размер поля (мин. 3х3, макс. 15х15): \n \n");
		if (k1 == 1) {
			if (x != -1) { printf("> 1) Ширина: %d\n", x); }
			else { printf("> 1) Ширина: некорректное значение \n"); }
		}
		else {
			if (x != -1) { printf("1) Ширина: %d\n", x); }
			else { printf("1) Ширина: некорректное значение \n"); }
		}
		if (k1 == 2) {
			if (y != -1) { printf("> 2) Высота: %d\n", y); }
			else { printf("> 2) Высота: некорректное значение \n"); }
		}
		else {
			if (y != -1) { printf("2) Высота: %d \n", y); }
			else { printf("2) Высота: некорректное значение \n"); }
		}
		if (k1 == 3) {
			if (r != -1) { printf("> 3) Клеток для победы: %d\n", r); }
			else { printf("> 3) Клеток для победы: некорректное значение\n"); }
		}
		else {
			if (r != -1) { printf("3) Клеток для победы: %d\n", r); }
			else { printf("3) Клеток для победы: некорректное значение\n"); }
		}
		if (k1 == 4) { printf("> 4) Продолжить \n"); }
		else { printf("4) Продолжить \n"); }
		printf("\nДля выхода назад нажмите ESC");
	}
}