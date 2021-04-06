#ifndef AGENT_VEHICULE_H
#define AGENT_VEHICULE_H

#include<QString>
#include<QDebug>
#include <QVector>

class Agent_vehicule
{
public:
    Agent_vehicule(QString nom_agent, QString nom_sommet_initiale, QString nom_sommet_final, double capacite_logistique);
    void affichage_console_agent_vehicule();

    QString getNom_sommet_initiale() const;
    QString getNom_sommet_final() const;
    double getCapacite_logistique() const;

private:
    QString nom_agent;
    QString nom_sommet_initiale;
    QString nom_sommet_final;
    double capacite_logistique;
    QVector<QString> liste_sommet_parcouru;
};

#endif // AGENT_VEHICULE_H
