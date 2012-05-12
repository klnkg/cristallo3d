// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// TraiterCycle
void TraiterCycleCB()
{
    // Trace pour bien montrer que la fonction est appelee cycliquement
    // printf(""Appel de TraiterCycleCB");

    ActualiserInterface();




    // On redessine la zone
    gInterface.ZoneDessin->redraw() ;

    if (gDonnees.Dark!=1&&gDonnees.Done!=1)
    {

    int ChiffresManquant=0;
    int i=0;

    for (i=0;i<81;i++)
    {
        if (grillin.table[i]==0) // Si la case est �gale � 0 on incr�mente
        {
            ChiffresManquant++; //On fait ici le calcul des chiffres manquant dans la grille
        }
    }
    if (ChiffresManquant==0) //Si on a 0 chiffres qui manquent, parfait la grille est completee
    {
        /*Il vaut mieux mettre la fonction Attente pour la simple raison que la fenetre qui dit qu'on a gagn�
        s'affiche � la position de la souris. Donc si l'utilisateur qui vient de rentrer le dernier chiffre clique de nouveau
        il va fermer directement le message sans le voir et penser que le logiciel ne fonctionne pas...
        Une simple attente d'une demi seconde permet d'eviter ce probl�me... C'est pour �a qu'on peut avoir une sensation de ralenti lorsque l'on gagne
        */
        Attente(0.4); //Fonction attente comme d�crit ci contre
        if (gDonnees.Solution==1) // Si on a trich� et utilis� la solution
        {
            fl_message("Grille Completee" ); //Un message simple
            JouerSon("media\\MyGranny.mp3"); //"Meme ma grand m�re peut faire mieux" Vous avez trich� mais bon
            gDonnees.Solution=0; //On remet la solution � 0
        }
        else // Si on a pas trich� (ou qu'on a juste utilis� le bouton Chuck Norris
        {
            fl_message("Vous avez complete la grille de sodoku : Bravo :)" ); //Bravo; FL MESSAGE
            JouerSon("media\\applause.mp3"); // Clap Clap Clap
        }

        //exit(0);
        gDonnees.Done=1; //LA grille est faite
        gInterface.BoutonChuck->hide();
        gInterface.BoutonVador->hide(); // On cache certains boutons genants
        gDonnees.Chrono=0; // chrono arret�
    }

    }


    if (gDonnees.Chrono == 1) //Si le chrono est lanc�
    {
        gDonnees.Time++; //On incr�mente � chaque cycle

        gDonnees.Seconds = gDonnees.Time / (200/3); // On divise le temps par la dur�e d'un cycle pour l'avoir en seconde (un simple produit en croix)
        if (gDonnees.Seconds > 59) // Si on passe � une minute
        {
            gDonnees.Time=0;
            gDonnees.Min++;
        }
        if (gDonnees.Min > 59) // Si on passe � une heure
        {
            gDonnees.Min=0;
            gDonnees.Heu++;
        }
    }



   // printf("%d",gDonnees.Seconds);

    // Code a activer en cas de probleme pour saisir les evenements du clavier
    // Probleme : si les evenements du clavier ne sont pas bien pris en compte pour agir sur la zone de dessin.
    // Solution : On ramene systematiquement le focus des evenements sur la zone de dessin
    // Attention, cela peut perturber certains elements d'interface comme des champs de saisie texte ou numerique

    // Fl::focus(gInterface.ZoneDessin);

    // Fin code a activer en cas de probleme
}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    int a=0, b=0;

    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!! ==> "Oui je sais bien je me suis fait avoir moi ^^"

    if ( Fl::event() == FL_PUSH )// Si on appui sur le bouton
    {
        if(gDonnees.EnSaisie==1) //Si on est en saisie, on ne fait rien
        {

        }
        else
        {
            printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y()); //On inscrit les valeur dans la console pour verifier
            a = (Fl::event_x()-30)/50; // On rapporte la position du clic � un nombre qui correspon � une case 0 pour la premiere case
            b = (Fl::event_y()-30)/50;

            // a et b numero de case (x et y) de l� ou on a cliqu�
            gDonnees.CaseSaisieX = a * 50 +30; // On prend le num�ro de case, on le multiplie par la largeur de la case plus l'offset du � la fen�tre
            gDonnees.CaseSaisieY = b * 50 +30;
            //gInterface.ChampSaisieNum->show();
            printf("PosX : %d PosY : %d", gDonnees.CaseSaisieX, gDonnees.CaseSaisieY); // On �crit dans la console la position de la case de saisie
            gDonnees.ActuON=1; // Si on a cliqu�, on a demand� a actualiser l'affichage
            if (grillin.table[a+9*b]==0) // Si il n'y a rien dans la case
            {
                gDonnees.DejaOccupe=0; // PAs occup��
                gDonnees.EnSaisie=1; // On est en saisie : le champ num va s'afficher
            }
            else //Si il y a d�j� quelque chose dans la case
            {
                gDonnees.DejaOccupe=1;
            }

        }


    }

}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) // On n'utilise pas le clavier dans le programme
{
    // Definition des variables
    int Touche ;
    int a,b,c,d,e,f,g,h,i = 0; // Pour le Konami code;)

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            a = 1;
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            b = 1;
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            c = 1;
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            d = 1;
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            e = 1;
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            f = 1;
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
    }
}

//Fin du programme :

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    //Utile quand on en a marre qu'on nous pose des questions ^^
    //exit(0);

    int Reponse ;

    Reponse = fl_ask("Voulez vous quitter ce jeu merveilleux ?"); // Il l'est n'es-ce pas? :-P
    if (Reponse == 1)
    {
        exit(0);
    }
    else {gDonnees.Recommencer=1;}; // Sinon  on se met en mode recommencer pour reload la fen�tre
}


/*
Les CB des boutons facile moyen et difficile font chacun la m�me chose :
g�n�ration d'une grille al�atoirement avec Creation grille
Puis on pr�pare la grille en fonction de la difficult� (1 pour facile 2 moyen et 3 difficile
Ensuite on cache certains boutons et on en affiche d'autre (comme le timer)
Et c'est parti
*/

void BoutonFacileCB(Fl_Widget* w, void* data)
{
    CreationGrille(&grillin);
    GrilleResolue=grillin;
    PreparationGrille(&grillin, 1);
    GrilleTemp=grillin;
    gInterface.BoutonFacile -> hide();
    gInterface.BoutonMoyen -> hide();
    gInterface.BoutonExpert -> hide();
    gInterface.BoutonChuck -> show();
    gInterface.BoutonSolOui ->show();
    gDonnees.Chrono=1;
    gInterface.Secondes->show();
    gInterface.Minutes->show();
    gInterface.Heures->show();
    gInterface.BoutonVador->hide();
    //JouerSon("media\\breath.mp3");
}

void BoutonMoyenCB(Fl_Widget* w, void* data)
{
    CreationGrille(&grillin);
    GrilleResolue=grillin;
    PreparationGrille(&grillin, 2);
    GrilleTemp=grillin;
    gInterface.BoutonFacile -> hide();
    gInterface.BoutonMoyen -> hide();
    gInterface.BoutonExpert -> hide();
    gInterface.BoutonChuck -> show();
    gInterface.BoutonSolOui ->show();
    gDonnees.Chrono=1;
    gInterface.Secondes->show();
    gInterface.Minutes->show();
    gInterface.Heures->show();
    gInterface.BoutonVador->hide();
}

void BoutonExpertCB(Fl_Widget* w, void* data)
{
    CreationGrille(&grillin);
    GrilleResolue=grillin;
    PreparationGrille(&grillin, 3);
    GrilleTemp=grillin;
    gInterface.BoutonFacile -> hide();
    gInterface.BoutonMoyen -> hide();
    gInterface.BoutonExpert -> hide();
    gInterface.BoutonChuck -> show();
    gInterface.BoutonSolOui ->show();
    gDonnees.Chrono=1;
    gInterface.Secondes->show();
    gInterface.Minutes->show();
    gInterface.Heures->show();
    gInterface.BoutonVador->hide();
}

//Bouton qui permet d'afficher l'aide...

void BoutonAideCB(Fl_Widget* w, void* data)
{
    fl_message("Cliquer sur les cases vides pour remplir la grille de sudoku :)" );
}

//Bouton d'affichage de la solution du sudoku...

void BoutonSolutionCB ( Fl_Widget* w, void* data)
{
    if (gInterface.BoutonSolOui->value() == 1 ) // SI on a appuy� sur le bouton solution
    {
        GrilleTemp = grillin;
        grillin = GrilleResolue; //On �crase grillin par la grille r�solue (celle qu'on avait au d�but avant d'effacer des nombres
        gDonnees.Solution=1; // Mais attention, on a trich�, on est fliqu�
    }
}


// Bouton Chuck Norris

void BoutonChuckCB( Fl_Widget* w, void* data )
{
    int alea1; // on cr�e un nombre al�atoire
    do
    {
        alea1 = rand () %81;// entre 0 et 81
        printf("test %d",alea1);
    } while (grillin.table[alea1]!=0); // On retire un nombre al�atoire tant que la case vis�e n'est pas vide
    // On comprendra bien que lorsqu'il ne reste qu'une case vide, on doit souvent faire une 80 aine de tirages ( c'est instantan�)
    //JouerSon("media\\Wololo.mp3");

    grillin.table[alea1]=GrilleResolue.table[alea1]; // On copie le chiffre de la case en question de la grille r�solue � la grille actuelle

}


// CB du bouton de saisie num�rique qui se balade en temps r��l
void ChampSaisieNumCB( Fl_Widget* w, void* data )
{
    int Valeur ;
    int a=0;
    int b=0;
    Valeur = gInterface.ChampSaisieNum->value() ; // On assigne ce qu'on a rentr� dans Valeur
    printf("Ca marche! : %d",Valeur);
    gInterface.ChampSaisieNum->hide() ; // On peut cacher le champ alors

    printf("Blabla3");
    a = (gDonnees.CaseSaisieX / 50); // On divise la position de la case dans laquelle on saisissais par la largeur de la case .
    b = (gDonnees.CaseSaisieY / 50); // Du coup, on a avec a et b les position dans la grille du chiffre
    printf("a:%d",a);
    printf("b:%d",b);
    grillin.table[a+9*b]=Valeur; // On assigne la valeur r�cup�r�e dans le tableau

    printf("Blabla");

    gDonnees.Incorrect=3; // On remet le message d'erreur � z�ro

    if (gDonnees.Dark==0) // Si on est pas en mode r�solution
    {
        if (grillin.table[a+9*b] != GrilleResolue.table[a+9*b]) // On compare la grille rentr�e � la vraie grille. si on a une diff�rence
        {
            //JouerSon("media\\No.mp3");
            //gInterface.NotificationErreur->value( "Reponse incorrecte" ) ;
            printf("Reponse incorrecte");
            gDonnees.Incorrect=1; // On est en incorrect
            //fl_alert("Reponse incorrecte :'(" );
            grillin.table[a+9*b]=0; // Et on remets las valeur dans le tableau � 0

        }

    }

    if (Valeur>9||Valeur<0) // Si on est pas dans la bonne gammme de valeur (ex : 12)
    {
        //gInterface.NotificationErreur->value( "Valeur incorrecte" ) ;
        //fl_alert("Reponse non comprise entre 0 et 9 :'(" );
        gDonnees.Incorrect=2; // Affichage d'un message d'erreur
        grillin.table[a+9*b]=0; // On remet � 0
    }

    //gInterface.NotificationErreur->value( "" ) ;
    /*
    if (grillin.table[a+9*b] == GrilleResolue.table[a+9*b])
        {
            JouerSon("media\\Yes.mp3");
        }
    */
    gDonnees.EnSaisie=0; // � la fin de la CB on a fini : on est plus en saisie

}



//CB du bouton r�solution de la grille par IA
void BoutonVadorCB( Fl_Widget* w, void* data )
{
    gInterface.Fenetre->begin();
    gInterface.Fenetre->color(FL_BLACK) ;
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();// On fait un peu le m�nage sur la fen�tre
    gInterface.BoutonChercherSolutions->show();
    gInterface.BoutonAide->hide();
    gInterface.BoutonExpert->hide();
    gInterface.BoutonFacile->hide();
    gInterface.BoutonMoyen->hide();
    gDonnees.Dark=1; // On est pass� en DarkSide
    JouerSon("media\\SabreLaser.mp3");
}


// CB du bouton pour trouver la solution de la grille rentr�e
void BoutonChercherSolutionsCB ( Fl_Widget* w, void* data )
{
    //ResolutionGrilleLigneParLigne(&grillin); // C'�tait une id�e pour r�soudre la grille mais elle n'a pas fonctionn�e

    /*
    =================================

    /!\ On utilise ici une fonction de r�solution du sudoku propos�e par
    Mr Rusty Russel
    (Le concepteur principal du FireWall de Linux

     ==================================
     */

    ResolutionGrilleMrLinux(&grillin); // On fait appel � la fonction R�solution
    gDonnees.Incorrect=4; //Ca marche donc on marque : grille r�solue
}


//CB du bouton recommencer , reload
void BoutonRecommencerCB ( Fl_Widget* w, void* data )
{
    gDonnees.Incorrect=3; //On efface le texte
    gDonnees.Recommencer = 1; // On recommence �  tout regenerer : on �crase la fen�tre et on en recr�e une autre

}
