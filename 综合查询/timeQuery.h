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

#define cheapest 0
#define timeNoWait 1
#define timeWithWait 2

void input();//�����ݴ��ļ�����
void output(wstring startName,wstring endName,int type);//�����վ��startName��վ��endName��·��
void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[],busLine* line[],int type);//dijkstra�㷨��sourceVertexΪԴ�㣬distanceFromSourceΪ������·�۸�predecessor�洢ǰ���ڵ�
void printPath(int predecessor[], busLine* line[], int endID);