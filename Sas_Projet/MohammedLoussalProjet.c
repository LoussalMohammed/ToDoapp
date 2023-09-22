#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int MAX_ENTRIES = 3000;
struct dateLimite{
        int jour;
        int mois;
        int annee;
    };
struct Entry {
    char id[300];
    char titre[50];
    char description[100];
    char status[20];
    struct dateLimite datel;

};
void ajouterNouvelleTache(struct Entry *entries, int *numLines, char *titre, char *description, int annee, int jour, int mois, char *status) {
    if (*numLines >= MAX_ENTRIES) {
        printf("Nombre maximal d'entrees atteint.\n");
        return;
    }

    char id[10];
    snprintf(id, sizeof(id), "%d", *numLines); 
    strcpy(entries[*numLines].id, id);


    strcpy(entries[*numLines].titre, titre);
    strcpy(entries[*numLines].description, description);
    entries[*numLines].datel.annee = annee;
    entries[*numLines].datel.jour = jour;
    entries[*numLines].datel.mois = mois;
    strcpy(entries[*numLines].status, status);

    (*numLines)++;


    printf("Nouvelle tache ajoutee avec succès. ID de la tache : %s\n", id);
}

void ajouterMultipleTache(int repet, struct Entry *entries, int *numLines, char *titre, char *description, int annee, int jour, int mois, char *status) {
    if (*numLines + repet >= MAX_ENTRIES) {
        printf("Nombre maximal d'entrees atteint.\n");
        return;
    }

    for (int i = 0; i < repet; i++) {

        char id[10];
        snprintf(id, sizeof(id), "%d", *numLines); 
        strcpy(entries[*numLines].id, id);


        strcpy(entries[*numLines].titre, titre);
        strcpy(entries[*numLines].description, description);
        entries[*numLines].datel.annee = annee;
        entries[*numLines].datel.jour = jour;
        entries[*numLines].datel.mois = mois;
        strcpy(entries[*numLines].status, status);

        (*numLines)++;
    }


    printf("%d nouvelles taches ajoutees avec succès.\n", repet);
}
void afficherTaches(struct Entry *entries, int numLines) {
    if (numLines == 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }

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


void afficheTachesTrieesParTitre(struct Entry *entries, int numLines) {
    if (numLines == 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }

    // Algorithme de tri a bulles pour trier les taches par titre
    for (int i = 0; i < numLines - 1; i++) {
        for (int j = 0; j < numLines - i - 1; j++) {
            // Comparez les titres des taches et echangez-les si necessaire
            if (strcmp(entries[j].titre, entries[j + 1].titre) > 0) {
                struct Entry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    // Affichez la liste triee des taches
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

// Fonction pour trier les taches par date limite en utilisant le tri a bulles
void afficheTachesTrieesParDeadline(struct Entry *entries, int numLines) {
    if (numLines == 0) {
        printf("Aucune tache a afficher.\n");
        return;
    }

    // Algorithme de tri a bulles pour trier les taches par date limite
    for (int i = 0; i < numLines - 1; i++) {
        for (int j = 0; j < numLines - i - 1; j++) {
            // Comparez les dates limites des taches et echangez-les si necessaire
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

    // Affichez la liste triee des taches
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
        struct dateLimite taskDeadline = entries[i].datel;

        // Calculate the difference in days between the task deadline and the current date
        int daysDifference = 0;

        // Convert the task deadline to a timestamp
        struct tm taskDeadlineDate;
        taskDeadlineDate.tm_year = taskDeadline.annee - 1900;
        taskDeadlineDate.tm_mon = taskDeadline.mois - 1; // Adjust for 0-based months
        taskDeadlineDate.tm_mday = taskDeadline.jour;

        time_t taskDeadlineTimestamp = mktime(&taskDeadlineDate);

        if (taskDeadlineTimestamp != -1) {
            // Calculate the difference in seconds
            time_t timeDifference = taskDeadlineTimestamp - current_time;

            // Convert the difference to days
            daysDifference = (int)(timeDifference / (60 * 60 * 24));
        }

        if (daysDifference <= 3) {
            printf("Titre: %s\n", entries[i].titre);
            printf("Description: %s\n", entries[i].description);
            printf("Date limite: %d/%d/%d\n", taskDeadline.jour, taskDeadline.mois, taskDeadline.annee);
            printf("Statut: %s\n", entries[i].status);
            printf("\n");
        }
    }
}

void modifierDescription(struct Entry *entries, int numLines, int taskID, char *newDescription) {
    if (taskID >= 0 && taskID < numLines) {
        // Check if the task with the specified ID exists
        strcpy(entries[taskID].description, newDescription);
        printf("Description de la tache %d modifiee avec succes !\n", taskID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", taskID);
    }
}
void modifierStatut(struct Entry *entries, int numLines, int taskID, char *newStatus) {
    if (taskID >= 0 && taskID < numLines) {
        // Check if the task with the specified ID exists
        strcpy(entries[taskID].status, newStatus);
        printf("Statut de la tache %d modifie avec succes !\n", taskID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", taskID);
    }
}

void modifierDeadline(struct Entry *entries, int numLines, int taskID, int newAnnee, int newJour, int newmois) {
    if (taskID >= 0 && taskID < numLines) {
        // Check if the task with the specified ID exists
        entries[taskID].datel.annee = newAnnee;
        entries[taskID].datel.jour = newJour;
        entries[taskID].datel.mois = newmois;
        printf("Deadline de la tache %d modifiee avec succes !\n", taskID);
    } else {
        printf("Tache avec l'ID %d n'existe pas.\n", taskID);
    }
}

int afficheNombreTotal(int numLines){
    return numLines;
}

int main() {
    struct Entry entries[MAX_ENTRIES];
    int numLines = 0;
    char id[3000];
    char titre[50];
    char description[100];
    char status[20];
    struct dateLimite datel;
    int annee;
    int jour;
    int mois;
    int taskID;
    const char *dataFileNama = "tasks.txt";
    FILE *file = fopen(dataFileNama, "r");
    if (file) {
        printf("File exists: %s\n", dataFileNama);
        if (file != NULL) {
            char line[100];
            while (fgets(line, sizeof(line), file) != NULL) {
                numLines++;
            }

            rewind(file);
            numLines = numLines / 7;

            for (int i = 0; i < numLines; i++) {
                fscanf(file, "%d %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]", &id, titre, description, annee, jour, mois, status);
                ajouterNouvelleTache(entries, &numLines, titre, description, annee, jour, mois, status);
            }
        }
       
    } 
    fclose(file);
    bool menu = true; 
    while(menu == true){
    int Pchoix, choix;
    debut11:
    printf("-----------------------Bonjour sur sas TODO List!--------------------------------- \n");
    printf("---------------Menu:      // Veuillez Entre Le type de process \n");
    printf("----------------1, L'ajoute: \n----------------2, L'affichage: \n----------------3, Modification: \n----------------4, Suppresion: \n----------------5, Recherche: \n----------------6, Statistique: \n----------------7, Exit: \n");
    scanf("%d", &Pchoix);
    printf("----------------votre choix: %d \n", Pchoix);
    if (Pchoix == 1 || Pchoix == 2 || Pchoix == 3 || Pchoix == 4 || Pchoix == 5 || Pchoix == 6 || Pchoix == 7 ) {
        switch (Pchoix) {
            case 1:
                debut:
                printf("\n1, Ajouter une nouvelle tache \n2, Ajouter plusieurs nouvelles taches \n");
                scanf("%d", &choix);
                switch (choix){ 
                    case 1:
                        printf("Entrez le titre de la nouvelle tache : ");
                        getchar();
                        fgets(titre, sizeof(titre), stdin);
                        titre[strcspn(titre, "\n")] = '\0';

                        printf("Entrez la description de la nouvelle tache : ");
                        fgets(description, sizeof(description), stdin);
                        description[strcspn(description, "\n")] = '\0';

                        printf("Entrez l'annee de la deadline de la tache : ");
                        scanf("%d[0-9]{4}", &annee);

                        printf("Entrez le jour de la deadline de la tache : ");
                        scanf("%d[0-9]{2}", &jour);

                        printf("Entrez le mois de la deadline de la tache : ");
                        scanf("%d[0-9]{2}", &mois);

                        printf("Entrez le statut de la tache (a realiser, en cours de realisation, finalisee) : ");
                        getchar(); // Pour consommer le caractère de nouvelle ligne restant
                        fgets(status, sizeof(status), stdin);
                        status[strcspn(status, "\n")] = '\0';

                        ajouterNouvelleTache(entries, &numLines, titre, description, annee, jour, mois, status);
                        break;
                    case 2:
                        debut0:
                        int repet;
                        printf("entre le nombre de tache tu va ajouter: ");
                        scanf("%d", &repet);
                        getchar();
                        for(int i = numLines; i < repet; i++){
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
                    
                        printf("Entrez le statut de la tache (a realiser, en cours de realisation, finalisee ) : ");
                        getchar(); 
                        fgets(status, sizeof(status), stdin);
                        status[strcspn(status, "\n")] = '\0';
                    
                        printf("Entrez le nombre de taches a ajouter : ");
                        scanf("%d", &repet);
                        ajouterNouvelleTache(entries, &numLines, titre, description, annee, jour, mois, status);
                        }
                        break;
                    default:
                        goto debut0;
                        break;
                
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
                break;
            case 3:
                debut2:
                printf("1, Modifier la description d'une tache \n2, Modifier le statut d'une tache \n3, Modifier le deadline d'une tache \n");
                scanf("%d", &choix);
                switch(choix) {
                    case 1:
                        int taskID;
                        char newDescription[100];

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &taskID);

                        printf("Entrez la nouvelle description de la tache : ");
                        getchar();
                        fgets(newDescription, sizeof(newDescription), stdin);
                        newDescription[strcspn(newDescription, "\n")] = '\0'; 

                        modifierDescription(entries, numLines, taskID, newDescription);
                        break;

                    case 2:
                        char newStatus[20];

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &taskID);

                        printf("Entrez le nouveau statut de la tache : ");
                        getchar();
                        fgets(newStatus, sizeof(newStatus), stdin);
                        newStatus[strcspn(newStatus, "\n")] = '\0'; // Remove trailing newline character

                        modifierStatut(entries, numLines, taskID, newStatus);
                        break;

                    case 3:
                        int newAnnee, newJour, newmois;

                        printf("Entrez l'ID de la tache dont vous souhaitez modifier la deadline : ");
                        scanf("%d", &taskID);

                        printf("Entrez la nouvelle annee de la deadline : ");
                        scanf("%d", &newAnnee);

                        printf("Entrez le nouveau jour de la deadline : ");
                        scanf("%d", &newJour);

                        printf("Entrez le nouveau mois de la deadline : ");
                        scanf("%d", &newmois);

                        modifierDeadline(entries, numLines, taskID, newAnnee, newJour, newmois);
                        break;
                    default:
                        printf("choix invalide!!");
                    goto debut2;
                    break;
                }
                break;
            case 4:
                debut3:
                printf("1, Supprimer une tache par identifiant \n");
                scanf("%d", &choix);
                switch(choix) {
                    case 1:

                        printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
                        scanf("%d", &taskID);
                        if (taskID >= 0 && taskID <= numLines){

                            for(int i = taskID; i <= numLines; i++)
                            {
                                entries[i] = entries[i + 1];
                                (numLines--);
                                printf("la tache tu saisi est supprimer avec success!");
                            }
                            break;
                        }
                        else{
                            printf("la tache tu saisi n'existe pas!");
                        }
                        break;
                    default:
                        printf("choix invalide!!");
                    goto debut3;
                    break;
                }
                break;
            case 5:
                debut4:
                printf("1, Rechercher une tache par son Identifiant \n2, Rechercher une tache par son Titre \n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        int Tid;
                        printf("donnez le nombre de tache: ");
                        scanf("%d", &Tid);
                        printf("le titre de tache d'indentification %d : %s \n", Tid, entries[Tid].titre);
                        printf("le description de tache d'indentification %d : %s \n", Tid, entries[Tid].description);
                        printf("le dead Line de tache d'indentification %d : %d / %d / %d  \n", Tid, entries[Tid].datel.annee, entries[Tid].datel.jour, entries[Tid].datel.mois);
                        printf("le statut de tache d'indentification %d : %s \n", Tid, entries[Tid].status);
                        break;
                    case 2:
                        char Ttitre[50];
                        char check[10];
                        printf("donnez le titre de votre tache: ");
                        scanf("%[^\n]", Ttitre);
                        for(int i = 0; i < numLines; i++){
                            if(strcmp(entries[i].titre, Ttitre) == 0){
                                printf("le titre de votre tache est: ", entries[i].titre);
                                printf("le description de votre tache est: ", entries[i].description);
                                printf("le status de votre tache est: ", entries[i].status);
                                printf("le deadline de votre tache est: %d / %d / %d", entries[i].datel.annee, entries[i].datel.jour, entries[i].datel.mois);
                            }
                        }
                        break;
                    default:
                        printf("choix invalide!!");
                        goto debut4;
                        break;
                }
                break;
            case 6:
                debut5:
                printf("1, Afficher le nombre total des taches \n2, Afficher le nombre de taches complètes et incomplètes \n3, Afficher le nombre de jours restants jusqu'au delai de chaque tache \n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        int totalTaches = afficheNombreTotal(numLines);
                        printf("le total de tache est: %d", totalTaches);
                        break;
                    case 2:
                        int count;
                        for(int i = 0; i < numLines; i++){
                            if(strcmp(entries[i].status, "a realiser") == 0 || strcmp(entries[i].status, "en cours de realisation") == 0){
                                count++;
                            }
                        }
                        printf("le nombre de tache incompletes est: %d", &count);
                        printf("le nombre de tache completes est: %d", &numLines - &count);
                        break;
                    case 3:
                        
                        break;
                    default:
                        printf("choix invalide!!");
                        goto debut5;
                        break;
                }
                break;
            case 7:
                if(numLines > 0){
                    FILE *file = fopen(dataFileNama, "w");
                    if (file == NULL) {
                    perror("Error opening file for writing");
                    exit(1); 
                    }
                    for(int i = 0; i < numLines; i++){
                        fprintf(file, "%s\n", entries[i].datel);
                        fprintf(file, "%s\n", entries[i].description);
                        fprintf(file, "%s\n", entries[i].id);
                        fprintf(file, "%s\n", entries[i].status);
                        fprintf(file, "%s\n", entries[i].titre);
                    }
                    fclose(file);
                    exit(0);
                    break;
                }
                break;
            
        default:
            printf("Entre Un choix valide!! \n");
            goto debut11;
}

    }
    }
        return 0;
}



