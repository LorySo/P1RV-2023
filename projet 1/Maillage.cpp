//#include <GL/gl.h>
#include <GLUT.h>
#include<vector>
#include"DiamantCarre.h"
#include"Vector3D.h"


void calcColor(float hauteur, float& r, float& g, float& b, int maxh) {
    float hauteurNormalisee = hauteur / maxh;
    r = hauteurNormalisee;
    g = 1.0f - hauteurNormalisee;
    b = 1.0f;
}

struct Triangle {
    float x1 = 0.0, y1 = 0.0, z1 = 0.0;
    float x2 = 0.0, y2 = 0.0, z2 = 0.0;
    float x3 = 0.0, y3 = 0.0, z3 = 0.0;
    float r1 = 0.0, g1 = 0.0, b1 = 0.0; //couleur 1er sommet
    float r2 = 0.0, g2 = 0.0, b2 = 0.0;
    float r3 = 0.0, g3 = 0.0, b3 = 0.0;
};

void triangles(const vector<vector<float>>& tab, int terrainSize, float echelle, float hautMax) {
    vector<Triangle> coloredTriangles;

    for (int x = 0; x < terrainSize - 1; x++) {
        for (int z = 0; z < terrainSize - 1; z++) {
            Triangle triangle1;
            triangle1.x1 = x * echelle;
            triangle1.y1 = tab[x][z];
            triangle1.z1 = z * echelle;
            triangle1.x2 = (x + 1) * echelle;
            triangle1.y2 = tab[x + 1][z];
            triangle1.z2 = z * echelle;
            triangle1.x3 = x * echelle;
            triangle1.y3 = tab[x][z + 1];
            triangle1.z3 = (z + 1) * echelle;

            //Mise en place des couleurs
            calcColor(triangle1.y1, triangle1.r1, triangle1.g1, triangle1.b1, hautMax);
            calcColor(triangle1.y2, triangle1.r2, triangle1.g2, triangle1.b2, hautMax);
            calcColor(triangle1.y3, triangle1.r3, triangle1.g3, triangle1.b3, hautMax);
            
            coloredTriangles.push_back(triangle1);

            Triangle triangle2;
            triangle2.x1 = x * echelle;
            triangle2.y1 = tab[x][z + 1];
            triangle2.z1 = (z + 1) * echelle;
            triangle2.x2 = (x + 1) * echelle;
            triangle2.y2 = tab[x + 1][z];
            triangle2.z2 = z * echelle;
            triangle2.x3 = (x + 1) * echelle;
            triangle2.y3 = tab[x + 1][z + 1];
            triangle2.z3 = (z + 1) * echelle;

            //Mise en place des couleurs
            calcColor(triangle2.y1, triangle2.r1, triangle2.g1, triangle2.b1, hautMax);
            calcColor(triangle2.y2, triangle2.r2, triangle2.g2, triangle2.b2, hautMax);
            calcColor(triangle2.y3, triangle2.r3, triangle2.g3, triangle2.b3, hautMax);

            coloredTriangles.push_back(triangle2);
        }
    }
    glBegin(GL_TRIANGLES);
    for (const Triangle& triangle : coloredTriangles) {
        glColor3f(triangle.r1, triangle.g1, triangle.b1);
        glVertex3f(triangle.x1, triangle.y1, triangle.z1);
        glColor3f(triangle.r2, triangle.g2, triangle.b2);
        glVertex3f(triangle.x2, triangle.y2, triangle.z2);
        glColor3f(triangle.r3, triangle.g3, triangle.b3);
        glVertex3f(triangle.x3, triangle.y3, triangle.z3);
    }
    glEnd();
}
