#include "App.h"

static App* singleton;



void explode(int value){
    
    if (!singleton->fire->done()){
        singleton->fire->advance();
        singleton->redraw();
        glutTimerFunc(32, explode, value);
    }
}

void move(int value){
    
    if (singleton->isMoving){
        singleton->fire->incY();
        singleton-> redraw();
        glutTimerFunc(32, move, value);
    }
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    
    singleton = this;
    mx = 0.0;
    my = 0.0;

    shroom = new TexRect("mushroom.bmp", 1, 1, 0, 0.0, 0.5, 0.5);
    fire = new TexRect("fireball.bmp", 6, 6, 0, 0.0, 0.5, 0.5);
    
    isMoving = false;
    
    glutTimerFunc(20, move, 1);

}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);

    shroom->draw();
    fire->draw();

    
    glDisable(GL_TEXTURE_2D);
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
        if (shroom->contains(mx, my))
        {
            delete shroom;

            fire->draw();
            fire->reset();
            explode(0);
        }
        else
        {
            isMoving=false;
        }
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::idle(){
    redraw();
}

void App::keyUp(unsigned char key) {

}

void App::keyPress(unsigned char key) {
    if (key == 27){
        
        delete fire;
        
        exit(0);
    }
}
