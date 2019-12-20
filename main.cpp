/* **************************************************
 *                  数据结构课程设计
 *    题    目  交通换乘规划
 *    姓    名  黄远鹏      学    号  183401050225
 *    班    级  软件1802
 *    指导教师  滕一平
 * ************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

#define MAXSIZE 200   // 最大顶点数
#define INF 0x3f3f3f3f   // 无穷大
enum vehicle_type { subway, normal_bus, air_bus, none = INF };

struct vertex
{
	string name;
	vector<string> line;   // 这一点经过的所有线路
};

class graph
{
private:
	int vertexNum;   // 总顶点数
	vertex vertices[MAXSIZE];   // 顶点信息
	unordered_map<string, size_t> index;   // 根据顶点信息找到对应下标
	vehicle_type adjM[MAXSIZE][MAXSIZE];   // 邻接矩阵
	int timeLT[MAXSIZE][MAXSIZE], pathLT[MAXSIZE][MAXSIZE];   // 保存"时间短"换乘方案结果
	bool insertVertex(string station_name);   // 增加顶点
public:
	graph();
	bool insertEdge(string edge1_name, string edge2_name, vehicle_type weight);   // 插入边
	void lessTime_calculate();   // 预先计算"时间短"换乘方案，查询时可直接输出
	void lessTime(string src_name, string dst_name);   // "时间短"换乘方案
	void lessCost(string src_name, string dst_name);   // "价格低"换乘方案
	void lessTransfer(string src_name, string dst_name);   // "价格低"换乘方案
};

bool graph::insertVertex(string station_name)
{
	if(index.find(station_name) != index.end())   // 已有该顶点，无需插入
		return false;
	vertices[vertexNum].name = station_name;   // 增加一个顶点并初始化相关信息
	index[station_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string vertex1_name, string vertex2_name, vehicle_type weight)
{
	insertVertex(vertex1_name);
	insertVertex(vertex2_name);
	size_t vertex1_index = index[vertex1_name], vertex2_index = index[vertex2_name];
	if(adjM[vertex1_index][vertex2_index] != INF)   // 已有这条边，无需插入
		return false;
	adjM[vertex1_index][vertex2_index] = weight;   // 插入新边
	adjM[vertex2_index][vertex1_index] = weight;
	return true;
}
graph::graph()
{
	vertexNum = 0;
	for(int i = 0; i < MAXSIZE; i++)
		for(int j = 0; j < MAXSIZE; j++)
			adjM[i][j] = none;
}
void graph::lessTime_calculate()
{
	for(int i = 0; i < vertexNum; i++)
		for(int j = 0; j < vertexNum; j++)
			switch(adjM[i][j])
			{
				case subway:     timeLT[i][j] = 3; break;   // 地铁3min走一站
				case normal_bus: timeLT[i][j] = 7; break;   // 公交7min走一站
				case air_bus:    timeLT[i][j] = 7; break;
				case none:       timeLT[i][j] = INF; break;   // 没有直达路径，初始化为INF
			}
	memset(pathLT, -1, sizeof(pathLT));
	for(int k = 0; k < vertexNum; k++)
		for(int i = 0; i < vertexNum; i++)
			for(int j = 0; j < vertexNum; j++)
				if(timeLT[i][k] + timeLT[k][j] < timeLT[i][j])
				{
					timeLT[i][j] = timeLT[i][k] + timeLT[k][j];
					pathLT[i][j] = k;
				}
}

graph map;
void loadMap()   // 加载地图
{
	system("title 交通换乘规划 - 加载地图");
	printf("     交通换乘规划：加载地图\n\n");
	printf("请输入地图文件名，以回车结束：");
	char mapFileName[256];
	cin.getline(mapFileName, 256);
	FILE *fp = fopen(mapFileName, "r");
	while(fp == NULL)
	{
		printf("\n文件打开失败，请检查文件名是否输入正确以及文件是否存在。\n\n");
		printf("请重新输入：");
		cin.getline(mapFileName, 256);
		FILE *fp = fopen(mapFileName, "r");
	}
	printf("\n请稍候...\n\n");
	int n;
	fscanf(fp, "%d", &n);
	string name;   // 线路名称
	int num, type, isCycle;   // 线路站点数  地铁0/普通公交1/空调公交2  是否环线
	for(int i = 0; i < n; i++)
	{
		cin >> name >> num >> type >> isCycle;
		string v1, v2;
		for(int j = 0; j < num - 1 + isCycle; j++)
		{
			cin >> v1 >> v2;
			map.insertEdge(v1, v2, (vehicle_type)type);
		}
	}
	fclose(fp);
	map.lessTime_calculate();
	printf("地图加载成功。");
	system("pause");
}

int main1()
{
	system("color fc");
	loadMap();

	char choice[256];
	while(true)
	{
		system("cls");
		system("title 交通换乘规划");
		fflush(stdin);

	}

	return 0;
}

int main()
{
	main1();



	return 0;
}