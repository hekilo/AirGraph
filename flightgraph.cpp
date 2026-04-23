#include "flightgraph.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <vector>
#include <algorithm>

FlightGraph::FlightGraph() {}

Airport FlightGraph::GetAirport(int id) const{
    auto it = airports.find(id);
    if(it == airports.end())
        return {-1, "Неизвестно", "Неизвестно"};

    return it->second;
}

const std::vector<Flight>& FlightGraph::GetFlightsFrom(int id) const{
    auto it = adjacencyList.find(id);

    if(it == adjacencyList.end()){
        static const std::vector<Flight> emptyList;
        return emptyList;
    }

    return it->second;
}

bool FlightGraph::LoadFromJson(const QString& path){

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Не удалось открыть файл" << path;
        return false;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &error);

    if(error.error != QJsonParseError::NoError){
        qWarning() << "Ошибка парсинга: " << error.errorString();
        return false;
    }

    Clear();
    QJsonObject root = doc.object();
    QJsonArray airportsArray = root["Airports"].toArray();

    for(const QJsonValue& val: airportsArray){
        QJsonObject obj = val.toObject();
        Airport airport;
        airport.Id = obj.value("Id").toInt();
        airport.City = obj.value("City").toString();
        airport.Code = obj.value("Code").toString();
        airports[airport.Id] = airport;
    }

    QJsonArray flightsArray = root["Flights"].toArray();
    for(const QJsonValue& val : flightsArray){
        QJsonObject obj = val.toObject();
        Flight flight;
        flight.FlightNumber = obj.value("FlightNumber").toString();
        flight.SourceId = obj.value("SourceId").toInt();
        flight.DestId = obj.value("DestId").toInt();
        flight.Price = obj.value("Price").toDouble();
        flight.Arrival = QDateTime::fromString(obj.value("Arrival").toString(), Qt::ISODate);
        flight.Departure = QDateTime::fromString(obj.value("Departure").toString(), Qt::ISODate);

        adjacencyList[flight.SourceId].push_back(flight);
    }

    qDebug() << "Успешно загружено; Аэропортов: " << airports.size() << " Количество полетов: " << flightsArray.size();
    return true;
}

bool FlightGraph::SaveToJson(const QString& path) const{

    QJsonObject root;

    QJsonArray airportsArray;
    for(const auto& p : airports){
        QJsonObject obj;
        obj["Id"] = p.second.Id;
        obj["Code"] = p.second.Code;
        obj["City"] = p.second.City;

        airportsArray.push_back(obj);
    }
    root["Airports"] = airportsArray;

    QJsonArray flights;
    for(const auto& p : adjacencyList){

        for(const auto& flight : p.second){
            QJsonObject obj;
            obj["FlightNumber"] = flight.FlightNumber;
            obj["Arrival"] = flight.Arrival.toString(Qt::ISODate);
            obj["Departure"] = flight.Departure.toString(Qt::ISODate);
            obj["DestId"] = flight.DestId;
            obj["SourceId"] = flight.SourceId;
            obj["Price"] = flight.Price;

            flights.append(obj);
        }
    }
    root["Flights"] = flights;

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        qWarning() << "Не удалось открыть файл" << path;
        return false;
    }

    QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Файлы усешно загружены";
    return true;
}

std::vector<int> FlightGraph::GetAllAirportsIds() const{

    std::vector<int> allIds;
    for(const auto& airportInfo : airports){
        allIds.push_back(airportInfo.first);
    }

    return allIds;
}

bool FlightGraph::AddAirport(const Airport& airport){
    if(airports.find(airport.Id) != airports.end()){
        return false;
    }

    airports[airport.Id] = airport;
    return true;
}

bool FlightGraph::AddFlight(const Flight& flight){

    if(airports.find(flight.SourceId) == airports.end() || airports.find(flight.DestId) == airports.end()){
        return false;
    }

    for(const auto& p : adjacencyList[flight.SourceId]){
        if(flight.FlightNumber == p.FlightNumber){
            return false;
        }
    }

    adjacencyList[flight.SourceId].push_back(flight);
    return true;
}

void FlightGraph::Clear(){
    adjacencyList.clear();
    airports.clear();
}

bool FlightGraph::DeleteAirport(int airportId) {
    if (airports.find(airportId) == airports.end()) {
        return false;
    }

    airports.erase(airportId);
    adjacencyList.erase(airportId);

    for (auto& p : adjacencyList) {

        p.second.erase(
            std::remove_if(p.second.begin(), p.second.end(),
                           [airportId](const Flight& f) { return f.DestId == airportId; }),
            p.second.end());

    }

    return true;
}

bool FlightGraph::DeleteFlight(const QString& flightNumber, int sourceId) {
    if (adjacencyList.find(sourceId) == adjacencyList.end()) {
        return false;
    }

    auto& flights = adjacencyList[sourceId];

    for (auto it = flights.begin(); it != flights.end(); ++it) {

        if (it->FlightNumber == flightNumber) {
            flights.erase(it);
            return true;
        }

    }

    return false;
}
