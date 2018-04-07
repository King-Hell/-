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


void input();//�����ݴ��ļ�����
void output(wstring startName,wstring endName);//�����վ��startName��վ��endName��·��
bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID);//�жϱ��ΪID����·�Ƿ�����ͼ�д洢
void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]);//dijkstra�㷨��sourceVertexΪԴ�㣬distanceFromSourceΪ������·�۸�predecessor�洢ǰ���ڵ�
busStop* outputStops(int fromID, int toID, busStop* fromStop);//�����fromID��·��toID��·��·������ʼվ��ΪfromStop
void outputSingleLine(int endID, busStop* start, busStop* end);//���������·�ϵ�·������ʼվ��Ϊstart������վ��Ϊend