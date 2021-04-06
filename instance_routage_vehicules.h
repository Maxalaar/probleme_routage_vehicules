#ifndef INSTANCE_ROUTAGE_VEHICULES_H
#define INSTANCE_ROUTAGE_VEHICULES_H

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QString>

#include "graphe.h"
#include "agent_vehicule.h"

class Instance_routage_vehicules
{
public:
    Instance_routage_vehicules(QString chemin_CSV_instance);
    void aff_con_liste_agent_vehicule();
    void aff_con_instance();

    int nom_int_sommet(QString nom_sommet);
    QString int_nom_sommet(int numero_sommet);

    QVector<Agent_vehicule> getListe_agent_vehicule() const;

    Graphe *getP_graphe() const;

private:
    Graphe* p_graphe;
    QVector<Agent_vehicule> liste_agent_vehicule;
};

#endif // INSTANCE_ROUTAGE_VEHICULES_H
