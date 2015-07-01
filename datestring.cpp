// datestring.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <pthread.h>  
//#include <crtdbg.h>  
#include <queue>
#include <iostream>
#include "RowObject.h"
#include "RowBean.h"
#include "ODBCDao.h"
#include <unistd.h>
using namespace std;





#define Max 10
 queue<RowBean*>        q;  
 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cond = PTHREAD_COND_INITIALIZER;/*初始化条件变量*/


void *consumer(void* args)  
{  
	ODBCDao dao;
	dao.getConn();
	RowBean *beanobject;
	int size=0;
	while(true)
	{
		pthread_mutex_lock(&mutex);
		size=q.size();
		if(size>0)
		{
			beanobject=q.front();
			q.pop();
			pthread_cond_broadcast(&cond);
			pthread_mutex_unlock(&mutex);
			dao.insertbulkParamInto(beanobject);
			delete beanobject;
		}
		else 
		{
			pthread_cond_broadcast(&cond);
			pthread_cond_wait(&cond,&mutex);/*解锁mutex，并等待cond改变*/
			pthread_mutex_unlock(&mutex);
			
		}
		
	}

	return NULL;  
}  

void *producer(void* args)
{
	while(true)
	{
		pthread_mutex_lock(&mutex);
		int size=q.size();
		if( size>= Max)  
		{  
			pthread_cond_broadcast(&cond); 
			pthread_cond_wait(&cond,&mutex);/*解锁mutex，并等待cond改变*/ 
			pthread_mutex_unlock(&mutex); 
			
			
		}  
		else
		{
			RowBean *beanobject=new RowBean;
			q.push(beanobject);
			pthread_cond_broadcast(&cond);  
			pthread_mutex_unlock(&mutex);
		}
	}
}
int main(int argc, char * argv[])
{
	
	
	pthread_t id;  
	
	 
	pthread_create(&id, NULL, producer, NULL); 
	pthread_create(&id, NULL, producer, NULL); 
	pthread_create(&id, NULL,consumer , NULL);
	pthread_create(&id, NULL,consumer , NULL);
	pthread_create(&id, NULL,consumer , NULL);

	
	
	for(;;)  sleep(1);
	//char* pChars = new char[10]; 
	//_CrtDumpMemoryLeaks(); 
	//cout<<"thread main"<<endl;

	
}



