#ifndef ROUTER_TABLE_HPP
#define ROUTER_TABLE_HPP

#include<iostream>
#include<vector>
#include<cstdint>
#include<string>
#include<stdexcept>


using namespace std;

struct Route{
    uint32_t destination;
    uint32_t netmask;
    uint32_t gateway; 
    string interface;
};

uint32_t ipToInt(const string& ip);

void addRoute(string dest, string mask, string gateway, string iface);

Route* findBestRoute(uint32_t target);

void printRouteingTable();

#endif