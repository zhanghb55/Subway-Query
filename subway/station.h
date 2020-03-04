//
//  station.h
//  subway
//
//  Created by �ź�� on 2019/12/5.
//  Copyright @ 2019 �ź��. All rights reserved.
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
//����վ�ṹ 
struct station {
	string station_name;//վ��
	int station_id;//վ���
	bool transfer;//�Ƿ�Ϊ��תվ
	int dist_to_next;//����һվ�ľ���
	string line_name;//��������·
	station() = default;
	station(string name, int id_, int dist,string linename) {
		station_name = name;
		station_id = id_;
		transfer = false;
		dist_to_next = dist;
		line_name = linename;
	}
};
//�����߽ṹ 
struct line {
	string line_name;//��·���ƣ���1����
	vector<station> all_station;
	line() = default;
	line(string name, vector<station>stations) {
		line_name = name;
		all_station = stations;
	}
};
//�ҵ����е���תվ 
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
//�������������г��� 
class subway {
private:
	vector<line> all_lines;
	vector<station> transfer_station;
public:
	subway(vector<line>lines) {
		all_lines = lines;
		vector<station> res;
		//�ҵ����еĵ�����תվ 
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
	//������������ʾ�������� 
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
		//����ʱ��1min
		for (int i = 0; i < transfer_station.size(); i += 2) {
			res[transfer_station[i].station_id][transfer_station[i + 1].station_id] = 1;
			res[transfer_station[i + 1].station_id][transfer_station[i].station_id] = 1;
		}
		return res;
	}
	//����map�����ҵ�����վ�ı��
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
	//����һ����·�ľ��� 
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
