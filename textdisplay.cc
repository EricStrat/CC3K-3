#include <iostream>
#include <fstream>
#include "textdisplay.h"
#include <vector>
#include "posn.h"

using namespace std;

TextDisplay::TextDisplay(): floor{1} {
	ifstream file("stage.txt");
	int row = 0;
	int col = 0;
	char cha;
	while (file.get(cha)) {
		if (col == 0 ) {
			theDisplay.emplace_back();
		}
		if (col >= 0 && col < 80){
			theDisplay[row].emplace_back(cha);
			col++;
		}
		if (col == 80){
			col = 0;
			row++;
		}
	}
}
	
TextDisplay::~TextDisplay() {}

void TextDisplay::notify(int r, int c, char cha) {
	theDisplay[r][c] = cha;
}

void TextDisplay::newfloor(){
	ifstream file("cc3kfloor.txt");
	int row = 0;
	int col = 0;
	char cha;
	while (file.get(cha)) {
		if (col == 0 ) {
			theDisplay.emplace_back();
		}
		if (col >= 0 && col < 80){
			theDisplay[row].emplace_back(cha);
			col++;
		}
		if (col == 80){
			col = 0;
			row++;
		}
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int row = 0; row < 25; row++){
		for(int col = 0; col < 80; col++){
			if ( td.theDisplay[row][col] == 'A'
				| td.theDisplay[row][col] == 'B'
				| td.theDisplay[row][col] == 'C'
				| td.theDisplay[row][col] == 'D'
                                | td.theDisplay[row][col] == 'E') cout << '.';
			else out << td.theDisplay[row][col];
		}
	}
	cout << endl;
	return out;
}

