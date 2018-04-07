#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include"busLine.h"
#include"busStop.h"
#include<sstream>
#include<vector>
#include<map>
#include<list>
#include<stack>


void input();
void output(wstring startName,wstring endName);
bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID);
void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]);
busStop* outStops(int fromID, int toID, busStop* fromStop);
void outSingleLine(int endID, busStop* start, busStop* end);