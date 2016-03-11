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
#define pro 4;

class Detector{
private:
	multimap<int,int> occupationTable;
	multimap<int,int> waittingTable;
	

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
	multimap<int,int>::iterator waitBeginIt=waittingTable.begin();
	multimap<int,int>::iterator waitEndIt=waittingTable.end();
	for(;waitBeginIt!=waitEndIt;waitBeginIt++){
		multimap<int,int>::iterator occupBeginIt=occupationTable.begin();
		multimap<int,int>::iterator occupEndIt=occupationTable.end();
		for(;occupBeginIt!=occupEndIt;occupBeginIt++){
			if(waitBeginIt->second==occupBeginIt->second){
				detectresult[waitBeginIt->first][occupBeginIt->first]=true;
			}
	
		}
	
	}
	//2.显示

	cout<<"\t";
	for(int in1=0;in1<n;in1++){
		cout<<"["<<in1<<"]\t";
	}
	cout<<endl;
	for(int t1=0;t1<n;t1++){
		cout<<"["<<t1<<"]\t";
		for(int e1=0;e1<n;e1++){
			cout<<" "<<detectresult[t1][e1]<<"\t";
		}
		cout<<endl;
	}




	vector<vector<bool> >  detect=detectresult;

	//2.检测
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				detect[i][j]=	detect[i][j]||(detect[i][k]&&detect[k][j]);
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
			cout<<" "<<detect[t][e]<<"\t";
		}
		cout<<endl;
	}

	//3.打印
	int flag=-1;
	int p=0;
	for(int ii=0;ii<n;ii++){
		if(detect[ii][ii]==1){
			flag=ii;
			break;
		}
	}
	cout<<endl<<endl<<"检测结果"<<endl;
	cout<<"───────────────────"<<endl;
	if(flag!=-1){
		cout<<"存在死锁"<<endl;
		cout<<"进程循环等待队列:";
		p=flag; //存在进程循环等待队列的那一进程
		//进程循环等待队列中的所有进程是table表中的这一行是1的进程,只是顺序要再确定
		while(true){
			cout<<p<<"  ";
			for(int j=0;j<n;j++){
				if(detectresult[p][j]==1){
					if(detect[j][flag]==1){
						p=j;
						break;
					}
				}
			}
			if(p==flag){
				break;
			}
		}
		cout<<flag<<endl;
	}
	else{
		cout<<"不存在死锁"<<endl;
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
		if(occupationbuffer!=NULL){
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
				}
				occupationpro=strtok(NULL,occupationdelimit);
			}
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
		if(waittingbuffer!=NULL){
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
					waittingTable.insert(make_pair(pronum,resnum));
				}
				waittingpro=strtok(NULL,waittingdelimit);
			}
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


