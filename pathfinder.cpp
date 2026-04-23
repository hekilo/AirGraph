#include "pathfinder.h"
#include <queue>

PathFinder::PathFinder(const FlightGraph& graph)
    : graph(graph)
    {}

double PathFinder::CalculatePathWeight(const std::vector<Flight>& path, Criteria criteria) const{
    if(path.empty())
        return 0;

    double sum = 0;
    QDateTime lastArrival = path[0].Departure;

    for(const Flight& flight : path){
        sum += CalculateWeight(flight, lastArrival, criteria);
        lastArrival = flight.Arrival;
    }

    return sum;
}

std::vector<std::vector<Flight>> PathFinder::GetDirectFlights(int startId, int endId, Criteria criteria, int k) const {
    std::vector<std::vector<Flight>> results;
    const auto& outgoing = graph.GetFlightsFrom(startId);

    for (const auto& f : outgoing) {
        if(results.size() >= k) {
            break;
        }

        if (f.DestId == endId) {
            results.push_back({f});
        }
    }

    std::sort(results.begin(), results.end(), [this, criteria](const std::vector<Flight>& a, const std::vector<Flight>& b) {
        return CalculateWeight(a[0], QDateTime(), criteria) < CalculateWeight(b[0], QDateTime(), criteria);
    });

    return results;
}

double PathFinder::CalculateWeight(const Flight& flight, const QDateTime& lastArrival, Criteria criteria) const{
    switch(criteria){
    case Criteria::Price :
        return flight.Price;
    case Criteria::Time : {
        qint64 duration = flight.Departure.secsTo(flight.Arrival);
        qint64 wait = 0;
        if (lastArrival.isValid()) {
            wait = lastArrival.secsTo(flight.Departure);
        }

        return static_cast<double>(duration + wait);
    }
    case Criteria::Combo : {
        qint64 duration = flight.Departure.secsTo(flight.Arrival);
        qint64 wait = 0;
        if (lastArrival.isValid()) {
            wait = lastArrival.secsTo(flight.Departure);
        }

        double hours = (wait + duration) / 3600.0;
        return hours * 10 + flight.Price;
    }
    }

    return 0;
}

std::vector<Flight> PathFinder::FindPathRestricted(
    int startId, int endId, Criteria criteria,
    const std::unordered_set<int>& forbiddenAirports,
    const std::vector<Flight>& forbiddenFlights,
    double initialWeight,
    QDateTime initialArrival) const
{
    std::priority_queue<LocalState, std::vector<LocalState>, std::greater<LocalState>> pq;
    pq.push({initialWeight, startId, initialArrival, {}});

    std::unordered_map<int, int> visitCount;

    while(!pq.empty()){
        LocalState state = pq.top();
        pq.pop();

        if(state.AirportId == endId){
            return state.path;
        }

        if (visitCount[state.AirportId] > 100) {
            continue;
        }
        visitCount[state.AirportId]++;

        const std::vector<Flight>& flights = graph.GetFlightsFrom(state.AirportId);

        for(const Flight& flight : flights){

            if (state.Arrival.isValid() && state.Arrival.addSecs(MIN_TRANSFER_TIME) > flight.Departure) {
                continue;
            }

            if(forbiddenAirports.find(flight.DestId) != forbiddenAirports.end()){
                continue;
            }

            bool hasCycle = false;
            if (flight.DestId == startId) hasCycle = true;
            else {
                for (const Flight& f : state.path) {
                    if (f.DestId == flight.DestId) {
                        hasCycle = true;
                        break;
                    }
                }
            }
            if (hasCycle) continue;

            bool isForbidden = false;
            for(const Flight& forbidden : forbiddenFlights){
                if(forbidden.FlightNumber == flight.FlightNumber &&
                    forbidden.DestId == flight.DestId)
                {
                    isForbidden = true;
                    break;
                }
            }

            if(isForbidden) continue;

            double weightStep = CalculateWeight(flight, state.Arrival, criteria);
            double newWeight = state.CurrentWeight + weightStep;

            std::vector<Flight> newPath = state.path;
            newPath.push_back(flight);

            pq.push({newWeight, flight.DestId, flight.Arrival, newPath});
        }
    }

    return {};
}

std::vector<std::vector<Flight>> PathFinder::FindKShortestPaths(int startId, int endId, Criteria criteria, int K) const{
    std::vector<std::vector<Flight>> answer;

    std::priority_queue<PathCandidate,std::vector<PathCandidate>, std::greater<PathCandidate>> pq;

    std::vector<Flight> shortest = FindPathRestricted(startId, endId, criteria);

    if(shortest.empty())
        return answer;

    answer.reserve(K);
    answer.push_back(shortest);

    for(int k = 1; k < K; ++ k ){

        const std::vector<Flight>& prevPath = answer[k - 1];

        for(int i = 0; i < prevPath.size(); ++ i){

            int spurNode = prevPath[i].SourceId;

            std::vector<Flight> rootPath(prevPath.begin(), prevPath.begin() + i);
            double weight = CalculatePathWeight(rootPath, criteria);

            QDateTime spurArrival;
            if (!rootPath.empty()) {
                spurArrival = rootPath.back().Arrival;
            }

            std::unordered_set<int> forbiddenAirports;
            std::vector<Flight> forbiddenFlights;

            for(const std::vector<Flight>& p : answer){
                if(p.size() <= i) continue;

                bool match = true;

                for(int j = 0; j < i; ++ j){
                    if(p[j].FlightNumber != rootPath[j].FlightNumber){
                        match = false;
                        break;
                    }
                }

                if(match){
                    forbiddenFlights.push_back(p[i]);
                }
            }

            for(const Flight& flight : rootPath){
                forbiddenAirports.insert(flight.SourceId);
            }

            std::vector<Flight> spurPath = FindPathRestricted(
                spurNode, endId, criteria,
                forbiddenAirports, forbiddenFlights,
                weight, spurArrival);

            if (!spurPath.empty()) {
                std::vector<Flight> totalPath = rootPath;
                totalPath.insert(totalPath.end(), spurPath.begin(), spurPath.end());

                double totalWeight = CalculatePathWeight(totalPath, criteria);
                pq.push({totalPath, totalWeight});
            }
        }

        if (pq.empty()) break;


        bool foundNewPath = false;
        while (!pq.empty()) {
            PathCandidate bestCandidate = pq.top();
            pq.pop();

            bool exists = false;
            for (const auto& p : answer) {

                if (p.size() == bestCandidate.path.size()) {

                    bool same = true;
                    for (int i = 0; i < p.size(); ++ i ) {
                        if (p[i].FlightNumber != bestCandidate.path[i].FlightNumber) {
                            same = false;
                            break;
                        }
                    }
                    if (same) {
                        exists = true;
                        break;
                    }

                }
            }

            if (!exists) {
                answer.push_back(bestCandidate.path);
                foundNewPath = true;
                break;
            }
        }

        if (!foundNewPath) break;
    }

    return answer;
}
