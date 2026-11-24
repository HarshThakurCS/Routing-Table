#include "../include/routing_table.hpp"
#include<iomanip>
#include<arpa/inet.h>

using namespace std;


uint32_t ipToInt(const string& ip){
    struct in_addr addr;

    if(inet_pton(AF_INET, ip.c_str(), &addr) != 1){
        throw runtime_error("Invalid IP");
    }
    return ntohl(addr.s_addr);
}

vector<Route> routingTable;

void addRoute(string dest, string mask, string gateway, string iface){
    Route route;

    route.destination = ipToInt(dest);
    route.netmask = ipToInt(mask);
    route.gateway = ipToInt(gateway);
    route.interface = iface;

    routingTable.push_back(route);
}

Route* findBestRoute(uint32_t target){
    Route* bestRoute = nullptr;
    int longestPrefix = -1;
    for(auto& route : routingTable){
        if((target & route.netmask) == route.destination){
            int prefix = __builtin_popcount(route.netmask);

            if(prefix > longestPrefix){
                longestPrefix = prefix;
                bestRoute = &route;
            }
        }
    }
    return bestRoute;
}

void printRouteingTable(){
    cout <<setw(20)<< "Destination"
        <<setw(20)<< "Gateway"
        <<setw(20)<< "Netmask"
        <<setw(20) << "interface";

    for(const auto& route : routingTable){
        cout<<setw(20) <<route.destination
            <<setw(20) << route.gateway
            <<setw(20) << route.netmask
            <<setw(20) << route.interface;
    }
}

