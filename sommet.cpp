#include "sommet.h"

Sommet::Sommet(QString nom)
{
    this->nom = nom;
}

void Sommet::ajouterArete(Sommet* p_sommet, double poid)
{
    liste_aretes_sortantes_p_sommet.append(p_sommet);
    liste_aretes_sortantes_poid.append(poid);
}

QString Sommet::getNom() const
{
    return nom;
}

double Sommet::getCout_actuel() const
{
    return cout_actuel;
}

void Sommet::setCout_actuel(double value)
{
    cout_actuel = value;
}

bool Sommet::getEst_marque() const
{
    return est_marque;
}

void Sommet::setEst_marque(bool value)
{
    est_marque = value;
}

QVector<Sommet *> Sommet::getListe_aretes_sortantes_p_sommet() const
{
    return liste_aretes_sortantes_p_sommet;
}

QVector<double> Sommet::getListe_aretes_sortantes_poid() const
{
    return liste_aretes_sortantes_poid;
}

Sommet *Sommet::getP_sommet_precedent() const
{
    return p_sommet_precedent;
}

void Sommet::setP_sommet_precedent(Sommet *value)
{
    p_sommet_precedent = value;
}
