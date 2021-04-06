#include "resolution_routage_vehicules.h"

Resolution_routage_vehicules::Resolution_routage_vehicules(QString chemin_CSV_instance, QString chemin_CSV_instance_parametre)
{
   p_instance_routage_vehicules = new Instance_routage_vehicules(chemin_CSV_instance);
   charger_CVS_parametre(chemin_CSV_instance_parametre);

    p_instance_routage_vehicules->aff_con_instance();
    aff_con_parametre_parametre();

    resolution_routage_vehicules();
}

void Resolution_routage_vehicules::charger_CVS_parametre(QString chemin_CSV_instance_parametre)
{
    QDebug info = qInfo().nospace();
    info.~QDebug();

    //On lie le fichier CSV pour construire notre graphe de base
    //On ouvre le fichier
    qInfo() << "";
    qInfo() << "Ouverture du fichier :" << chemin_CSV_instance_parametre;

    QFile file(chemin_CSV_instance_parametre);
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

     int ligne;

     //On rentre les paramétres de alpha
     ligne = 1;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            alpha[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            alpha[i-2] = qQNaN();
        }
     }

     //On rentre les paramétres de beta
     ligne = 2;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            beta[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            beta[i-2] = qQNaN();
        }
     }

     //On rentre les paramétres de gamma
     ligne = 3;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            gamma[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            gamma[i-2] = qQNaN();
        }
     }

     //On rentre les paramétres de Q
     ligne = 4;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            Q[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            Q[i-2] = qQNaN();
        }
     }

     //On rentre les paramétres de rho
     ligne = 5;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            rho[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            rho[i-2] = qQNaN();
        }
     }

     //On rentre les paramétres de m
     ligne = 6;
     m = fichierString[ligne][2].toInt();

     //On rentre les paramétres de n
     ligne = 7;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            n[i-2] = fichierString[ligne][i].toInt();
        }
        else
        {
            n[i-2] = qSNaN();
        }
     }

     //On rentre les paramétres de c
     ligne = 8;
     for(int i = 2; i < 7; i++)
     {
        if(i < fichierString[ligne].size())
        {
            c[i-2] = fichierString[ligne][i].toDouble();
        }
        else
        {
            c[i-2] = qQNaN();
        }
     }
}

void Resolution_routage_vehicules::aff_con_parametre_parametre()
{
    qInfo() << "";
    qInfo() << "Les paramétres :";
    qInfo() << "Afichage de alpha :";
    for(double element : alpha)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de beta :";
    for(double element : beta)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de gamma :";
    for(double element : gamma)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de Q :";
    for(double element : Q)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de rho :";
    for(double element : rho)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de m :";
    qInfo() << m;

    qInfo() << "";
    qInfo() << "Afichage de n :";
    for(double element : n)
    {
         qDebug() << element;
    }

    qInfo() << "";
    qInfo() << "Afichage de c :";
    for(double element : c)
    {
         qDebug() << element;
    }
    qInfo() << "";
}

void Resolution_routage_vehicules::resolution_routage_vehicules()
{
    qInfo() << "Debut de la résolution :";

    //On crée les fourmis
    for(Agent_vehicule v_prov : p_instance_routage_vehicules->getListe_agent_vehicule())
    {
        liste_fourmis.append(new Agent_fourmi(p_instance_routage_vehicules->nom_int_sommet(v_prov.getNom_sommet_initiale()), p_instance_routage_vehicules->nom_int_sommet(v_prov.getNom_sommet_final()), v_prov.getCapacite_logistique(), p_instance_routage_vehicules->getP_graphe()));
    }

    //Le nombre de répétion
    for(int i = 0; i < m; i++)
    {
        //Le nombre de solution par répétion
        for(int j = 0; j < n[0]; j++)
        {
            //On crée la liste des sommet possible:
            QVector<int> liste_sommet_possible;
            liste_sommet_possible.clear();

            for(int i = 0; i < p_instance_routage_vehicules->getP_graphe()->getListe_nom_sommets_demande().size(); i++)
            {
                liste_sommet_possible.append(i);
            }

            //On définie les paramétres des fourmis
            for(int k = 0; k < liste_fourmis.size(); k++)
            {
                liste_fourmis[k]->set_parametre(alpha[0], beta[0], gamma[0], liste_sommet_possible);
            }

            //Tant que tous les sommet ne sont pas marquer
            while(liste_sommet_possible.size() > 0)
            {
                //On cherhce l'agent fourmis active avec la plus petite valeur de distance parcourue
                Agent_fourmi* p_agent_fourmi_moins_distance = nullptr;
                double moins_distance = INFINITY;

                for(int i = 0; i < liste_fourmis.size(); i++)
                {
                    if(liste_fourmis[i]->getDistance_parcourue() < moins_distance && liste_fourmis[i]->getEstActive() == true)
                    {
                        moins_distance = liste_fourmis[i]->getDistance_parcourue();
                        p_agent_fourmi_moins_distance = liste_fourmis[i];
                    }
                }

                if(p_agent_fourmi_moins_distance != nullptr)
                {
                    int sommet_marquer;
                    sommet_marquer = p_agent_fourmi_moins_distance->mouvement();

                    //Si le sommet est marquer, on le suprime de la liste des sommets possible
                    if(sommet_marquer > -1)
                    {
                        //On suprimes ce sommet de la liste des sommets possible
                        int index = 0;
                        while(liste_sommet_possible[index] != sommet_marquer)
                        {
                            index++;
                        }
                        liste_sommet_possible.remove(index);


                        //Pour toute les autres forumis ce sommet n'est pas disponible
                        for(int k = 0; k < liste_fourmis.size(); k++)
                        {
                            liste_fourmis[k]->suprimer_sommet_possible(-8);
                        }

                    }
                }
                else
                {
                    qInfo() << "Attention : l'instance n'est pas réalisable";
                }
            }

        }

    }
}
