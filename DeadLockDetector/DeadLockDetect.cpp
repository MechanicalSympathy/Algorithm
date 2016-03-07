// Detect.cpp : Defines the entry point for the console application.
//
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
	multimap<int,int> occupationTable;//res-pro
	multimap<int,int> waittingTable;//pro-res
	

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
	multimap<int,int>::const_iterator xstart=waittingTable.begin();
	multimap<int,int>::const_iterator xend=waittingTable.end();
	for(;xstart!=xend;xstart++){
		int xp=xstart->first;
		int xs=xstart->second;
		multimap<int,int>::const_iterator ystart=occupationTable.begin();
		multimap<int,int>::const_iterator yend=occupationTable.end();
		for(;ystart!=yend;ystart++){
			int yp=ystart->first;
			int ys=ystart->second;
			//cout<<"xp:"<<xp<<"xs:"<<xs<<endl;
			//cout<<"yp:"<<yp<<"ys:"<<ys<<endl;
			if(xs==ys){
				//cout<<"xp:"<<xp<<"yp:"<<yp<<endl;
				detectresult[xp-1][yp-1]=true;
			}
		}
	}

	//2.检测
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
	multimap<int,int>::iterator occupationBegin=occupationTable.begin();
	multimap<int,int>::iterator occupationEnd=occupationTable.end();
	for(;occupationBegin!=occupationEnd;occupationBegin++){
		cout<<occupationBegin->first<<"->"<<occupationBegin->second<<endl;
	}
	cout<<"=============资源占用表==========="<<endl;

	cout<<"=============资源等待表==========="<<endl;
	multimap<int,int>::iterator waittingBegin=waittingTable.begin();
	multimap<int,int>::iterator waittingEnd=waittingTable.end();
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
	while(!occupationfile.eof()){
		occupationfile.getline(occupationbuffer,50,'\n');
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
				occupationTable.insert(make_pair(pronum,resnum));
				//occupationTable[pronum]=resnum;
			}
			occupationpro=strtok(NULL,occupationdelimit);
		}
	
	}
	occupationfile.close();


	//读取等待
	fstream waittingfile;
	waittingfile.open(waittingTableLocation,ios::in);
	const char* waittingdelimit=",";
	char  waittingbuffer[50];
	char* waittingpro;
	char* waittingres;
	while(!waittingfile.eof()){
		waittingfile.getline(waittingbuffer,50,'\n');
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
				//waittingTable[pronum]=resnum;
				waittingTable.insert(make_pair(pronum,resnum));
			}
			waittingpro=strtok(NULL,waittingdelimit);
		}
	
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



