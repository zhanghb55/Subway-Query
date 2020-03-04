//
//  station.h
//  subway
//
//  Created by 张洪宾 on 2019/12/5.
//  Copyright @ 2019 张洪宾. All rights reserved.
//

#ifndef station_h
#define station_h
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef vector<vector<int>> Graph;
//地铁站结构 
struct station {
	string station_name;//站名
	int station_id;//站编号
	bool transfer;//是否为中转站
	int dist_to_next;//到下一站的距离
	string line_name;//在哪条线路
	station() = default;
	station(string name, int id_, int dist,string linename) {
		station_name = name;
		station_id = id_;
		transfer = false;
		dist_to_next = dist;
		line_name = linename;
	}
};
//地铁线结构 
struct line {
	string line_name;//线路名称，如1号线
	vector<station> all_station;
	line() = default;
	line(string name, vector<station>stations) {
		line_name = name;
		all_station = stations;
	}
};
//找到所有的中转站 
vector<station> find_transfer(line& A, line& B) {
	vector<station> res;
	for (int i = 0; i < A.all_station.size(); i++) {
		for (int j = 0; j < B.all_station.size(); j++) {
			if (A.all_station[i].station_name == B.all_station[j].station_name) {
				res.push_back(A.all_station[i]);
				res.push_back(B.all_station[j]);
				A.all_station[i].transfer = B.all_station[j].transfer = true;
			}
		}
	}
	return res;
}
//对整个地铁进行抽象 
class subway {
private:
	vector<line> all_lines;
	vector<station> transfer_station;
public:
	subway(vector<line>lines) {
		all_lines = lines;
		vector<station> res;
		//找到所有的地铁中转站 
		for (int i = 0; i < lines.size(); i++) {
			vector<station> temp;
			for (int j = i + 1; j < lines.size(); j++) {
				temp = find_transfer(lines[i], lines[j]);
				for (int k = 0; k < temp.size(); k++) {
					res.push_back(temp[k]);
				}
			}
		}
		transfer_station = res;
	}
	vector<station> get_transfer() {
		return transfer_station;
	}
	int get_total_number() {
		int total = 0;
		for (int i = 0; i < all_lines.size(); i++) {
			total += all_lines[i].all_station.size();
		}
		return total;
	}
	//建立矩阵来表示地铁线网 
	Graph mkgraph() {
		Graph res;
		int total = get_total_number();
		for (int i = 0; i < total; i++) {
			vector<int> temp;
			for (int j = 0; j < total; j++) {
				temp.push_back(0);
			}
			res.push_back(temp);
		}
		for (int i = 0; i < all_lines.size(); i++) {
			for (int j = 0; j < all_lines[i].all_station.size() - 1; j++) {
				int target = all_lines[i].all_station[j].station_id;
				int target1 = all_lines[i].all_station[j + 1].station_id;
				res[target][target1] = all_lines[i].all_station[j].dist_to_next;
				res[target1][target] = all_lines[i].all_station[j].dist_to_next;
			}
		}
		//换线时间1min
		for (int i = 0; i < transfer_station.size(); i += 2) {
			res[transfer_station[i].station_id][transfer_station[i + 1].station_id] = 1;
			res[transfer_station[i + 1].station_id][transfer_station[i].station_id] = 1;
		}
		return res;
	}
	//建立map用于找到地铁站的编号
	map<string, vector<int>>find_station_id() {
		map<string, vector<int>> res;
		for (int i = 0; i < all_lines.size(); i++) {
			for (int j = 0; j < all_lines[i].all_station.size(); j++) {
				res[all_lines[i].all_station[j].station_name].push_back(all_lines[i].all_station[j].station_id);
			}
		}
		return res;
	}
	map<int, station>find_station() {
		map<int, station> res;
		for (int i = 0; i < all_lines.size(); i++) {
			for (int j = 0; j < all_lines[i].all_station.size(); j++) {
				res[all_lines[i].all_station[j].station_id] = all_lines[i].all_station[j];
			}
		}
		return res;
	}
	//计算一条线路的距离 
	int calcuate_dist(vector<int>res) {
		map<int, station> temp = this->find_station();
		int total = 0;
		for (int i = 0; i < res.size(); i++) {
			total += temp[res[i]].dist_to_next;
		}
		return total;
	}
	vector<station> list_all_station() {
		vector<station> res;
		for (int i = 0; i < all_lines.size(); i++) {
			for (int j = 0; j < all_lines[i].all_station.size(); j++) {
				res.push_back(all_lines[i].all_station[j]);
			}
		}
		return res;
	}
};


#endif /* station_h */
