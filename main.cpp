#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAXSIZE 200   // 最大站点数
#define INF INT_MAX   // 无穷大

struct vertex
{
	string name;
	bool isTransferStation;


};

class graph
{
private:
	int vertexNum;   // 总站点数
	vertex vertices[MAXSIZE];   // 站点信息
	unordered_map<string, size_t> index;   // 根据站点名找到内存中下标
	int adjM[MAXSIZE][MAXSIZE];
	bool insertVertex(string station_name)
	{
		if(index.find(station_name) != index.end())
			return false;   // 已有该站，无需插入
		vertices[vertexNum].name=
	}
public:
	graph()
	{
		for(int i = 0; i < MAXSIZE; i++)
			for(int j = 0; j < MAXSIZE; j++)
				adjM[i][j] = INF;

	}
};

int main()
{


	return 0;
}