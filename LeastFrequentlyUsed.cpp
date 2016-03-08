// LFU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<map>
#include<iostream>
using namespace std;
class lfudis{
private:
	map<int,int> hitrate;
public:
	void dis();

};
void lfudis::dis(){
	hitrate[23]=10;
	hitrate[43]=10;
	hitrate[11]=10;
	hitrate[4]=10;
	hitrate[8]=10;
	int pagenum=0;
	while(true){
		cout<<"ÇëÊäÈëÒ³ÃæºÅ£º"<<endl;
		cin>>pagenum;
		map<int,int>::const_iterator resultIt=hitrate.find(pagenum);
		if(resultIt==hitrate.end()){
			map<int,int>::const_iterator beginIt=hitrate.begin();
			map<int,int>::const_iterator endIt=hitrate.end();
			for(;beginIt!=endIt;beginIt++){
				cout<<beginIt->first<<endl;
			}
		}
	}
	
	

}


int main(int argc, char* argv[])
{
	lfudis dis;
	dis.dis();
	return 0;
}

