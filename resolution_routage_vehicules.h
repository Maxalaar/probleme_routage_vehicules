#ifndef RESOLUTION_ROUTAGE_VEHICULES_H
#define RESOLUTION_ROUTAGE_VEHICULES_H

#include<QVector>

#include"instance_routage_vehicules.h"
#include"agent_fourmi.h"

class Resolution_routage_vehicules
{
public:
    Resolution_routage_vehicules(QString chemin_CSV_instance, QString chemin_CSV_instance_parametre);
    void charger_CVS_parametre(QString chemin_CSV_instance_parametre);
    void aff_con_parametre_parametre();
    void resolution_routage_vehicules();

private:
    Instance_routage_vehicules* p_instance_routage_vehicules;
    double alpha[5];
    double beta[5];
    double gamma[5];
    double Q[5];
    double rho[5];
    int m;
    double n[5];
    double c[5];
    double f;
    QVector<Agent_fourmi*> liste_fourmis;
};

#endif // RESOLUTION_ROUTAGE_VEHICULES_H
