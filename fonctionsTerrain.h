#define DIMSOL 15
#define NBSOL 800
#define LARGEURMAP 500

#define VERT 1
#define VERT2 11
#define ROUGE 2
#define BLEU 3
#define BLEU2 13
#define BLEU3 23
#define GRIS1 4
#define GRIS2 5
#define GRIS3 6
#define NOIR 7
#define MARRON 8
#define MARRON2 18
#define JAUNE 9
#define JAUNEPALE 19
#define BLANC 39

#define DARKER 1
#define NORMAL 2

#define SOLEIL 1
#define NUAGE 2

#define PENTU 1
#define PLAT 2

#define OUVERT 1
#define FERME 0


typedef int Sol[NBSOL];
typedef int Sol2D[NBSOL][LARGEURMAP];
typedef int INVENTAIRE[6][10];

void initSol();
void perlinNoise1D(int*, int);
void handleEvents();
void createRect(SDL_Surface*, int , int, char, int);
float tirage(float, float);
int interpolation(int*, int);
void ValeursLimitesEtInterpolation(int*, int, int);
SDL_Surface* initFenetre();
void initSol2D(SDL_Surface*, int*, Sol2D);
void creuseGaleries(Sol2D);
void GenerationMatriceBruit(Sol2D, int, int, int, int, int);
int noise2(int x, int y);
float lin_inter(float, float, float);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);
float perlin2d(float, float, float, int);
void ajoutEau(Sol2D);
void randomisationCouches(Sol2D);
void ajoutArbres(Sol2D);
