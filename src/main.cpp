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
uint8_t board[24][4] = {
    {0,0,1,false},{2,0,1,false},{4,0,1,false},{0,6,1,false}
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
void draw(){
    for( int i=0; i++; i < sizeof(board) ){
        switch ( board[i][3] ){
            case 1:
                dprint("inside test case");
                gfx_SetColor(0);
                break;
            
            case 3:
                gfx_SetColor(224);
                break;
            
            default:
                break;
        }
        gfx_Rectangle(board[i][0],board[i][1],8,8);
    }
}


int main( void ) {
    dprint("start");
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