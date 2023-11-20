//Taille du tableau
int nbIteration;
//Taille du dessin
int longueur=700;
int largeur=700;
int hauteur=500;
int perturbationHauteur;
int typePerturbation;
//Plus grande hauteur d'une montagne
float higher;
//Rotation du dessin
float rotationX=PI/3;
float rotationY=0;
float rotationZ=0;
float vitesseRotation=0.0;
//Autre variable du dessin
boolean move=true;
int textu=0;
float[][] graine= new float[2][2];
float[][] tmpGraine= new float[2][2];

void setup(){
  size(700,500,P3D);
  newStart(3,100,1);
}

//Cette fonction permet de relancer le calcul dans le code javascript de la page web
//On ne peut pas le relancer avec setup() qui ne s'execute qu'une fois
void newStart(int setnbIteration, int setPerturbationHauteur, int setTypePerturbation){
  higher=0;
  nbIteration=setnbIteration;
  typePerturbation=setTypePerturbation;
  perturbationHauteur=setPerturbationHauteur;
  graine= new float[2][2];
  //Initialisation graine
  graine[0][0]=random(hauteur);
  graine[0][1]=random(hauteur);
  graine[1][0]=random(hauteur);
  graine[1][1]=random(hauteur);
  //Croissance de la graine
  for(int i=0;i<=nbIteration;i++){
    diamant();
    carre();
  };
  //Getting highest montain
  for(int i=0;i<=graine.length-1;i++){
    for(int j=1;j<=graine[i].length-1;j++){
      if(higher<graine[i][j]){higher=graine[i][j];};
    };
  };
}

//Comment perturber chaque noeud
float choixPerturbation(int i, int j){
  float tmp=0.0;
  if(typePerturbation==1){tmp=random(-perturbationHauteur,perturbationHauteur);}else{tmp=random(-perturbationHauteur/(graine.length-1),perturbationHauteur/(graine.length-1));}
  return tmp;
}

//Diamant
void diamant(){
  print("diamant");
  //Ajouter une valeur 0 entre chaque colonne
  for(int i=0;i<=graine.length-1;i++){
    for(int j=1;j<=graine[i].length-1;j=j+2){
      graine[i]=(float[]) splice(graine[i],0.0,j);
    }
  };
  float[][] tmpGraineNew= new float[graine[0].length][2*(graine.length-1)+1];
  
  for(int i=1;i<=graine.length-1;i++){
    float [][] tmpLigne=new float[1][graine[0].length];
    for(int k=0;k<=tmpLigne[0].length-1;k++){
      tmpLigne[0][k]=0.0;
    }
    //Introduction d'une valeur alleatoire au centre d'un carre
    for(int j=1;j<=tmpLigne[0].length-2;j=j+2){
       tmpLigne[0][j]=(graine[i-1][j-1]+graine[i-1][j+1]+graine[i][j-1]+graine[i][j+1])/4+choixPerturbation(i,j);
    }
    tmpGraineNew[2*i-2]=graine[i-1];
    tmpGraineNew[2*i-1]=tmpLigne[0];
    
  }
    tmpGraineNew[tmpGraineNew.length-1]=graine[graine.length-1];
    graine=tmpGraineNew;
    afficheConsole();
}

//Carre
void carre(){
  print("carré");
  for(int i=0;i<=graine.length-1;i++){
    for(int j=0;j<=graine[i].length-1;j++){
      if(graine[i][j]==0.0){
        //si ligne paire, si ligne impaire
        //Premiere ligne
        if(i==0)
        {
          graine[i][j]=(graine[i][j-1]+graine[i][j+1]+graine[i+1][j])/3+choixPerturbation(i,j);
        }
        else
        {
          //Dernière ligne
          if(i==graine.length-1)
          {
            graine[i][j]=(graine[i][j-1]+graine[i][j+1]+graine[i-1][j])/3+choixPerturbation(i,j);
          }
          else
          {
            //Premiere colonne
            if(j==0)
            {
              graine[i][j]=(graine[i-1][j]+graine[i+1][j]+graine[i][j+1])/3+choixPerturbation(i,j);
            }
            else
            {
              //Derniere colonne
              if(j==graine[i].length-1)
              {
                graine[i][j]=(graine[i-1][j]+graine[i+1][j]+graine[i][j-1])/3+choixPerturbation(i,j);
              }
              else
              //Cases pas sur les bords
              {
                graine[i][j]=(graine[i-1][j]+graine[i+1][j]+graine[i][j-1]+graine[i][j+1])/4+choixPerturbation(i,j);
              }
            }
          }
        }
      }
    }
  }
  afficheConsole();
} 

void afficheConsole(){
for(int i=0;i<=graine.length-1;i++){
    print("\n");
    //Lecture colonne j de la ligne i
    for(int j=0;j<=graine[i].length-1;j++){
      print(/*"i=",i," j=",j," ",*/graine[i][j]," ");
    };
  };
  print("\n");
}

void setVitesseRotation(int choix){
if(choix==0){vitesseRotation=0;}
else{vitesseRotation=0.01;}
}

void draw(){
  stroke(0);
  strokeWeight(1);
  if(move){
    float largeurCarreau=largeur/(graine[0].length-1);
    float longueurCarreau=longueur/(graine.length-1);
    background(0,0,200);
    translate(largeur/2,longueur/3,-higher/2);
	rotationZ=(rotationZ+vitesseRotation);
    rotateX(rotationX);
    //rotateY(rotationY);
    rotateZ(rotationZ);
    smooth();
      for(int i=0;i<=graine.length-2;i++){
        for(int j=0;j<=graine[0].length-2;j++){
          //Pour chaque carré, on dessine 2 triangles pour déformer la surface
          beginShape();
            //Couleur
            fill(255);
            //Texture
            vertex(j*largeurCarreau-largeur/2,i*longueurCarreau-longueur/2,graine[i][j]-hauteur/2);
            vertex((j+1)*largeurCarreau-largeur/2,i*longueurCarreau-longueur/2,graine[i][j+1]-hauteur/2);
            vertex(j*largeurCarreau-largeur/2,(i+1)*longueurCarreau-longueur/2,graine[i+1][j]-hauteur/2);
          endShape(CLOSE);
          beginShape();
            vertex((j+1)*largeurCarreau-largeur/2,i*longueurCarreau-longueur/2,graine[i][j+1]-hauteur/2);
            vertex((j+1)*largeurCarreau-largeur/2,(i+1)*longueurCarreau-longueur/2,graine[i+1][j+1]-hauteur/2);
            vertex(j*largeurCarreau-largeur/2,(i+1)*longueurCarreau-longueur/2,graine[i+1][j]-hauteur/2);
          endShape(CLOSE);
        };
        //Carreaux sur le côté droit
        beginShape();
          vertex((graine[0].length-1)*largeurCarreau-largeur/2,i*longueurCarreau-longueur/2,graine[i][graine[0].length-1]-hauteur/2);
          vertex((graine[0].length-1)*largeurCarreau-largeur/2,(i+1)*longueurCarreau-longueur/2,graine[i+1][graine[0].length-1]-hauteur/2);
          vertex((graine[0].length-2)*largeurCarreau-largeur/2,(i+1)*longueurCarreau-longueur/2,graine[i+1][graine[0].length-2]-hauteur/2);
        endShape(CLOSE);
      };
  }
 }
