#include "agent_fourmi.h"

Agent_fourmi::Agent_fourmi(int sommet_initiale, int sommet_final, double agent_capaciter_logisitque, Graphe* p_graphe)
{
    this->sommet_initiale = sommet_initiale;
    this->sommet_final = sommet_final;
    this->agent_capaciter_logisitque = agent_capaciter_logisitque;
    this->p_graphe = p_graphe;

    //On consturie le graphe de phéromone
    for(int i = 0; i < this->p_graphe->taille_graphe_complet(); i++)
    {
        QVector<double> ligne_graphe_pheromone;
        for(int j = 0; j < this->p_graphe->taille_graphe_complet(); j++)
        {
            ligne_graphe_pheromone.append(1);
        }
        graph_pheromone.append(ligne_graphe_pheromone);
    }
}

void Agent_fourmi::set_parametre(double alpha, double beta, double gamma, QVector<int> liste_sommet_possible)
{
    this->estActive = true;
    this->alpha = alpha;
    this->beta = beta;
    this->gamma = gamma;
    distance_parcourue = 0;
    this->liste_sommet_possible = liste_sommet_possible;
}

int Agent_fourmi::arriver(int sommet)
{
    //qDebug() << "arriver !";
    suprimer_sommet_possible(sommet);

    //On ajoute le sommet à la liste des sommets parcouru
    liste_sommet_parcouru.append(sommet);


    //On ajoute la disantce parcoure à distance_parcourue
    distance_parcourue += p_graphe->poid_sommet(liste_sommet_parcouru.last(), sommet);

    return sommet;
}



int Agent_fourmi::mouvement()
{
    int sommet_actuelle;

    if(liste_sommet_parcouru.size() > 0)
    {
        sommet_actuelle = liste_sommet_parcouru.last();
    }
    else
    {
        sommet_actuelle = sommet_initiale;
    }


    QVector<double> liste_desirabilite_sommet;

    qDebug() << "Liste des sommet possible :" << liste_sommet_possible;

    //On calcule la désirabiliter pour chaque sommet possible
    for(int sommet_possible : liste_sommet_possible)
    {
        liste_desirabilite_sommet.append(gamma + qPow((1/p_graphe->poid_sommet(sommet_actuelle, sommet_possible)), beta) * qPow(graph_pheromone[sommet_actuelle][sommet_possible], alpha));
    }

    //On choisie un sommet
    double somme_desirabilite = 0;
    for(int i = 0; i < liste_desirabilite_sommet.size(); i++)
    {
        somme_desirabilite += liste_desirabilite_sommet[i];
    }

    int index_sommet_suivant;
    double somme_prov = 0;
    double valeur_alea = QRandomGenerator::global()->bounded(somme_desirabilite);
    //qDebug() << "valeur de la somme : " << somme_desirabilite;
    //qDebug() << "valeur de l'alea : " << valeur_alea;

    index_sommet_suivant = 0;
    for(int i = 0; i < liste_desirabilite_sommet.size() && somme_prov < valeur_alea; i++)
    {
        somme_prov += liste_desirabilite_sommet[i];
        index_sommet_suivant += 1;
    }
    index_sommet_suivant -= 1;

    //qDebug() << "sommet_suivant : " << liste_sommet_possible[index_sommet_suivant];

    return arriver(liste_sommet_possible[index_sommet_suivant]);
}

void Agent_fourmi::suprimer_sommet_possible(int sommet)
{
    //On suprimes ce sommet de la liste des sommets possible
    int index = 0;
    while(index < liste_sommet_possible.size() && liste_sommet_possible[index] != sommet)
    {
        index++;
    }
    if(index < liste_sommet_possible.size())
    {
        liste_sommet_possible.remove(index);
    }

}

double Agent_fourmi::getDistance_parcourue() const
{
    return distance_parcourue;
}

bool Agent_fourmi::getEstActive() const
{
    return estActive;
}
