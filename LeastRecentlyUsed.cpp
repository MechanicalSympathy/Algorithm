// LeastRecnetUsed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include<iostream>
#define memblock 3;
using namespace std;

class pagedis{
public:
	void start();
};

void pagedis::start(){
	list<int> lru;
	int pagenum;
	while(true){
		cout<<"输入页面号"<<endl;
		cin>>pagenum;
		//判断是否命中
		bool has=false;//默认竟然为true，坑
		list<int>::const_iterator beginIt=lru.begin();
		list<int>::const_iterator endIt=lru.end();
		for(;beginIt!=endIt;beginIt++){
			if(*beginIt==pagenum){
				has=true;
			}
		}
		if(has){//命中
			lru.remove(pagenum);
			lru.push_back(pagenum);
		}else{//没命中
			if(lru.size()==3){
				//置换
				lru.remove(*lru.begin());		
			}
			lru.push_back(pagenum);
		}
		list<int>::const_iterator showbeginIt=lru.begin();
		list<int>::const_iterator showendIt=lru.end();
		for(;showbeginIt!=showendIt;showbeginIt++){
			cout<<" "<<*showbeginIt;
		}
		cout<<endl;
	}

}

int main(int argc, char* argv[])
{
	pagedis dis;
	dis.start();
	return 0;
}

