#include "graphe.h"

Graphe::Graphe(QVector<QString> liste_nom_sommets, QVector<QVector<double>> graphe_initiale, QVector<QString> liste_nom_sommets_demande, QVector<double> liste_capacite_sommets_demande)
{
    this->liste_nom_sommets = liste_nom_sommets;
    this->graphe_initiale = graphe_initiale;
    this->liste_nom_sommets_demande = liste_nom_sommets_demande;
    this->liste_capacite_sommets_demande = liste_capacite_sommets_demande;
    cree_graphe_complet();
}

void Graphe:: cree_graphe_complet()
{
    QDebug info = qInfo().nospace();
    info.~QDebug();

    QVector<Sommet> liste_sommets;
    QVector<Sommet*> liste_p_sommets_demande;


    //On crée les sommets
    for(int i = 0; i < liste_nom_sommets.size(); i++)
    {
        liste_sommets.append(Sommet(liste_nom_sommets[i]));
    }

    //On crée les liens
    for(int i = 0; i < liste_nom_sommets.size(); i++)
    {
        for(int j = 0; j < liste_nom_sommets.size(); j++)
        {
            liste_sommets[i].ajouterArete(&liste_sommets[j], graphe_initiale[i][j]);
        }
    }

    //On cherhce les pointeurs des sommes avec demande
    for(QString nom_sommet : liste_nom_sommets_demande)
    {
        Sommet* p_sommet = nullptr;

        for(int i = 0; i < liste_sommets.size() && p_sommet == nullptr; i++)
        {
            if(liste_sommets[i].getNom() == nom_sommet)
            {
                p_sommet = &(liste_sommets[i]);

                liste_p_sommets_demande.append(p_sommet);
            }
        }
    }

    //On cherche le cout entre chaque sommet avec demande
    for(Sommet* p_sommet_origine : liste_p_sommets_demande)
    {
        QVector<double> ligne_graphe_complet_poid;
        QVector<QVector<QString>> ligne_graphe_complet_itineraire;


        for(Sommet* p_sommet_cible : liste_p_sommets_demande)
        {

            //Réinitailise tous les sommets
            for(int i = 0; i < liste_sommets.size(); i++)
            {
                liste_sommets[i].setP_sommet_precedent(nullptr);
                liste_sommets[i].setEst_marque(false);
                liste_sommets[i].setCout_actuel(std::numeric_limits<double>::infinity());
            }

            //On initialise le front d'exploration
            QVector<Sommet*> front_exploration;
            p_sommet_origine->setCout_actuel(0);
            front_exploration.append(p_sommet_origine);
            bool continue_exploration = true;

            while(continue_exploration)
            {
                //On cherche le sommet dans le front d'exploration avec le cout le plus faible
                Sommet* p_sommet_cout_plus_faible = front_exploration[0];
                for(int i = 1; i < front_exploration.size(); i++)
                {
                    if(front_exploration[i]->getCout_actuel() < p_sommet_cout_plus_faible->getCout_actuel())
                    {
                        p_sommet_cout_plus_faible = front_exploration[i];
                    }
                }

                //On verifie si le p_sommet_cout_plus_faible n'est pas le p_sommet_cible
                front_exploration.removeOne(p_sommet_cout_plus_faible);
                p_sommet_cout_plus_faible->setEst_marque(true);
                if(p_sommet_cout_plus_faible != p_sommet_cible)
                {
                    //On mette à jour le coup pour atindre le voisin du sommet et on marque le sommet
                    int index = 0;

                    for(Sommet* sommet_voisin : p_sommet_cout_plus_faible->getListe_aretes_sortantes_p_sommet())
                    {

                        //Si le voisin n'est pas marquer
                        if(sommet_voisin->getEst_marque() == false)
                        {
                            //Si le cout du voisin est superieur à notre cout actuelle plus le cout pour le joindre on le remplace
                            if(p_sommet_cout_plus_faible->getCout_actuel() + p_sommet_cout_plus_faible->getListe_aretes_sortantes_poid()[index] < sommet_voisin->getCout_actuel())
                            {
                                sommet_voisin->setCout_actuel(p_sommet_cout_plus_faible->getCout_actuel() + p_sommet_cout_plus_faible->getListe_aretes_sortantes_poid()[index]);
                                sommet_voisin->setP_sommet_precedent(p_sommet_cout_plus_faible);
                            }

                            //Si le sommet voisin n'est pas dans le front d'exploration on l'ajoute
                            if(front_exploration.contains(sommet_voisin) == false)
                            {
                                front_exploration.append(sommet_voisin);
                            }
                        }

                        index = index + 1;
                    }
                }
                else
                {
                    //On note les informations
                    continue_exploration = false;
                    QVector<QString> element_graphe_complet_itineraire;

                    ligne_graphe_complet_poid.append(p_sommet_cout_plus_faible->getCout_actuel());

                    QDebug info = qInfo().nospace();
                    do
                    {
                        element_graphe_complet_itineraire.push_front(p_sommet_cout_plus_faible->getNom());

                        if(p_sommet_cout_plus_faible->getP_sommet_precedent() != nullptr)
                        {
                            p_sommet_cout_plus_faible = p_sommet_cout_plus_faible->getP_sommet_precedent();
                        }
                    }
                    while(p_sommet_cout_plus_faible->getP_sommet_precedent() != nullptr);

                    element_graphe_complet_itineraire.push_front(p_sommet_cout_plus_faible->getNom());
                    ligne_graphe_complet_itineraire.append(element_graphe_complet_itineraire);
                }
            }
        }
        graphe_complet_poid.append(ligne_graphe_complet_poid);
        graphe_complet_itineraire.append(ligne_graphe_complet_itineraire);
    }
}

void Graphe::aff_con_nom_sommet()
{
    qInfo() << "";
    qInfo() << "Liste des noms sommets : " << liste_nom_sommets;
    qInfo() << "";
}

void Graphe::aff_con_nom_sommet_demande()
{
    qInfo() << "";
    qInfo() << "Liste des noms sommets demandé : " << liste_nom_sommets_demande;
    qInfo() << "Liste capacites sommets demandés : " << liste_capacite_sommets_demande;
    qInfo() << "";
}

void Graphe::aff_con_poid_graphe_initiale()
{
    qInfo() << "";
    qInfo() << "Affichage graphe initiale :";

    for (int i = 0; i < graphe_initiale.size(); i++)
    {
        QDebug info = qInfo();
        for (int j = 0; j < graphe_initiale[i].size(); j++)
        {
            if(graphe_initiale[i][j] == std::numeric_limits<double>::infinity())
            {
                info << '*';
            }
            else
            {
                info << graphe_initiale[i][j];
            }
        }
    }
    qInfo() << "";
}

void Graphe::aff_con_poid_graphe_complet()
{
    qInfo() << "";
    qInfo() << "Le graphe complet :";


    for (int i = 0; i < graphe_complet_poid.size(); i++)
    {
        QDebug info = qInfo();
        for (int j = 0; j < graphe_complet_poid[i].size(); j++)
        {
            info << graphe_complet_poid[i][j];
        }
        info.~QDebug();
    }
    qInfo() << "";
}

void Graphe::aff_con_itineraire_graphe_complet()
{
    qInfo() << "";
    qInfo() << "Les itinéraires du graphe complet :";
    qInfo() << "";

    for(QString nom_sommet_origine : liste_nom_sommets_demande)
    {
        for(QString nom_sommet_cible : liste_nom_sommets_demande)
        {
            if(nom_sommet_origine != nom_sommet_cible)
            {
                qInfo() << "De" << nom_sommet_origine << "à" << nom_sommet_cible << ":";

                QDebug info = qInfo();
                info << "Itinéraire : ";
                for (QString element : noms_sommets_itineraire(nom_sommet_origine, nom_sommet_cible))
                {
                    info << element;
                }
                info.~QDebug();

                qInfo() << "Avec un cout de : " << noms_sommets_cout(nom_sommet_origine, nom_sommet_cible);
                qInfo() << "";
            }
        }
    }
}

QVector<QString> Graphe::getListe_nom_sommets_demande() const
{
    return liste_nom_sommets_demande;
}

int Graphe::taille_graphe_complet()
{
    return graphe_complet_poid.size();
}

double Graphe::noms_sommets_cout(QString nom_sommet_origine, QString nom_sommet_cible)
{
    int index_sommet_origine;
    int index_sommet_cible;

    for(index_sommet_origine = 0; index_sommet_origine < liste_nom_sommets_demande.size() && liste_nom_sommets_demande[index_sommet_origine] != nom_sommet_origine; index_sommet_origine++)
    {
    }

    for(index_sommet_cible = 0; index_sommet_cible < liste_nom_sommets_demande.size() && liste_nom_sommets_demande[index_sommet_cible] != nom_sommet_cible; index_sommet_cible++)
    {
    }

    return graphe_complet_poid[index_sommet_origine][index_sommet_cible];
}

QVector<QString> Graphe::noms_sommets_itineraire(QString nom_sommet_origine, QString nom_sommet_cible)
{
    int index_sommet_origine;
    int index_sommet_cible;

    for(index_sommet_origine = 0; index_sommet_origine < liste_nom_sommets_demande.size() && liste_nom_sommets_demande[index_sommet_origine] != nom_sommet_origine; index_sommet_origine++)
    {
    }

    for(index_sommet_cible = 0; index_sommet_cible < liste_nom_sommets_demande.size() && liste_nom_sommets_demande[index_sommet_cible] != nom_sommet_cible; index_sommet_cible++)
    {
    }

    return graphe_complet_itineraire[index_sommet_origine][index_sommet_cible];
}

int Graphe::nom_int_sommet(QString nom_sommet)
{
    int index = 0;
    for(QString element : liste_nom_sommets_demande)
    {
        if(element == nom_sommet)
        {
            return index;
        }
        index++;
    }

    return -1;
}

QString Graphe::int_nom_sommet(int numero_sommet)
{
    return liste_nom_sommets_demande[numero_sommet];
}

double Graphe::poid_sommet(int sommet_origine, int sommet_cible)
{
    return graphe_complet_poid[sommet_origine][sommet_cible];
}
