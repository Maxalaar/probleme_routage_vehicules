#include "instance_routage_vehicules.h"

Instance_routage_vehicules::Instance_routage_vehicules(QString chemin_CSV)
{
    QDebug info = qInfo().nospace();
    info.~QDebug();

    //On lie le fichier CSV pour construire notre graphe de base
    //On ouvre le fichier
    qInfo() << "";
    qInfo() << "Ouverture du fichier :" << chemin_CSV;

    QFile file(chemin_CSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << file.errorString();
    }

    //on lit le fichier
    QVector<QString> liste_nom_sommets;
    QVector<QVector<QString>> fichierString;
    QVector<QString> liste_nom_sommets_demande;
    QVector<double> liste_capacite_sommets_demande;
    QVector<QVector<double>> graphe_initiale;

    //Pour chaque ligne du fichier
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QVector<QString> ligneFichierString;

        //Pour chaque élément de la ligne du fichier on le copie dans fichierString
        for (QString element : line.split(','))
        {
            QString element_prov = element;
            element_prov.remove(QRegExp("\\n"));
            element_prov.remove(" ");

            if(element_prov != "")
            {
                ligneFichierString.append(element_prov);
            }
        }
        fichierString.append(ligneFichierString);
    }

    for(int i = 0; i < fichierString.size(); i++)
    {
        for(int j = 0; j < fichierString[i].size(); j++)
        {

            if(fichierString[i][j] == "1-init")
            {
                i++;
                do
                {
                    //On remplit la liste de noms de sommets avec demande
                    for (QString element : fichierString[i])
                    {
                        liste_nom_sommets_demande.append(element);
                    }

                    i++;

                    //On remplit la valeur de la demande de chaque sommet avec demande
                    for (QString element : fichierString[i])
                    {
                        liste_capacite_sommets_demande.append(element.toDouble());
                    }

                    i++;
                }
                while(fichierString[i][j] != "1-end");
            }

            if(fichierString[i][j] == "2-init")
            {
                i++;
                do
                {
                    //On remplit la liste des agents vehicule
                    liste_agent_vehicule.append(Agent_vehicule(fichierString[i][0], fichierString[i][1], fichierString[i][2], fichierString[i][3].toDouble()));
                    i++;
                }
                while(fichierString[i][j] != "2-end");
            }

            if(fichierString[i][j] == "3-init")
            {
                i++;

                for(int k = 1; k < fichierString[i].size(); k++)
                {
                    liste_nom_sommets.append(fichierString[i][k]);
                }

                i++;

                do
                {
                    //On remplit le tableau du graphe initiale
                    while(fichierString[i][0] != "3-end")
                    {
                        QVector<double> ligne_graphe_initiale;

                        for(int k = 1; k < fichierString[i].size(); k++)
                        {
                            if(fichierString[i][k] == "*")
                            {
                                ligne_graphe_initiale.append(std::numeric_limits<double>::infinity());
                            }
                            else
                            {
                                ligne_graphe_initiale.append(fichierString[i][k].toDouble());
                            }
                        }
                        graphe_initiale.append(ligne_graphe_initiale);
                        i++;
                    }
                }
                while(fichierString[i][j] != "3-end");
            }
        }
    }

    p_graphe = new Graphe(liste_nom_sommets, graphe_initiale, liste_nom_sommets_demande, liste_capacite_sommets_demande);
}

void Instance_routage_vehicules::aff_con_liste_agent_vehicule()
{
    //On affiche la liste des véicules du problèmes
    qInfo() << "";
    qInfo() << "Liste des agents vehicules :";
    for(Agent_vehicule agent : liste_agent_vehicule)
    {
        agent.affichage_console_agent_vehicule();
    }
    qInfo() << "";
}

void Instance_routage_vehicules::aff_con_instance()
{
    p_graphe->aff_con_nom_sommet();
    p_graphe->aff_con_nom_sommet_demande();
    aff_con_liste_agent_vehicule();
    p_graphe->aff_con_poid_graphe_initiale();
    p_graphe->aff_con_poid_graphe_complet();
    //p_graphe->aff_con_itineraire_graphe_complet();
}

int Instance_routage_vehicules::nom_int_sommet(QString nom_sommet)
{
    return p_graphe->nom_int_sommet(nom_sommet);
}

QString Instance_routage_vehicules::int_nom_sommet(int numero_sommet)
{
    return p_graphe->int_nom_sommet(numero_sommet);
}

QVector<Agent_vehicule> Instance_routage_vehicules::getListe_agent_vehicule() const
{
    return liste_agent_vehicule;
}

Graphe *Instance_routage_vehicules::getP_graphe() const
{
    return p_graphe;
}
