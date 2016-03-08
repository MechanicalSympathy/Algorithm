// LFU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<list>
#include<iostream>
#define  memsize 3;
using namespace std;

class page{
public:
	page(int id,int hit){
		this->id=id;
		this->hit=hit;
	}
	page(){
	}
	int id;
	int hit;
	bool operator<(const page& p){
		return hit<p.hit;
	}
	bool operator>(const page& p){
		return hit>p.hit;
	}
};

class lfudis{
private:
	list<page> hitrate;
public:
	void dis();

};

void lfudis::dis(){
	int pagenum=0;
	while(true){
		cout<<"请输入页面号："<<endl;
		cin>>pagenum;
		bool find=false;
		list<page>::iterator beginIt=	hitrate.begin();
		list<page>::iterator endIt=	hitrate.end();
		for(;beginIt!=endIt;beginIt++){
			if(beginIt->id==pagenum){
				beginIt->hit++;
				find=true;
				break;
			}
		}
		if(!find){
			page p(pagenum,1);
			//判断是不是需要调度
			if(hitrate.size()==3){
				hitrate.sort();
				hitrate.pop_front();
				hitrate.push_back(p);
			}else{
				hitrate.push_back(p);
			}
		}
		hitrate.sort();
		list<page>::iterator showstartIt=hitrate.begin();
		list<page>::iterator showendIt=	hitrate.end();
		for(;showstartIt!=showendIt;showstartIt++){
			cout<<"id:"<<showstartIt->id<<",hit:"<<showstartIt->hit<<endl;
		}
	}
}


int main(int argc, char* argv[])
{
	lfudis dis;
	dis.dis();
	return 0;
}

