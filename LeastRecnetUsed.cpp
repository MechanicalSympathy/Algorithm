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
		cout<<"����ҳ���"<<endl;
		cin>>pagenum;
		//�ж��Ƿ�����
		bool has=false;//Ĭ�Ͼ�ȻΪtrue����
		list<int>::const_iterator beginIt=lru.begin();
		list<int>::const_iterator endIt=lru.end();
		for(;beginIt!=endIt;beginIt++){
			if(*beginIt==pagenum){
				has=true;
			}
		}
		if(has){//����
			lru.remove(pagenum);
			lru.push_back(pagenum);
		}else{//û����
			if(lru.size()==3){
				//�û�
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

