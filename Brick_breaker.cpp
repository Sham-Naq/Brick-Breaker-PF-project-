#include<iostream>
#include "youregraphics.h"
#include <fstream>

using namespace std;
int brickX[10][10];
int brickY[10][10];
void printbricks(int arr[][10]) {
	int x = 20, y = 60;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (arr[i][j] <= 3) {
				drawRectangle(x, y, x + 75, y + 15, 255, 255, 255, 120 + x, 10 + y - 50, 100 + x - y);
				brickX[i][j] = x;
				brickY[i][j] = y;
			}x += 85;
		}
		y += 25;
		x = 20;
	}
}
int main() {
	int highscore[6] = { 0,0,0,0,0,0 };
	int temp, index = 0;
	// Initialising
	int w, h;
	int life = 3;
	int score = 0;
	getWindowDimensions(w, h);

	cls();
	showConsoleCursor(false);


	// main event loop
	int i = (w / 2) - 100, j = h + 50;
	
	int ballX = (w / 2) - 10, ballY = j - 20;

	bool x = true, y = true;

	int b = 5, straight = 0;


	int brick[10][10];

	for (int r = 0; r < 10; r++) {
		for (int C = 0; C < 10; C++) {
			if (r == 0 || r == 1) {
				brick[r][C] = 3;
			}
			else if (r > 1 && r < 6) {
				brick[r][C] = 2;
			}
			else if (r >= 6) {
				brick[r][C] = 1;
			}
		}
	}
	printbricks(brick);
	ifstream high;
	high.open("highscore.txt");
	for (int i = 0; i < 5; i++) {
		high >> highscore[i];
	}
	high.close();

	while (true) {

		gotoxy(0, 0);
		cout << "  Lives left: " << life << "                                                       Score: " << score;


		drawLine(0, 50, w, 50, 255);
		drawLine(0, 50, 0, h + 50, 255);
		drawLine(0, h + 50, w, h + 50, 255);
		drawLine(w, h + 50, w, 50, 255);

		drawRectangle(i, j, i + 200, j + 25, 255, 0, 0, 255, 255, 255);
		drawEllipse(ballX, ballY, ballX + 20, ballY + 20, 0, 0, 0, 242, 12, 169);

		delay(25);
		drawRectangle(i, j, i + 200, j + 25, 10, 10, 10, 10, 10, 10);
		drawEllipse(ballX, ballY, ballX + 20, ballY + 20, 10, 10, 10, 10, 10, 10);


		char c = getKey();

		if (c == 'q') break;

		if (c == 'a' && i > 0) i -= 20;

		if (c == 'd' && i + 200 < w) i += 20;

		if (c == 'p') {
			while (true) {
				gotoxy(33, 0);
				cout << "Press U To Unpause";

				drawRectangle(i, j, i + 200, j + 25, 255, 0, 0, 255, 255, 255);
				drawEllipse(ballX, ballY, ballX + 20, ballY + 20, 0, 0, 0, 242, 12, 169);

				char v = getKey();
				if (v == 'u') {
					drawRectangle(i, j, i + 200, j + 25, 10, 10, 10, 10, 10, 10);
					drawEllipse(ballX, ballY, ballX + 20, ballY + 20, 10, 10, 10, 10, 10, 10);

					break;
				}

			}
		}
		if (c == 's') {
			ofstream save;
			save.open("save.txt");
			save << life << endl;
			save << ballX << endl;
			save << ballY << endl;
			save << i << endl;
			save << j << endl;
			save << score << endl;
			save << x << endl;
			save << y << endl;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					save << brick[i][j] << endl;
					save << brickX[i][j] << endl;
					save << brickY[i][j] << endl;
				}


			}
			save.close();




		}
		if (c == 'l') {
			ifstream save;
			save.open("save.txt");
			save >> life;
			save >> ballX;
			save >> ballY;
			save >> i;
			save >> j;
			save >> score;
			save >> x;
			save >> y;
			drawRectangle(0, 0, w, h, 0, 0, 0, 0, 0, 0);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					save >> brick[i][j];
					save >> brickX[i][j];
					save >> brickY[i][j];
					if (brick[i][j] != 0)
						drawRectangle(brickX[i][j], brickY[i][j], brickX[i][j] + 75, brickY[i][j] + 15, 255, 255, 255, 120 + brickX[i][j], 10 + brickY[i][j] - 50, 100 + brickX[i][j] - brickY[i][j]);

				}


			}
		}


		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int bx = brickX[i][j];
				int by = brickY[i][j];
				if (brick[i][j] == 0) {
					continue;
				}
				if (

					(ballX < bx + 75 &&
						ballX + 20 > bx) &&

					((ballY < by + 20 &&
						ballY + 20 > by + 20) ||
						(ballY + 20 > by &&
							ballY < by))) {

					if (straight == 1) straight = 2;
					else y = !y;

					brick[i][j] --;

					if (brick[i][j] == 2) {
						drawRectangle(bx, by, bx + 75, by + 15, 255, 255, 255, 233, 131, 53);
						score++;
					}

					if (brick[i][j] == 1) {
						drawRectangle(bx, by, bx + 75, by + 15, 255, 255, 255, 238, 62, 62);
						score++;
					}

					if (brick[i][j] == 0) {
						drawRectangle(bx, by, bx + 75, by + 15, 10, 10, 10, 10, 10, 10);
						score++;
					}
					
				}


			}

		}



		if (ballY + 20 > h + 50) {
			if (ballX + 10 > i && ballX + 10 <= i + 70) {
				if (x) {
					x = !x;
					y = !y;
					straight = 0;
				}
				else {
					y = !y;
					straight = 0;
				}
			}
			else if(ballX + 10 > i + 70 && ballX + 10 <= i + 130) {
				straight = 1;
			}
			else if(ballX + 10 > i + 130 && ballX + 10 < i + 190){
				if (x) {
					y = !y;
					straight = 0;
				}
				else {
					x = !x;
					y = !y;
					straight = 0;
				}
			}
		}
		if (ballY < 50) {
			if (straight == 1) straight = 2;
			else y = !y;
		}

		if (ballX < 0 || ballX + 20 > w) x = !x;



		if (straight == 1) {
			ballY -= 8;
		}
		else if (straight == 2) {
			ballY += 8;
		}
		else if (x && y) {
			ballX += 4;
			ballY -= 8;
		}
		else if (x && !y) {
			ballX += 4;
			ballY += 8;
		}
		else if (!x && y) {
			ballX -= 4;
			ballY -= 8;
		}
		else if (!x && !y) {
			ballX -= 4;
			ballY += 8;
		}

		if (ballY + 20 > h + 50 && (ballX + 20 < i || ballX > i + 200)) {
			delay(2000);

			i = (w / 2) - 100, j = h + 50;
			ballX = (w / 2) - 10, ballY = j - 20;

			x = 1, y = 1, straight = 0;
			life--;

			if (life == 0) {
				break;
			}
		}

		

		if (score >= 100) break;

		
	}
	ofstream HIGH;
	HIGH.open("highscore.txt");
	for (int i = 0; i < 5; i++) {
		if (score > highscore[i]) {
			index = i;
			break;
		}
	}
	temp = highscore[index];
	highscore[index] = score;
	for (int i = index; i < 5; i++) {
		swap(temp, highscore[i + 1]);
	}
	for (int i = 0; i < 5; i++) {
		HIGH << highscore[i] << " ";
	}
	HIGH.close();

	cls();

	char v;
	do {
		
		if (score >= 100) {
			gotoxy(40, 10);
			cout << "Congragualtions!!!" << endl << endl;
		}
		else {
			gotoxy(40, 10);

			cout << "Game over" << endl << endl << endl;
		}




		cout << "final score:  " << score << endl;
		cout << "high scores     " << endl;

		for (int i = 0; i < 5; i++) {
			cout << highscore[i] << endl;
		}

		gotoxy(40, 0);
		cout << "Press Q to exit";

		v = getKey();


	} while (v != 'q');
	
		

	cls();
	showConsoleCursor(true);

	gotoxy(0, 0);

	return 0;
}
