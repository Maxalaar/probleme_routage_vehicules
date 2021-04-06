#ifndef GRAPHE_H
#define GRAPHE_H

#include <QVector>
#include <QString>
#include <QDebug>

#include "sommet.h"

class Graphe
{
public:
    Graphe(QVector<QString> liste_nom_sommets, QVector<QVector<double>> graphe_initiale, QVector<QString> liste_nom_sommets_demande, QVector<double> liste_capacite_sommets_demande);
    void cree_graphe_complet();
    double noms_sommets_cout(QString nom_sommet_origine, QString nom_sommet_cible);
    QVector<QString> noms_sommets_itineraire(QString nom_sommet_origine, QString nom_sommet_cible);

    int nom_int_sommet(QString nom_sommet);
    QString int_nom_sommet(int numero_sommet);

    double poid_sommet(int sommet_origine, int sommet_cible);
    double poid_sommet(QString sommet_origine, QString sommet_cible);

    QVector<QString> itineraire_sommet(int sommet_origine, int sommet_cible);
    QVector<QString> itineraire_sommet(QString sommet_origine, QString sommet_cible);

    void aff_con_nom_sommet();
    void aff_con_nom_sommet_demande();
    void aff_con_poid_graphe_initiale();
    void aff_con_poid_graphe_complet();
    void aff_con_itineraire_graphe_complet();

    QVector<QString> getListe_nom_sommets_demande() const;

    int taille_graphe_complet();

private:
    QVector<QString> liste_nom_sommets;
    QVector<QVector<double>> graphe_initiale;
    QVector<QVector<double>> graphe_complet_poid;
    QVector<QVector<QVector<QString>>> graphe_complet_itineraire;
    QVector<QString> liste_nom_sommets_demande;
    QVector<double> liste_capacite_sommets_demande;

};

#endif // GRAPHE_H
