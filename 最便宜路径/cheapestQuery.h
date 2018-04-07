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
#include<queue>
#include<functional>


void input();//将数据从文件读入
void output(wstring startName,wstring endName);//输出从站点startName到站点endName的路线
bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID);//判断编号为ID的线路是否已在图中存储
void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]);//dijkstra算法，sourceVertex为源点，distanceFromSource为到各线路价格，predecessor存储前驱节点
busStop* outputStops(int fromID, int toID, busStop* fromStop);//输出从fromID线路到toID线路的路径，起始站点为fromStop
void outputSingleLine(int endID, busStop* start, busStop* end);//输出单条线路上的路径，起始站点为start，结束站点为end