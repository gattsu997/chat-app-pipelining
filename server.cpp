#include <sys/types.h>
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#define el "\n"
#define sp " "
#define ll long long 
using namespace std;

int main()
{
	int shmid;		//shared memory id
	char *shmem;    //shared memory variable;

	//Initialization of the shared memory
	if ((shmid = shmget((key_t)1080, 27 , IPC_CREAT | 0666)) < 0) 
	{
		cout<<"\nError in shmget";
		exit(1);
	}

	//Attachment to the shared memory
	if ((shmem = (char *)shmat(shmid, NULL, 0)) == (char *) -1) {
		cout<<"\nError in shmat";
		exit(1);
	}

	//Exchange of messages
	*(shmem)= '!';
	int cnt=0,i;
	char s='!';
	while(*(shmem)!='*')
	{		
		if(*(shmem)!='*'&& s!=*(shmem))
		{
			while(*(shmem)!='1'&& *(shmem)!='2'&& *(shmem)!='3' && *(shmem)!='4' && *(shmem)!='5' && *(shmem)!='*')
			sleep(1);
			s=*(shmem);
			if(*(shmem)=='*')
			{
				cout<<"Connection closed by Client";
				break;
			}
			else
			{
				cout<<"\nClient "<<*(shmem)<<" : ";
				for(i=0;*(shmem+i+1)!='\0';i++)
					cout<<*(shmem+i+1);
				cout<<el;
			}
			sleep(5);
			continue;
		}
		else
		{
			string a;			
			cout<<"\nServer: ";
			getline(cin,a);
			if(a[0]=='*')
			{
				*(shmem)='*';
				continue; 
			}
			for(i=0;i<a.size();i++)
				*(shmem+i+1)=a[i];
			*(shmem+i+1)='\0';
			*(shmem)='^';

		}
	}

	//Deattach the shared memory
	shmid = shmdt(shmem);
	exit(0);
}