#include "../include/routing_table.hpp"
#include "../src/RouterTable.cpp"

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
