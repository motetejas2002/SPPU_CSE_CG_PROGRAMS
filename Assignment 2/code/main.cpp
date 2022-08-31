/**
 Assignment 2: Write C++ program to implement Cohen Southerland
 line clipping algorithm.
 
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

/* Defining the value of Pi */
#define PI 3.1415926535

// Global Initilizations
int n;
float wx1, wy1, wx2, wy2;
float x[20], y[20];

// This is plot function
void plot(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

// Line and Polygon Clipping Function
void lineClipping(int x1, int y1,int x2, int y2) {
	int a[4], b[4], c[4];
	int xa, ya, xb, yb;
	xa = x1;
	ya = y1;
	xb = x2;
	yb = y2;

	for (int i = 0; i < 4; i++) {
		a[i] = 0;
		b[i] = 0;
	}
	
	if (x1 < wx1) {
        a[3] = 1;
    }
	if (x1 > wx2) {
		a[2] = 1;
    }
	if (y1 < wy1) {
		a[1] = 1;
    }
	if (y1 > wy2) {
		a[0] = 1;
    }	
	if (x2 < wx1) {
		b[3] = 1;
    }
	if (x2 > wx2) {
		b[2] = 1;
    }
	if (y2 < wy1) {
		b[1] = 1;
    }
	if (y2 > wy2) {
		b[0] = 1;
    }
		
	if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0) {
		plot(xa, ya, xb, yb);
    }
	else {
        c[0] = a[0] && b[0];
		c[1] = a[1] && b[1];
		c[2] = a[2] && b[2];
		c[3] = a[3] && b[3];

		if (c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 0) {
			if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 1) {
				xa = wx1;
				ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if (a[0] == 0 && a[1] == 0 && a[2] == 1 && a[3] == 0) {
				xa = wx2;
				ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if (a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 0) {
				ya = wy1;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if (a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 0) {
				ya = wy2;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if (a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 1) {
				ya = wy2;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0) {
					xa = wx1;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (a[0] == 1 && a[1] == 0 && a[2] == 1 && a[3] == 0) {
				ya = wy2;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0) {
					xa = wx2;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 1) {
				ya = wy1;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0) {
					xa = wx1;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (a[0] == 0 && a[1] == 1 && a[2] == 1 && a[3] == 0) {
				ya = wy1;
				xa = (ya - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xa - x1) * (y1 - y2) - (ya - y1) * (y1 - y2) != 0) {
					xa = wx2;
					ya = (xa - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			
			if (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 1) {
				xb = wx1;
				yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if (b[0] == 0 && b[1] == 0 && b[2] == 1 && b[3] == 0) {
				xb = wx2;
				yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
			}
			else if (b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 0) {
				yb = wy1;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if (b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 0) {
				yb = wy2;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
			}
			else if (b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 1) {
				yb = wy2;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0) {
					xb = wx1;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (b[0] == 1 && b[1] == 0 && b[2] == 1 && b[3] == 0) {
				yb = wy2;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0) {
					xb = wx2;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 1) {
				yb = wy1;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0) {
					xb = wx1;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			else if (b[0] == 0 && b[1] == 1 && b[2] == 1 && b[3] == 0) {
				yb = wy1;
				xb = (yb - y1) * (x1 - x2) / (y1 - y2) + x1;
				
				if ((xb - x1) * (y1 - y2) - (yb - y1) * (y1 - y2) != 0) {
					xb = wx2;
					yb = (xb - x1) * (y1 - y2) / (x1 - x2) + y1;
				}
			}
			
			plot(xa, ya, xb, yb);
		}
	}
}

/* Rendering Function */
void Render() {
    std::cout << std::endl << "Enter the diagonally opposite co-ordinates of the clipping window" << std::endl;
    std::cout << "Bottom point enter x and y co-ordinats: ";
    std::cin >> wx1 >> wy1;
    std::cout << "Top point enter x and y co-ordinats: ";
    std::cin >> wx2 >> wy2;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << "Enter the number of vertices of the polygon: ";
    std::cin >> n;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << "Enter their coordinates" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << "Point " << i + 1 << ": Enter x and y co-ordinate(space between them): ";
        std::cin >> x[i] >> y[i];
    }


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0 ,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(wx1, wy1);
        glVertex2f(wx2, wy1);
        glVertex2f(wx2, wy2);
        glVertex2f(wx1, wy2);
    glEnd();

    glPointSize(2.0);
    glColor3f(0.0, 0.0 ,1.0);

    if (n == 2) {
        lineClipping(x[0], y[0], x[1], y[1]);
    }
    else {
        for (int i = 0; i < (n - 1); i++) {
            lineClipping(x[i], y[i], x[i + 1], y[i + 1]);
        }
        lineClipping(x[n - 1], y[n - 1], x[0], y[0]);
    }
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);        // Set projection parameters.
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
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
