/**
 Assignment 3: Write C++ program to draw the following pattern.
 Use DDA line and Bresenham‘s circle drawing algorithm.
 Apply the concept of encapsulation.
 
 Editor: NeoVim v0.7.2
 Operating System: MacOS Monterey
 Hardware: MacBook Air Running M1(ARM64)
 Programmer: Mr. Tejas Dattatray Mote
 Comfortable Operating Systems: Linux, MacOS, Linux-Like Systems
 */

#if __APPLE__
    #include <GL/glew.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>


// This is plot function
void plot(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Midpoint Function
void midpoint(float cx, float cy, float r1) {	
	float x, y, p;
	p = 5/4 - r1;
	x = 0;
	y = r1;
	
	while (x <= y) {
		if (p < 0) {
            p += 2 * x + 3;
			x += 1;
		}
		else if (p >= 0) {
			p += 2 * (x - y) + 5;
			x += 1;
			y -= 1;
		}
		
		plot(x, y);
		plot(x, -y);
		plot(-x, y);
		plot(-x, -y);
		plot(y, x);
		plot(-y, x);
		plot(y, -x);
		plot(-y, -x);
	}
}

// Breshnham Circle Algorithm
void Bresnham(float cx, float cy, float r) {
    float x, y, p, delta, delta_dash;

	x = 0;
	y = r;
	p = 2 * (1 - r);

	while (x <= y) {
		if(p < 0) {
            delta = 2 * p + 2 * y - 1;
            if(delta <= 0) {
                x += 1;
				p = p + 2 * x + 1;
			}
			else {
				p = p + 2 * x - 2 * y + 2;
				x += 1;
				y -= 1;
			}
		}
		else if (p > 0) {
			delta_dash = 2 * p - 2 * x - 1;
			if (delta_dash <= 0) {
				x += 1;
				y -= 1;
				p = p + 2 * x - 2 * y + 2;
			}
			else {
                y -= 1;
            }
		}
		else {
			x += 1;
			y -= 1;
			p = p + 2 * x - 2 * y + 2;
		}

		plot(x, y);
		plot(x, -y);
		plot(-x, y);
		plot(-x, -y);
		plot(y, x);
		plot(-y, x);
		plot(y, -x);
		plot(-y, -x);
	}
}

// DDA line drawing algorithm function
void DDA_Line_Drawing(float x1, float y1, float x2, float y2) {
    // Initialization of function variables
    float dy, dx, diffrence, x, y, i, x_inc, y_inc;
    
    dx = x2 - x1;
    dy = y2 - y1;
    
    if (abs(dx) > abs(dy)) {
        diffrence = abs(dx);
    }
    else {
        diffrence = abs(dy);
    }
    
    x_inc = dx / diffrence;
    y_inc = dy / diffrence;
    
    x = x1;
    y = y1;
    
    plot(roundf(x), roundf(y));
    
    for (i = 0; i < diffrence; i++) {
        x = x + x_inc;
        y = y + y_inc;
        
        plot(roundf(x), roundf(y));
    }
    glFlush();
}

void Render() {    
    float r0 = 0;
    std::cout << "Enter the radius of circle: ";
    std::cin >> r0;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);

    glColor3f(0.0f, 0.0f, 1.0f);
    DDA_Line_Drawing(-400.0, 0, 400.0, 0);
    DDA_Line_Drawing(0, -400.0, 0, 400.0);

    glColor3f(0.0f, 0.0f, 0.0f);
    
    /* Outer circle */
    midpoint(0, 0, 2 * r0);

    /* Inner circle */
    midpoint(0, 0, r0);

    /* Triangle */
    DDA_Line_Drawing(0, 2 * r0, 2 * r0 * 0.866, -r0);
    DDA_Line_Drawing(2 * r0 * 0.866, -r0, -2 * r0 * 0.866, -r0);
    DDA_Line_Drawing(-2 * r0 * 0.866, -r0, 0, 2 * r0);

    glFlush();
}



void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);        // Set projection parameters.
    gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("This is our Output Canvas");
    
    init();
    glutDisplayFunc(Render);
    glutMainLoop();
}
