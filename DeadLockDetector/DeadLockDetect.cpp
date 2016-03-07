// DeadLockDetect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream> 
#include<map>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
#define pro 3;

class Detector{
private:
	map<int,int> occupationTable;
	map<int,int> waittingTable;
	

public:
	void load(char* occupationTable,char* waittingTable);
	void show();
	bool detect();
};

bool Detector::detect(){
	const int n=pro;
	vector<vector<bool> >  detectresult(n);
	for(int i=0;i <n;i++) 
       detectresult[i].resize(n);
	//1.构建依赖关系表
	for(int w=0;w<waittingTable.size();w++){
		int ws=waittingTable[w];
		for(int o=0;o<occupationTable.size();o++){
			if(ws==occupationTable[o]){
				detectresult[w][o]=true;
			}
		}
	}

	//2.检测
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				detectresult[i][j]=	detectresult[i][j]|(detectresult[i][k]&detectresult[k][j]);
			}
		}			
	}
	cout<<"\t";
	for(int in=0;in<n;in++){
		cout<<"["<<in<<"]\t";
	}
	cout<<endl;
	for(int t=0;t<n;t++){
		cout<<"["<<t<<"]\t";
		for(int e=0;e<n;e++){
			cout<<" "<<detectresult[t][e]<<"\t";
		}
		cout<<endl;
	}
	return false;
}



void Detector::show(){
	cout<<"=============资源占用表==========="<<endl;
	map<int,int>::iterator occupationBegin=occupationTable.begin();
	map<int,int>::iterator occupationEnd=occupationTable.end();
	for(;occupationBegin!=occupationEnd;occupationBegin++){
		cout<<occupationBegin->first<<"->"<<occupationBegin->second<<endl;
	}
	cout<<"=============资源占用表==========="<<endl;

	cout<<"=============资源等待表==========="<<endl;
	map<int,int>::iterator waittingBegin=waittingTable.begin();
	map<int,int>::iterator waittingEnd=waittingTable.end();
	for(;waittingBegin!=waittingEnd;waittingBegin++){
		cout<<waittingBegin->first<<"->"<<waittingBegin->second<<endl;
	}
	cout<<"=============资源等待表==========="<<endl;
}



void Detector::load(char* occupationTableLocation,char* waittingTableLocation){
	//读取占用表
	fstream occupationfile;
	occupationfile.open(occupationTableLocation,ios::in);
	const char* occupationdelimit=",";
	char occupationbuffer[50];
	char* occupationpro;
	char* occupationres;
	occupationfile.getline(occupationbuffer,50,'\n');
	while(!occupationfile.eof()){
		occupationpro=strtok(occupationbuffer,occupationdelimit);
		while(occupationpro!=NULL){
			occupationres=strtok(NULL,occupationdelimit);
			if(occupationres!=NULL){
				istringstream first(occupationpro);
				istringstream second(occupationres);
				int pronum;
				first>>pronum;
				int resnum;
				second>>resnum;
				occupationTable[pronum]=resnum;
			}
			occupationpro=strtok(NULL,occupationdelimit);
		}
		occupationfile.getline(occupationbuffer,50,'\n');
	}
	occupationfile.close();


	//读取等待
	fstream waittingfile;
	waittingfile.open(waittingTableLocation,ios::in);
	const char* waittingdelimit=",";
	char  waittingbuffer[50];
	char* waittingpro;
	char* waittingres;
	waittingfile.getline(waittingbuffer,50,'\n');
	while(!waittingfile.eof()){
		waittingpro=strtok(waittingbuffer,waittingdelimit);
		while(waittingpro!=NULL){
			waittingres=strtok(NULL,waittingdelimit);
			if(waittingres!=NULL){
				istringstream first(waittingpro);
				istringstream second(waittingres);
				int pronum;
				first>>pronum;
				int resnum;
				second>>resnum;
				waittingTable[pronum]=resnum;
			}
			waittingpro=strtok(NULL,waittingdelimit);
		}
		waittingfile.getline(waittingbuffer,50,'\n');
	}
	waittingfile.close();

}


int main(int argc, char* argv[])
{	
	Detector detector;
	detector.load("occupationtable.txt","wattingtable.txt");
	detector.show();
	detector.detect();
	return 0;
}



