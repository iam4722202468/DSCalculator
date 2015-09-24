#include <nds.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <cmath>

#include "buttons.h"
#include "utilities.h"

#include "calculator.h"
#include "graph.h"

PrintConsole topScreen;

std::vector<int> lastlength;
std::string equation;
std::string lastanswer = "";
std::string lastequation = "";

bool ispressed = false;
int mode = 1;
int frameCounter = 0;
bool cursorOnScreen;

bool help = false;

std::string button[6][8] = {
{	"B",	"CA",	"M",	"sin(",	"asin(",	"!",	"log(",	"ln("},
{	"X",	"Y",	"Z",	"cos(",	"acos(",	"%",	"pi",	"e"},
{	"7",	"8",	"9",	"tan(",	"atan(",	"int(",	"rn(",	"avg("},
{	"4",	"5",	"6",	"+",	"-",		"(",	"nPr(",	"cPr("},
{	"1",	"2",	"3",	"*",	"/",		")",	"rnd(",	"mag("},
{	"NL",	"0",	".",	"^",	"v",		",",	"help",	"="}};

std::string buttonhelp[6][8] = {
{"Back", "Clear screen", "Change mode", "Sine", "Arc sine", "Factorial", "Logarithm", "Natural logarithm"},
{"X variable: In graph mode used as x, in calculator mode used as last value calculated", "Y variable: In calculator mode used to store last equation", "No help for: Z", "Cosine", "Arc Cosine", "Modulus", "Pi!", "Euler's Number"},
{"The number 7...","The number 8...","The number 9...","Tangent","Arc tangent","Convert float to integer","Round number: <number to round>, <decimal places to round to>","Mean of data: <number 1>, <number 2>, ..."},
{"The number 4...","The number 5...","The number 6...","Addition","Subtraction","Open bracket","Combinations: <n>, <r>","Permutations: <n>, <r>"},
{"The number 1...","The number 2...","The number 3...","Multiplication","Division","Close bracket","Random number: <min value> <max value> (<decimal places>) (defaults to 0 decimal places)","Magnitude of number"},
{"New line","The number 0...","Decimal","Exponent","Root","Comma","Returns help information for button","Equals"}};

int mapped[6][8][4] = {
	6,3, 34,30,   38,3,65,30,    70,3,96,30,    101,3,128,30,    133,3,160,30,    165,3,192,30,		197,3,224,30,		229,3,256,30,
	6,35,34,60,   38,35,65,60,   70,35,96,60,   101,35,128,60,   133,35,160,60,   165,35,192,60,	197,35,224,60,		229,35,256,60,
	6,65,34,93,   38,65,65,93,   70,65,96,93,   101,65,128,93,   133,65,160,93,   165,65,192,93,	197,65,224,93,		229,65,256,93,
	6,98,34,125,  38,98,65,125,  70,98,96,125,  101,98,128,125,  133,98,160,125,  165,98,192,125,	197,98,224,125,		229,98,256,125,
	6,128,34,155, 38,128,65,155, 70,128,96,155, 101,128,128,155, 133,128,160,155, 165,128,192,155,	197,128,224,155,	229,128,256,155,
	6,160,34,187, 38,160,65,187, 70,160,96,187, 101,160,128,187, 133,160,160,187, 165,160,192,187,	197,160,224,187,	229,160,256,187};

void sleep(int time)
{
	while(time != 0)
	{
		time--;
		swiWaitForVBlank();
	}
	return;
}

void setmode()
{
	consoleClear();
	
	if(mode == 1)
	{    
		videoSetMode(MODE_0_2D);
		vramSetBankA(VRAM_A_MAIN_BG);
		consoleInit(&topScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
		consoleSelect(&topScreen);
		
		printf("\t Calculator Mode: Degrees\n\n");
		mode=0;
	}
	else if(mode == 2)
	{
		printf("\t Graph Mode\n\n");
		mode=1;
	}
	else if(mode == 0)
	{
		printf("\t Calculator Mode: Radians\n\n");
		mode=2;				
	}
	
	return;
}

void backspace(int amount)
{
	while(amount != 0)
	{
		amount--;
		printf("\b");
		equation = equation.substr(0, equation.size()-1);
	}
	return;
}

void calcpressed(std::string touched, int x, int y)
{
	if(help)
	{
		help = false;
		printf("%s\n", buttonhelp[x][y].c_str());
	}
	else if(touched == "help")
	{
		help = true;
	}
	else if(touched == "=")
	{
		if(mode != 1)
		{
			lastequation = equation;
			lastanswer = solve(equation, mode);
			printf("=\x1b[41;1m%s\x1b[37;1m\n", lastanswer.c_str());
			lastlength.clear();
			lastlength.push_back(0);
			equation = "";
		}
		else
			graph(equation);
	}
	else if(touched == "B")
	{
		if(lastlength.at(lastlength.size()-1) > 0)
		{
			backspace(lastlength.at(lastlength.size()-1));
			lastlength.pop_back();
		}
	}
	else if(touched == "CA")
	{
		consoleClear();
		lastlength.clear();
		lastlength.push_back(0);
		equation = "";
		setmode();
		setmode();
		setmode();
	}
	else if(touched == "X" && mode != 1)
	{
		equation += lastanswer;
		printf("%s", lastanswer.c_str());
		lastlength.push_back(lastanswer.length());
	}
	else if(touched == "Y")
	{
		for(char& c : lastequation)
		{
			printf("%c", c);
			lastlength.push_back(1);
			equation += c;
		}
	}
	else if(touched == "NL")
	{
		lastlength.clear();
		lastlength.push_back(0);
		equation = "";
		printf("\n");			
	}
	else if(touched == "M")
	{
		consoleClear();
		lastlength.clear();
		lastlength.push_back(0);
		equation = "";
		setmode();
	}
	else
	{
		equation += touched;
		printf("%s", touched.c_str());
		lastlength.push_back(touched.length());
	}
	return;
}

void touch()
{
	touchPosition touch;
	touchRead(&touch);
	if(touch.px==0&&touch.py==0){
		ispressed=false;
		return;
	}
	if(cursorOnScreen==true){
		printf("\b");
		cursorOnScreen=false;
		frameCounter=50;
	}
	for(int x=0; x<8; x++)
		for(int y=0; y<8; y++)
			if(touch.px>mapped[x][y][0] && touch.px<mapped[x][y][2] && touch.py>mapped[x][y][1] && touch.py<mapped[x][y][3])
			{
				if(ispressed == false){
					calcpressed(button[x][y], x, y);
				}
				ispressed = true;
				return;
			}
	return;
}

int main(void) {
	
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);	
		
    consoleInit(&topScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleSelect(&topScreen);
 
    bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    decompress(buttonsBitmap, BG_GFX_SUB,  LZ77Vram);
    
    /*
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
		
    consoleInit(&topScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleSelect(&topScreen);
    */
    
    /*
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
	int sx,sy;
	for(sx = 0; sx < 256; sx++)
	    for(sy = 0; sy < 192; sy++)
			VRAM_A[(sy * 256) + (sx)] = RGB15(31,31,31);
	*/
    
    memcpy(BG_PALETTE_SUB, buttonsPal, sizeof(short)*256);
    
    lastlength.push_back(0);
	
	setmode();
	
	while(1) 
	{
		touch();

		switch(frameCounter){
			case 0:
				printf("\x16");
				cursorOnScreen=true;
				break;
			case 50:
				if(cursorOnScreen==true)
					printf("\b");
				cursorOnScreen=false;
				break;
			case 99:
				frameCounter=-1;
		}
		frameCounter++;
		swiWaitForVBlank();
	}
	return 0;
}
