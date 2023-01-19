#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> /* A inclure dans le fichier SG_math.c */

#define NBL 10
#define NBC 15

#define reset "\033[0m"
#define reverse "\033[7m"

#define rouge "\033[;31m"
#define vert "\033[;32m"
#define bleu "\033[;34m"
#define jaune "\033[;33m"

/*********************************************************/
/* Structure case	                                     */
/* bille : charactère - Couleur V,B,R ou x    			 */
/* occupe : int - Booléen si la case est occupée par une bille ou non*/
/*********************************************************/
typedef struct Case{
	char bille;
	int occupe;
}Case;

/*********************************************************/
/* Structure plateau                                     */
/* plat : Matrice 10x15 de cases            			 */
/* nb_occupé : int - Nombre de billes sur le plateau     */
/*********************************************************/
typedef struct Plateau{
	Case mat[NBL][NBC];
	int nb_occupe;
}plateau;

void affichagePlateau (plateau plat1){
	for (int i=NBL-1; i>=0; i--){
		printf(" %d ",i);
		for (int j=0; j< NBC; j++){
			if((plat1.mat[i][j]).bille == 'R'){
				printf(" %s%s  %s ", rouge,reverse,reset);
			}
			else if((plat1.mat[i][j]).bille == 'V'){
				printf(" %s%s  %s ", vert,reverse,reset);
			}
			else if ((plat1.mat[i][j]).bille == 'B'){
				printf(" %s%s  %s ", bleu,reverse,reset);
			} 
			else if ((plat1.mat[i][j]).bille == 'x'){
				printf(" %s%s  %s ", jaune,reverse,reset);
			}
			else{
				printf("  . ");
			}
		}
		printf("\n\n");
	}
	printf("     ");
	for (int k=0; k<9;k++){
		printf("%d   ", k);
	}
	for (int k=9; k<NBC;k++){
		printf("%d  ", k);
	}
}

/*********************************************************/
/* Transformation des billes selectionnées en jaune       */
/* plat1 : Donnee/Résultat - Type : plateau - plateau de cases*/
/* ncol : Donnée - Type : entier - numéro de colonne de la bille sélectionnée*/
/* nlig : Donnée - Type : entier - numéro de ligne de la bille sélectionnée*/
/* nb_x : Donnée/Résultat - Type : entier - nombre de billes transformées en jaune*/
/*********************************************************/
void transformationX (plateau* plat1, int ncol, int nlig, int *nb_x){

	char couleurChoisie=(plat1->mat[nlig][ncol]).bille;
	(plat1->mat[nlig][ncol]).bille='x';
	*nb_x += 1;
	plat1->nb_occupe = plat1->nb_occupe - 1;
	
	//test à gauche
	if((plat1->mat[nlig][ncol-1]).bille==couleurChoisie && (ncol-1)>=0){
	
	transformationX (plat1,ncol-1,nlig,nb_x);
	}
	
	//test en haut
	if((plat1->mat[nlig+1][ncol]).bille==couleurChoisie && (nlig+1)<NBL){
	
	transformationX (plat1,ncol,nlig+1,nb_x);
	}
	
	//test à droite
	if((plat1->mat[nlig][ncol+1]).bille==couleurChoisie && (ncol+1)<NBC){
	
	transformationX (plat1,ncol+1,nlig,nb_x);
	}
	
	//test en bas
	if((plat1->mat[nlig-1][ncol]).bille==couleurChoisie && (nlig-1)>=0){
	
	transformationX (plat1,ncol,nlig-1,nb_x);
	}
}

/*********************************************************/
/* Suppression des billes jaunes (sélectionnées) et écroulement des billes supérieures*/
/* plat1 : Donnee/Résultat - Type : plateau - plateau de cases*/
/* ncol : Donnée - Type : entier - numéro de colonne de la bille sélectionnée*/
/* nlig : Donnée - Type : entier - numéro de ligne de la bille sélectionnée*/
/*********************************************************/
void ecroulement (plateau* plat1, int ncol, int nlig){
	//test en haut
	if((plat1->mat[nlig+1][ncol]).bille=='x' && (nlig+1)<NBL){
		ecroulement (plat1,ncol,nlig+1);
	}
	else{
		//ecroulement
			int i= nlig+1;
			while(i < NBL && (plat1->mat[i][ncol]).bille != 'o'){
				(plat1->mat[i-1][ncol]).bille = (plat1->mat[i][ncol]).bille;
				i+=1;
			}
			(plat1->mat[i-1][ncol]).bille = 'o';
			(plat1->mat[i-1][ncol]).occupe = 0;
		
		//test à gauche
		if((plat1->mat[nlig][ncol-1]).bille=='x' && (ncol-1)>=0){
			ecroulement (plat1,ncol-1,nlig);
		}
		
		//test à droite
		if((plat1->mat[nlig][ncol+1]).bille=='x' && (ncol+1)<NBC){
			ecroulement (plat1,ncol+1,nlig);
		}
		
		//test en bas
		if((plat1->mat[nlig-1][ncol]).bille=='x' && (nlig-1)>=0){
			ecroulement (plat1,ncol,nlig-1);
		}
	}
}

/*********************************************************/
/* Décalage des rangées vides du tableau à droite			*/
/* plat1 : Donnee/Résultat - Type : plateau - plateau de cases*/
/*********************************************************/
void decalage (plateau* plat1){
	int p;
	for (int j=0; j< NBC; j++){
		if((plat1->mat[0][j]).occupe == 0){
			p=0;
			while((plat1->mat[0][j+p]).occupe == 0){
				p += 1;
			}
			if(p<13){
				for(int i=j;i<NBC-p;i++){
					for(int k=0;k<NBL;k++){
						(plat1->mat[k][i]).bille = (plat1->mat[k][i+p]).bille;
						(plat1->mat[k][i]).occupe = (plat1->mat[k][i+p]).occupe;
					}
				}
				for(int l=0;l<NBL;l++){
					for(int m=NBC-p;m<NBC;m++){
						(plat1->mat[l][m]).bille = 'o';
						(plat1->mat[l][m]).occupe = 0;
					}
				}
			}
		}
	}
}

/* A recopier dans le fichier SG_math.c */
double f1 (int i, int j){
	return sin ((double)i*j + (double)j);
}

double f2 (int i, int j){
	double z = f1 (i, j);
	return z * z;
}

int main(){
	plateau plat1;
	float z;
	
	for (int i=0; i< NBL; i++){
		for (int j=0; j< NBC; j++){
			z=f2(i,j);
			if(z<0){
				(plat1.mat[i][j]).occupe=1;
				(plat1.mat[i][j]).bille='R';
			}
			else if(z<0.5){
				(plat1.mat[i][j]).occupe=1;
				(plat1.mat[i][j]).bille='V';
			}
			else{
				(plat1.mat[i][j]).occupe=1;
				(plat1.mat[i][j]).bille='B';
			}
		}
	}
	plat1.nb_occupe=150;
	
	printf("Choix de la bille : \n");
	affichagePlateau (plat1); 
	
	int ncol,nlig, score;
	int nb_x;
	
	while(plat1.nb_occupe > 0){
		nb_x=0;
		printf("Saisir une colonne : ");
		scanf("%d", &ncol);
		printf("Saisir une ligne : ");
		scanf("%d", &nlig);
		
		while((plat1.mat[nlig][ncol]).occupe != 1 || 0>ncol || ncol>14 || nlig<0 || nlig>14){
			printf("Saisir une case non vide : \n");
			printf("Saisir une colonne : ");
			scanf("%d", &ncol);
			printf("Saisir une ligne : ");
			scanf("%d", &nlig);
		}
		printf("\n\n");
		
		transformationX (&plat1,ncol,nlig,&nb_x);
		
		printf("Affichage du groupe sélectionné : \n");
		affichagePlateau (plat1);
		printf("\n\n");
		
		score = score + (nb_x-1)*(nb_x-1);
	
		ecroulement (&plat1,ncol,nlig);
		
		printf("Ecroulement des billes : \n");
		affichagePlateau (plat1);
		printf("\n\n");
		
		decalage (&plat1);
		printf("Décalage des colonnes : \n");
		affichagePlateau (plat1);
		
		printf("\n Vous avez fait %d points à ce tour ! \n\n", ((nb_x-1)*(nb_x-1)));
	}
	printf("Bravo ! Vous avez fini le jeu. Vous finissez avec %d points ! \n", score);
}
