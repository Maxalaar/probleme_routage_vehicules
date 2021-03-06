#ifndef AGENT_FOURMI_H
#define AGENT_FOURMI_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <graphe.h>
#include <QtMath>
#include <QRandomGenerator>

class Agent_fourmi
{
public:
    Agent_fourmi(int sommet_initiale, int sommet_final, double agent_capaciter_logisitque, Graphe* p_graphe, double pheromone_initiale, QString nom);
    void set_parametre(double alpha, double beta, double gamma, QVector<int> liste_sommet_possible);
    int mouvement_apprentissage();
    int mouvement_final();

    void suprimer_sommet_possible(int sommet);
    void application_pheromone(double rho, QVector<int> liste_sommet_parcour, double quantite_pheromone);

    double getDistance_parcourue() const;
    bool getEstActive() const;
    QVector<int> getListe_sommet_parcouru() const;

    QString getNom() const;

private:
    QString nom;
    int arriver(int sommet);
    int sommet_initiale;
    int sommet_final;
    double agent_capaciter_logisitque;
    QVector<int> liste_sommet_possible;
    QVector<int> liste_sommet_parcouru;
    QVector<QVector<double>> graph_pheromone;
    double alpha;
    double beta;
    double gamma;
    Graphe* p_graphe;
    double distance_parcourue = 0;
    bool estActive = false;
};

#endif // AGENT_FOURMI_H
