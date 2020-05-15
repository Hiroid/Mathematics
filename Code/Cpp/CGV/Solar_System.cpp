// Copyright 2020, All Rights Reserved
// Code by Liangxuan Guo, 2017302509
// For Course Project of Computer Graphics and Visualization
// /*
#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<soil.h>

double xx = 8, yy = 8, zz = 8;
double p_earth = 0, self_earth = 0, p_moon = 0, self_moon = 0;
double p_Mercury = 1, self_Mercury = 0;
double p_Satellite = 2, self_Satellite = 0;
double p_Venus = 3, self_Venus = 0;
double step = 0.01f; bool active = 0;
GLUquadricObj* e_tex = gluNewQuadric();
const int img_num = 3;
GLuint all_texture[img_num];

void init(void) {
    // Sun
    all_texture[0] = SOIL_load_OGL_texture (
        "sun.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glBindTexture(GL_TEXTURE_2D, all_texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Earth
    all_texture[1] = SOIL_load_OGL_texture(
        "earth_4k.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glBindTexture(GL_TEXTURE_2D, all_texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Moon
    all_texture[2] = SOIL_load_OGL_texture(
        "moon.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    glBindTexture(GL_TEXTURE_2D, all_texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glLightModeli(0x81F8, 0x81F9);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void material_sun() {
    GLfloat sun_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat sun_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   
    GLfloat sun_mat_emission[] = { 1.0f, 1.0f, 1.0f, 0.0f }; 
    GLfloat sun_mat_shininess = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
}

void material_planet() {
    GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f }; 
    GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat earth_mat_shininess = 50.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void sun() {
    glPushMatrix();
    material_sun();
    gluQuadricTexture(e_tex, GLU_TRUE);
    // glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, all_texture[0]);
    gluSphere(e_tex, 1.0f, 50.0f, 50.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    // glPopAttrib();
    gluQuadricTexture(e_tex, GLU_FALSE);
    glPopMatrix();
}

void earth() {
    glPushMatrix();

    material_planet();
    glEnable(GL_LIGHTING);

    glRotatef((GLfloat)p_earth, 0.0, 0.0, 1.0);
    glTranslatef(5, 0.0, 0.0);
    
    glPushMatrix();
    glRotatef((GLfloat)self_earth, 0.0, 1.0, 0.0);
    glPopMatrix();

    gluQuadricTexture(e_tex, GLU_TRUE);
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, all_texture[1]);
    gluQuadricDrawStyle(e_tex, GLU_FILL);
    gluSphere(e_tex, 0.4, 50, 50);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
    gluQuadricTexture(e_tex, GLU_FALSE);

    
    glPushMatrix();
    glRotatef((GLfloat)p_moon, 0.0, 0.0, 1.0);
    glTranslatef(2, 0.0, 0.0);
    glPushMatrix();
    glRotatef((GLfloat)self_moon, 0.0, 1.0, 0.0);
    glPopMatrix();
    gluQuadricTexture(e_tex, GLU_TRUE);
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, all_texture[2]);
    gluQuadricDrawStyle(e_tex, GLU_FILL);
    gluSphere(e_tex, 0.2, 50, 50);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)p_Satellite, 0.0, 0.0, 1.0);
    glTranslatef(1.5, 0.0, 0.0);
    glPushMatrix();
    glRotatef((GLfloat)self_Satellite, 0.0, 1.0, 0.0);
    glPopMatrix();
    gluQuadricTexture(e_tex, GLU_TRUE);
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, all_texture[2]);
    gluQuadricDrawStyle(e_tex, GLU_FILL);
    gluSphere(e_tex, 0.05, 50, 50);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPopMatrix();
}

void display(void) {
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt((GLfloat)xx, (GLfloat)yy, (GLfloat)zz, 0.0, 0.0, 0.0, 0.0, 1.0, 50.0);
    
    glEnable(GL_LIGHT0);
    GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);

    sun();
    earth();

    glutSwapBuffers();

    p_earth += step * (float)active;
    self_earth += step * (float)active;

    p_moon += 2 * step * (float)active;
    self_moon += 2 * step * (float)active;

    p_Satellite += 4 * step * (float)active;
    self_Satellite += 4 * step * (float)active;

}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 0.0);
}

void processSpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_PAGE_UP) {
        p_earth -= 100 * step;
    }
    if (key == GLUT_KEY_PAGE_DOWN) {
        p_earth += 100 * step;
    }
    if (key == GLUT_KEY_UP) {
        p_moon -= 200 * step;
    }
    if (key == GLUT_KEY_DOWN) {
        p_moon += 200 * step;
    }
    if (key == GLUT_KEY_LEFT) {
        p_Satellite -= 250 * step;
    }
    if (key == GLUT_KEY_RIGHT) {
        p_Satellite += 250 * step;
    }
}

void processNormalkeys(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case'z':
            active = !active;
            break;
        case'w':
            xx += 0.5;
            break;
        case's':
            xx -= 0.5;
            break;
        case'a':
            yy += 0.5;
            break;
        case'd':
            yy -= 0.5;
            break;
        case'q':
            zz += 0.5;
            break;
        case'e':
            zz -= 0.5;
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalkeys);

    glutMainLoop();
    return 0;
}
