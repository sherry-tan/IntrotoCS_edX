//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle in pixels
#define P_HEIGHT 8
#define P_WIDTH 75

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// max ball speed
#define LIMIT 1.0

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    //initialize ball velocity
    double v_x = drand48() * LIMIT;
    double v_y = 2.0;
        
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
         // check for mouse event
         GEvent event = getNextEvent(MOUSE_EVENT);

         // if we heard one
         if (event != NULL)
         {
            // if the event was movement, ensure paddle follows cursor and doesn't go beyond window
            if (getEventType(event) == MOUSE_MOVED)
                {
                    double x = getX(event) - P_WIDTH / 2;
                    double y = HEIGHT - (2*P_HEIGHT);
               
                    if (x < 0 )
                        setLocation(paddle, 0, y);
                    else if (x > WIDTH - P_WIDTH)
                        setLocation(paddle, WIDTH - P_WIDTH, y);
                    else
                        setLocation(paddle, x, y);        
                }
         }
           
         // move ball
         move(ball, v_x, v_y);

         // bounce off top edge of window
         if (getY(ball) < 0)
         {
            v_y = -v_y;
         }
         
         // bounce off left and right edge of window
         if (getX(ball) < 0 || getX(ball) > WIDTH - (2*RADIUS) )
         {
            v_x = -v_x;
         }
                
         // bounce off collision object    
         if (detectCollision(window, ball)!=NULL)
         {
            GObject collide = detectCollision(window, ball);
            
            //bounce off paddle       
            if(collide == paddle)
            {
                v_y = -v_y;
            }
            //bounce off brick, removing brick from window and updating score
            else if (strcmp(getType(collide), "GRect")==0)
            {
                v_y = -v_y;
                removeGWindow(window, collide);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
            }
         } 

         // linger before moving again
         pause(5);
        
         //pause game and decrease lives if ball goes past bottom of window        
         if (getY(ball) > HEIGHT)
         { 
            lives--;
            
            waitForClick();
            
            //reinitalializes ball at centre of window when game resumes
            if(lives > 0)
            {
                setLocation(ball, WIDTH/2, HEIGHT/2);
                pause(1000); 
            } 
         }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initializes width and height of bricks
    int w = 0.90 * WIDTH / COLS;
    int h = 0.90 * 0.15 * HEIGHT / ROWS;
    
    //initalizes distance between top left corner of adjacent bricks
    int d_w = WIDTH / COLS;
    int d_h = 0.15 * HEIGHT / ROWS;
    
    //initializes color
    string color[] = {"RED", "BLUE", "GREEN", "YELLOW", "ORANGE"};
    
    for (int i =0 ; i < ROWS; i++)
        {
            for (int j =0; j < COLS; j++)
               {
                   GRect brick = newGRect(j * d_w, i * d_h + (HEIGHT/10), w, h);
                   setFilled(brick, true);
                   setColor(brick, color[i]);
                   add(window, brick);
               }
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
     GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
     setFilled(ball, true);
     setColor(ball, "BLACK");
     add(window, ball);
    
     return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    GRect paddle = newGRect((WIDTH - P_WIDTH)/2, HEIGHT - (2*P_HEIGHT), P_WIDTH, P_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);

    // update label
    setLabel(label, "0");
    
    // center label
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT - getHeight(label)) / 2.5;
    setLocation(label, x, y);

    // linger for 100 milliseconds
    pause(100);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
