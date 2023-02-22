#include <iostream>
#include <fstream>
using namespace std;

/*
    DESIR Adjy Sedar
    Groupe 2
    Licence 2 Info
*/

struct Maillon {
  int col; // numéro de la colonne à laquelle correspond le coefficient
  int coef;// coefficient de la matrice
  Maillon *next = nullptr;// élément suivant non nul sur la ligne
};

struct MatriceAdjacence {
  int ordre; // nombre de sommets du graphe
  Maillon* *lignes;// tableau à allouer de taille "ordre", représentant les lignes de la matrice
};

int getCoeff(MatriceAdjacence mat, int l, int c);


bool estSymetrique(MatriceAdjacence mat){ // verifie si la matrice est symetrique
  for(int i=0; i< mat.ordre; i++){
    Maillon *ptr = nullptr;

    for(ptr = mat.lignes[i]; ptr!= nullptr; ptr = ptr->next){
      //Recupere les valeurs dans la liste des lignes
      int col = ptr->col;
      int coef = ptr->coef; 
      if (getCoeff(mat, col, i) != coef) // Verifie si les coordonnees existe dans la colonne symetrique
        return false;
    }
  }
  return true;
}
bool estComplet(MatriceAdjacence mat){ // Verifie si la matrice est complet
  for(int i = 0; i<mat.ordre; i++)
      for(int j = 0; j<mat.ordre; j++)
          if((i != j) && getCoeff(mat, i, j) == 0)
            return false;
  return true;// aucun 0 trouvé
}

// hypothèses :
// - mat contient une matrice
// - l et c sont des coordonnées valides
int getCoeff(MatriceAdjacence mat, int l, int c){
  for(Maillon *ptr = mat.lignes[l]; ptr != nullptr; ptr = ptr->next)
    if(ptr->col == c)
      return ptr->coef;
  return 0; // on a pas trouvé la colonne c
}

void creerMatrice(MatriceAdjacence &m, int taille){
  m.ordre = taille; // la taille de la matrice
  m.lignes = new Maillon*[taille]; // Creer le tableau des lignes
  for(int i=0; i<taille; i++)
    m.lignes[i] = nullptr; // initialise le tableau des lignes a null pointer
}

void effacerMatrice(MatriceAdjacence &mat){ // Permet d'effacer la matrice
  for(int i=0; i<mat.ordre; i++){
    while(mat.lignes[i] != nullptr){
      Maillon *ptr = mat.lignes[i];
      mat.lignes[i] = mat.lignes[i]->next; 
      delete ptr; // Efface les maillons de la liste
    }
  }
  mat.ordre = 0; // mettre l'ordre a 0
  delete [] mat.lignes; // Efface le tableau de lignes
  
}

bool charger(char *nom, MatriceAdjacence &mat){ // Permet de remplir la matrice
  ifstream fichier;//flot d’entrée

  // ouverture du fichier en mode lecture
  fichier.open(nom, ios::in);
    
  //test d'ouverture du fichier
  if( !fichier.is_open()){
    cout << "erreur d'ouverture "<< endl;
    return false;
  }

  int taille;
  fichier >> taille ; // recupere la première valeur du fichier comme la taille de la matrice
  creerMatrice( mat,  taille);

  for(int i=0; i<taille; i++){
    for(int j=0; j<taille; j++){
      int val;
      fichier>>val;

      if(val != 0){
        Maillon *maillon = new Maillon;
        maillon->col = j;
        maillon->coef = val;// coefficient de la matrice

        Maillon *prev = nullptr;
        for(Maillon *ptr = mat.lignes[i]; ptr != nullptr; ptr = ptr->next) // parcours ma liste
          prev = ptr;
        
        if(prev == nullptr) // Verifie si la tete est vide
          mat.lignes[i] = maillon;
        else
          prev->next = maillon; // Racorde mon maillon a la liste
               
      }
    }   
  }

  //fermeture du fichier
   fichier.close();
    return true;
}


void afficher(MatriceAdjacence mat){ // Permet afficher la matrice
  for(int i=0; i<mat.ordre; i++){
    Maillon *ptr = mat.lignes[i];
    for(int j=0; j<mat.ordre; j++){
      if(ptr != nullptr && j == ptr->col){
        cout<<ptr->coef; // Affiche les valeurs dont la colonne existe dans ma liste
        ptr = ptr->next;
      }
      else
        cout<<"0"; // Affiche 0 si il ne se trouve pas
      
      cout<<" ";
    }
    cout<<endl;
  }
}

int main(int argc, char *argv[]){
  
  if(argc!=2){
    printf("Erreur - il manque le nom du fichier à lire\n");
    return -1;
  }

  MatriceAdjacence mat;

  creerMatrice(mat, 3); 
  afficher(mat); 

  effacerMatrice(mat); 
  cout<<endl;
  
  if(!charger(argv[1], mat)) return -1;
  
  afficher(mat);


  if(estSymetrique(mat))
    cout << "symétrique" << endl;
  else
    cout << "non symétrique" << endl;

  if(estComplet(mat))
    cout << "complet" << endl;
  else
    cout << "incomplet" << endl;

  effacerMatrice(mat);
  cout<<"fin";
  return 1;
}


/*
bool estSymetrique(MatriceAdjacence mat){
  for(int i=0; i< mat.ordre; i++){
    Maillon *ptr = nullptr;

    for(ptr = mat.lignes[i]; ptr!= nullptr; ptr = ptr->next){
      int col = ptr->col;
      int coef = ptr->coef;

      Maillon *ptr2 = nullptr;
      for(ptr2 = mat.lignes[col]; ptr2 != nullptr; ptr2 = ptr2->next ){
        if(ptr2->col == i && ptr2->coef == coef)
          break;
      }
      if(ptr2 == nullptr)
        return false;
    }
  }
  return true;
}
*/