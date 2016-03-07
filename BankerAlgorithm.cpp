// BankerAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define resourceKind 3
#define progressNum 5
#include <iostream>
using namespace std; 

class state{
public:
	int resourceMax[resourceKind];
	int resourceAlivable[resourceKind];
	int resourceMaxRequest[progressNum][resourceKind];
	int alreadyAllocate[progressNum][resourceKind];
	int request[resourceKind];
	bool checkSafe();//检查状态
	bool allocate();//分配
	void restore();//分配失败，恢复
	int currentProgress;//当前处理的进程
	void show();//显示当前资源状态
	void init();//初始化系统
	void start();//启动状态机
	state(){
		for(int i=0;i<resourceKind;i++){
			resourceMax[i]=0;
			resourceAlivable[i]=0;
			request[i]=0;
		}
		for(int j=0;j<progressNum;j++){
			for(int i=0;i<resourceKind;i++){
				alreadyAllocate[j][i]=0;
				resourceMaxRequest[j][i]=0;
			}	
		}
	}
};

void state::start(){
	state s;
	while(true){
		cout<<"==============欢迎================"<<endl;
		cout<<"= 请输入具体操作:            ="<<endl;
		cout<<"= 1.初始化:                  ="<<endl;
		cout<<"= 2.显示资源情况             ="<<endl;
		cout<<"= 3.分期申请资源             ="<<endl;
		cout<<"= 4.退出                     ="<<endl;
		cout<<"=================================="<<endl;
		int opt=0;
		cin>>opt;
		switch(opt){
		case 1:{
			s.init();
			break;
			   }
		case 2:{
			s.show();
			break;
			   }
		case 3:{
			if(s.allocate()){
				if(!s.checkSafe()){
					s.restore();
				}
			}
			break;
			   }
		case 4:{
			
			return;
			   }
		}
	}
}


void state::init(){
	int curPro=0;
	cout<<"初始化各个资源的数量："<<endl;
	for(int ii=0;ii<resourceKind;ii++){
		cout<<"resource["<<ii<<"]:"<<endl;
		cin>>resourceMax[ii];
		resourceAlivable[ii]=resourceMax[ii];
	}
	for(int p=0;p<progressNum;p++){
		cout<<"初始化进程最大需求数量：0---"<<progressNum-1<<endl;
		cout<<"请输入进程号：";
		cin>>curPro;
		cout<<"请输入各个资源的最大需求数量：";
		for(int i=0;i<resourceKind;i++){
			cout<<"["<<i<<"]:";
			cin>>resourceMaxRequest[curPro][i];
			if(resourceMaxRequest[curPro][i]>resourceAlivable[i]){
				cout<<"分配不合法！超过当前拥有的数量！！"<<endl;
				resourceMaxRequest[curPro][i]=0;
				return;
			}
		}
	}
}



void state::show(){
	cout<<"=====================资源详情========================"<<endl;
	for(int j=0;j<resourceKind;j++){
		cout<<"\t"<<"R["<<j<<"]:剩余["<<resourceAlivable[j]<<"]";
	}
	cout<<endl;
	for(int i=0;i<progressNum;i++){
		cout<<"p["<<i<<"]:";
		for(int j=0;j<resourceKind;j++){
			cout<<"\t   "<<alreadyAllocate[i][j]<<":最大["<<resourceMaxRequest[i][j]<<"]";
		}
		cout<<endl;
	}
	cout<<"===================================================="<<endl;
}


bool state::allocate(){
	cout<<"请输入申请进程号："<<"0--"<<progressNum-1<<endl;
	cin>>currentProgress;
	cout<<"请输入申请数量："<<endl;
	for(int r=0;r<resourceKind;r++){
		cout<<"["<<r<<"]:"<<endl;
		cin>>request[r];
		if(request[r]>(resourceMaxRequest[currentProgress][r]-alreadyAllocate[currentProgress][r])){
			cout<<"分配不合法！超过当前拥有的数量！！"<<endl;
			return false;
		}
		if(request[r]>resourceAlivable[r]){
			cout<<"分配不合法！超过当前拥有的数量！！"<<endl;
			return false;
		}
	}
	for(int i=0;i<resourceKind;i++){
		resourceAlivable[i]-=request[i];
		alreadyAllocate[currentProgress][i]+=request[i];
	}
	return true;
}

void state::restore(){
	for(int i=0;i<resourceKind;i++){
		resourceAlivable[i]+=request[i];
		alreadyAllocate[currentProgress][i]-=request[i];
	}
}

bool state::checkSafe(){
	bool possible=true;
	int curResourceAlivable[resourceKind];
	for(int i=0;i<resourceKind;i++){
		curResourceAlivable[i]=resourceAlivable[i];
	}
	bool finish[progressNum];
	for(int f=0;f<progressNum;f++){
		finish[f]=false;
	}
	int step=0;
	int success=0;
	int rMatch=0;
	int safeSeq[progressNum];
	while(possible){
		step=0;
		for(int p=0;p<progressNum;p++){
			rMatch=0;
			if(finish[p]){
				step++;
				continue;
			}
			for(int s=0;s<resourceKind;s++){
				if((resourceMaxRequest[p][s]-alreadyAllocate[p][s])<=curResourceAlivable[s]){
					rMatch++;
				}
			}
			if(rMatch==resourceKind){
				for(int re=0;re<resourceKind;re++){
					curResourceAlivable[re]+=alreadyAllocate[p][re];
				}
				finish[p]=true;
				safeSeq[success]=p;
				success++;
			}else{
				step++;
			}
		}
		if(step==progressNum){//不安全
			cout<<"请求资源不合法，被撤销"<<endl;
			return false;
		}
		if(success==progressNum){//成功申请
			cout<<"安全序列为："<<endl;
			for(int i=0;i<progressNum;i++){
				cout<<safeSeq[i]<<endl;
			}
			return true;
		}
		
	}
	return false;
}


int main(int argc, char* argv[])
{
	state s;
	s.start();
	return 0;
}

