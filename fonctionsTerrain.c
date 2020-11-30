#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>

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

typedef int Sol[NBSOL];
typedef int Sol2D[NBSOL][LARGEURMAP];
typedef int INVENTAIRE[6][10];

Sol2D* initSol(SDL_Surface *fenetre);
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

///// Partie Baptiste /////

int SEED = 0;

int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

int noise2(int x, int y)
{
    int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}


void perlinNoise1D(int* psol, int type){
	srand(time(NULL));
	for(int i = 0; i<NBSOL; i++){
		*(psol + i) = 0;
	}
	int* psolTemp = malloc(sizeof(int)*NBSOL);

	//On définit la pente
	int taille1 = 200, taille2 = 32, taille3 = 16, taille4 = 8, taille5 = 4, taille6 = 2;
	int amp1, amp2, amp3, amp4, amp5, amp6;
	if(type == PENTU){
		amp1 = 10, amp2 = 1, amp3 = 1, amp4 = 1, amp5 = 1, amp6 = 1;
	}
	else{
		amp1 = 1, amp2 = 0, amp3 = 0, amp4 = 1, amp5 = 0, amp6 = 1;
	}


	ValeursLimitesEtInterpolation(psolTemp, taille1, amp1);
	for(int i=0; i<NBSOL; i++){
		*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille2, amp2);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille3, amp3);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille4, amp4);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille5, amp5);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille5, amp5);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	ValeursLimitesEtInterpolation(psolTemp, taille6, amp6);
		for(int i=0; i<NBSOL; i++){
			*(psol+i) += *(psolTemp+i);
	}
	//décallage
	int bloc1 = *(psol+10);
	for(int i=0; i<NBSOL; i++){
		*(psol+i) -= (bloc1 + 70);
	}

}
void ValeursLimitesEtInterpolation(int* psol, int taille, int amp){
	int a = 0;
	//Creation des valeurs limites de l'octave
	for(int i=0; i<NBSOL; i++){
		*(psol+i) = 0;
	}
	for(int i=0; i<NBSOL-taille; i+=taille){
		a = (int) tirage((float) a, (float) amp);
		*(psol+i) = a;
	}
	//interpolation entre ces valeurs limites
	interpolation(psol, taille);

}

int interpolation(int* psol, int taille){
	int bord1 = *psol;
	int bord2 = *(psol+taille);

	//Les bords sont les points qui ont été pris au tirage. Un point tous les "taille"
	for(int i=0; i<NBSOL; i++){
		if(i%taille==0 && i>=taille && i<=NBSOL-taille){
			bord1 = *(psol+i);
			bord2 = *(psol+i+taille);

		}
		else {
			*(psol+i) = bord1 + (i%taille)*(bord2 - bord1)/taille;
		}
	}

}
float tirage(float a, float amp){
	int r;
	r = rand()%10;
	if(r < 3) return a+=amp;
	else if(r < 6) return a;
	else return a-=amp;
}

void handleEvents(){
	int continuer = 1;
	SDL_Event event;

	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
		case SDL_QUIT:
			continuer = 0;
			break;

		case SDL_KEYDOWN: // Si appui sur une touche 
			continuer = 0;
		    break;
		}
	}
}
void createRect(SDL_Surface* ecran, int x, int y, char couleur, int eclairement){
	SDL_Surface *rectangle = NULL;

	if(eclairement == DARKER){
		int d = 2;
		switch(couleur){
			case VERT:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 154/d, 205/d, 50/d));
				break;
			case VERT2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 102/d, 204/d, 0));
				break;
			case ROUGE:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255/d, 0, 0));
				break;
			case BLEU:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 51/d, 153/d, 255/d));
				break;
			case BLEU2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 76/d, 250/d));
				break;
			case BLEU3:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 76/d, 153/d));
				break;
			case NOIR:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
				break;
			case GRIS1:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 200/d, 200/d, 200/d));
				break;
			case GRIS2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 150/d, 150/d, 150/d));
				break;
			case GRIS3:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 100/d, 100/d, 100/d));
				break;
			case MARRON:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 139/d, 69/d, 19/d));
				break;
			case MARRON2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 102/d, 51/d, 0));
				break;
			case JAUNE:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255/d, 255/d, 51/d));
				break;
			}

	}
	if(eclairement == NORMAL){
		switch(couleur){
			case VERT:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 154, 205, 50));
				break;
			case VERT2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 102, 204, 0));
				break;
			case ROUGE:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
				break;
			case BLEU:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 51, 153, 255));
				break;
			case BLEU2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 76, 250));
				break;
			case BLEU3:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 76, 153));
				break;
			case NOIR:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
				break;
			case GRIS1:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 200, 200, 200));
				break;
			case GRIS2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 150, 150, 150));
				break;
			case GRIS3:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 100, 100, 100));
				break;
			case MARRON:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 139, 69, 19));
				break;
			case MARRON2:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 102, 51, 0));
				break;
			case JAUNE:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 51));
				break;
			case JAUNEPALE:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 200));
				break;
			case BLANC:
				rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMSOL, DIMSOL, 32, 0, 0, 0, 0);
				SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
				break;
			}
	}



	SDL_Rect position;

	position.x = x;
	position.y = y;
	SDL_BlitSurface(rectangle, NULL, ecran, &position);
}
SDL_Surface* initFenetre(){

	SDL_Init(SDL_INIT_VIDEO);

	//créer la fenêtre
	SDL_Surface *fenetre=NULL;
	SDL_WM_SetCaption("Projet oui", NULL);
	fenetre = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE );  //arguments : longueur, largeur, nbBitsDeCouleur, utiliserMémoireDeCarteGraphique
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 102, 205,255));
	return fenetre;
}

void initSol2D(SDL_Surface* ecran, int* psol, Sol2D sol2D){
	int hauteur;

	//Initialisation de Sol2D
	for(int i = 0; i<NBSOL; i++){
		for(int j=0; j<LARGEURMAP; j++){
			sol2D[i][j] = 0;
		}
	}
	//On met tout sol dans sol2D
	for(int i=0; i<NBSOL; i++){
		hauteur = -1*(*(psol+i)) + 250;
		if(hauteur < LARGEURMAP - 3 && hauteur > 0){
			for(int j=0; j<200; j++){
				if(j==0) sol2D[i][hauteur-j] = VERT;
				if(j>=1 && j<4) sol2D[i][hauteur-j] = MARRON;
				if(j>=4 && j< 7) sol2D[i][hauteur-j] = GRIS1;
				if(j>=7 && j< 20)sol2D[i][hauteur-j] = GRIS2;
				if(j>=20 )sol2D[i][hauteur-j] = GRIS3;
			}
			//Remplissage de la couche 0
			sol2D[i][0] = GRIS3;

			for(int j=1; j<250; j++){
				sol2D[i][j] = GRIS3;
			}
		}
	}

	randomisationCouches(sol2D);

	creuseGaleries(sol2D);
	ajoutEau(sol2D);
	ajoutArbres(sol2D);
}

void ajoutEau(Sol2D sol2D){
	for(int i=0; i<NBSOL; i++){
		for(int j=200; j<LARGEURMAP; j++){
			if(sol2D[i][j] == 0 && j<320){
				sol2D[i][j] = BLEU;
			}
			if(sol2D[i][j] == VERT && j<320){
				sol2D[i][j] = BLEU;
			}
			if( (sol2D[i][j] == 0 || sol2D[i][j] == BLEU) && j<317){
				sol2D[i][j] = BLEU2;
			}
			if( (sol2D[i][j] == 0 || sol2D[i][j] == BLEU || sol2D[i][j] == BLEU2) && j<314){
				sol2D[i][j] = BLEU3;
			}
		}
	}
}
void randomisationCouches(Sol2D sol2D){
	float perlin;
	int tailleBruit = 5;


	int tailleChunk_X = 50, ouOnEst = 4, hauteur = 200, nontrouve = 1;


	for(int k = 4; k<NBSOL - tailleChunk_X; k+=tailleChunk_X){

		//Determine la profondeur du haut de la couche supérieure
		for (int j=200; j<500; j++){
			for(int i = k; i < k + tailleChunk_X; i++){
				if(sol2D[i][j] == MARRON){
					if(nontrouve == 1){
						hauteur = j;
						nontrouve = 0;
					}
				}
			}
		}
		nontrouve = 1;
		hauteur -= 30;
		//CouchesSupérieures
		for(int i=k; i<k + tailleChunk_X; i+=tailleBruit){
			for(int j =100; j<hauteur; j+=tailleBruit){

				perlin = perlin2d(i, j, 1, 1)*1 + 5.8;
				for(int k = 0; k<tailleBruit; k++){
					for(int l = 0; l<tailleBruit; l++){
						sol2D[i+k][j+l] = (int) perlin;
					}
				}
			}
		}
		//Couches inférieures
		tailleBruit = 8;
		for(int i=k; i<k + tailleChunk_X; i+=tailleBruit){
			for(int j =50; j<100; j+=tailleBruit){

				perlin = perlin2d(i, j, 1, 1)*2 + 5.4;
				for(int k = 0; k<tailleBruit; k++){
					for(int l = 0; l<tailleBruit; l++){
						sol2D[i+k][j+l] = (int) perlin;
					}
				}
			}
		}
	}
}

void ajoutArbres(Sol2D sol2D){
	int r;
	int couleur;
	for(int i=10; i<NBSOL - 20; i++){
		for(int j =200; j<LARGEURMAP-20; j++){
			//Gros arbre
			if(sol2D[i-2][j] == VERT && sol2D[i-1][j] == VERT && sol2D[i][j] == VERT && sol2D[i+1][j] == VERT && sol2D[i+2][j] == VERT){
				r = rand()%4;
				if(r == 1){
					for(int a = -1; a<=1; a++){
						sol2D[i+a][j+1] = MARRON2;
						sol2D[i+a][j+2] = MARRON2;
						sol2D[i+a][j+3] = MARRON2;
						sol2D[i+a][j+4] = MARRON2;
						sol2D[i+a][j+5] = MARRON2;
						sol2D[i+a][j+5] = MARRON2;
					}
					r = rand()%3;
					if(r == 1)sol2D[i-2][j+3] = MARRON;
					if(r == 2)sol2D[i+2][j+3] = MARRON;

					r = rand()%3;
					if(r==1) sol2D[i][j+7] = VERT2;
					else sol2D[i][j+7] = VERT;

					r = rand()%3;
					if(r==1) sol2D[i-1][j+7] = VERT2;
					else sol2D[i-1][j+7] = VERT;

					r = rand()%3;
					if(r==1) sol2D[i][j+6] = VERT2;
					else sol2D[i][j+6] = VERT;

					r = rand()%3;
					if(r==1) sol2D[i-1][j+6] = VERT2;
					else sol2D[i-1][j+6] = VERT;


					sol2D[i+1][j+6] = VERT;
					sol2D[i-2][j+6] = VERT;
					sol2D[i+2][j+6] = VERT;

					sol2D[i+2][j+5] = VERT;
					sol2D[i-2][j+5] = VERT;
					sol2D[i-1][j+5] = VERT;
				}
			}
			//Petit arbre
			else if(sol2D[i][j] == VERT && sol2D[i+1][j] == VERT && sol2D[i-1][j] == VERT){
				r = rand()%5;
				if(r == 1){
					sol2D[i][j+1] = MARRON2;
					sol2D[i][j+2] = MARRON2;
					sol2D[i][j+3] = MARRON2;

					r = rand()%3;
					if(r==1) {
						couleur = VERT;
					}
					else{
						couleur = VERT2;
					}
					sol2D[i-1][j+3] = couleur;
					sol2D[i+1][j+3] = couleur;
					sol2D[i+1][j+4] = couleur;
					sol2D[i][j+4] = couleur;
					sol2D[i-1][j+4] = couleur;
					sol2D[i][j+5] = VERT2;
				}

			}
		}
	}
}

void creuseGaleries(Sol2D sol2D){
	int rx = 0, ry = 0, rr = 0, rc = 0, rd = 0, r = 0;
	//Creuse des cercles
	int centreX = 200, centreY = 200;
	for(int k =0; k<10; k++){
		//srand(time(NULL));
		rx = rand()%600 + 50;
		ry = rand()%200 + 150;
		rr = rand()%30 + 5;
		rc = rand()%5 + 1;
		rd = rand()%5 + 1;
		for(int i = -rr; i<rr; i++){
			for(int j = -rr; j<rr; j++){
				if( i*i/(rc*rc) + j*j/(rd*rd) < rr ){
					sol2D[rx + i][ry + j] = 5;
				}
			}
		}
	}
	//Creuse des couloirs
	int r_epaisseur;
	for(int k = 0; k<20; k++){
		r_epaisseur = rand()%7;
		r = rand()%2;
		rx = rand()%600 + 100;
		ry = rand()%200 + 150;
		if(r==0){
			//bas gauche
			for(int i=0; i<20; i++){
				for(int j=0; j<r_epaisseur; j++){
					sol2D[rx - i - j][ry - i] = 5;
				}
			}
		}
		if(r==1){
			//bas droite
			for(int i=0; i<20; i++){
				for(int j=0; j<r_epaisseur; j++){
					sol2D[rx + i + j][ry - i] = 5;
				}
			}
		}
	}


}


Sol2D* initSol(SDL_Surface* fenetre){
	int noise;
	int Hauteur = DIMSOL*100;
	int temps = SOLEIL;

	int* psol = malloc(NBSOL*sizeof(int));


	perlinNoise1D(psol, PLAT);

	//SOLEIL
	if(temps == SOLEIL){
		createRect(fenetre, 11*DIMSOL, 7*DIMSOL, JAUNE, NORMAL);
		createRect(fenetre, 11*DIMSOL, 6*DIMSOL, JAUNE, NORMAL);
		createRect(fenetre, 12*DIMSOL, 7*DIMSOL, JAUNE, NORMAL);
		createRect(fenetre, 12*DIMSOL, 6*DIMSOL, JAUNE, NORMAL);
	}
	//NUAGE
	if(temps == NUAGE){
		createRect(fenetre, 10*DIMSOL, 7*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 10*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 9*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 11*DIMSOL, 7*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 11*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 11*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 12*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 11*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 11*DIMSOL, 8*DIMSOL, BLANC, NORMAL);

		createRect(fenetre, 13*DIMSOL, 7*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 13*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		createRect(fenetre, 14*DIMSOL, 6*DIMSOL, BLANC, NORMAL);
		for(int a=10; a<=13; a++){
			createRect(fenetre, a*DIMSOL, 5*DIMSOL, BLANC, NORMAL);
		}

		createRect(fenetre, 11*DIMSOL, 7*DIMSOL, JAUNEPALE, NORMAL);
		createRect(fenetre, 11*DIMSOL, 6*DIMSOL, JAUNEPALE, NORMAL);
		createRect(fenetre, 12*DIMSOL, 7*DIMSOL, JAUNEPALE, NORMAL);
		createRect(fenetre, 12*DIMSOL, 6*DIMSOL, JAUNEPALE, NORMAL);
	}



	Sol2D sol2D;
	initSol2D(fenetre, psol, sol2D);

	Sol2D* psol2D;
	psol2D = &sol2D;
	return psol2D;
}

void dessinDuMonde(SDL_Surface *fenetre, Sol2D sol2D){
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 102, 205, 255));
	int temps = SOLEIL;
	for (int i=0; i<86; i++){
		for(int j=292; j<342; j++){
			if(sol2D[i][j]!=0){
				//Pour DIMSOL 15, décallage=(0, DIMSOL*340)
				//Pour DIMSOL 1, décallage=(200, DIMSOL*500)
				if(temps == SOLEIL)createRect(fenetre, i*DIMSOL, -j*DIMSOL + DIMSOL*340, sol2D[i][j], NORMAL);
				if(temps == NUAGE)createRect(fenetre, i*DIMSOL, -j*DIMSOL + DIMSOL*340, sol2D[i][j], DARKER);
			}
		}
	}
}
