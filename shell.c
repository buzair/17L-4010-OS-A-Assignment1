#include <iostream>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<fstream>
using namespace std;

void cmd_execute(char **args)
{
    int status;
    pid_t pid = fork();
    if (pid < 0)
    {

        perror("ERROR in Execution");
    }
    else if (pid == 0)
    {
        int p = execvp(*args, args);
        if(p < 0){
            perror("ERROR in Execution");
        }
    }
    else
    {
        while (wait(&status) != pid);
    }
}
int main()
{
    char str[1000];
    while (1)
    {
        cout << "$: " ;
        cin.getline(str, 1000);
        char **args = new char *[100];
        char delim[] = " ";
        char *token = strtok(str, delim);
        char *file;
        int i = 0;

        while (token)
        {
            args[i] = token;
            token = strtok(NULL, delim);
            i++;
        }
        args[i] = NULL;
        if (strcmp(args[0], "exit") == 0)
        {
            return 0;
        }
        cmd_execute(args);
    }
    return 0;
}


/*
int main(int argc,char ** argv)
{

	char *c=new char[100];
  	cout<<"17-4010	";
  	cin.getline(c,100);
  	while(strcmp(c,"quit"))
  	{
	  	int count=0;
	  	for(int i=0;c[i]!='\0';i++)
	  	{
	  		if(c[i]==' ')
	  		count++;
	  	}
	  	count++;
	  	char **buff =new char *[count+1];
	  	for(int i=0;i<count+1;i++)
	  		buff[i]=new char [100];
	  		char a[10];
	  		int i=0;
	  		if(count ==1)
	  		{	
			  	for(;c[i]!='\0';i++)
			  			a[i]=c[i];
	  			a[i]='\0';
	  			buff[count-1]=a;	
	  		}
	  		else 
	  		{
			   int k=0;
			  	for(int i=0,m=0;c[i]!='\0';i++,k++)
			  	{	
			  		a[k]=c[i];
			  		if(c[i]==' ')
	  				{
	  					a[k]='\0';
						int j=0;
						for(;j<strlen(a);j++)
  							buff[m][j]=a[j];
						buff[m][j]='\0';
	  					k=-1;
	  					m++;
	  				}
		  			
				}
				a[k]='\0';
				int j=0;
				for(;j<strlen(a);j++)
					buff[count-1][j]=a[j];
				buff[count-1][j]='\0';
			}
			buff[count]=NULL; 
		pid_t pid=0;
		pid=fork();
		if(pid==0)
		{
			execvp(buff[0],buff);
		}
		else if(pid>0)
		{
			wait(NULL);
		}
		else
			perror("Forking failed");
			
		cout<<"17-4010	";
		cin.getline(c,100);
	}
	return 0;
}
*/