#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#define MAXSIZE 200   // ���վ����
#define INF INT_MAX   // �����

struct vertex
{
	string name;
	bool isTransferStation;


};

class graph
{
private:
	int vertexNum;   // ��վ����
	vertex vertices[MAXSIZE];   // վ����Ϣ
	unordered_map<string, size_t> index;   // ����վ�����ҵ��ڴ����±�
	int adjM[MAXSIZE][MAXSIZE];
	bool insertVertex(string station_name)
	{
		if(index.find(station_name) != index.end())
			return false;   // ���и�վ���������
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