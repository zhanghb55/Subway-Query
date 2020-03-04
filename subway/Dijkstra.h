#pragma once


#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "station.h"

#define INF 2147483647
using namespace std;


class Vertex {
public:
	int order;
	int dist;
	int from;
	Vertex(int o, int d) {
		order = o;
		dist = d;
		from = -1;
	}
};
bool operator < (const Vertex& a, const Vertex& b) {
	return a.dist < b.dist;
}

vector<vector<int>> mkgraph() {
	int n;
	cin >> n;
	vector<vector<int>> graph;
	for (int i = 0; i < n; i++) {
		vector<int> temp;
		for (int j = 0; j < n; j++) {
			int r;
			cin >> r;
			temp.push_back(r);
		}
		//  cout << endl << i << endl;
		graph.push_back(temp);
	}
	return graph;
}

vector<Vertex> Dijkstra(int s, Graph a) {
	//s是起点，a是图 
	int n = a.size();
	vector<Vertex> all_Vertex;
	priority_queue<Vertex> pqueue;
	vector<bool>visit;
	for (int i = 0; i < n; i++) {
		Vertex temp(i, INF);
		all_Vertex.push_back(temp);
		visit.push_back(false);
	}
	all_Vertex[s].dist = 0;
	all_Vertex[s].from = s;
	visit[s] = true;
	pqueue.push(all_Vertex[s]);
	while (!pqueue.empty()) {
		Vertex temp = pqueue.top();
		pqueue.pop();
		for (int i = 0; i < n; i++) {
			if (a[temp.order][i] != 0 && !visit[i]) {
				if (temp.dist + a[temp.order][i] < all_Vertex[i].dist) {
					all_Vertex[i].dist = temp.dist + a[temp.order][i];
					all_Vertex[i].from = temp.order;
					pqueue.push(all_Vertex[i]);
				}
			}
		}
	}
	return all_Vertex;
}
vector<int> find_way(vector<Vertex> all_Vertex, int begin, int end) {
	int target = -1;
	for (int i = 0; i < all_Vertex.size(); i++) {
		if (all_Vertex[i].order == end) {
			target = i;
			break;
		}
	}
	for (int i = 0; i < all_Vertex.size(); i++) {
		if (all_Vertex[i].order == end) {
			target = i;
			break;
		}
	}
	vector<int> res;
	stack<int> temp_res;
	temp_res.push(all_Vertex[target].order);
	while (all_Vertex[target].order != begin) {
		int front_point = all_Vertex[target].from;
		for (int i = 0; i < all_Vertex.size(); i++) {
			if (all_Vertex[i].order == front_point) {
				target = i;
				break;
			}
		}
		temp_res.push(all_Vertex[target].order);
	}
	while (!temp_res.empty()) {
		int temp = temp_res.top();
		res.push_back(temp);
		temp_res.pop();
	}
	return res;
}
//用于获取路线的函数
vector<station> get_result(string from,string to) {
	ifstream in;
	in.open("subway_information.txt");
	int n;
	in >> n;//输入地铁线数量
	vector<line> lines;
	int count = 0;
	for (int i = 0; i < n; i++) {
		string line_name;
		in >> line_name;//输入线路名称
		int m;
		in >> m;//输入该线路地铁站数量
		line temp;
		temp.line_name = line_name;
		for (int j = 0; j < m; j++) {
			string sname;
			in >> sname;
			int to_next;
			in >> to_next;
			station new_station(sname, count++, to_next,line_name);
			temp.all_station.push_back(new_station);
		}
		lines.push_back(temp);
	}
	in.close();
	//构建广州地铁类 
	subway Guangzhou(lines);
	//得到广州地铁所有中转站 
	vector<station> res = Guangzhou.get_transfer();
	//构建矩阵 
	Graph matrix = Guangzhou.mkgraph();
	//获取所有的站点信息 
	vector<station> all_station = Guangzhou.list_all_station();
	//建立map来对应信息 
	map<string, vector<int>> find_id = Guangzhou.find_station_id();
	//输入起点和终点 
/*	string from;
	cin >> from;
	string to;
	cin >> to;*/

	int min_dist = INF;
	int final_begin = -1;
	int final_end = -1;
	vector<int> final_res;
	for (int i = 0; i < find_id[from].size(); i++) {
		for (int j = 0; j < find_id[to].size(); j++) {
			int begin = find_id[from][i];
			int end = find_id[to][j];
			vector<Vertex> temp = Dijkstra(begin, matrix);
			vector<int> res1 = find_way(temp, begin, end);
			int temp_dist = Guangzhou.calcuate_dist(res1);
			if (temp_dist < min_dist) {
				min_dist = temp_dist;
				final_begin = begin;
				final_end = end;
				final_res = res1;
			}
		}
	}

//	map<station, line> find_station_line = Guangzhou.find_staion_in_which_line();
	//找到我们需要的路线的编号，用vector<int>存储 
	map<int, station> find_station = Guangzhou.find_station();
	vector<station> output;
	for (int i = 0; i < final_res.size(); i++) {
		output.push_back(find_station[final_res[i]]);
	}
	return output;
/*	cout << "From ";
	cout << find_station[final_res[0]].line_name;
	cout << ":" << endl;
	for (int i = 0; i < final_res.size(); i++) {
		cout << find_station[final_res[i]].station_name;
		if (i < final_res.size() - 1 && find_station[final_res[i]].line_name != find_station[final_res[i + 1]].line_name) {
			cout << endl << "Transfer ";
			cout  <<  find_station[final_res[i + 1]].line_name << ":" << endl;
		}
		else if (i < final_res.size() - 1)cout << "->";
		else cout << endl;
	}
	*/
}

vector<string> get_line_name() {
	ifstream in;
	in.open("subway_information.txt");
	int n;
	in >> n;//输入地铁线数量
	vector<string> res;
	vector<line> lines;
	int count = 0;
	for (int i = 0; i < n; i++) {
		string line_name;
		in >> line_name;//输入线路名称
		int m;
		in >> m;//输入该线路地铁站数量
		line temp;
		temp.line_name = line_name;
		for (int j = 0; j < m; j++) {
			string sname;
			in >> sname;
			int to_next;
			in >> to_next;
			station new_station(sname, count++, to_next, line_name);
			temp.all_station.push_back(new_station);
		}
		lines.push_back(temp);
	}
	for (int i = 0; i < lines.size(); i++) {
		res.push_back(lines[i].line_name);
	}
	in.close();
	return res;
}
vector<line> get_line() {
	ifstream in;
	in.open("subway_information.txt");
	int n;
	in >> n;//输入地铁线数量
	vector<line> lines;
	int count = 0;
	for (int i = 0; i < n; i++) {
		string line_name;
		in >> line_name;//输入线路名称
		int m;
		in >> m;//输入该线路地铁站数量
		line temp;
		temp.line_name = line_name;
		for (int j = 0; j < m; j++) {
			string sname;
			in >> sname;
			int to_next;
			in >> to_next;
			station new_station(sname, count++, to_next, line_name);
			temp.all_station.push_back(new_station);
		}
		lines.push_back(temp);
	}
	in.close();
	return lines;
}