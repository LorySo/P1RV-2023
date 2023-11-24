#include <Windows.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include "Vector3D.h"

using namespace std;
#include <GL/gl.h>
#include <GLUT.h>

#include "DiamantCarre.h"
#include"Maillage.h"


const int terrainSize = 513;  //taille de la map
const float echelle = 0.2;
vector<vector<float>> tableau(terrainSize, vector<float>(terrainSize, 0.0f)); //matrice des hauteurs à 0


// angles de rotation (coordonnees spheriques) pour calculer le vecteur vision de la camera
float angleTheta = 0.0f;
float anglePhi = 0.0f;

// Camera viewing vectors
Vector3D forwardView;
Vector3D rightView;
// On garde le vecteur "up" du monde : 0 1 0
Vector3D upWorld(0.0, 1.0, 0.0);

// Difference "Fly" vs. "FPS" modes
Vector3D forwardMove;
Vector3D rightMove;

// Camera position
Vector3D camPos;
Vector3D targetPos;

// Sensibilite de deplacement
float moveSensitivity;
float mouseRotSensitivity;

// Déplacement "Fly" ou "FPS" ?
bool flyMode = false;
bool unflyMode = false;

// les increments des angles theta et phi sont egaux a 0 quand on n'appuie sur aucune touche
float deltaTheta = 0.0f;
float deltaPhi = 0.0f;

// increments de deplacement
// remis a 0 quand on appuis sur rien
float deltaMove = 0;
float deltaStrafe = 0.0f;

// coordonnes de la souris au moment du clic gauche
int xOrigin = -1;
int yOrigin = -1;

// Fonction de redimensionnement de la fenetre
void redimensionner(int w, int h) {

    // On evite une division par 0
    // la fenetre ne peut avoir une largeur de 0
    if (h == 0)
        h = 1;

    // Calcul du ratio
    float ratio = (w * 1.0) / h;

    // On passe en mode "matrice de projection"
    glMatrixMode(GL_PROJECTION);

    // on charge la matrice identite
    glLoadIdentity();

    // on definit le viewport pour prendre toute la fenetre
    glViewport(0, 0, w, h);

    // on definit la projection perspective
    gluPerspective(65.0f, ratio, 0.1f, 100.0f);

    // on repasse en mode "matrice modelview"
    glMatrixMode(GL_MODELVIEW);
}

// Fonction de gestion du deplacement de la camera
void cameraMovement(float dM, float dS) {
    // est-on en "fly" mode ou non ?
    if (flyMode) {
        camPos += upWorld * moveSensitivity;
        targetPos += upWorld * moveSensitivity;
    }

    else if (unflyMode) { 
        camPos -= upWorld * moveSensitivity;
        targetPos -= upWorld * moveSensitivity;
    }

    // Mettre a jour la cible

}

// fonction d'affichage de notre scene 3D
void affichageScene() {

    // On gere le deplacement de la camera
    cameraMovement(deltaMove, deltaStrafe);

    // On efface les tampons de couleur et de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // On passe en matice modelview
    // On passe en matice modelview
    glMatrixMode(GL_MODELVIEW);

    // on charge la matrice identite
    glLoadIdentity();

    // on definit la position de la camera et où elle regarde
    gluLookAt(camPos.getVx(), camPos.getVy(), camPos.getVz(),
        targetPos.getVx(), targetPos.getVy(), targetPos.getVz(),
        upWorld.getVx(), upWorld.getVy(), upWorld.getVz());


    // On dessine les triangles
    triangles(tableau, terrainSize, echelle, 10.0);

    // on echange les tampons d'affichage
    glutSwapBuffers();
}

// Fonction de gestion du clavier (touche enfoncee)
void clavier(unsigned char key, int xx, int yy) {

    // Quelle touche a ete appuyee ?
    switch (key) {
        // Q et S on strafe
    case 'q':
    case 'Q':
        camPos -= rightMove * moveSensitivity;
        targetPos -= rightMove * moveSensitivity;


        break;
    case 'd':
    case 'D':
        camPos += rightMove * moveSensitivity;
        targetPos += rightMove * moveSensitivity;
        break;

        // Z et S avance/recule
    case 'z':
    case 'Z':
        camPos += forwardMove * moveSensitivity;
        targetPos += forwardMove * moveSensitivity;

        break;
    case 's':
    case 'S':
        camPos -= forwardMove * moveSensitivity;
        targetPos -= forwardMove * moveSensitivity;

        break;

        // F pour activer/desactiver le mode "fly"
    case 'f':
    case 'F':
        flyMode = !flyMode;

        // On force la camera a revenir sur le sol 

        // Y pour activer/desactiver le mode "unfly"
    case 'y':
    case 'Y':
        unflyMode = !unflyMode;

        // On force la camera a revenir sur le sol
        break;

        // ESCAPE on termine l'application
    case 27:
        exit(0);
        break;
    }

}

// Fonction de gestion du clavier (touche relachee)
void clavierUp(unsigned char key, int x, int y) {

    // Que faire quand une touche est relachee
    switch (key) {

        // On arrete de strafer
    case 'q':
    case 'd':
    case 'Q':
    case 'D':
        deltaStrafe = 0;
        break;

        // On arrete d'avance/reculer
    case 'z':
    case 's':
    case 'Z':
    case 'S':
        deltaMove = 0;
        break;
    }
}


// Fonction de gestion du clavier (touche speciale appuyee)
void specialKeyDown(int key, int xx, int yy) {

    switch (key) {
        // Deplacement avance/recul
    case GLUT_KEY_UP:
        camPos += forwardMove * moveSensitivity;
        targetPos += forwardMove * moveSensitivity;
        break;
    case GLUT_KEY_DOWN:
        camPos -= forwardMove * moveSensitivity;
        targetPos -= forwardMove * moveSensitivity;
        break;

        // Strafe a gauche/droite
    case GLUT_KEY_RIGHT:
        camPos += rightMove * moveSensitivity;
        targetPos += rightMove * moveSensitivity;
        break;
    case GLUT_KEY_LEFT:
        camPos -= rightMove * moveSensitivity;
        targetPos -= rightMove * moveSensitivity;
        break;
    default:
        break;
    }

}

// Fonction de gestion du clavier (touche speciale relachee)
//bjr
void releaseSpecialKey(int key, int x, int y) {

    switch (key) {
        // On remet le delate deplacement a 0
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        deltaMove = 0;
        break;

        // On remet le delta strafe a 0
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        deltaStrafe = 0;
        break;
    }
}

// Fonction de gestion du deplacement de la souris
void deplacementSouris(int x, int y) {

    // On ne fait quelque chose que si l'utilisateur a deja clique quelque part avec le bouton gauche
    if (xOrigin >= 0 || yOrigin >= 0) {

        // mise a jour des deltas des angles theta et
        float oldTheta = angleTheta;
        angleTheta = (x - xOrigin) * mouseRotSensitivity + deltaTheta;
        anglePhi = (y - yOrigin) * mouseRotSensitivity + deltaPhi;


        // Calcul du nouveau vecteur vision :
        // En se basant sur les coordonnes spheriques
         //Vector3D dist(camPos, targetPos);
        /* targetPos.setVtargetPos.getV) + cos(anglePhi) * dist.length());
         targetPos.setVz(targetPos.getVz() + sin(anglePhi) * dist.length());
         targetPos.setVy(targetPos.getVy() + cos(angleTheta) * dist.length());*/

         // normalisation du vecteur forward
        forwardView.setVx(sin(angleTheta) * cos(anglePhi));
        forwardView.setVy(sin(anglePhi));
        forwardView.setVz(cos(angleTheta) * cos(anglePhi));
        forwardView.normalize();

        // Up ne change pas
        // et right est le cross product entre up et forward
        rightView = forwardView.crossProduct(upWorld).normalize();

        // Mettre a jour la cible = point "vise" par la camera
        // xOrigin = x;
         //yOrigin = y;
        targetPos = camPos + forwardView;

        // Pour le mode "FPS" on force les deplacements a avoir lieu sur le plan de la camera !
        // Mise a jour des vecteurs forwardMove et rightMove
        if (flyMode) {
            forwardMove = forwardView;
            rightMove = rightView;
        }
        else {
            forwardMove.setVx(forwardView.getVx());
            forwardMove.setVz(forwardView.getVz());
            forwardMove.setVy(0.0);
        }
    }
}

// Fonction de gestion des clics souris
void clicSouris(int button, int state, int x, int y) {

    // On ne fait quelque chose que sur le bouton gauche de la souris
    if (button == GLUT_LEFT_BUTTON) {

        // si on relache le bouton on met a jour les angles theta et phi
        // et on dit que l'on a pas clique
        if (state == GLUT_UP) {
            deltaTheta = angleTheta;
            deltaPhi = anglePhi;
        }
        else {// state = GLUT_DOWN
            // si l'on a clique sur le bouton gauche
            // on garde les positions de la souris au moment du clic gauche
            xOrigin = x;
            yOrigin = y;
        }
    }
}


int main(int argc, char** argv) {
    diamantCarre(tableau);
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("FPS Camera");

    // enregistrement des callbacks d'affichage
    // de redimensionnement et d'idle
    glutDisplayFunc(affichageScene);
    glutReshapeFunc(redimensionner);
    glutIdleFunc(affichageScene);

    // pour que l'on puisse rester appuye sur les touches
    glutIgnoreKeyRepeat(1);

    // Declaration des callbacks clavier
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(releaseSpecialKey);

    // declarationdes callbacks souris
    glutMouseFunc(clicSouris);
    glutMotionFunc(deplacementSouris);

    // on active le tampon de profondeur
    glEnable(GL_DEPTH_TEST);

    // on initialise la position de la camera
    camPos = Vector3D(0, 0.3, 2);

    // on initialise les vecteurs 'view'
    forwardView = Vector3D(0, 0, -1);
    upWorld = Vector3D(0, 1, 0);
    rightView = Vector3D(1, 0, 0);

    // Pour le FPS mode
    forwardMove = Vector3D(0, 0, -1);
    rightMove = Vector3D(1, 0, 0);

    // on initialise la cible a partir de la camera et du vecteur vision
    targetPos = camPos + forwardView;

    // Initialisation des "constantes"
    moveSensitivity = 2.0f;
    mouseRotSensitivity = 0.001f;

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}

//int main() {
//    diamantCarre(tableau);
//
//    for (int i = 0; i < terrainSize; i++) { //afficher tableau
//        for (int j = 0; j < terrainSize; j++) {
//            cout << tableau[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
