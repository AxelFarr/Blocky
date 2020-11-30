#define XJOUER 530
#define YJOUER 320
#define XQUITTER 530
#define YQUITTER 440
#define WECRAN 1280
#define HECRAN 720
#define WJOUER 220
#define HJOUER 80
#define WQUITTER 220
#define HQUITTER 80
#define HMENU 100
#define XMENU 1180
#define WBARRE 1009
#define XBARRE 136
#define YBARRE 620
#define OUVERT 1
#define FERME 0
#define OUI 1
#define NON 0
#define GAUCHE 1
#define DROITE 0
#define LIGNES 6
#define COLONNES 10
#define WINVENTAIRE 769
#define HINVENTAIRE 384
#define XINV 0
#define YINV 0
#define DECALAGE 120
#define WMENUJEU 250
#define HMENUJEU 400
#define WBUTMENU 220
#define HBUTMENU 80


//Permet de mettre en pause le programme si besoin (inutile dans la version finale)
void pause();

//Affiche le titre sur le menu
void afficherTitre(SDL_Surface*);

//Affiche le bouton "Jouer" sur le menu
void afficherJouer(SDL_Surface*);

//Affiche le bouton "Quitter" sur le menu
void afficherQuitter(SDL_Surface*);

//Affiche le menu (Quand le jeu est lancé)
void afficherMenu(SDL_Surface*);

//Affiche le menu (Quand le joueur clique sur "Retour Menu" à partir du jeu
void afficherRetourMenu(SDL_Surface*);

//Affiche les items dans la barre inférieure de l'inventaire
void afficherItemsBarre(SDL_Surface*, int matInventaire[LIGNES][COLONNES]);

//Permet de mettre à jour la barre inférieure de l'inventaire
void afficherAntiSelection(SDL_Surface*);

//Affiche la barre inférieure de l'inventaire complète
void afficherBarre(SDL_Surface*, int matInventaire[LIGNES][COLONNES]);

//Affiche le sélecteur sur la barre inférieure de l'inventaire (à sa position initiale)
void afficherSelection(SDL_Surface*);

//Affiche les items dans l'inventaire
void afficherItems(SDL_Surface*, int matInventaire[LIGNES][COLONNES]);

//Affiche la grille de l'inventaire 
void afficherGrille(SDL_Surface*);

//Affiche l'inventaire complet
void afficherInventaire(SDL_Surface*, int matInventaire[LIGNES][COLONNES]);

//Teste si la souris est sur "Quitter"
int ifQuitter(SDL_Rect);

//Teste si la souris est sur "Jouer"
int ifJouer(SDL_Rect);

//Teste si la souris est sur "Menu"
int ifMenu(SDL_Rect);

//Teste si le joueur scroll vers le haut et si le selecteur peut bouger
int scrollUp(SDL_Event, int, SDL_Rect);

//Teste si le joueur scroll vers le bas et si le selecteur peut bouger
int scrollDown(SDL_Event, int, SDL_Rect);

//Met à jour la position du sélecteur
void afficherSelectionDyn(SDL_Surface*, SDL_Rect, int);

//Gère l'ensemble du processus de déplacement du sélecteur quand le joueur scroll
int scroll(SDL_Event event, int, SDL_Surface*, SDL_Rect, int matInventaire[LIGNES][COLONNES]);

//Affiche l'écran de jeu
void afficherJeu(SDL_Surface*, int matInventaire[LIGNES][COLONNES], Sol2D*);

//Initialise les valeurs de matInventaire
void initInv(int matInventaire[LIGNES][COLONNES]);

//Gère la réponse aux actions du joueur
void action(SDL_Surface*);
