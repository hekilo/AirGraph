#ifndef FLIGHTGRAPH_H
#define FLIGHTGRAPH_H

#include "graph_structures.h"
#include <vector>
#include <unordered_map>

class FlightGraph
{
private:
    std::unordered_map<int, Airport> airports;
    std::unordered_map<int, std::vector<Flight>> adjacencyList;
public:
    FlightGraph();

    bool LoadFromJson(const QString& path);
    bool SaveToJson(const QString& path) const;

    std::vector<int> GetAllAirportsIds() const;

    Airport GetAirport(int id) const;
    const std::vector<Flight>& GetFlightsFrom(int id) const;

    bool AddAirport(const Airport& airport);
    bool AddFlight(const Flight& flight);

    bool DeleteAirport(int id);
    bool DeleteFlight(const QString& flightNumber, int sourceId);

    void Clear();
};

#endif // FLIGHTGRAPH_H
