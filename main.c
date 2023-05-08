#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp_commande, *fp_produit, *fp_stock, *fp_resultats;
    int reference, quantite;
    int reference2;
    int reference3, quantite_totale;
    int quantite_restante;
    char nom_client[50], produit[50];
    float prix_achat = 0, prix_unitaire;
    int n = 0;
    
   
    fp_produit = fopen("produits.txt", "rt");
    fp_stock = fopen("stock.txt", "rt");
    fp_resultats = fopen("nextFact", "w");
    
    for(int i = 0001; i <= 0003; i++){
    char nom_fichier[30];
    sprintf(nom_fichier, "commandes/commande%04d.txt", i);
    fp_commande = fopen(nom_fichier, "r");
    if(fp_commande == NULL){
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
        return 1;
    }
    
    if(fp_produit == NULL){
        printf("Erreur d'ouverture du fichier produits.txt\n");
        return 1;
    }
    
    if(fp_stock == NULL){
        printf("Erreur d'ouverture du fichier produits.txt\n");
        return 1;
    }

	if(fp_resultats == NULL){
    printf("Erreur d'ouverture du fichier resultats.txt\n");
    return 1;
	}
	
    // lire le nom du client
    fscanf(fp_commande, "%s", nom_client);
	
	fprintf(fp_resultats, "Résultats pour le client %s :\n\n", nom_client);
    // boucle principale pour parcourir le fichier commande0001.txt
    while(fscanf(fp_commande, "%d %d", &reference, &quantite) == 2){
        // réinitialiser le pointeur de fichier fp_produit pour le lire à nouveau
        rewind(fp_produit);
        rewind(fp_stock);

        // boucle pour chercher la référence dans le fichier produits.txt
        while(fscanf(fp_produit, "%d %s %f", &reference2, produit, &prix_unitaire) == 3){
            if(reference == reference2){
                prix_achat = quantite * prix_unitaire;
                fprintf(fp_resultats, "Le client %s doit payer %.2f euros pour ce produit %s\n", nom_client, prix_achat, produit);
                break;
            }
        }
        
        while(fscanf(fp_stock, "%d %d", &reference3, &quantite_totale) == 2){
            if(reference == reference3){
                quantite_restante = quantite_totale - quantite;
                fprintf(fp_resultats, "Il reste %d exemplaire(s) de l'article numéro %d\n\n", quantite_restante, n);
                if(quantite_restante <= 0){
					fprintf(fp_resultats, "ATTENTION !!! Nous n'avons plus l'article numéro %d dans le stock\n\n", n);
					}
                break;
				}
			}
        fprintf(fp_resultats, "\n");
		}
	}

    
    fclose(fp_commande);
    fclose(fp_produit);
    fclose(fp_resultats);
    
    return 0;
}

