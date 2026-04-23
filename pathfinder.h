#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "flightgraph.h"

#include <unordered_set>

enum class Criteria {Price, Time, Combo};

struct PathCandidate{
    std::vector<Flight> path;
    double weight;

    bool operator>(const PathCandidate& other) const{
        return weight > other.weight;
    }
};

struct LocalState {
    double CurrentWeight;
    int AirportId;
    QDateTime Arrival;
    std::vector<Flight> path;

    bool operator>(const LocalState& other) const {
        return CurrentWeight > other.CurrentWeight;
    }
};

class PathFinder
{
private:
    const double MIN_TRANSFER_TIME = 3600;

    const FlightGraph& graph;
    double CalculateWeight(const Flight& flight, const QDateTime& lastArrival, Criteria criteria) const;

    std::vector<Flight> FindPathRestricted(int startId, int endId, Criteria crit,
                                           const std::unordered_set<int>& forbiddenAirports = {},
                                           const std::vector<Flight>& forbiddenFlights = {},
                                           double initialWeight = 0,
                                           QDateTime initialArrival = QDateTime()) const;

    double CalculatePathWeight(const std::vector<Flight>& path, Criteria) const;

public:
    PathFinder(const FlightGraph&);

    std::vector<std::vector<Flight>> FindKShortestPaths(int startId, int endId, Criteria crit, int K = 1) const;

    std::vector<std::vector<Flight>> GetDirectFlights(int startId, int endId, Criteria criteria, int k = 1) const;

};

#endif // PATHFINDER_H
