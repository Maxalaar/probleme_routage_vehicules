#include "mainwindow.h"

#include <QApplication>

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QString>

#include "graphe.h"
#include "agent_vehicule.h"
#include "instance_routage_vehicules.h"
#include "resolution_routage_vehicules.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    /*
    qInfo() << "Début du programme";

    Graphe* p_graphe = lecture_CSV("graph_4.csv");
    p_graphe->aff_con_poid_graphe_initiale();
    p_graphe->cree_graphe_complet();
    p_graphe->aff_con_poid_graphe_complet();
    p_graphe->aff_con_itineraire_graphe_complet();
    */

    //Instance_routage_vehicules("graph_4.csv");

    Resolution_routage_vehicules("graph_5.csv", "para_1.csv");

    //w.show();
    //return a.exec();

    return 0;
}
