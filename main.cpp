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
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

#define MAXSIZE 200   // 最大顶点数
#define INF 0x3f3f3f3f   // 无穷大

struct vertex
{
	string name;
	bool isTransferStation;


};

class graph
{
private:
	int vertexNum;   // 总顶点数
	vertex vertices[MAXSIZE];   // 顶点信息
	unordered_map<string, size_t> index;   // 根据顶点信息找到对应下标
	int adjM[MAXSIZE][MAXSIZE];   // 邻接矩阵
	int distanceLT[MAXSIZE][MAXSIZE], pathLT[MAXSIZE][MAXSIZE];   // 保存"时间短"换乘方案结果
	bool insertVertex(string station_name);   // 增加顶点
public:
	graph();
	bool insertEdge(string edge1_name, string edge2_name, int weight);   // 插入边
	void floyd();   // floyd算法求解换乘方案
	void lessTime(string src, string dst);   // "时间短"换乘方案
	void lessCost();   // "价格低"换乘方案
};

bool graph::insertVertex(string station_name)
{
	if(index.find(station_name) != index.end())   // 已有该顶点，无需插入
		return false;
	vertices[vertexNum].name = station_name;   // 增加一个顶点并初始化相关信息
	vertices[vertexNum].isTransferStation = false;
	index[station_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string edge1_name, string edge2_name, int weight)
{
	insertVertex(edge1_name);
	insertVertex(edge2_name);
	size_t edge1_index = index[edge1_name], edge2_index = index[edge2_name];
	if(adjM[edge1_index][edge2_index] != INF)   // 已有这条边，无需插入
		return false;
	adjM[edge1_index][edge2_index] = weight;   // 插入新边
	adjM[edge2_index][edge1_index] = weight;
	return true;
}
graph::graph()
{
	vertexNum = 0;
	for(int i = 0; i < MAXSIZE; i++)
		for(int j = 0; j < MAXSIZE; j++)
			adjM[i][j] = INF;
}
void graph::floyd()
{
	// "时间短"换乘方案
	memcpy(distanceLT, adjM, sizeof(adjM));
	memset(pathLT, -1, sizeof(pathLT));
	for(int k = 0; k < vertexNum; k++)
		for(int i = 0; i < vertexNum; i++)
			for(int j = 0; j < vertexNum; j++)
				if(distanceLT[i][k] + distanceLT[k][j] < distanceLT[i][j])
				{
					distanceLT[i][j] = distanceLT[i][k] + distanceLT[k][j];
					pathLT[i][j] = k;
				}

	// "价格低"换乘方案

}
void graph::lessTime(string src, string dst)
{

}
void graph::lessCost()
{

}

graph map;
void loadMap()   // 加载地图
{
	system("title 交通换乘规划 - 加载地图");
	printf("   交通换乘规划：加载地图\n\n");
	printf("   请输入地图文件名，以回车结束：");
	char mapFileName[256];
	scanf("%[^\n]", mapFileName);
	FILE *fp = fopen(mapFileName, "r");
	int n;
	fscanf(fp, "%d", &n);
	char lineName[256];
	for(int i = 0; i < n; i++)
	{

	}




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


	return 0;
}