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
    //x,y,rank (1=general,2=lieutenant,3=commander,4=normal),color (black=false,red=true),is king
    {0,0,1,false,false},{2,0,1,false,false},{4,0,1,false,false},{0,6,1,false,false}
};

void dprint( char* text ){
    dbg_sprintf(text, dbgout);
}

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
    //go through every piece in board
    for( int i=0; i++; i < sizeof(board) ){
        //determine what color to use for a piece
        if ( board[i][3] ) {
            gfx_SetColor(224);
        } else {
            gfx_SetColor(0);
        }
        //piece
        gfx_Rectangle(board[i][0]*8,board[i][1]*8,8,8);
    }
}


int main( void ) {
    dprint("start");
    gfx_SetColor(0);
    gfx_Begin();
    gfx_SetDrawBuffer();

    while (step()) {
        dprint("in loop");
        if (partial_redraw){
            gfx_BlitScreen();
        }
        draw(); 
        dprint("draw");
        gfx_SwapDraw(); 
    }

    dprint("program end");
    return 0;
}