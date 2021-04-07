#include "agent_vehicule.h"

Agent_vehicule::Agent_vehicule(QString nom_agent, QString nom_sommet_initiale, QString nom_sommet_final, double capacite_logistique)
{
    this->nom_agent = nom_agent;
    this->nom_sommet_initiale = nom_sommet_initiale;
    this->nom_sommet_final = nom_sommet_final;
    this->capacite_logistique = capacite_logistique;
}

void Agent_vehicule::affichage_console_agent_vehicule()
{
    qDebug() << "Nom de l'agent :" << nom_agent << "Sommet initiale :" << nom_sommet_initiale << "Sommet final :" << nom_sommet_final << "Capacité logistique :" << capacite_logistique;
}

QString Agent_vehicule::getNom_sommet_initiale() const
{
    return nom_sommet_initiale;
}

QString Agent_vehicule::getNom_sommet_final() const
{
    return nom_sommet_final;
}

double Agent_vehicule::getCapacite_logistique() const
{
    return capacite_logistique;
}

QString Agent_vehicule::getNom_agent() const
{
    return nom_agent;
}
