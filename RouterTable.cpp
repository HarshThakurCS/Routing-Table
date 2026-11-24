#include<iostream>
#include<arpa/inet.h>
#include<vector>
#include<cstdint>
#include<string>
#include<iomanip>

using namespace std;

struct Route{
    uint32_t destination;
    uint32_t netmask;
    uint32_t gateway; 
    string interface;
};

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

int main(){
    addRoute("10.0.0.0", "255.0.0.0", "192.168.1.1", "eth0");  
    addRoute("10.1.0.0", "255.255.0.0", "192.168.1.2", "eth0");  
    addRoute("10.1.2.0", "255.255.255.0", "192.168.1.3", "eth0");  
    printRouteingTable();  

    string target;
    cout<<"Enter target IP: ";
    cin>>target;

    uint32_t targetip = ipToInt(target);
    Route* best = findBestRoute(targetip);

    if(best != nullptr){
        cout<<"\nBest Route found!\n";

        cout<< "Gateway: "<<best->gateway<<endl;
        cout <<"Interface: "<<best->interface<<endl;
    }else{
        cout<<"\nNo matuching route found.\n";
    }

    return 0;
}