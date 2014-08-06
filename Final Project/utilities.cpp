#pragma once 
#include <iostream>
#include "queue.cpp"
#include "EasyBMP.h"
using namespace std;

//color control
enum color {BLACK, WHITE, GREEN, RED, BLUE, ORANGE};

struct vectorParts{
	char letter;
	int holes;
	bool vertical;
	bool horizontal;
	double quadrentPercent[4];
};

class neighborhood{
public:
	point* neighbor[8];
	//CONSTRUCTOR: set all pointers to NULL.
	neighborhood(){
		for(int k=0; k<8; k++)
			neighbor[k] = NULL;
	}
	//FUNCTION: given a point this will construct a neighborhood of the surrounding pixels.
	//Tests the pixels for black before adding it to the neighborhood.
	//returns a pointer to the neighborhood of only black pixels.
	//neighborhood* findNeighbors(BMP& inBMP, point p, color inColor){
	neighborhood(BMP& inBMP, point p, color inColor){	
		int x = p.getx();
		int y = p.gety();
		int xmax = inBMP.TellWidth()-1;
		int ymax = inBMP.TellHeight()-1;
		//set all neighbors to NULL
		for(int k=0; k<8; k++)
			neighbor[k] = NULL;
		int colorValue = 0;
			switch(inColor){
			case BLACK:
				colorValue = 20;
				//test north
		 		if(y!=0 && inBMP(x,y-1)->Red < colorValue && inBMP(x,y-1)->Green < colorValue && inBMP(x,y-1)->Blue <colorValue)
					neighbor[0] = new point(x,y-1);
				//test north-east
				if(x!=xmax && y!=0 && inBMP(x+1,y-1)->Red < colorValue && inBMP(x+1,y-1)->Green < colorValue && inBMP(x+1,y-1)->Blue <colorValue)
					neighbor[1] = new point(x+1,y-1);
				//test east
				if(x!=xmax && inBMP(x+1,y)->Red < colorValue && inBMP(x+1,y)->Green < colorValue && inBMP(x+1,y)->Blue <colorValue)
					neighbor[2] = new point(x+1,y);
				//test south-east
				if(y!=ymax && x!=xmax && inBMP(x+1,y+1)->Red < colorValue && inBMP(x+1,y+1)->Green < colorValue && inBMP(x+1,y+1)->Blue <colorValue)
					neighbor[3] = new point(x+1,y+1);
				//test south
				if(y!=ymax && inBMP(x,y+1)->Red < colorValue && inBMP(x,y+1)->Green < colorValue && inBMP(x,y+1)->Blue <colorValue)
					neighbor[4] = new point(x,y+1);
				//test south-west
				if(y!=ymax && x!=0 && inBMP(x-1,y+1)->Red < colorValue && inBMP(x-1,y+1)->Green < colorValue && inBMP(x-1,y+1)->Blue<colorValue)
					neighbor[5] = new point(x-1,y+1);
				//test west
				if(x!=0 && inBMP(x-1,y)->Red < colorValue && inBMP(x-1,y)->Green < colorValue && inBMP(x-1,y)->Blue <colorValue)
					neighbor[6] = new point(x-1,y);
				//test north-west
				if(y!=0 && x != 0 && inBMP(x-1,y-1)->Red < colorValue && inBMP(x-1,y-1)->Green < colorValue && inBMP(x-1,y-1)->Blue <colorValue)
					neighbor[7] = new point(x,y-1);
				break;
			case WHITE:
				colorValue = 200;
				//test north
				if(y!=0 && inBMP(x,y-1)->Red > colorValue && inBMP(x,y-1)->Green > colorValue && inBMP(x,y-1)->Blue >colorValue)
					neighbor[0] = new point(x,y-1);
				//test north-east
				if(x!=xmax && y!=0 && inBMP(x+1,y-1)->Red > colorValue && inBMP(x+1,y-1)->Green > colorValue && inBMP(x+1,y-1)->Blue >colorValue)
					neighbor[1] = new point(x+1,y-1);
				//test east
				if(x!=xmax && inBMP(x+1,y)->Red > colorValue && inBMP(x+1,y)->Green > colorValue && inBMP(x+1,y)->Blue >colorValue)
					neighbor[2] = new point(x+1,y);
				//test south-east
				if(y!=ymax && x!=xmax && inBMP(x+1,y+1)->Red > colorValue && inBMP(x+1,y+1)->Green > colorValue && inBMP(x+1,y+1)->Blue >colorValue)
					neighbor[3] = new point(x+1,y+1);
				//test south
				if(y!=ymax && inBMP(x,y+1)->Red > colorValue && inBMP(x,y+1)->Green > colorValue && inBMP(x,y+1)->Blue >colorValue)
					neighbor[4] = new point(x,y+1);
				//test south-west
				if(y!=ymax && x!=0 && inBMP(x-1,y+1)->Red > colorValue && inBMP(x-1,y+1)->Green > colorValue && inBMP(x-1,y+1)->Blue>colorValue)
					neighbor[5] = new point(x-1,y+1);
				//test west
				if(x!=0 && inBMP(x-1,y)->Red > colorValue && inBMP(x-1,y)->Green > colorValue && inBMP(x-1,y)->Blue >colorValue)
					neighbor[6] = new point(x-1,y);
				//test north-west
				if(y!=0 && x != 0 && inBMP(x-1,y-1)->Red > colorValue && inBMP(x-1,y-1)->Green > colorValue && inBMP(x-1,y-1)->Blue >colorValue)
					neighbor[7] = new point(x,y-1);
				break;
			default:
				cout << "ONLY BLACK AND WHITE TEST CASES ARE ALLOWED" << endl;
			}	
		}
	};
