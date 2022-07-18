#include "def.h"
#include <string.h>
#include <string>
#include <tonc.h>

class TextArea{
public:
		int tileId;
		int startX;
		int startY;
		int endX;
		int endY;

		TextArea(){}
		TextArea(int tid,int sx, int sy, int ex, int ey){
			tileId = tid;

			startX = sx;
			endX = ex;
			startY = sy;
			endY = ey;
		}
};

TextArea *textArea = nullptr;

void aprint(std::string str, int x, int y){
	u16 * dest = (u16 * )se_mem[29];
	dest+= 32*y+x;
	for(int i = 0; i < (int) str.length(); i++){
		int c = str[i]-32;
		int letter = 0xf000;
		letter += c;
		*dest++ = letter;
	}
}

void aprintf(int n, int x, int y){
	aprint(std::to_string(n),x,y);
}

void aprintColor(std::string str, int x, int y,int palette){
	u16 * dest = (u16*) se_mem[29];
	dest+=32*y+x;
	for(int i = 0; i < (int) str.length(); i++){
		int c = str[i]-32;
		int letter = 0xf000-0x1000*palette;
		letter += c;
		*dest++ = letter;
	}
}

void clearText(){
    memset32(&se_mem[29],0x0000,32*20);

	if(textArea == nullptr)
		return;

	memset16(&tile_mem[2][textArea->tileId],0,(textArea->endX)*(textArea->endY)*2);

	u16* dest = (u16*) se_mem[29];
	int counter = 0;
	for(int i = textArea->startY; i <= textArea->endY; i++)
		for(int j = textArea->startX; j <= textArea->endX; j++)
			dest[i*32+j] = 0xf000 + textArea->tileId + counter++;

}

void setSmallTextArea(int tid, int startX,int startY,int endX,int endY){
	if(textArea != nullptr)
		delete textArea;

	textArea = new TextArea(tid,startX,startY,endX,endY);

	//set screen entry to tile mem section, needs to happen once unless overriden
	u16* dest = (u16*) se_mem[29];
	int counter = 0;
	for(int i = startY; i <= endY; i++)
		for(int j = startX; j <= endX; j++)
			dest[i*32+j] = 0xf000 + textArea->tileId + counter++;
}

void aprints(std::string str, int x, int y, int colorIndex){//x and y are pixel
	if(textArea == nullptr)
		return;
	TILE* dest2;

    //width of current line, acts like a cursor position so that
    //text is drawn on the next line if w is greater than text area width
	int w = 0;

	//Empty everything from the start and below of writing area
	memset32(&tile_mem[2][textArea->tileId+(y/8)*(textArea->endX-1)+x/8],0,(textArea->endX-1)*((textArea->endY-1)-y/8)*8);

	for(int i = 0; i < (int) str.length(); i++){
		if(str[i] == '\n'){
			w = 0;
			y += 8;
			continue;
		}else if(str[i] == ' '){
			w += 4;
			continue;
		}

		u16 character = font3x5[str[i]-32];

        //least significant byte determines if the character should be
        //drawn 1 pixel down (for characters like q g j)
		int drop = character & 1;

		int counter = 0;
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 3; k++){
				dest2 = (TILE *) &tile_mem[2][textArea->tileId+((y+j+drop)/8)*(textArea->endX-1)+(x+w+k)/8];

                //figure out if pixel at j,k should be drawn
                int draw = (character >> (15-counter)) & 1;

				if(draw)
					dest2->data[(y+j+drop)%8] |= colorIndex << (((x+w+k)%8)*4);
				counter++;
			}
		}
		w+=4;
	}
}

const u16 fontTiles[1552] __attribute__((aligned(4)))=
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x3000,0x0033,0x2000,0x0032,0x3000,0x0033,
	0x3200,0x0032,0x3200,0x0032,0x3300,0x0033,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0032,0x3200,0x0322,0x2200,0x0332,0x3220,0x0322,
	0x2230,0x0332,0x3220,0x0032,0x3230,0x0033,0x3300,0x0000,
	0x2000,0x0003,0x2200,0x0322,0x2320,0x0333,0x2230,0x0032,
	0x2300,0x0323,0x2220,0x0332,0x2330,0x0033,0x3000,0x0003,

	0x0000,0x0000,0x0000,0x3200,0x3200,0x3320,0x3300,0x0332,
	0x2000,0x0033,0x3200,0x0323,0x3320,0x0330,0x0330,0x0000,
	0x0000,0x0000,0x2200,0x0003,0x3320,0x0032,0x2230,0x0033,
	0x2320,0x0323,0x3320,0x0332,0x2230,0x3223,0x3300,0x3333,
	0x3200,0x0000,0x3200,0x0000,0x3300,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0032,0x2000,0x0003,0x3200,0x0000,0x3200,0x0000,
	0x3200,0x0000,0x2300,0x0003,0x3000,0x0032,0x0000,0x0033,

	0x2000,0x0003,0x3000,0x0032,0x0000,0x0323,0x0000,0x0320,
	0x0000,0x0320,0x0000,0x0332,0x2000,0x0033,0x3000,0x0003,
	0x2000,0x0003,0x2320,0x0323,0x3230,0x0332,0x2300,0x0033,
	0x3200,0x0032,0x2320,0x0323,0x2330,0x0333,0x3000,0x0003,
	0x0000,0x0000,0x2000,0x0003,0x2000,0x0003,0x2220,0x0322,
	0x2330,0x0333,0x2000,0x0003,0x3000,0x0003,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x2000,0x0003,0x2000,0x0003,0x3000,0x0003,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2220,0x0322,
	0x3330,0x0333,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x3200,0x0000,0x3300,0x0000,
	0x0000,0x0000,0x0000,0x3200,0x0000,0x3320,0x0000,0x0332,
	0x2000,0x0033,0x3200,0x0003,0x3320,0x0000,0x0330,0x0000,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x3220,0x3222,
	0x2220,0x3223,0x3220,0x3223,0x2230,0x3322,0x3300,0x0333,

	0x0000,0x0000,0x2200,0x0032,0x2300,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x2220,0x0022,0x3220,0x3223,0x0330,0x3220,
	0x2200,0x3322,0x3220,0x0333,0x2220,0x3222,0x3330,0x3333,
	0x0000,0x0000,0x2220,0x0322,0x3220,0x3223,0x2330,0x3322,
	0x3000,0x3223,0x3220,0x3220,0x2220,0x3322,0x3330,0x0333,
	0x0000,0x0000,0x0000,0x0322,0x2000,0x0322,0x2200,0x0322,
	0x3220,0x0322,0x2220,0x3222,0x3330,0x3322,0x0000,0x0333,

	0x0000,0x0000,0x2220,0x3222,0x3220,0x3333,0x2220,0x3222,
	0x3330,0x3223,0x3220,0x3220,0x2220,0x3322,0x3330,0x0333,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x0333,0x2220,0x3222,
	0x3220,0x3223,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x2220,0x0322,0x3330,0x0322,0x2000,0x0332,
	0x2000,0x0032,0x2200,0x0033,0x2200,0x0003,0x3300,0x0003,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x2230,0x3322,
	0x3220,0x3223,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,

	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x3220,0x3220,
	0x2220,0x3222,0x3330,0x3223,0x2200,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x3200,0x0000,0x3300,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x3200,0x0000,0x3300,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x3200,0x0000,0x3300,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x3200,0x0000,0x3200,0x0000,0x3300,0x0000,
	0x0000,0x0032,0x2000,0x0033,0x3200,0x0003,0x3320,0x0000,
	0x3230,0x0000,0x2300,0x0003,0x3000,0x0032,0x0000,0x0033,

	0x0000,0x0000,0x0000,0x0000,0x2220,0x0322,0x3330,0x0333,
	0x2220,0x0322,0x3330,0x0333,0x0000,0x0000,0x0000,0x0000,
	0x2000,0x0003,0x3000,0x0032,0x0000,0x0323,0x0000,0x3230,
	0x0000,0x3320,0x0000,0x0332,0x2000,0x0033,0x3000,0x0003,
	0x2200,0x0032,0x3220,0x0322,0x3220,0x0322,0x3330,0x0332,
	0x2000,0x0033,0x3000,0x0003,0x2000,0x0003,0x3000,0x0003,
	0x2200,0x0032,0x3320,0x0323,0x2032,0x3232,0x3232,0x3223,
	0x3232,0x3220,0x2320,0x3322,0x2200,0x0332,0x3300,0x0033,

	0x0000,0x0000,0x2000,0x3222,0x2200,0x3223,0x3220,0x3223,
	0x2220,0x3222,0x3220,0x3223,0x3220,0x3220,0x3330,0x3330,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3223,0x2220,0x3322,
	0x3220,0x3223,0x3220,0x3220,0x2220,0x3322,0x3330,0x0333,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3223,0x3220,0x3330,
	0x3220,0x3220,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x3220,0x3220,
	0x3220,0x3220,0x3220,0x3220,0x2220,0x3322,0x3330,0x0333,

	0x0000,0x0000,0x2200,0x0322,0x3220,0x0333,0x2220,0x0322,
	0x3220,0x0333,0x3220,0x0000,0x2220,0x0322,0x3330,0x0333,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x0333,0x2220,0x0322,
	0x3220,0x0333,0x3220,0x0000,0x3220,0x0000,0x3330,0x0000,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3333,0x3220,0x3222,
	0x3220,0x3220,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x3200,0x3220,0x3220,0x3220,0x2220,0x3222,
	0x3220,0x3223,0x3220,0x3220,0x3220,0x3220,0x3330,0x3330,

	0x0000,0x0000,0x0000,0x0032,0x2000,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x0000,0x0032,0x2000,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2200,0x0033,0x3300,0x0003,
	0x0000,0x0000,0x3200,0x3220,0x3220,0x3322,0x2220,0x0332,
	0x2220,0x0032,0x3220,0x0322,0x3220,0x3223,0x3330,0x3330,
	0x0000,0x0000,0x3200,0x0000,0x3220,0x0000,0x3220,0x0000,
	0x3220,0x0000,0x3220,0x0000,0x2220,0x3222,0x3330,0x3333,

	0x0000,0x0000,0x0032,0x3200,0x0322,0x3220,0x3222,0x3222,
	0x2222,0x3222,0x2322,0x3223,0x3322,0x3223,0x0333,0x3330,
	0x0000,0x0000,0x3220,0x3220,0x2220,0x3223,0x2220,0x3222,
	0x3220,0x3222,0x3220,0x3223,0x3220,0x3230,0x3330,0x3300,
	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x3220,0x3220,
	0x3220,0x3220,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3223,0x3220,0x3220,
	0x2220,0x3322,0x3220,0x0333,0x3220,0x0000,0x3330,0x0000,

	0x0000,0x0000,0x2200,0x0322,0x3220,0x3223,0x3220,0x3220,
	0x2220,0x3222,0x3220,0x3223,0x2230,0x3222,0x3300,0x3333,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3223,0x3220,0x3220,
	0x2220,0x3322,0x3220,0x3223,0x3220,0x3220,0x3330,0x3330,
	0x0000,0x0000,0x2200,0x3222,0x3220,0x3223,0x2220,0x3332,
	0x2330,0x3222,0x3220,0x3223,0x2220,0x3322,0x3330,0x0333,
	0x0000,0x0000,0x2200,0x3222,0x2300,0x3332,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,

	0x0000,0x0000,0x3200,0x3220,0x3220,0x3220,0x3220,0x3220,
	0x3220,0x3220,0x3220,0x3220,0x2230,0x3322,0x3300,0x0333,
	0x0000,0x0000,0x3200,0x3220,0x3220,0x3220,0x3220,0x3220,
	0x3220,0x3220,0x2230,0x3322,0x2300,0x0332,0x3000,0x0033,
	0x0000,0x0000,0x0320,0x3220,0x0322,0x3220,0x2322,0x3223,
	0x2322,0x3223,0x2222,0x3222,0x3223,0x3322,0x3330,0x0333,
	0x0000,0x0000,0x3220,0x3220,0x2220,0x3223,0x2330,0x3332,
	0x2000,0x0032,0x3220,0x3222,0x3220,0x3223,0x3330,0x3330,

	0x0000,0x0000,0x3200,0x3220,0x3220,0x3220,0x3220,0x3220,
	0x2230,0x3322,0x2300,0x0332,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x2220,0x0322,0x3330,0x0322,0x2000,0x0332,
	0x2200,0x0033,0x3220,0x0003,0x2220,0x0322,0x3330,0x0333,
	0x2200,0x0032,0x3200,0x0033,0x3200,0x0000,0x3200,0x0000,
	0x3200,0x0000,0x3200,0x0000,0x2200,0x0032,0x3300,0x0033,
	0x0000,0x0000,0x0320,0x0000,0x3230,0x0000,0x2300,0x0003,
	0x3000,0x0032,0x0000,0x0323,0x0000,0x3230,0x0000,0x3300,

	0x2000,0x0322,0x3000,0x0323,0x0000,0x0320,0x0000,0x0320,
	0x0000,0x0320,0x0000,0x0320,0x2000,0x0322,0x3000,0x0333,
	0x0000,0x0000,0x2000,0x0003,0x3200,0x0032,0x3320,0x0323,
	0x0332,0x3230,0x0033,0x3300,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2220,0x0322,0x3330,0x0333,
	0x0000,0x0000,0x0000,0x0032,0x0000,0x0323,0x0000,0x0330,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x2000,0x0032,0x3000,0x0322,0x2000,0x0322,
	0x3200,0x0322,0x3200,0x0322,0x2300,0x0322,0x3000,0x0333,
	0x0000,0x0000,0x2000,0x0003,0x2200,0x0003,0x2200,0x0322,
	0x2200,0x0323,0x2200,0x0323,0x2200,0x0332,0x3300,0x0033,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0322,0x2200,0x0333,
	0x2200,0x0003,0x2200,0x0003,0x2200,0x0322,0x3300,0x0333,
	0x0000,0x0000,0x0000,0x0320,0x0000,0x0322,0x2000,0x0322,
	0x3200,0x0322,0x3200,0x0322,0x2300,0x0322,0x3000,0x0333,

	0x0000,0x0000,0x0000,0x0000,0x2000,0x0032,0x2200,0x0323,
	0x2200,0x0322,0x2200,0x0333,0x2200,0x0322,0x3300,0x0333,
	0x0000,0x0000,0x0000,0x0322,0x2000,0x0332,0x2200,0x0322,
	0x2300,0x0332,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x2000,0x0322,0x3200,0x0322,0x3200,0x0322,
	0x2300,0x0322,0x3000,0x0322,0x2000,0x0332,0x3000,0x0033,
	0x0000,0x0000,0x2000,0x0003,0x2200,0x0003,0x2200,0x0032,
	0x2200,0x0323,0x2200,0x0323,0x2200,0x0323,0x3300,0x0333,

	0x0000,0x0000,0x2000,0x0032,0x3000,0x0033,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x0000,0x0032,0x2000,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2200,0x0033,0x3300,0x0003,
	0x0000,0x0000,0x2000,0x0003,0x2200,0x0003,0x2200,0x0323,
	0x2200,0x0332,0x2200,0x0323,0x2200,0x0323,0x3300,0x0333,
	0x0000,0x0000,0x2200,0x0003,0x2000,0x0032,0x2000,0x0032,
	0x2000,0x0032,0x2000,0x0032,0x2000,0x0032,0x3000,0x0033,

	0x0000,0x0000,0x0000,0x0000,0x2200,0x3222,0x3220,0x3232,
	0x3220,0x3232,0x3220,0x3232,0x3220,0x3232,0x3330,0x3333,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0322,0x2200,0x0323,
	0x2200,0x0323,0x2200,0x0323,0x2200,0x0323,0x3300,0x0333,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0032,0x2200,0x0323,
	0x2200,0x0323,0x2200,0x0323,0x2300,0x0332,0x3000,0x0033,
	0x0000,0x0000,0x2000,0x0322,0x2200,0x0323,0x2200,0x0323,
	0x2200,0x0332,0x2200,0x0033,0x2200,0x0003,0x3300,0x0003,

	0x0000,0x0000,0x2000,0x0322,0x3200,0x0322,0x3200,0x0322,
	0x2200,0x0322,0x3300,0x0322,0x0000,0x0322,0x0000,0x0333,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0323,0x2200,0x0332,
	0x2200,0x0033,0x2200,0x0003,0x2200,0x0003,0x3300,0x0003,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0322,0x2200,0x0333,
	0x2200,0x0322,0x3300,0x0322,0x2200,0x0322,0x3300,0x0333,
	0x0000,0x0000,0x0000,0x0032,0x2000,0x0032,0x2200,0x0322,
	0x2300,0x0332,0x2000,0x0032,0x2000,0x0322,0x3000,0x0333,

	0x0000,0x0000,0x0000,0x0000,0x2000,0x0323,0x2200,0x0323,
	0x2200,0x0323,0x2200,0x0323,0x2300,0x0322,0x3000,0x0333,
	0x0000,0x0000,0x0000,0x0000,0x2000,0x0323,0x2200,0x0323,
	0x2200,0x0323,0x2300,0x0332,0x2000,0x0032,0x3000,0x0033,
	0x0000,0x0000,0x0000,0x0000,0x3200,0x3200,0x3220,0x3200,
	0x3220,0x3232,0x2220,0x3222,0x2230,0x3323,0x3300,0x0333,
	0x0000,0x0000,0x0000,0x0000,0x2200,0x0323,0x2200,0x0323,
	0x2300,0x0332,0x2200,0x0323,0x2200,0x0323,0x3300,0x0333,

	0x0000,0x0000,0x0000,0x0000,0x3200,0x0322,0x3200,0x0322,
	0x2200,0x0322,0x3300,0x0322,0x2200,0x0332,0x3300,0x0033,
	0x0000,0x0000,0x0000,0x0000,0x2200,0x0322,0x3300,0x0322,
	0x2000,0x0332,0x2200,0x0033,0x2200,0x0322,0x3300,0x0333,
	0x2000,0x0032,0x2200,0x0033,0x2300,0x0003,0x3200,0x0003,
	0x2300,0x0003,0x2200,0x0003,0x2300,0x0032,0x3000,0x0033,
	0x2000,0x0003,0x2000,0x0003,0x2000,0x0003,0x2000,0x0003,
	0x2000,0x0003,0x2000,0x0003,0x2000,0x0003,0x3000,0x0003,

	0x2000,0x0032,0x3000,0x0322,0x0000,0x0332,0x0000,0x0323,
	0x0000,0x0332,0x0000,0x0322,0x2000,0x0332,0x3000,0x0033,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x3220,0x0000,
	0x2332,0x3203,0x3033,0x3322,0x0000,0x0333,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x3220,0x0322,0x3320,0x3232,
	0x3220,0x3232,0x3320,0x3232,0x3220,0x3322,0x3330,0x0333,
	0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,
	0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,
};

const u16 font3x5 [96] = {
	0x0000,
	0x4904,
	0xb400,
	0xbefa,
	0x7bbc,
	0xa54a,
	0x555c,
	0x4800,
	0x2922,
	0x4494,
	0x1550,
	0xba0,
	0x0028,
	0x0380,
	0x0004,
	0x2548,
	0x76dc,
	0x592e,
	0xc5ce,
	0xc51c,
	0x92f2,
	0xf39c,
	0x73dc,
	0xe548,
	0x77dc,
	0x779c,
	0x0820,
	0x0828,
	0x2a22,
	0x1c70,
	0x88a8,
	0xe504,
	0x56c6,
	0x77da,
	0x775c,
	0x7246,
	0xd6dc,
	0x73ce,
	0x73c8,
	0x72d6,
	0xb7da,
	0xe92e,
	0x64d4,
	0xb75a,
	0x924e,
	0xbeda,
	0xd6da,
	0x56d4,
	0xd7c8,
	0x76f6,
	0x775a,
	0x711c,
	0xe924,
	0xb6d6,
	0xb6d4,
	0xb6fa,
	0xb55a,
	0xb524,
	0xe54e,
	0x6926,
	0x9112,
	0x6496,
	0x5400,
	0x000e,
	0x4400,
	0x0ed6,
	0x9adc,
	0x0e46,
	0x2ed6,
	0x0ee6,
	0x5668,
	0x559d,
	0x935a,
	0x4122,
	0x4129,
	0x975a,
	0x4922,
	0x17da,
	0x1ada,
	0x0ad4,
	0xd6e9,
	0x76b3,
	0x1748,
	0x0f1c,
	0x9a46,
	0x16d6,
	0x16dc,
	0x16fa,
	0x155a,
	0xb595,
	0x1cae,
	0x6b26,
	0x4924,
	0xc9ac,
	0x5400,
	0x56f0,
};
