/*
 * main.cpp
 *
 *  Created on: 24/03/2017
 *      Author: Jo�o Tom� Saraiva
 */

#include "utils.h"
#include "Graph.h"
#include <sstream>
#include <iostream>
#include "Vehicle.h"

using namespace std;


Graph<int> CreateTestGraph()
{
	Graph<int> myGraph;

	myGraph.addVertex(1,1,1,1);
	myGraph.addVertex(2,1000,2453,1231);
	myGraph.addVertex(3,12038,231,353);
	myGraph.addVertex(4,1232,3243,876);
	myGraph.addVertex(5,3421,2356,012);
	myGraph.addVertex(6,132,1324,985);
	myGraph.addVertex(7,292,1324,812);
	myGraph.addVertex(8,6598,3716,921);
	myGraph.addVertex(9,143,987,687);
	myGraph.addVertex(10,8652,2343,543);


	// distancias em kms
	myGraph.addEdge(1, 2);
	myGraph.addEdge(1, 3);
	myGraph.addEdge(1, 7);
	myGraph.addEdge(2, 4);
	myGraph.addEdge(3, 8);
	myGraph.addEdge(4, 6);
	myGraph.addEdge(4, 5);
	myGraph.addEdge(5, 10);
	myGraph.addEdge(7, 6);
	myGraph.addEdge(8, 9);
	myGraph.addEdge(9, 5);
	myGraph.addEdge(2, 1);
	myGraph.addEdge(3, 1);
	myGraph.addEdge(7, 1);
	myGraph.addEdge(4, 2);
	myGraph.addEdge(8, 3);
	myGraph.addEdge(6, 4);
	myGraph.addEdge(5, 4);
	myGraph.addEdge(10, 5);
	myGraph.addEdge(6, 7);
	myGraph.addEdge(9, 8);
	myGraph.addEdge(5, 9);
	myGraph.addEdge(9, 10);


	return myGraph;
}

int main() {
	Graph<int> myGraph = CreateTestGraph();
	bool quit = false;
	int i = 0;
	vector<Automovel> a;
	vector<RefuelStation> r;
	while(!quit) {
		cout << "0 - quit | 1 - add Vehicle | 2 - Add Refuel Station | 3 - Add Point | 4 - Add Edge | 5 - Calculate Shortest Distance Between two points in vehicle A | 6 - List Vehicle | 7 - List Refuel Stations" << endl;
		cin >> i;
		if (i == 0) {
			quit = true;
		}
		else if (i == 1) {
			bool add = true;
			int id;
			float battery, consume;
			cout << "Id of the Vehicle %of the battery and %/km";
			cin >> id >> battery >> consume;
			for(unsigned int i = 0; i < r.size(); i++) {
				if (a[i].getId() == id) {
					cout << "Vehicle  already exists" << endl;
					add = false;
				}
			}
			if (battery > 100 || battery < 0) {
				cout << "Battery must be a value between 100 and 0" << endl;
				add =false;
			}
			if (consume < 0) {
				cout << "The consume of a vehicle must be positive" << endl;
				add = false;
			}
			if (add) {
				a.push_back(*new Automovel(id,battery,consume));
				cout << a.back().getId() << " " << a.back().getConsume() << " " << a.back().getBattery() << endl;
			}
		}
		else if (i == 2) {
			bool add = true;
			int id,velocity,x,y,z;
			cout << "Id of the Refuel Station x y z Rechargement Velocity";
			cin >> id >> x >> y >> z >> velocity;
			for(unsigned int i = 0; i < r.size(); i++) {
				if (r[i].getX() == x && r[i].getY() == y) {
					cout << "Refuel Station already exists" << endl;
					add = false;
				}
			}
			if (velocity != 1 && velocity != 2 && velocity != 3) {
				cout << "Velocity must be 1 2 or 3" << endl;
				add = false;
			}
			if (add) {
				r.push_back(*new RefuelStation(id,velocity,x,y,z));
				cout << r.back().getId() << " " << r.back().getVelocity() << endl;
			}
		}
		else if (i == 3) {
			int id,x,y,z;
			cout << "Id x and y and z" << endl;
			cin >> id >> x >> y >> z;
			myGraph.addVertex(id,x,y,z);
		}
		else if (i == 4) {
			int id,id2,dist;
			cout << "Id P1 Id P2" << endl;
			cin >> id >> id2;
			myGraph.addEdge(id,id2);
		}
		else if (i ==5) {
			if(a.size() == 0)
				cout << "No Vehicles avaiable" << endl;
			if(r.size() == 0)
				cout << "No Refuel Stations avaiable" << endl;
			else if (a.size() != 0) {
				int start, end, vehicleid;
				cout << "Start point and end point and vehicle id" << endl;
				cin >> start >> end >> vehicleid;
				unsigned int j;
				for (j = 0; j < a.size(); j++) {
					if (a[j].getId() == vehicleid)
						break;
				}
				if (!myGraph.exists(start))
					cout << "Doens't exists the point " << start << endl;
				if (!myGraph.exists(end))
					cout << "Doens't exists the point " << end << endl;
				if (a[j].getId() != vehicleid) {
					cout << "There is no vehicle with id = " << vehicleid
							<< endl;
				} else if (myGraph.exists(start) && myGraph.exists(end)){
					myGraph.checkIsPointAndRefuelStation(r);
					myGraph.dijkstraShortestPath(start, &a[j]);
					cout << a[j].getBattery() << endl;
					cout << myGraph.getVertex(end)->getDist() << endl;
					myGraph.getInitialPath(end, &a[j],r);
				}
			}
		}
		else if(i == 6) {
			cout << "Vehicle ID              BATTERY           CONSUME" << endl;
			for(unsigned int i = 0; i < a.size(); i++) {
				cout << a[i].getId() << "              " << a[i].getBattery() << "              " << a[i].getConsume() << endl;
			}
		}
		else if(i == 7) {
			cout << "Vehicle ID                X               Y             Z              Velocity" << endl;
			for(unsigned int i = 0; i < r.size(); i++) {
				cout << r[i].getId() << "              " << r[i].getX() << "              " << r[i].getY() << "              " << r[i].getZ() << "              " << r[i].getVelocity() << endl;
			}
		}
	}
}

