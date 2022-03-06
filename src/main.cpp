/*
 *--------------------------------------
 * Program Name: Commander Checkers
 * Author: Itzz-Me
 * License: GPL 3.0
 * Description:
 *--------------------------------------
*/

#include <graphx.h>
#include <debug.h>

bool partial_redraw = false;
uint8_t board[24][5] = {
    //x,y,rank (1=general,2=lieutenant,3=commander,4=normal),color (black=0,red=1),is king
    {0,0,4,0,0},{2,0,4,0,0},{4,0,4,0,0},{6,0,4,0,0},
    {1,1,4,0,0},{3,1,4,0,0},{5,1,4,0,0},{7,1,4,0,0},
    {0,2,4,0,0},{2,2,4,0,0},{4,2,4,0,0},{6,2,4,0,0},
    {0,5,4,1,0},{2,5,4,1,0},{4,5,4,1,0},{6,5,4,1,0},
    {1,6,4,1,0},{3,6,4,1,0},{5,6,4,1,0},{7,6,4,1,0},
    {0,7,4,1,0},{2,7,4,1,0},{4,7,4,1,0},{6,7,4,1,0},
};
int xOffset = 160-64;
int yOffset = 120-64;

void begin(){
    //TODO
}

void end(){
    //TODO
}

bool step(){
    return true;
}

//handle graphics
void draw(){
    gfx_FillScreen(255);
    dbg_sprintf(dbgout,"in draw");
    //go through every piece in board
    for( int i=0; i < sizeof(board) / 5; i++ ){
        //determine what color to use for a piece
        if ( board[i][3] ) {
            gfx_SetColor(224);
        } else {
            gfx_SetColor(0);
        }
        //piece
        gfx_FillCircle(board[i][0]*16+xOffset,board[i][1]*16+yOffset,8);
    }
}


int main( void ) {
    dbg_sprintf(dbgout,"began main");
    gfx_SetColor(0);
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_FillScreen(255);

    while (step()) {
        dbg_sprintf(dbgout,"in loop");
        if (partial_redraw){
            gfx_BlitScreen();
        }
        draw(); 
        
        dbg_sprintf(dbgout,"swap draw");
        gfx_SwapDraw(); 
    }
    return 0;
}