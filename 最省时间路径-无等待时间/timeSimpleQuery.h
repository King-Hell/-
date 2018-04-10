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
void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[],busLine* line[]);//dijkstra算法，sourceVertex为源点，distanceFromSource为到各线路价格，predecessor存储前驱节点
void printPath(int predecessor[], busLine* line[], int endID);