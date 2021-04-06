#ifndef SOMMET_H
#define SOMMET_H

#include <QVector>
#include <QString>
#include "arete.h"

class Sommet
{
public:
    Sommet(QString nom);
    void ajouterArete(Sommet* p_sommet, double poid);

    QString getNom() const;

    double getCout_actuel() const;
    void setCout_actuel(double value);


    bool getEst_marque() const;
    void setEst_marque(bool value);

    QVector<Sommet *> getListe_aretes_sortantes_p_sommet() const;

    QVector<double> getListe_aretes_sortantes_poid() const;

    Sommet *getP_sommet_precedent() const;
    void setP_sommet_precedent(Sommet *value);

private:
    QString nom;
    QVector<Sommet*> liste_aretes_sortantes_p_sommet;
    QVector<double> liste_aretes_sortantes_poid;

    bool est_marque = false;
    Sommet* p_sommet_precedent = nullptr;
    double cout_actuel = std::numeric_limits<double>::infinity();
};

#endif // SOMMET_H
