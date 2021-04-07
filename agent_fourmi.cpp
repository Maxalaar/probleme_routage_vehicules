#include "agent_fourmi.h"

Agent_fourmi::Agent_fourmi(int sommet_initiale, int sommet_final, double agent_capaciter_logisitque, Graphe* p_graphe, double pheromone_initiale, QString nom)
{
    this->nom = nom;
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
            ligne_graphe_pheromone.append(pheromone_initiale);
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
    this->liste_sommet_parcouru.clear();
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

QVector<int> Agent_fourmi::getListe_sommet_parcouru() const
{
    return liste_sommet_parcouru;
}

QString Agent_fourmi::getNom() const
{
    return nom;
}



int Agent_fourmi::mouvement_apprentissage()
{
    //Si il n'y plus de sommmet possible l'agent ce stope
    if(liste_sommet_possible.size() <= 0)
    {
        estActive = false;
        return -1;
    }

    int sommet_actuelle;

    if(liste_sommet_parcouru.size() > 0)
    {
        sommet_actuelle = liste_sommet_parcouru.last();
    }
    else
    {
        liste_sommet_parcouru.append(sommet_initiale);
        sommet_actuelle = liste_sommet_parcouru.last();
    }

    QVector<double> liste_desirabilite_sommet;

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

    //On ajoute la distance à la distance totale
    distance_parcourue += p_graphe->poid_sommet(sommet_actuelle,  liste_sommet_possible[index_sommet_suivant]);

    /*
    qDebug() << "";
    qDebug() << "Agent : " << nom;
    qDebug() << "sommet actuel : " << sommet_actuelle;
    qDebug() << "Liste des sommets possible :" << liste_sommet_possible;
    qDebug() << "Liste des sommets parcouru :" << liste_sommet_parcouru;
    qDebug() << "Les proba :" << liste_desirabilite_sommet;
    qDebug() << "index sommet_suivant : " << index_sommet_suivant;
    qDebug() << "sommet_suivant : " << liste_sommet_possible[index_sommet_suivant];
    qDebug() << "cout : " << p_graphe->poid_sommet(sommet_actuelle, liste_sommet_possible[index_sommet_suivant]);
    qDebug() << "cout total : " << distance_parcourue;
    qDebug() << "";*/

    return arriver(liste_sommet_possible[index_sommet_suivant]);
}


int Agent_fourmi::mouvement_final()
{
    //Si il n'y plus de sommmet possible l'agent ce stope
    if(liste_sommet_possible.size() <= 0)
    {
        estActive = false;
        return -1;
    }

    int sommet_actuelle;

    if(liste_sommet_parcouru.size() > 0)
    {
        sommet_actuelle = liste_sommet_parcouru.last();
    }
    else
    {
        liste_sommet_parcouru.append(sommet_initiale);
        sommet_actuelle = liste_sommet_parcouru.last();
    }

    QVector<double> liste_pheromone_sommet;

    //On calcule la désirabiliter pour chaque sommet possible
    for(int sommet_possible : liste_sommet_possible)
    {
        liste_pheromone_sommet.append(graph_pheromone[sommet_actuelle][sommet_possible]);
    }

    //On chosie le sommet possible avec le plus de pheromone
    double valeur_pheromone = -INFINITY;
    int index_sommet_suivant;

    for(int i = 0; i < liste_sommet_possible.size(); i++)
    {
        if(graph_pheromone[sommet_actuelle][liste_sommet_possible[i]] > valeur_pheromone)
        {
            valeur_pheromone = graph_pheromone[sommet_actuelle][liste_sommet_possible[i]];
            index_sommet_suivant = i;
        }
    }

    //On ajoute la distance à la distance totale
    distance_parcourue += p_graphe->poid_sommet(sommet_actuelle,  liste_sommet_possible[index_sommet_suivant]);


    qDebug() << "";
    qDebug() << "Agent : " << nom;
    qDebug() << "sommet actuel : " << sommet_actuelle;
    qDebug() << "Liste des sommets possible :" << liste_sommet_possible;
    qDebug() << "Liste des sommets parcouru :" << liste_sommet_parcouru;
    qDebug() << "Les pheromone :" << liste_pheromone_sommet;
    qDebug() << "index sommet_suivant : " << index_sommet_suivant;
    qDebug() << "sommet_suivant : " << liste_sommet_possible[index_sommet_suivant];
    qDebug() << "cout : " << p_graphe->poid_sommet(sommet_actuelle, liste_sommet_possible[index_sommet_suivant]);
    qDebug() << "cout total : " << distance_parcourue;
    qDebug() << "";

    return arriver(liste_sommet_possible[index_sommet_suivant]);
}

void Agent_fourmi::suprimer_sommet_possible(int sommet)
{
    //On suprimes ce sommet de la liste des sommets possible
    int index_sommet = 0;
    while(index_sommet < liste_sommet_possible.size() && liste_sommet_possible[index_sommet] != sommet)
    {
        index_sommet++;
    }
    if(index_sommet < liste_sommet_possible.size())
    {
        liste_sommet_possible.remove(index_sommet);
    }

}

void Agent_fourmi::application_pheromone(double rho, QVector<int> liste_sommet_parcour, double quantite_pheromone)
{
    for(int i = 0; i < graph_pheromone.size(); i++)
    {
        for(int j = 0; j < graph_pheromone[i].size(); j++)
        {
            graph_pheromone[i][j] = (1 - rho) * graph_pheromone[i][j];
        }
    }

    for(int i = 0; i < liste_sommet_parcour.size() - 1; i++)
    {
        graph_pheromone[liste_sommet_parcour[i]][liste_sommet_parcour[i+1]] += quantite_pheromone;
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
