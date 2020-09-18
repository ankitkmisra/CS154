/*
	Author: Ankit Kumar Misra (with starter code by Prof. RK Joshi, CS154)

	This program runs a 15-Puzzle game for the user to solve through an interactive interface.

	Packages required: libfltk1.3, fluid
	Compilation: fltk-config --compile 15puzzleboardFull.cpp
	Execution: ./15puzzleboardFull
*/

#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

using namespace std;

char *int2charstar (int v) {
 char *s = new char[sizeof(int)];
 sprintf(s,"%d",v);
 return s;
};

class Board;
class Piece;

class Piece: public Fl_Button {
 Board *parent;
 int xpos, ypos;
 public:
	Piece(Board *b, int xp, int yp, int x, int y, int pw, int ph); 
	int handle (int);
};


class Board: public Fl_Window{
 Piece* pieces[4][4];
 int ex, ey; // position of empty piece
 public:
	Board(int, int, int, int);
	int move(int,int,bool);
	void randomize();
	bool isSolved();
	void endgame();
};

void Board::endgame() {
	Fl_Window *win = new Fl_Window (500,80,"CONGRATULATIONS!");
	Fl_Box *dabba = new Fl_Box (50,25,400,30,"You have solved the puzzle successfully!");
	win -> end();
	win -> show();
	Fl::run();
}

bool Board::isSolved() {
   	for (int x=0; x<4;x++)
        for (int y=0; y<4;y++) {
				if (x==3 && y==3) break;
                if (atoi(pieces[x][y]->label()) != x+y*4+1)
				return 0;
	    }
	return 1;
}

Piece::Piece(Board *b, int xp, int yp, int x, int y, int pw, int ph): 
			Fl_Button(x,y,pw,ph,((xp+yp*4+1)==16)?(char*)"":int2charstar(xp+yp*4+1)) {
			parent = b;
			xpos = xp; ypos=yp;
}
int Piece::handle(int event) {  
		if (event==FL_PUSH)
			parent->move(xpos,ypos,true);
		return 1;
};

Board::Board(int x0, int y0, int pw, int ph):
			Fl_Window(2*x0+4*pw, 2*y0+4*ph, "CS 154 15-Puzzle-Board") { 
   	 for (int x=0; x<4;x++)
           for (int y=0; y<4;y++) 
                pieces [x][y] = new Piece(this,x,y,x0+x*pw,y0+y*ph, pw, ph);
	 ex = ey = 3;
	 randomize();
	 show();
}

int Board:: move(int x, int y, bool solving) {
		if (((ex==x) && (abs(y-ey)==1))||(ey==y)&&(abs(x-ex)==1)) {
			pieces[ex][ey]->label(pieces[x][y]->label());
			pieces[x][y]->label((char *)"");
			ex=x; 
	 		ey=y;
			if (isSolved() && solving) {endgame();}
		}
		return 1;
}


void Board::randomize() {
	
	srand(time(0));
	int times = 40;
	int count = 0;
	while (count < times) {
		switch (rand()%4) {
			case 0: if(ex<3) {move(ex+1,ey,false); count++;} break;
			case 1: if(ex>0) {move(ex-1,ey,false); count++;} break;
			case 2: if(ey<3) {move(ex,ey+1,false); count++;} break;
			case 3: if(ey>0) {move(ex,ey-1,false); count++;} break;
		}
	}
	if (isSolved())
		randomize();
}

int main(int argc, char *argv[]) {

   int X = 400, Y = 400;
   int bx = 150, by = 50;
   int pw = X/4, ph = Y/4;

   int emptyx = 3, emptyy = 3;

   Board b(by, bx, pw, ph);

   return Fl::run();
}