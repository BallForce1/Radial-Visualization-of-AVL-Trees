#include <iostream>
#include "AvlTree.h"
#include "EasyBMP.h"
#include <string>
#include <sstream>
#include <time.h>

const int SIZE = 100;

using namespace std;

void setPixel(BMP& p, int x, int y, RGBApixel color)
{
	p.SetPixel(x,y,color);
}



int main(int argc, char argv[])
{
	AvlTree<int> mytree;
	string e = "0";
	int w = 0;
	int n=0;
	string tempString, tempString2;
	bool insert = false;
	bool print_steps = false;
	BMP myBMP;
	string filename;
	string output = "insert";
	int number = 0;
	string filetype = ".bmp";
	stringstream ss;
	time_t start, end;


	unsigned int rand_red, rand_blue, rand_green;
	RGBApixel rand_pixel;
	srand ( time(NULL) );

	bool go = false;
	while(!go)
	{
		cout << "Type \"insert\" to add your own integers into the tree" 
			<< "or type \"generate\" to randomly generate a full AVL Tree of size 2^n-1: ";
		cin >> tempString;

		cout << "Would you like to generate an image after each insert? (WARNING: This will take much longer to process)";
		cin >> tempString2;
		cout << endl;
		if(tempString2[0] == 'y')
			print_steps = true;

		mytree.setRadii(250,40);
		
		if(tempString == "insert")
		{
			insert = true;
			cout << "Insert integers into AVL Tree. Type \"done\" to finish." << endl;
			string input;
			int count=0;
			while(!go)
			{
				cout << "key=";
				cin >> input;
				cout << endl;
				if(input=="done")
					go=true;
				else
				{
					rand_pixel.Red = rand() % 256;
					rand_pixel.Green = rand() % 256;
					rand_pixel.Blue = rand() % 256;
					mytree.insert(atoi(&input[0]), rand_pixel);
					if(print_steps)
					{
						ss << output << number++ << filetype;
						start = clock();
						mytree.printTree(myBMP);
						end = clock();
						cout << "To generate image " << count++ << " took: " << end-start << " cycles" << endl;
						myBMP.WriteToFile(ss.str().c_str());
						ss.str("");
					}
				}
			}
		}
		else if(tempString == "generate")
		{
			while(n==0)
			{
				cout << "Generate AVL Tree of random key values of size 2^n-1 n=";
					cin >> n;
				cout << endl;
				if(n<0 || n>7)
				{
					cout << "Value out of range. Try again" << endl;
					n = 0;
				}
			}
			for(int k = 0; k<(1<<n)-1; k++)
			{
				rand_pixel.Red = rand() % 256;
				rand_pixel.Green = rand() % 256;
				rand_pixel.Blue = rand() % 256;
				mytree.insert(rand()%10000,rand_pixel);
				if(print_steps)
				{
					ss << output << number++ << filetype;
					start = clock();
					mytree.printTree(myBMP);
					end = clock();
					cout << "To generate image " << k << " took: " << end-start << " cycles" << endl;
					myBMP.WriteToFile(ss.str().c_str());
					ss.str("");
				}
			}
			go=true;
		}
		else
			go=false;
	}

	start = clock();
	mytree.printTree(myBMP);
	end = clock();
	cout << "To generate the output image took: " << end-start << " cycles" << endl;

	
	myBMP.WriteToFile("output.bmp");
	
	
	#ifdef _WIN32
       system("pause");
    #endif
	return 0;
}