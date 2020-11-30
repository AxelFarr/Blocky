#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include "fonctionsTerrain.c"
#include "fonctionsInterface.h"

///// Partie Axel /////

void pause(){
	int continuer = 1;
	SDL_Event event;
	
	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				continuer = 0;
		}
	}
}

void afficherTitre(SDL_Surface *pEcran){
	SDL_Surface *pTitre = NULL;
	pTitre = SDL_LoadBMP("./images/titre.bmp");
	SDL_Rect positionTitre;
	positionTitre.x = pEcran->w / 2 - pTitre->w / 2;
	positionTitre.y = pEcran->h / 6;
	SDL_BlitSurface(pTitre, NULL, pEcran, &positionTitre);
	SDL_FreeSurface(pTitre);
}

void afficherJouer(SDL_Surface *pEcran){
	SDL_Surface *pJouer = NULL;
	pJouer = SDL_LoadBMP("./images/jouer.bmp");
	SDL_Rect positionJouer;
	positionJouer.x = pEcran->w / 2 - pJouer->w / 2;
	positionJouer.y = pEcran->h / 2 - pJouer->h / 2;
	SDL_BlitSurface(pJouer, NULL, pEcran, &positionJouer);
	SDL_FreeSurface(pJouer);
}

void afficherQuitter(SDL_Surface *pEcran){
	SDL_Surface *pQuitter = NULL;
	pQuitter = SDL_LoadBMP("./images/quitter.bmp");
	SDL_Rect positionQuitter;
	positionQuitter.x = pEcran->w / 2 - pQuitter->w / 2;
	positionQuitter.y = pEcran->h / 2 + pQuitter->h + DECALAGE;
	SDL_BlitSurface(pQuitter, NULL, pEcran, &positionQuitter);
	SDL_FreeSurface(pQuitter);
}

void afficherCharger(SDL_Surface *pEcran){
	SDL_Surface *pCharger = NULL;
	pCharger = SDL_LoadBMP("./images/charger.bmp");
	SDL_Rect positionCharger;
	positionCharger.x = pEcran->w / 2 - pCharger->w / 2;
	positionCharger.y = pEcran->h / 2 + pCharger->h;
	SDL_BlitSurface(pCharger, NULL, pEcran, &positionCharger);
	SDL_FreeSurface(pCharger);
}

void afficherMenu(SDL_Surface *pEcran){
	SDL_FillRect(pEcran, NULL, SDL_MapRGB(pEcran->format, 255, 255, 255));
	afficherTitre(pEcran);
	afficherJouer(pEcran);
	afficherQuitter(pEcran);
	afficherCharger(pEcran);
	SDL_Flip(pEcran);
}

void afficherRetourMenu(SDL_Surface *pEcran){
	SDL_Surface *pMenu = NULL;
	pMenu = SDL_LoadBMP("./images/reglages.bmp");
	SDL_Rect positionMenu;
	positionMenu.x = XMENU;
	positionMenu.y = 0;
	SDL_SetColorKey(pMenu, SDL_SRCCOLORKEY, SDL_MapRGB(pMenu->format, 255, 255, 255));
	SDL_BlitSurface(pMenu, NULL, pEcran, &positionMenu);
	SDL_FreeSurface(pMenu);
}

void afficherItemsBarre(SDL_Surface *pEcran, int matInventaire[LIGNES][COLONNES]){
	SDL_Surface *pBigItem = NULL;
	pBigItem = SDL_LoadBMP("./images/bigItem.bmp");
	SDL_Rect positionBigItem;
	positionBigItem.y = 620 + 5;
	for(int i=0; i<COLONNES; i++){
		if(matInventaire[0][i] == 1){
			positionBigItem.x = WECRAN / 2 - WBARRE / 2 + 5 + i*90 + i*11;
			SDL_BlitSurface(pBigItem, NULL, pEcran, &positionBigItem);
		}
	}
}

void afficherAntiSelection(SDL_Surface *pEcran){
	SDL_Rect positionAntiSelection;
	positionAntiSelection.x = WECRAN / 2 - WBARRE / 2 + 5;
	positionAntiSelection.y = 620 + 5;
	SDL_Surface *pAntiSelection = NULL;
	pAntiSelection = SDL_LoadBMP("./images/antiSelection.bmp");
	for(int i=0; i<COLONNES; i++){		
		SDL_BlitSurface(pAntiSelection, NULL, pEcran, &positionAntiSelection);
		positionAntiSelection.x += 101;
	}
	SDL_FreeSurface(pAntiSelection);
}

void afficherBarre(SDL_Surface *pEcran, int matInventaire[LIGNES][COLONNES]){
	SDL_Surface *pBarre = NULL;
	pBarre = SDL_LoadBMP("./images/barre.bmp");
	SDL_Rect positionBarre;
	positionBarre.x = WECRAN / 2 - WBARRE / 2;
	positionBarre.y = YBARRE;
	SDL_BlitSurface(pBarre, NULL, pEcran, &positionBarre);
	SDL_FreeSurface(pBarre);
	afficherAntiSelection(pEcran);
	afficherItemsBarre(pEcran, matInventaire);
	afficherSelection(pEcran);
	SDL_Flip(pEcran);
}

void afficherSelection(SDL_Surface *pEcran){
	SDL_Surface *pSelection = NULL;
	pSelection = SDL_LoadBMP("./images/selection.bmp");
	SDL_Rect positionSelection;
	positionSelection.x = WECRAN / 2 - WBARRE / 2 + 5;
	positionSelection.y = 620 + 5;
	SDL_BlitSurface(pSelection, NULL, pEcran, &positionSelection);
	SDL_FreeSurface(pSelection);
}

void afficherSelectionBarre(int k, SDL_Surface* pEcran){
	SDL_Surface *pSelectionBarre = NULL;
	pSelectionBarre = SDL_LoadBMP("./images/selectionBarre.bmp");
	SDL_Rect positionSelectionBarre;
	positionSelectionBarre.x = XBARRE + 5 + 11*k + 90*k;
	positionSelectionBarre.y = YBARRE + 5;
	SDL_BlitSurface(pSelectionBarre, NULL, pEcran, &positionSelectionBarre);
	SDL_FreeSurface(pSelectionBarre);
	SDL_Flip(pEcran);
}

void afficherItems(SDL_Surface *pEcran, int matInventaire[LIGNES][COLONNES]){
	SDL_Surface *pItem = NULL;
	pItem = SDL_LoadBMP("./images/item.bmp");
	SDL_Rect positionItem;
	for(int i=0; i<LIGNES; i++){
		for(int j=0; j<COLONNES; j++){
			if(matInventaire[i][j] == 1 && i!=0){
				positionItem.x = WECRAN / 2 - WINVENTAIRE / 2 + 3 + j*70 + j*7;
				positionItem.y = HECRAN / 2 - HINVENTAIRE / 2 + 3 + (i-1)*70 + (i-1)*7;
				SDL_BlitSurface(pItem, NULL, pEcran, &positionItem);
			}
		}
	}
	SDL_FreeSurface(pItem);
}

void afficherGrille(SDL_Surface *pEcran){
	SDL_Surface *pInventaire = NULL;
	pInventaire = SDL_LoadBMP("./images/inventaire.bmp");
	SDL_Rect positionInventaire;
	positionInventaire.x = WECRAN / 2 - WINVENTAIRE / 2;
	positionInventaire.y = HECRAN / 2 - HINVENTAIRE / 2;
	SDL_BlitSurface(pInventaire, NULL, pEcran, &positionInventaire);
	SDL_FreeSurface(pInventaire);
}

void afficherSelectionInv(int i, int j, SDL_Surface* pEcran){
	SDL_Surface *pSelectionItem = NULL;
	pSelectionItem = SDL_LoadBMP("./images/itemSelection.bmp");
	SDL_Rect positionSelectionItem;
	positionSelectionItem.x = (WECRAN / 2 - WINVENTAIRE / 2) + 3 + 70*j + 7*j;
	positionSelectionItem.y = (HECRAN / 2 - HINVENTAIRE / 2) + 3 + 70*(i-1) + 7*(i-1);
	SDL_BlitSurface(pSelectionItem, NULL, pEcran, &positionSelectionItem);
	SDL_Flip(pEcran);
	SDL_FreeSurface(pSelectionItem);
}

void afficherInventaire(SDL_Surface *pEcran, int matInventaire[LIGNES][COLONNES]){
	afficherGrille(pEcran);
	afficherItems(pEcran, matInventaire);
	SDL_Flip(pEcran);
}

void afficherMenuJeu(SDL_Surface* pEcran){
	SDL_Surface *pMenuJeu;
	pMenuJeu = SDL_LoadBMP("./images/menuJeu.bmp");
	SDL_Rect positionMenuJeu;
	positionMenuJeu.x = WECRAN / 2 - WMENUJEU / 2;
	positionMenuJeu.y = HECRAN / 2 - HMENUJEU / 2;
	SDL_BlitSurface(pMenuJeu, NULL, pEcran, &positionMenuJeu);
	SDL_Flip(pEcran);
}

int ifQuitter(SDL_Rect positionSouris){
	if(positionSouris.x >= XQUITTER && positionSouris.x <= (WECRAN / 2 + WQUITTER / 2) && positionSouris.y >= YQUITTER + DECALAGE && positionSouris.y <= (HECRAN / 2 + 2*HQUITTER) + DECALAGE)
		return 1;
	else
		return 0;
}

int ifJouer(SDL_Rect positionSouris){
	if(positionSouris.x >= XJOUER && positionSouris.x <= (XJOUER + WJOUER) && positionSouris.y >= YJOUER && positionSouris.y <= (YJOUER + HJOUER))
		return 1;
	else
		return 0;
}

int ifMenu(SDL_Rect positionSouris){
	if(positionSouris.x >= XMENU && positionSouris.y <= HMENU)
		return 1;
	else
		return 0;
}

int scrollUp(SDL_Event event, int jeu, SDL_Rect positionSelection){
	if(event.button.button == SDL_BUTTON_WHEELUP && positionSelection.x < (XBARRE + 5 + 9*101) && jeu)
		return 1;
	else 
		return 0;
}

int scrollDown(SDL_Event event, int jeu, SDL_Rect positionSelection){
	if(event.button.button == SDL_BUTTON_WHEELDOWN && positionSelection.x > (XBARRE + 5) && jeu)
		return 1;
	else
		return 0;
}

void afficherSelectionDyn(SDL_Surface *pEcran, SDL_Rect positionSelection, int sens){
	SDL_Surface *pSelection = NULL;
	pSelection = SDL_LoadBMP("./images/selection.bmp");
	if(sens == DROITE)
		positionSelection.x += 101;
	if(sens == GAUCHE)
		positionSelection.x -= 101;
	SDL_BlitSurface(pSelection, NULL, pEcran, &positionSelection);
	SDL_FreeSurface(pSelection);
	SDL_Flip(pEcran);
}

int scroll(SDL_Event event, int jeu, SDL_Surface *pEcran, SDL_Rect positionSelection, int matInventaire[LIGNES][COLONNES]){
	int sens = -1;
	if(scrollUp(event, jeu, positionSelection)){	//Si on scroll up la selection bouge vers la droite sur la barre
		sens = DROITE;
		afficherAntiSelection(pEcran);
		afficherItemsBarre(pEcran, matInventaire);
		afficherSelectionDyn(pEcran, positionSelection, sens); 
	}
	if(scrollDown(event, jeu, positionSelection)){	//Si on scroll down la selection bouge vers la gauche sur la barre
		sens = GAUCHE;
		afficherAntiSelection(pEcran);
		afficherItemsBarre(pEcran, matInventaire);
		afficherSelectionDyn(pEcran, positionSelection, sens); 
		/*POSSIBLE AMELIORATION (on pourrait faire en sorte de regrouper le scrollUp et le scrollDown
		en faisant une fonction qui renverrait +/-101 pour actualiser la position du selecteur*/
	}
	if(sens == DROITE)
		return 101;
	if(sens == GAUCHE)
		return -101;
	else
		return 0;
}

void afficherJeu(SDL_Surface *pEcran, int matInventaire[LIGNES][COLONNES], Sol2D *psol2D){
	SDL_FillRect(pEcran, NULL, SDL_MapRGB(pEcran->format, 255, 255, 255));
	dessinDuMonde(pEcran, *psol2D);
	afficherRetourMenu(pEcran);
	afficherBarre(pEcran, matInventaire);
	afficherSelection(pEcran);
	SDL_Flip(pEcran);
}

void initInv(int matInventaire[LIGNES][COLONNES]){
	for(int i=0; i<LIGNES; i++){
		for(int j=0; j<COLONNES; j++){
			matInventaire[i][j] = 0;
		}
	}
	matInventaire[0][5] = 1;
	matInventaire[2][1] = 1;
}

int ifCase(SDL_Rect positionSouris, SDL_Surface* pEcran, int matInventaire[LIGNES][COLONNES], int selectItem){
	int souX = positionSouris.x;
	int souY = positionSouris.y;
	for(int i=1; i<LIGNES; i++){
		for(int j=0; j<COLONNES; j++){
			if(souX > (WECRAN / 2 - WINVENTAIRE / 2) + 3 + 70*j + 7*j && souX < (WECRAN / 2 - WINVENTAIRE / 2) + 3 + 70*(j+1) + 7*j){ 
				if(souY > (HECRAN / 2 - HINVENTAIRE / 2) + 3 + 70*(i-1) + 7*(i-1) && souY < (HECRAN / 2 - HINVENTAIRE / 2) + 3 + 70*i + 7*(i-1)){ 
					//Si on clic sur une case
					if(matInventaire[i][j] == 1){ //S'il y a un item
						printf("colonne %d et ", j);
						printf("ligne %d\n", i);
						if(!selectItem){
							matInventaire[i][j] = 0;
							afficherSelectionInv(i, j, pEcran);
							return 1;
						}
					}
					else if(selectItem){
							matInventaire[i][j] = 1;
							afficherInventaire(pEcran, matInventaire);
							afficherBarre(pEcran, matInventaire);
							return 0;
					}
				}
			}
		}
	}
	for(int k=0; k<COLONNES; k++){
		if(souY > YBARRE + 5 && souY < YBARRE + 5 + 90 && souX > XBARRE + 5 + 11*k + 90*k && souX < XBARRE + 5 + 11*(k+1) + 90*(k+1)){
			if(matInventaire[0][k] == 1){
				printf("barre %de case\n", k);
				if(!selectItem){
					matInventaire[0][k] = 0;
					afficherSelectionBarre(k, pEcran);
					return 1;
				}
			}
			else if(selectItem){
				matInventaire[0][k] = 1;
				afficherInventaire(pEcran, matInventaire);
				afficherBarre(pEcran, matInventaire);
				return 0;
			}
		}
	}
	if(!selectItem)
		return 0;
	else if(selectItem)
		return 1;
}

int ifCharger(SDL_Rect positionSouris){
	if(positionSouris.x >= XQUITTER && positionSouris.x <= (WECRAN / 2 + WQUITTER / 2) && positionSouris.y >= YQUITTER && positionSouris.y <= (HECRAN / 2 + 2*HQUITTER))
		return 1;
	else
		return 0;
}

int ifChoixMenu(SDL_Rect positionSouris){
	if(positionSouris.x >= WECRAN / 2 - WMENUJEU / 2 + 15 && positionSouris.x <= WECRAN / 2 - WMENUJEU / 2 + WBUTMENU //Il manque quelques pixels vers la droite
	&& positionSouris.y >= HECRAN / 2 - HMENUJEU / 2 + 41 && positionSouris.y <= HECRAN / 2 - HMENUJEU / 2 + 41 + HBUTMENU)
		return 1;
	else
		return 0;
}

int ifChoixSave(SDL_Rect positionSouris){
	if(positionSouris.x >= WECRAN / 2 - WMENUJEU / 2 + 15 && positionSouris.x <= WECRAN / 2 - WMENUJEU / 2 + WBUTMENU //Il manque quelques pixels vers la droite
	&& positionSouris.y >= HECRAN / 2 - HMENUJEU / 2 + 41 + HBUTMENU + 17 && positionSouris.y <= HECRAN / 2 - HMENUJEU / 2 + 41 + 2*HBUTMENU + 17) 
		return 1;
	else
		return 0;
}

int ifChoixRetour(SDL_Rect positionSouris){
	if(positionSouris.x >= WECRAN / 2 - WMENUJEU / 2 + 15 && positionSouris.x <= WECRAN / 2 - WMENUJEU / 2 + WBUTMENU //Il manque quelques pixels vers la droite
	&& positionSouris.y >= HECRAN / 2 - HMENUJEU / 2 + 41 + 2*HBUTMENU + 2*17 && positionSouris.y <= HECRAN / 2 - HMENUJEU / 2 + 41 + 3*HBUTMENU + 2*17) 
		return 1;
	else
		return 0;
}

void ajouterItem(int matInventaire[LIGNES][COLONNES]){
	int trouve = NON;
	for(int i=0; i<LIGNES; i++){
		for(int j=0; j<COLONNES; j++){
			if(matInventaire[i][j] == 0 && !trouve){
				matInventaire[i][j] = 1;
				trouve = OUI;
				printf("Item ajouté\n");
			}
		}
	}
}

void action(SDL_Surface *pEcran){
	SDL_Event event;
	int continuer = OUI;
	int menu = OUVERT;
	int jeu = FERME;
	int inventaire = FERME;
	int selectItem = NON;
	int menuJeu = FERME;
	SDL_Rect positionSouris;
	SDL_Rect positionSelection;
	positionSelection.x = WECRAN / 2 - WBARRE / 2 + 5;
	positionSelection.y = 620 + 5;
	int matInventaire[LIGNES][COLONNES];
	initInv(matInventaire);
	Sol2D* psol2D;
	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT: //Si on appuie sur la croix
				continuer = NON;
				break;
			case SDL_MOUSEBUTTONUP:
				positionSouris.x = event.button.x;
				positionSouris.y = event.button.y;
				if(event.button.button == SDL_BUTTON_LEFT){ //Si on fait un clic gauche
					if(menu){ //Si on est dans le menu
						if(ifQuitter(positionSouris)){ //Si la souris est sur le bouton "Quitter"
							printf("Quitter! \n");
							continuer = NON;
						}
						if(ifJouer(positionSouris)){ //Si la souris est sur le bouton "Jouer"
							printf("Jouer! \n");
							psol2D = initSol(pEcran);
							afficherJeu(pEcran, matInventaire, psol2D);
							initInv(matInventaire);
							menu = FERME;
							jeu = OUVERT;
						}
						if(ifCharger(positionSouris)){ 
							printf("Charger! \n"); 
						}
					}
					else if(jeu && !inventaire && !menuJeu){
						if(ifMenu(positionSouris)){ //Si la souris est sur le bouton "Menu"
							if(!menuJeu){
								afficherMenuJeu(pEcran);
								printf("MenuJeu! \n");
								menuJeu = OUVERT;
							}
						}
					}
					else if(menuJeu){
						if(ifChoixMenu(positionSouris)){ //Si la souris est sur le bouton "Menu"
							printf("Retour Menu !\n");
							afficherMenu(pEcran);
							menuJeu = FERME;
							jeu = FERME;
							menu = OUVERT;
						}
						else if(ifChoixSave(positionSouris)){ //Si la souris est sur le bouton "Sauvegarder"
							printf("Sauvegarder !\n");
						}
						else if(ifChoixRetour(positionSouris)){ //Si la souris est sur le bouton "Retour au jeu"
							afficherJeu(pEcran, matInventaire, psol2D);
							menuJeu = FERME;
						}
					}
					else if(inventaire){ //Si on est dans l'inventaire
						selectItem = ifCase(positionSouris, pEcran, matInventaire, selectItem);	
					}
				}
				if(!inventaire){
					positionSelection.x += scroll(event, jeu, pEcran, positionSelection, matInventaire); //Si on scroll (barre d'inventaire)
				}
				break;
				
			case SDL_KEYDOWN: //Si on appuie sur une touche
				switch(event.key.keysym.sym){
					case SDLK_i: //Si on appuie sur i (Ouvre l'inventaire)
						if(!inventaire && jeu && !menuJeu){
							afficherInventaire(pEcran, matInventaire);
							inventaire = OUVERT;
						}
						else if(inventaire && !selectItem){ // (ferme l'inventaire)
							afficherJeu(pEcran, matInventaire, psol2D);
							positionSelection.x = WECRAN / 2 - WBARRE / 2 + 5;
							inventaire = FERME;
						}
						break;
					case SDLK_a: //Si on appuie sur a (Ajoute un bloc)
						if(jeu && !menuJeu && !inventaire){
							ajouterItem(matInventaire);
							afficherBarre(pEcran, matInventaire);
						}
						break;
				}
				break;
		}
	}
}

void mesBails(){
	
	SDL_Surface *pEcran = initFenetre();
	
	afficherMenu(pEcran);
	
	action(pEcran);

	SDL_Quit();
}
