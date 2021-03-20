//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include <fstream>
#include<ctime>
#include<string>
#include <sstream>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
fstream dataFile ;
void Display();
void score_saving( int ) ;
void food1(void) ;
void food2(void) ;
void food3(void) ;
void food4(void) ;
void food5(void) ;
void Bigfood(void) ;
char* from_int_to_string( int x ) ;
//void FoodTimer(void) ;
void snake_movement(void) ;
void out_from_opposite_side(void) ;
//void foodTimer( int );
void self_collision_detector(void) ;
void DisplayPause() ;
void DisplayMenue() ;
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}



int disp = 0 ;
int xc_food1 = 50  , yc_food1 = 50 ;
int xc_food2 = 19  , yc_food2 = 45 ;
int xc_food3 = 10  , yc_food3 = 53 ;
int xc_food4 = 12  , yc_food4 = 10 ;
int xc_food5 = 13  , yc_food5 = 56 ;
int xc_bigfood = 41 , yc_bigfood = 32 ;
int xc = 5 , yc = 5 , direction = 1 ;
int* ptr = &xc ;
int totall = 0 ;
int bigcount = 0 ;
int array[300][2] ;
int l = 4 , ex = 0 , speed = 1500 ;
int detect[300][2] ;




// snake movement function (main logic of game) . 
void snake_movement(void) {
		
	array[0][0] = xc , array[0][1] = yc ;
	int temp0 = array[0][0] , temp1 = array[0][1] ;

	for ( int j = 1 ; j < l ; j ++ ){
			  	
		swap( array[j][0] , temp0 ) ;
		swap( array[j][1] , temp1 ) ;
		detect[j-1][0] = temp0 ; 
		detect[j-1][1] = temp1 ;	
		}
	for ( int k = 0 ; k < l ; k ++ ){
			if ( array[k][0] == xc && array[k][1] == yc ){
				if ( abs(array[k][0] - xc_food1) < 2 && abs(array[k][1] - yc_food1) < 5 )
					DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 9 , colors[4] ) ;	
				else if ( abs(array[k][0] - xc_food2) < 2 && abs(array[k][1] - yc_food2) < 5 )
					DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 9 , colors[4] ) ;
				else if ( abs(array[k][0] - xc_food3) < 2 && abs(array[k][1] - yc_food3) < 5 )
					DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 9 , colors[4] ) ;
				else if ( abs(array[k][0] - xc_food4) < 2 && abs(array[k][1] - yc_food4) < 5 )
					DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 9 , colors[4] ) ;
				else if ( abs(array[k][0] - xc_food5) < 2 && abs(array[k][1] - yc_food5) < 5 )	
						DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 9 , colors[4] ) ;
				else
				DrawCircle( array[k][0]*10-5 , array[k][1]*10-5 , 7 , colors[101] ) ;
				}	
			else
				DrawSquare( array[k][0]*10-10 , array[k][1]*10-10 , 10 , colors[18] ) ;		
			}
	
	return ;	
	}




/*this function will  check if the score is high then it will write it on external
 file else to nothing */
void score_saving( int score ){
	dataFile.open( "dont_change_this.txt" , ios :: in ) ;
	int a ; 
	dataFile >> a ;
	dataFile.close(); 
	if ( a < score ){
		dataFile.open( "dont_change_this.txt" , ios :: out ) ;
		dataFile << score ;
		dataFile.close();
	}

}





void DisplayPause(){

        
    glClearColor(0.0/*Red Component*/, 0.5/*Green Component*/,
            0.5/*Blue Component*/, 1.0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    DrawString( 240, 370, "Paused", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
  if ( disp == 1 )
   	 Display() ;
   glutSwapBuffers(); // do not modify this line..
}




void DisplayMenue(){

        
    glClearColor(0.0/*Red Component*/, 0.5/*Green Component*/,
            0.5/*Blue Component*/, 1.0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
   
   dataFile.open( "dont_change_this.txt" , ios :: in ) ;
	int aa ; 
	dataFile >> aa ;
	dataFile.close(); 
 
    ostringstream oss ;
	
	string my ;
	oss << aa ;
	my = oss.str() ;
   
   //cout << totall ;
   ostringstream ossss ;
	string mystr ;
	ossss << totall ;
	mystr = ossss.str() ;
   
    DrawString( 240, 370, "Game Over :( ", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
    DrawString( 220, 310, "Your score = ", colors[MISTY_ROSE]);
    DrawString( 380, 310, mystr , colors[MISTY_ROSE]);
    DrawString( 220, 270, "Highest score = ", colors[MISTY_ROSE]);
    DrawString( 390, 270, my , colors[MISTY_ROSE]);
   glutSwapBuffers(); // do not modify this line..
}









//food gerating function 1.
void food1(void){

	if ( ( xc_food1 == xc ) && ( yc_food1 == yc ) ) {
		speed -= 30 ; 	
	    l += 2 ;
	    totall += 5 ; 
	    bigcount ++ ;
	    xc_food1 = rand()%64+1 ;           
	    yc_food1 = rand()%64+1 ;

	while( xc_food1 == xc_food2 || xc_food1 == xc_food3 || xc_food1 == xc_food4 || xc_food1 == xc_food5 ||  yc_food1 == yc_food2 ||  			yc_food1 == yc_food3 || yc_food1 == yc_food4 || yc_food1 == yc_food5 || xc_food1 - yc_food1 == xc_food2 - yc_food2 || xc_food1 - 			yc_food1 == xc_food3 - yc_food3 ||  xc_food1 - yc_food1 == xc_food4 - yc_food4 ||  xc_food1 - yc_food1 == xc_food5 - yc_food5 ||  			xc_food1 + yc_food1 == xc_food2 + yc_food2 || xc_food1 + yc_food1 == xc_food3 + yc_food3 ||  xc_food1 + yc_food1 == xc_food4 + 			yc_food4 ||  xc_food1 + yc_food1 == xc_food5 + yc_food5 ){
	
			yc_food1  = rand() % 65 ;
			xc_food1  = rand() % 65 ;
	}
		
	}
	else    
		DrawCircle( xc_food1*10-5 , yc_food1*10-5 , 4 , colors[68] ) ;
	

	return ;
}



//food gerating function 2.
void food2(void){

	if ( ( xc_food2 == xc ) && ( yc_food2 == yc ) ) {
		speed -= 30 ; 	
	    l += 2 ; 
	    totall += 5 ;
	    bigcount ++ ;
	    xc_food2 = rand()%64+1 ;           
	    yc_food2 = rand()%64+1 ;
	while( xc_food2 == xc_food1 || xc_food2 == xc_food3 || xc_food2 == xc_food4 || xc_food2 == xc_food5 ||yc_food2 == yc_food1 || yc_food2 			== yc_food3 || yc_food2 == yc_food4 || yc_food2 == yc_food5 || xc_food2 + yc_food2 == xc_food1 + yc_food1 || xc_food2 + yc_food2 == 			xc_food3 + yc_food3 ||  xc_food2 + yc_food2 == xc_food4 + yc_food4 ||  xc_food2 + yc_food2 == xc_food5 + yc_food5 || xc_food2 - 		yc_food2 == xc_food1 - yc_food1 || xc_food2 - yc_food2 == xc_food3 - yc_food3 ||  xc_food2 - yc_food2 == xc_food4 - yc_food4 ||  			xc_food2 - 	yc_food2 == xc_food5 - yc_food5 ){
	
			yc_food2  = rand() % 65 ;
			xc_food2  = rand() % 65 ;
	}
	}
	else    
		DrawCircle( xc_food2*10-5 , yc_food2*10-5 , 4 , colors[68] ) ;
	

	return ;
}






//food gerating function 3.
void food3(void){

	if ( ( xc_food3 == xc ) && ( yc_food3 == yc ) ) {
		speed -= 30 ; 	
	    bigcount ++ ;
	    l += 2 ; 
	    totall += 5 ;
	    xc_food3 = rand()%64+1 ;           
	    yc_food3 = rand()%64+1 ;
	    while( xc_food3 == xc_food1 || xc_food3 == xc_food2 || xc_food3 == xc_food4 || xc_food3 == xc_food5 || yc_food3 == yc_food1 || 				yc_food3 == yc_food2 || yc_food3 == yc_food4 || yc_food3 == yc_food5 || xc_food3 - yc_food3 == xc_food1 - yc_food1 || xc_food3 				- yc_food3 == xc_food2 - yc_food2 || xc_food3 - yc_food3 == xc_food4 - yc_food4 || xc_food3 - yc_food3 == xc_food5 - yc_food5
	    	|| xc_food3 + yc_food3 == xc_food1 + yc_food1 || xc_food3 + yc_food3 == xc_food2 + yc_food2 || xc_food3 + yc_food3 == xc_food4 				+ yc_food4 || xc_food3 + yc_food3 == xc_food5 + yc_food5 ){
	    	
			yc_food3  = rand() % 65 ;
			xc_food3  = rand() % 65 ;
	
	}
	}
	else    
		DrawCircle( xc_food3*10-5 , yc_food3*10-5 , 4 , colors[68] ) ;
	

	return ;
}


//food gerating function 4.
void food4(void){

	if ( ( xc_food4 == xc ) && ( yc_food4 == yc ) ) {
		
		bigcount ++ ;
		speed -= 30 ; 	
	    l += 2 ; 
	    totall += 5 ;
	    xc_food4 = rand()%64+1 ;           
	    yc_food4 = rand()%64+1 ;
	    while( xc_food4 == xc_food1 || xc_food4 == xc_food2 || xc_food4 == xc_food3 || xc_food4 == xc_food5 ||yc_food4 == yc_food1 || 				yc_food4 == yc_food2 || yc_food4 == yc_food3 || yc_food4 == yc_food5 || xc_food4 +  yc_food4 == xc_food1 + yc_food1 || xc_food4 			+ yc_food4 == xc_food2 + yc_food2 || xc_food4 +  yc_food4 == xc_food3 + yc_food3 || xc_food4 +  yc_food4 == xc_food5 + yc_food5 			|| xc_food4 -  yc_food4 == xc_food1 - yc_food1 || xc_food4 -  yc_food4 == xc_food2 - yc_food2 || xc_food4 -  yc_food4 == 				xc_food3 - yc_food3 || xc_food4 -  yc_food4 == xc_food5 - yc_food5 ) {
	   
		    yc_food4  = rand() % 65 ;
			xc_food4  = rand() % 65 ;
	    
	    }
	}
	else    
		DrawCircle( xc_food4*10-5 , yc_food4*10-5 , 4 , colors[68] ) ;
	

	return ;
}




//food generating function 5.
void food5(void){

	if ( ( xc_food5 == xc ) && ( yc_food5 == yc ) ) {
		speed -= 30 ; 
		bigcount ++ ;	
	    l += 2 ; 
	    totall += 5 ;
	    xc_food5 = rand()%64+1 ;           
	    yc_food5 = rand()%64+1 ;
	    
	while( xc_food5 == xc_food1 || xc_food5 == xc_food2 || xc_food5 == xc_food3 || xc_food5 == xc_food4 || yc_food5 == yc_food1 || yc_food5 		== yc_food2 || yc_food5 == yc_food3 || yc_food5 == yc_food4 || xc_food5 + yc_food5 == xc_food1 + yc_food1 || xc_food5 + yc_food5 == 		xc_food2 + yc_food2 ||  xc_food5 + yc_food5 == xc_food3 + yc_food3 ||  xc_food5 + yc_food5 == xc_food4 + yc_food4 || xc_food5 - 		yc_food5 == xc_food1 - yc_food1 || xc_food5 - yc_food5 == xc_food2 - yc_food2 ||  xc_food5 - yc_food5 == xc_food3 - yc_food3 ||  			xc_food5 - yc_food5 == xc_food4 - yc_food4 ){
		
		   yc_food5  = rand() % 65 ;
		   xc_food5  = rand() % 65 ;
	 
	}
	}
	else    
		DrawCircle( xc_food5*10-5 , yc_food5*10-5 , 4 , colors[68] ) ;
	

	return ;
}




//big food generator
void Bigfood(void){

	if ( ( xc_bigfood == xc ) && ( yc_bigfood == yc ) ) {
		bigcount = 0 ;
		cout << bigcount ;
		speed -= 30 ; 	
	    l += 4 ; 
	    totall += 20 ;
	    xc_bigfood = rand()%64+1 ;           
	    yc_bigfood = rand()%64+1 ;
	    
	    }
	
	else    
		DrawCircle( xc_bigfood*10-5 , yc_bigfood*10-5 , 9 , colors[5] ) ;
	

	return ;
}




/* this function allows snake to come out from opposite side of frame when 
	moved out from other side of frame */
void out_from_opposite_side( void ){
	
	if ( xc >= 65 )
		xc = 0 ;
	else if ( xc <= 0 )
		xc = 65 ;
	else if ( yc > 65 )
		yc = 0;
	else if ( yc <= 0 )	
		yc = 65 ;
	
	return ;	
}



// this function will detect the collision of snake with itself
void self_collision_detector(void){
			
	for ( int q = 0 ; q < l ; q ++ ){		
	
	if ( xc == detect[q][0] && yc == detect[q][1] ){
		cout << '\a' ;
		score_saving( totall ) ;
		ex = 1;
		return ;
	}
	
	}

}






int kk = 1 ; 


//void foodTimer( int mm ) {

	//DrawCircle( 35*10-5 , 13*10-5 , 12 , colors[7]);
	 
		//glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
   //glutTimerFunc( 1000/FPS , foodTimer, 0);
//}







//converter





/*
 * Main Canvas drawing function.
 * */
 
double startx=320,starty=400;


void Display(){

    *ptr = *ptr + 1*direction ;
         
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
    glClearColor(0.5/*Red Component*/, 1/*Green Component*/,
            1/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    //DrawSquare( 300 , 300 ,100,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
    //DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600

	ostringstream oss ;
	string mystr ;
	oss << totall ;
	mystr = oss.str() ;
	
	DrawString( 520 , 5 , "Score = " , colors[131]);
    DrawString( 600 , 5 , mystr  , colors[131]); // this will print given string at x=50 , y=570
    //DrawCircle( xc_head , yc_head , 12 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
    //                    v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
    //DrawLine( 550 , 50 ,  550 , 600 , 20 , colors[MISTY_ROSE] );
// glutTimerFunc(5000 / FPS, foodTimer, 0);
    snake_movement() ; 
    food1() ;
    food2() ;
    food3() ;
    food4() ;
    food5() ;
    if ( bigcount >= 5 )
    	Bigfood() ;
    
   
    //foodTimer(5000) ;
    out_from_opposite_side() ;
    self_collision_detector() ;
    if (ex == 1)
    	 glutDisplayFunc(DisplayMenue);
    if ( disp == 1 ){	 
    	 disp = 0 ;
    	 DisplayPause();
    }
   glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
											// what to do when left key is pressed...
      
      if (!(direction == 1 && ptr == &xc ) ){
     
      direction = -1 ;
      ptr = &xc ;
   	  }
      
      
    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	
		if (!( direction == -1 && ptr == &xc ) ){
	
		direction = 1 ;
		ptr = &xc ;
	    } 
	   
		
    } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        
        if (!( direction == -1 && ptr == &yc ) ){
        
        direction = 1 ;
        ptr = &yc ;
        }
        
        
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
	
		if (!( direction == 1 && ptr == &yc) ){
		
		direction = -1 ;
		ptr = &yc ;
		}
	
	
    }
    

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if ( key == KEY_ENTER)
    {  
		   	disp = 1 ;   	
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(speed / FPS, Timer, 0);
}












/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
  //glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
// tell library which function to call for drawing Canvas.  
   	glutDisplayFunc(Display);
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	
//   glutTimerFunc(50000, foodTimer, 0);
    glutTimerFunc(500.0 / 60, Timer, 0);
     
// now handle the control to library and it will call our registered functions when
// it seems necessary... 
	
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

