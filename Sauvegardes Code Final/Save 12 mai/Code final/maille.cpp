#include "maille.h"
#include <cstring>

Maille* alloc_maille()
{
    Maille* m = (Maille*) malloc(sizeof(Maille));
        m->types = NULL;
        m->atomes = NULL;
        m->lignes = NULL;
        m->p_atomes = NULL;
    return m;
}

void free_maille(Maille* maille)
{
    if(maille != NULL)
    {
        // Tableaux
        free(maille->types);

        // Octree
        vider_octree(maille->atomes);

        // Listes
        vider_l_ligne(maille->lignes);
        vider_l_pre_atome(maille->p_atomes);
    }
}

int premaille_to_maille(Premaille premaille, Maille** maille)
{
    // Premaille est-il valide ? OSEF

    free_maille(*maille);
    *maille = alloc_maille();

    (*maille)->agrandissement = 1.;
    (*maille)->a = premaille.a;
    (*maille)->b = premaille.b;
    (*maille)->c = premaille.c;

    (*maille)->alpha = premaille.alpha;
    (*maille)->beta = premaille.beta;
    (*maille)->gamma = premaille.gamma;

    (*maille)->lignes = premaille.lignes;
    (*maille)->p_atomes = premaille.atomes;

    // On ajoute 3 lignes de symetries "translation"
    concat(&((*maille)->lignes), symetries_translation());

    // Chargement des types
    char symbole[6];
    L_Symbole* l = NULL;
    L_Pre_Atome* buff = premaille.atomes;
    (*maille)->nb_type_atomes = 0;
    while(buff != NULL)
    {
        label_to_symbole(buff->label, symbole);
        (*maille)->nb_type_atomes += ajouter_symbole(&l, symbole);
        buff = buff->queue;
    }
    L_Symbole* buff2 = l;
    int i = 0;
    int index_couleur = 5;
    (*maille)->types = (Atome_Type*) malloc(sizeof(Atome_Type)*(*maille)->nb_type_atomes);
    while(buff2 != NULL && i<(*maille)->nb_type_atomes)
    {
        strcpy((*maille)->types[i].symbole, buff2->symbole);

        (*maille)->types[i].rayon_ionique = 0.1;

        (*maille)->types[i].index_couleur = index_couleur;
        i++;
        do
        {
            index_couleur += 3;
            index_couleur %= 13;
        }
        while(index_couleur == 12); // Pas de transparents
        buff2 = buff2->suivant;
    }

    vider_symbole(l);

    // OSEF
    (*maille)->couleur_trait.r = 0;
    (*maille)->couleur_trait.v = 0;
    (*maille)->couleur_trait.b = 0;

    return 0;
}

int ajouter_symbole(L_Symbole** l, const char symbole[6])
{
    if(*l == NULL)
    {
        *l = (L_Symbole*) malloc(sizeof(L_Symbole));
        strcpy((*l)->symbole, symbole);
        (*l)->suivant = NULL;
        return 1;
    }
    else if(strcmp((*l)->symbole, symbole) == 0)
        return 0;
    else
        return ajouter_symbole(&((*l)->suivant), symbole);
}

void vider_symbole(L_Symbole* l)
{
    if(l!=NULL)
    {
        vider_symbole(l->suivant);
        free(l);
    }
}

void label_to_symbole(const char label[10], char symbole[6])
{
    int i = 0;
    while(label[i] != 0 && (label[i]<= 48 || label[i]> 57) && i<5)
    {
        symbole[i] = label[i];
        i++;
    }
    symbole[i] = 0;
}

void charger_octree(Maille* maille, int nx, int ny, int nz)
{

    L_ligne* lignes = NULL;
    L_Pre_Atome* p_atomes = maille->p_atomes;

    // On calcule le triedre
    Point t_x = {1,0,0};
    Point t_y = {0,1,0};
    Point t_z = {0,0,1};

    // Pour la position dans la maille
    double min_x, min_y, min_z;
    double max_x, max_y, max_z;
    min_max_from_n(nx, &min_x, &max_x);
    min_max_from_n(ny, &min_y, &max_y);
    min_max_from_n(nz, &min_z, &max_z);

    Atome atome;
    int erreur = 0;

    while(p_atomes != NULL)
    {
        atome.type = find_type(maille->types, p_atomes->label, maille->nb_type_atomes);
        lignes = maille->lignes;
        while(lignes != NULL)
        {
            // On remplit la maille
            atome.position = add_pts(mult_scal_pts(calcul_arbre(lignes->x, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_x),
                             add_pts(mult_scal_pts(calcul_arbre(lignes->y, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_y),
                                     mult_scal_pts(calcul_arbre(lignes->z, p_atomes->x, p_atomes->y, p_atomes->z, &erreur), t_z)));
            if(est_dans_cube(atome,min_x,min_y,min_z,max_x,max_y,max_z))
                ajouter_a_l_affichage((&maille->atomes) ,atome);
            lignes = lignes->queue;
        }
        p_atomes = p_atomes->queue;
    }

    remplir_maille(maille, nx, ny, nz);
}

void remplir_maille(Maille* m, int nx, int ny, int nz)
{
    Octree* a_ajouter;
    // Pour la position dans la maille
    double min_x, min_y, min_z;
    double max_x, max_y, max_z;
    min_max_from_n(nx, &min_x, &max_x);
    min_max_from_n(ny, &min_y, &max_y);
    min_max_from_n(nz, &min_z, &max_z);

    m->atomes = supp_octree(m->atomes, min_x, min_y, min_z, max_x, max_y, max_z);

    do
    {
        a_ajouter = NULL;
        former_octree(m->lignes, m->atomes, &a_ajouter, min_x, min_y, min_z, max_x, max_y, max_z);
    }
    while(fusionner_arbre(a_ajouter, &(m->atomes)));
}

void former_octree(L_ligne* lignes, Octree* arbre, Octree** resultat, double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
    if(arbre != NULL)
    {
        ajout_octree(lignes, arbre, resultat, min_x, min_y, min_z, max_x, max_y, max_z);
        int i;
        for(i=0; i<8; i++)
            former_octree(lignes, arbre->fils[i], resultat, min_x, min_y, min_z, max_x, max_y, max_z);
    }
}

void ajout_octree(L_ligne* lignes, Octree* sommet, Octree** resultat, double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
    if(sommet == NULL)
        return;

    Atome atome;
    atome.type = sommet->M.type;
    // On calcule le triedre
    Point t_x = {1,0,0};
    Point t_y = {0,1,0};
    Point t_z = {0,0,1};

    int erreur = 0;
    while(lignes != NULL)
    {
        // On remplit la maille
        atome.position = add_pts(mult_scal_pts(calcul_arbre(lignes->x, sommet->M.position.x, sommet->M.position.y, sommet->M.position.z, &erreur), t_x),
                         add_pts(mult_scal_pts(calcul_arbre(lignes->y, sommet->M.position.x, sommet->M.position.y, sommet->M.position.z, &erreur), t_y),
                                 mult_scal_pts(calcul_arbre(lignes->z, sommet->M.position.x, sommet->M.position.y, sommet->M.position.z, &erreur), t_z)));
        if(est_dans_cube(atome,min_x,min_y,min_z,max_x,max_y,max_z))
            ajouter_a_l_affichage(resultat,atome);
        lignes = lignes->queue;
    }
}

int est_dans_cube(Atome a, double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
    return (a.position.x >= min_x && a.position.x <= max_x
            && a.position.y >= min_y && a.position.y <= max_y
            && a.position.z >= min_z && a.position.z <= max_z);
}

void min_max_from_n(int n, double* min, double* max)
{
    *min = -0.5;
    *max = 0.5;
    int i;
    for(i=2; i<=n; i++)
    {
        if(i%2 == 0) // On change le max
            *max += 0.5;
        else         // On change le min
            *min -= 0.5;
    }
    *min -= EPSILON;
    *max += EPSILON;
}

int find_type(Atome_Type types[], char label[10], int nb_types)
{
    int i;
    for(i=0; i<nb_types; i++)
    {
        if(strstr(label, types[i].symbole) != NULL)
            return i;
    }
    return -1;
}
