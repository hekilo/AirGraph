#ifndef GRAPH_STRUCTURES_H
#define GRAPH_STRUCTURES_H

#include <QDateTime>
#include <QString>

struct Airport{
    int Id;
    QString Code;
    QString City;
};

struct Flight{
    QString FlightNumber;
    int SourceId;
    int DestId;
    double Price;
    QDateTime Departure;
    QDateTime Arrival;
};

#endif // GRAPH_STRUCTURES_H
