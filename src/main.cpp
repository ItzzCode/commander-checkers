/*
 *--------------------------------------
 * Program Name: Commander Checkers
 * Author: Itzz-Me
 * License: GPL 3.0
 * Description:
 *--------------------------------------
*/

#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <debug.h>

bool partial_redraw = false;
uint8_t board[24][5] = {
    //x,y,rank (1=general,2=lieutenant,3=commander,4=normal),color (black=0,red=1),is king
    {1,0,4,0,0},{3,0,4,0,0},{5,0,4,0,0},{7,0,4,0,0},
    {0,1,4,0,0},{2,1,4,0,0},{4,1,4,0,0},{6,1,4,0,0},
    {1,2,4,0,0},{3,2,4,0,0},{5,2,4,0,0},{7,2,4,0,0},
    {0,5,4,1,0},{2,5,4,1,0},{4,5,4,1,0},{6,5,4,1,0},
    {1,6,4,1,0},{3,6,4,1,0},{5,6,4,1,0},{7,6,4,1,0},
    {0,7,4,1,0},{2,7,4,1,0},{4,7,4,1,0},{6,7,4,1,0},
};
int xOffset = 160-64;
int yOffset = 120-64;
uint8_t select;
uint8_t selectedChecker = 25;
uint8_t moveSelect[2];
bool hasSelected = false;

/**
 * @brief TODO
 * 
 */
void begin(){
    //TODO
}

/**
 * @brief TODO
 * 
 */
void end(){
    //TODO
}

/**
 * @brief handles inputs
 * 
 * @warning is bracket hell.
 */
void inputHandling(){
	//input handling (and bracket hell) :>
	if( kb_IsDown(kb_Key2nd) ){
		if( !hasSelected ){
			selectedChecker = select;
			hasSelected = true;
		} else if( (moveSelect[0]+moveSelect[1])%2 != 0 ){
            bool inOtherChecker = false;
			for( int i=0; i<24; i++ ){
                if( (board[i][0] == board[select][0]) && (board[i][1] == board[select][1]) ){
                    inOtherChecker = true;
                }
                if (!inOtherChecker){
                    board[select][0] = moveSelect[0];
			        board[select][1] = moveSelect[1];
                    selectedChecker = 25;
			        hasSelected = false;
                }
            }
		}
	} else if( kb_IsDown(kb_KeyAlpha) ){
		hasSelected = false;
        selectedChecker = 25;
	} else if( hasSelected ){
		if( kb_IsDown(kb_KeyLeft) && (moveSelect[0]-1 >= 0) ){
            moveSelect[0]--;
		} else if( kb_IsDown(kb_KeyRight) && (moveSelect[0]+1 <= 7) ){
			moveSelect[0]++;
		} else if( kb_IsDown(kb_KeyUp) && (moveSelect[1]-1 >= 0) ){
			moveSelect[1]--;
		} else if( kb_IsDown(kb_KeyDown) && (moveSelect[1]+1 <= 7) ){
			moveSelect[1]++;
		}
	} else if( kb_IsDown(kb_KeyLeft) && (select-1 >= 0) ){
		select--;
	} else if( kb_IsDown(kb_KeyRight) && (select+1 <= 23) ){
		select++;
	}
    dbg_sprintf(dbgout, "%i-1 = %i\n", moveSelect[0], moveSelect[0]-1);
	delay(100);
}

/**
 * @brief handle logic
 * 
 * @return true 
 * @return false 
 */
bool step(){
    dbg_sprintf(dbgout, "inside of step()\n");

    //find and handle the input from keypad
    kb_Scan();
    if( !kb_IsDown(kb_KeyClear) ){
        dbg_sprintf(dbgout, "user did not exit\n");
        inputHandling();
        return true;
    } else {
        return false;
    }
}

/**
 * @brief handle graphics
 * 
 */
void draw(){
    //draw the board
    gfx_FillScreen(255);
    for( int i = 0; i < 8; i++ ){
        for( int e = 0; e < 8; e++ ){
            if ( (i+e)%2 == 0){
                gfx_SetColor(127);
            } else {
                gfx_SetColor(128);
            }
            gfx_FillRectangle(xOffset+i*16, yOffset+e*16, 16, 16);
        }
    }

    //draw the pieces
    dbg_sprintf(dbgout,"in draw\n");
    //go through every piece in board
    for( int i=0; i < (int)sizeof(board) / 5; i++ ){
        //determine what color to use for a piece 
        if ( board[i][3] ) {
            gfx_SetColor(224);
        } else {
            gfx_SetColor(0);
        }
        //piece
        gfx_FillCircle(board[i][0]*16+xOffset+8,board[i][1]*16+yOffset+8,8);
    }

    dbg_sprintf(dbgout, "%i, %i, %i\n", moveSelect[0], moveSelect[1], select);

    //show select box
    if ( hasSelected ){
        gfx_SetColor(6);
        gfx_Rectangle(xOffset+moveSelect[0]*16, yOffset+moveSelect[1]*16, 16, 16);
        //this seems quite odd and i think there's a better way to do this
        gfx_Rectangle(xOffset+moveSelect[0]*16-1, yOffset+moveSelect[1]*16-1, 18, 18); 
    } else {
        gfx_SetColor(196);
        gfx_Rectangle(board[select][0]*16+xOffset,board[select][1]*16+yOffset,16,16);
        //this also seems quite odd and i think there's a better way to do this
        gfx_Rectangle(board[select][0]*16-1+xOffset,board[select][1]*16-1+yOffset,18,18);
    }

    //show selected checker (copy paste of previous code, only with selectedChecker as the coords)
    gfx_SetColor(168);
    gfx_Rectangle(board[selectedChecker][0]*16+xOffset,board[selectedChecker][1]*16+yOffset,16,16);
    gfx_Rectangle(board[selectedChecker][0]*16-1+xOffset,board[selectedChecker][1]*16-1+yOffset,18,18);
}

/**
 * @brief main
 * 
 * @return int 
 */
int main( void ) {
    dbg_sprintf(dbgout,"began main\n");
    gfx_SetColor(0);
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_FillScreen(255);

    while (step()) {
        dbg_sprintf(dbgout,"in loop\n");
        if (partial_redraw){
            gfx_BlitScreen();
        }
        draw(); 
        
        dbg_sprintf(dbgout,"swap draw\n");
        gfx_SwapDraw(); 
    }

    gfx_End();
    return 0;
}