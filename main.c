#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 80

// Structure pour représenter un nœud de la liste chaînée
typedef struct Node {
    char nom[MAX_NAME_LENGTH];
    char article[MAX_NAME_LENGTH];
    int nombre;
    int prix;
    struct Node* next;
} Node;

// Fonction pour créer un nouveau nœud
Node* createNode(const char* nom, const char* article, int nombre, int prix) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->nom, nom);
    strcpy(newNode->article, article);
    newNode->nombre = nombre;
    newNode->prix = prix;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour ajouter un nœud à la fin de la liste
void appendNode(Node** head, Node* newNode) {
    if (*head == NULL) {
        *head = newNode; // Si la liste est vide, le nouveau nœud devient la tête
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next; // Parcourir jusqu'au dernier nœud
    }
    current->next = newNode; // Ajouter le nouveau nœud à la fin
}

// Fonction pour afficher la liste chaînée
void printList(Node* head) {
    Node* current = head;
    int i = 1;
    while (current != NULL) {
        printf("Ligne %d:\n", i);
        printf("Nom: %s\n", current->nom);
        printf("Article: %s\n", current->article);
        printf("Nombre: %d\n", current->nombre);
        printf("Prix: %d\n\n", current->prix);
        current = current->next;
        i++;
    }
}

int main() {
    // Initialisation de la tête de la liste chaînée
    Node* head = NULL;

    // Ouverture du fichier en mode lecture
    FILE* fp = fopen("donnees.txt", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return EXIT_FAILURE;
    }

    // Lecture des données depuis le fichier
    char nom[MAX_NAME_LENGTH];
    char article[MAX_NAME_LENGTH];
    int nombre, prix;
    while (fscanf(fp, "%79s %79s %d %d", nom, article, &nombre, &prix) == 4) {
        Node* newNode = createNode(nom, article, nombre, prix);
        appendNode(&head, newNode);
    }

    // Fermeture du fichier
    fclose(fp);

    // Affichage du contenu de la liste chaînée
    printf("Contenu de la liste chaînée :\n");
    printList(head);

    // Libération de la mémoire allouée pour la liste chaînée
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}
