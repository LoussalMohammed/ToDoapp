#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_ENTRIES = 3000;
struct dateLimite{
        int jour;
        int mois;
        int annee;
    };

struct Entry {
    char id[50];
    char titre[50];
    char description[50];
    char status[50];
    struct dateLimite datel;
    
};

char id[50];
    char titre[50];
    char description[50];
    char status[50];
    int jour;
    int mois;
    int annee;

void ajouterNouvelleTache(struct Entry *entries, int *numLines) {
    if (*numLines >= MAX_ENTRIES) {
        printf("Nombre maximal d'entrees atteint.\n");
        return;
    }

    printf("Entrez le titre de la nouvelle tache : ");
    getchar();
    fgets(titre, sizeof(titre), stdin);
    titre[strcspn(titre, "\n")] = '\0';

    printf("Entrez la description de la nouvelle tache : ");
    getchar();
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = '\0';

    printf("Entrez l'annee de la deadline de la tache : ");
    scanf("%d", &annee);

    printf("Entrez le jour de la deadline de la tache : ");
    scanf("%d", &jour);

    printf("Entrez le mois de la deadline de la tache : ");
    scanf("%d", &mois);

    askStatus:
    printf("Entrez le statut de la tache (a realiser, en cours de realisation, finalisee ) : ");
    getchar(); 
    fgets(status, sizeof(status), stdin);
    status[strcspn(status, "\n")] = '\0';
    if(strcmp(status, "a realiser") != 0 && strcmp(status, "en cours de realisation") != 0 && strcmp(status, "finalisee") != 0 ){
            goto askStatus;
    }

    char id[50];
    snprintf(id, sizeof(id), "%d", *numLines); 
    strcpy(entries[*numLines].id, id);

    
    strcpy(entries[*numLines].titre, titre);
    strcpy(entries[*numLines].description, description);
    entries[*numLines].datel.annee = annee;
    entries[*numLines].datel.jour = jour;
    entries[*numLines].datel.mois = mois;
    strcpy(entries[*numLines].status, status);

    (*numLines)++; 

    
    printf("Nouvelle tache ajoutee avec succes. ID de la tache : %s\n", id);
}

void ajouterMultipleTache(int repet, struct Entry *entries, int *numLines) {
    if (*numLines + repet >= MAX_ENTRIES) {
        printf("Nombre maximal d'entrees atteint.\n");
        return;
    }

    for (int i = 0; i < repet; i++) {
        printf("Entrez le titre de la nouvelle tache : ");
        getchar();  
        fgets(titre, sizeof(titre), stdin);
        titre[strcspn(titre, "\n")] = '\0';

        printf("Entrez la description de la nouvelle tache : ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0';

        printf("Entrez l'annee de la deadline de la tache : ");
        scanf("%d", &annee);

        printf("Entrez le jour de la deadline de la tache : ");
        scanf("%d", &jour);

        printf("Entrez le mois de la deadline de la tache : ");
        scanf("%d", &mois);

        askStatus:
        printf("Entrez le statut de la tache (a realiser, en cours de realisation, finalisee) : ");
        getchar();  
        fgets(status, sizeof(status), stdin);
        status[strcspn(status, "\n")] = '\0';
        if(strcmp(status, "a realiser") != 0 && strcmp(status, "en cours de realisation") != 0 && strcmp(status, "finalisee") != 0){
            goto askStatus;
        }

        char id[50];
        snprintf(id, sizeof(id), "%d", *numLines);
        strcpy(entries[*numLines].id, id);

        strcpy(entries[*numLines].titre, titre);
        strcpy(entries[*numLines].description, description);
        entries[*numLines].datel.annee = annee;
        entries[*numLines].datel.jour = jour;
        entries[*numLines].datel.mois = mois;
        strcpy(entries[*numLines].status, status);

        (*numLines)++;

        printf("Nouvelle tache ajoutee avec succes. ID de la tache : %s\n", id);
    }

    printf("%d nouvelles taches ajoutees avec succes.\n", repet);
}

void afficherTaches(struct Entry *entries, int numLines) {
    if (numLines <= 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }
    else {
    printf("Liste des taches :\n");
    for (int i = 0; i < numLines; i++) {
        printf("ID : %s\n", entries[i].id);
        printf("Titre : %s\n", entries[i].titre);
        printf("Description : %s\n", entries[i].description);
        printf("Date limite : %d-%d-%d\n", entries[i].datel.annee, entries[i].datel.jour, entries[i].datel.mois);
        printf("Statut : %s\n", entries[i].status);
        printf("-------------------------\n");
    }
    }
}


void afficheTachesTrieesParTitre(struct Entry *entries, int numLines) {
    if (numLines == 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }

    for (int i = 0; i < numLines - 1; i++) {
        for (int j = 0; j < numLines - i - 1; j++) {
            if (strcmp(entries[j].titre, entries[j + 1].titre) > 0) {
                struct Entry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    printf("Taches triees par titre :\n");
    for (int i = 0; i < numLines; i++) {
        printf("ID : %s\n", entries[i].id);
        printf("Titre : %s\n", entries[i].titre);
        printf("Description : %s\n", entries[i].description);
        printf("Date limite : %d-%d-%d\n", entries[i].datel.annee, entries[i].datel.jour, entries[i].datel.mois);
        printf("Statut : %s\n", entries[i].status);
        printf("-------------------------\n");
    }
}

void afficheTachesTrieesParDeadline(struct Entry *entries, int numLines) {
    if (numLines == 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }

    for (int i = 0; i < numLines - 1; i++) {
        for (int j = 0; j < numLines - i - 1; j++) {
            if (entries[j].datel.annee > entries[j + 1].datel.annee ||
                (entries[j].datel.annee == entries[j + 1].datel.annee &&
                 (entries[j].datel.jour > entries[j + 1].datel.jour ||
                  (entries[j].datel.jour == entries[j + 1].datel.jour &&
                   entries[j].datel.mois > entries[j + 1].datel.mois)))) {
                struct Entry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    printf("Taches triees par date limite :\n");
    for (int i = 0; i < numLines; i++) {
        printf("ID : %s\n", entries[i].id);
        printf("Titre : %s\n", entries[i].titre);
        printf("Description : %s\n", entries[i].description);
        printf("Date limite : %d-%d-%d\n", entries[i].datel.annee, entries[i].datel.jour, entries[i].datel.mois);
        printf("Statut : %s\n", entries[i].status);
        printf("-------------------------\n");
    }
}

void afficherTachesProches(struct Entry *entries, int numLines) {
    time_t current_time;
    struct tm *tm_info;

    time(&current_time);
    tm_info = localtime(&current_time);

    struct tm currentDate;
    currentDate.tm_year = tm_info->tm_year + 1900; // Current year
    currentDate.tm_mon = tm_info->tm_mon;         // Current month (0-11)
    currentDate.tm_mday = tm_info->tm_mday;       // Current day

    printf("Taches avec un deadline dans 3 jours ou mois :\n");

    for (int i = 0; i < numLines; i++) {
        struct dateLimite tacheDeadline = entries[i].datel;

        int daysDifference = 0;

        struct tm tacheDeadlineDate;
        tacheDeadlineDate.tm_year = tacheDeadline.annee - 1900;
        tacheDeadlineDate.tm_mon = tacheDeadline.mois - 1;
        tacheDeadlineDate.tm_mday = tacheDeadline.jour;

        time_t tacheDeadlineTimestamp = mktime(&tacheDeadlineDate);

        if (tacheDeadlineTimestamp != -1) {
            time_t timeDifference = tacheDeadlineTimestamp - current_time;

            daysDifference = (int)(timeDifference / (60 * 60 * 24));
        }

        if (daysDifference <= 3) {
            printf("Titre: %s\n", entries[i].titre);
            printf("Description: %s\n", entries[i].description);
            printf("Date limite: %d/%d/%d\n", tacheDeadline.jour, tacheDeadline.mois, tacheDeadline.annee);
            printf("Statut: %s\n", entries[i].status);
            printf("\n");
        }
    }
}

void afficherTempsRestant(struct Entry *entries, int numLines) {
    time_t current_time;
    struct tm *tm_info;

    time(&current_time);
    tm_info = localtime(&current_time);

    printf("Temps restant pour chaque tache :\n");

    for (int i = 0; i < numLines; i++) {
        struct dateLimite taskDeadline = entries[i].datel;

        struct tm taskDeadlineDate = {0};
        taskDeadlineDate.tm_year = taskDeadline.annee - 1900;
        taskDeadlineDate.tm_mon = taskDeadline.mois - 1;
        taskDeadlineDate.tm_mday = taskDeadline.jour;

        time_t taskDeadlineTimestamp = mktime(&taskDeadlineDate);

        if (taskDeadlineTimestamp != -1) {
            time_t timeDifference = taskDeadlineTimestamp - current_time;

            int daysDifference = (int)(timeDifference / (60 * 60 * 24));

            printf("ID de la tache: %s\n", entries[i].id);
            printf("Temps restant: %d jours\n", daysDifference);
            printf("\n");
        }
    }
}

void modifierDescription(struct Entry *entries, int numLines, int tacheID, char *newDescription) {
    if (tacheID >= 0 && tacheID < numLines) {
        strcpy(entries[tacheID].description, newDescription);
        printf("Description de la tache %d modifiee avec succes !\n", tacheID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", tacheID);
    }
}
void modifierStatut(struct Entry *entries, int numLines, int tacheID, char *newStatus) {
    if (tacheID >= 0 && tacheID < numLines) {
        strcpy(entries[tacheID].status, newStatus);
        printf("Statut de la tache %d modifie avec succes !\n", tacheID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", tacheID);
    }
}

void modifierDeadline(struct Entry *entries, int numLines, int tacheID, int newAnnee, int newJour, int newmois) {
    if (tacheID >= 0 && tacheID < numLines) {
        entries[tacheID].datel.annee = newAnnee;
        entries[tacheID].datel.jour = newJour;
        entries[tacheID].datel.mois = newmois;
        printf("Deadline de la tache %d modifiee avec succes !\n", tacheID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", tacheID);
    }
}

int afficheNombreTotal(int numLines){
    return numLines;
}

void supprimerTache(int tacheID, struct Entry *entries, int numLines){
                            if (tacheID >= 0 && tacheID <= numLines){

                                for(int i = tacheID; i <= numLines; i++)
                                {
                                    entries[i] = entries[i + 1];
                                    (numLines--);
                                    printf("la tache tu saisi est supprimer avec success!");
                                }
                        }
}

void rechercherTacheByID(int tacheID, struct Entry *entries, int numLines){
                        printf("le titre de tache d'indentification %d : %s \n", tacheID, entries[tacheID].titre);
                        printf("le description de tache d'indentification %d : %s \n", tacheID, entries[tacheID].description);
                        printf("le dead Line de tache d'indentification %d : %d / %d / %d  \n", tacheID, entries[tacheID].datel.annee, entries[tacheID].datel.jour, entries[tacheID].datel.mois);
                        printf("le statut de tache d'indentification %d : %s \n", tacheID, entries[tacheID].status);
                        }

void chargerTachesDepuisFichier(struct Entry *entries, int *numLines) {
    FILE *file = fopen("taches.txt", "r");
    if (file == NULL) {
        printf("Le fichier 'taches.txt' n'existe pas. Un nouveau fichier sera cree.\n");
        return;//
    }

    *numLines = 0; 

    while (fread(&entries[*numLines], sizeof(struct Entry), 1, file)) {
        (*numLines)++;
    }

    fclose(file);
}

void sauvegarderTachesDansFichier(struct Entry *entries, int numLines) {
    FILE *file = fopen("taches.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde des taches dans le fichier.\n");
        return;
    }

    for (int i = 0; i < numLines; i++) {
        fwrite(&entries[i], sizeof(struct Entry), 1, file);
    }

    fclose(file);
}

void afficherMenu() {
    printf("-----------------------Bonjour sur sas TODO List!---------------------------------\n");
    printf("---------------Menu: // Veuillez Entrer Le type de process\n");
    printf("1, L'ajout:\n2, L'affichage:\n3, Modification:\n4, Suppression:\n5, Recherche:\n6, Statistique:\n7, Exit:\n");
}

int main() {
    struct Entry entries[MAX_ENTRIES];
    int numLines = 0;
    struct dateLimite datel;
    int tacheID;
    chargerTachesDepuisFichier(entries, &numLines);
    printf("click pour enter initializer: ");
    bool menu = true; 
    while(menu == true){
    int Pchoix, choix;

    getchar();

    debut11:
    afficherMenu();
    scanf("%d", &Pchoix);
    printf("----------------votre choix: %d \n", Pchoix);
    if (Pchoix == 1 || Pchoix == 2 || Pchoix == 3 || Pchoix == 4 || Pchoix == 5 || Pchoix == 6 || Pchoix == 7 ) {
        switch (Pchoix) {
            case 1:
                debut:
                getchar();
                printf("\n1, Ajouter une nouvelle tache \n2, Ajouter plusieurs nouvelles taches \n");
                scanf("%d", &choix);
                printf("\e[1;1H\e[2J");
                switch (choix){ 
                    case 1:
                        ajouterNouvelleTache(entries, &numLines);
                        goto debut11;
                        break;
                    case 2:
                        debut0:
                        int repet;
                        printf("entre le nombre de tache tu va ajouter: ");
                        scanf("%d", &repet);
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer

                        ajouterMultipleTache(repet, entries, &numLines);

                        goto debut11;
                        break;
                    default:
                        goto debut0;
                        break;
                goto debut11;
                break;
                }
            case 2:
                debut1:
                printf("1, Afficher les tache on order alphabetique: \n2, affiche les taches Trier par deadline \n3, Afficher les taches dont le deadline est dans 3 jours ou mois \n");
                scanf("%d", &choix);
                switch(choix) {
                    case 1:
                        afficheTachesTrieesParTitre(entries, numLines);

                        break;
                    case 2:
                        afficheTachesTrieesParDeadline(entries, numLines);

                        break;
                    case 3:
                        afficherTachesProches(entries, numLines);

                        break;
                    default:
                        printf("choix invalide!!");
                    goto debut1;
                    break;
                }
                goto debut11;
                break;
            case 3:
                debut2:
                printf("1, Modifier la description d'une tache \n2, Modifier le statut d'une tache \n3, Modifier le deadline d'une tache \n");
                scanf("%d", &choix);
                switch(choix) {
                    case 1:
                        tacheID;
                        char newDescription[100];

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &tacheID);

                        printf("Entrez la nouvelle description de la tache : ");
                        getchar();
                        fgets(newDescription, sizeof(newDescription), stdin);
                        newDescription[strcspn(newDescription, "\n")] = '\0'; 

                        modifierDescription(entries, numLines, tacheID, newDescription);
                        
                        break;

                    case 2:
                        char newStatus[20];

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &tacheID);

                        printf("Entrez le nouveau statut de la tache : ");
                        getchar();
                        fgets(newStatus, sizeof(newStatus), stdin);
                        newStatus[strcspn(newStatus, "\n")] = '\0';

                        modifierStatut(entries, numLines, tacheID, newStatus);
                        goto debut11;
                        break;

                    case 3:
                        int newAnnee, newJour, newmois;

                        printf("Entrez l'ID de la tache dont vous souhaitez modifier la deadline : ");
                        scanf("%d", &tacheID);

                        printf("Entrez la nouvelle annee de la deadline : ");
                        scanf("%d", &newAnnee);

                        printf("Entrez le nouveau jour de la deadline : ");
                        scanf("%d", &newJour);

                        printf("Entrez le nouveau mois de la deadline : ");
                        scanf("%d", &newmois);

                        modifierDeadline(entries, numLines, tacheID, newAnnee, newJour, newmois);

                        break;
                    default:
                        printf("choix invalide!!");
                    goto debut2;
                    break;
                }
                goto debut11;
                break;
            case 4:
                debut3:
                printf("1, Supprimer une tache par identifiant \n");
                scanf("%d", &choix);
                switch(choix) {
                    case 1:

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &tacheID);
                        if(tacheID > 0 && tacheID <= numLines){
                        supprimerTache(tacheID, entries, numLines);
                            goto debut11;
                            break;
                        }
                        else{
                            printf("la tache tu saisi n'existe pas!");
                        }
                        goto debut11;
                        break;
                    default:
                        printf("choix invalide!!");
                    goto debut3;
                    break;
                }
                goto debut11;
                break;
            case 5:
                debut4:
                printf("1, Rechercher une tache par son Identifiant \n2, Rechercher une tache par son Titre \n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        int Tid;
                        printf("donnez le nombre de tache: ");
                        scanf("%d", &tacheID);
                        if(tacheID > 0 && tacheID <= numLines){
                        rechercherTacheByID(tacheID, entries, numLines);
                            goto debut11;
                            break;
                        }
                        else{
                            printf("la tache tu saisi n'existe pas!");
                        }
                        goto debut11;
                            break;
                    case 2:
                        char Ttitre[50];
                        char check[10];
                        getchar();
                        printf("donnez le titre de votre tache: ");
                        scanf("%[^\n]", Ttitre);
                        for(int i = 0; i < numLines; i++){
                            if(strcmp(entries[i].titre, Ttitre) == 0){
                                printf("le titre de tache d'indentification %d : %s \n", Tid, entries[Tid].titre);
                                printf("le description de tache d'indentification %d : %s \n", Tid, entries[Tid].description);
                                printf("le dead Line de tache d'indentification %d : %d / %d / %d  \n", Tid, entries[Tid].datel.annee, entries[Tid].datel.jour, entries[Tid].datel.mois);
                                printf("le statut de tache d'indentification %d : %s \n", Tid, entries[Tid].status);
                            }
                        }
                        goto debut11;
                        break;
                    default:
                        printf("choix invalide!!");
                        goto debut4;
                        break;
                }
                goto debut11;
                break;
            case 6:
                debut5:
                printf("1, Afficher le nombre total des taches \n2, Afficher le nombre de taches completes et incompletes \n3, Afficher le nombre de jours restants jusqu'au delai de chaque tache \n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        int totalTaches = afficheNombreTotal(numLines);
                        printf("le total nombre de taches est: %d \n", totalTaches);
                        goto debut11;
                        break;
                    case 2:
                        int count = 0;
                        for(int i = 0; i < numLines; i++){
                            if(strcmp(entries[i].status, "finalisee") != 0){
                                count++;
                            }
                        }
                        printf("le nombre de tache incompletes est: %d\n", count);
                        printf("le nombre de tache completes est: %d\n", numLines - count);
                        goto debut11;
                        break;
                    case 3:
                        afficherTempsRestant(entries, numLines);
                        goto debut11;
                        break;
                    default:
                        printf("choix invalide!!");
                        goto debut5;
                        break;
                }
                goto debut11;
                break;
            case 7:
            printf("confirme votre choix pour exit le programme entrez 1. ou non entrez 0: ");
            scanf("%d", &choix);
            switch(choix){
                case 1:
                    sauvegarderTachesDansFichier(entries, numLines);
                    printf("au revoire \n");
                    menu = false;
                    exit(0);
                    break;
                }
                break;
                case 0:
                    goto debut11;
                    break;
            }
            
        
}

    }
    return 0;
}
