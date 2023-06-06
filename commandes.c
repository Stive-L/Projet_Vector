//
// Created by Stive on 03/06/2023.
//
#include "commandes.h"
#include <string.h>
#include <ctype.h>

Command * create_command(){
    Command * cmd = malloc(sizeof(Command));
    cmd -> int_size = 0;
    cmd ->str_size = 0;
    cmd -> name[0] = '\0';

    for (int i = 0;i < 10;i++){
        cmd -> int_params[i] = 0;
        cmd ->str_params[i] = NULL;
    }
    return cmd;
}

void add_str_param(Command * cmd, char* p){
    if (cmd ->str_size > 9){
        printf("Erreur : hors indice tableau str_params");
        return;
    }
    cmd->str_params[(cmd->str_size)] = malloc(strlen(p) + 1);
    strcpy(cmd->str_params[(cmd->str_size)++], p);

}

void add_int_param(Command * cmd, int p){
    if (cmd ->int_size > 9){
        printf("Erreur : hors indice du tableau int_param");
        return;
    }
    cmd->int_params[(cmd->int_size)++] = p;
}

void free_cmd(Command *cmd){
    free(cmd);
    cmd = NULL;
}

void read_from_stdin(Command* cmd){
    printf(">>");
    char nom_cmd[100];
    fgets(nom_cmd,100,stdin);
    nom_cmd[strcspn(nom_cmd, "\n")] = '\0'; // On enleve le caractère retour à la ligne lors de l'utilisation de fgets
    char * token_cmd = strtok(nom_cmd," "); // Extraire le nom de la commande saisit par l'utilisateur
    if (token_cmd  != NULL){
        strcpy(cmd->name,token_cmd);
        token_cmd = strtok(NULL," ");
        while (token_cmd != NULL){
            if (isdigit(token_cmd[0])){ // On vérifie si c'est un entier
                int valeur = atoi(token_cmd); // Convertir une chaine en un entier
                add_int_param(cmd, valeur);
            }
            else{
                add_str_param(cmd, token_cmd);
            }
            token_cmd = strtok(NULL," ");
        }
    }
}

int read_exec_command(Command * cmd, Area * area){
    //printf("%s", cmd->name);
    if (strcmp(cmd->name,"clear") == 0) {
        clear_area(area);
    }

    else if (strcmp(cmd->name, "exit") == 0){
        return 1;
    }

    else if (strcmp(cmd->name, "point") == 0){
        Shape * point = create_point_shape(cmd->int_params[0],cmd->int_params[1]);
        add_shape_to_area(area, point);
    }

    else if (strcmp(cmd->name, "line") == 0){
        Shape * line = create_line_shape(cmd->int_params[0],cmd->int_params[1],cmd->int_params[2],cmd->int_params[3]);
        add_shape_to_area(area, line);
    }

    else if (strcmp(cmd->name, "circle") == 0){
        Shape * circle = create_circle_shape(cmd->int_params[0],cmd->int_params[1], cmd->int_params[2]);
        add_shape_to_area(area,circle);
    }

    else if (strcmp(cmd->name, "square") == 0){
        Shape * square = create_square_shape(cmd->int_params[0],cmd->int_params[1],cmd->int_params[2]);
        add_shape_to_area(area,square);
    }

    else if (strcmp(cmd->name, "rectangle") == 0){
        Shape * rectangle = create_rectangle_shape(cmd->int_params[0],cmd->int_params[1],cmd->int_params[2],cmd->int_params[3]);
        add_shape_to_area(area,rectangle);
    }

    else if (strcmp(cmd->name, "polygon") == 0){
        Shape * polygon = create_polygon_shape(cmd->int_params, cmd->int_size);
        add_shape_to_area(area,polygon);
    }

    else if (strcmp(cmd->name, "plot") == 0){
        draw_area(area);
        print_area(area);

    }

    else if (strcmp(cmd->name, "list") == 0){
        for (int i = 0; i<area->nb_shapes;i++){
            printf("ID : %d  ", area->shapes[i]->id);
            print_shape(area->shapes[i]);
            printf("\n");
        }
    }

    else if (strcmp(cmd->name, "delete") == 0){
         for (int i = 0 ; i<area->nb_shapes;i++){ // On parcourt tous les shapes de l'area
             if (cmd->int_params[0] == area->shapes[i]->id){
                 delete_shape(area->shapes[i]);
                 for (int j = i;j<area->nb_shapes;j++){
                     area->shapes[j] = area->shapes[j+1];
                 }
                 area->nb_shapes--; // On décrémente le nombre de formes
                 area->shapes[area->nb_shapes] = NULL;
                 break;
             }
         }
        clear_area(area); // On remet/refresh tous les pixels à 0
    }

    else if (strcmp(cmd->name,"erase")==0){
        erase_area(area);
    }

    else if(strcmp(cmd->name, "help") == 0){
        printf("Voici ci-dessous la liste des commandes : \n");
        printf("- clear : effacer l'écran\n");
        printf("- exit : quitter l'écran\n");
        printf("- point x y : ajouter un point\n");
        printf("- line x1 y1 x2 y2 : ajouter un segment reliant deux points (x1, y1) et (x2,y2)\n");
        printf("- circle x y radius : ajouter un cercle de centre (x,y) et de rayon radius\n");
        printf("- square x y length : ajouter un carré dont le coin supérieur gauche est (x,y) et de côté length\n");
        printf("- rectangle x y width height : ajouter un rectangle dont le coin supérieur gauche est (x,y), de largeur width et de longueur height\n");
        printf("- polygon x1 y1 x2 y2 x3 y3 ... ... : ajouter un polygon avec la liste des points donnés\n");
        printf("- plot : rafraîchir l'écran pour afficher toutes les formes géométriques de l'image (en fonction des règles d'affichage)\n");
        printf("- list : afficher la liste de l'ensemble des formes géométriques qui composent l'image ainsi que toutes leurs informations\n");
        printf("- delete id : supprimer une forme à partir de son identifiant id");
        printf("- erase : supprimer toutes les formes d'une image\n");
        printf("- help : afficher la liste des commandes ainsi qu'un mini mode d'emploi permettant à l'utilisateur d'utiliser les commandes correctement\n");
    }
    else {
        printf("Commande inconnue, tapez help pour découvrir la liste des commandes disponibles !\n");
    }
    return 0;
}
