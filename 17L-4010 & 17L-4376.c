#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

struct private_files          // sruct for storing private files
	{
		char name[100];
		char password[100];
	};

struct private_files stk_private[10];
static int prvt_index = 0;

void tokenize(char buff[100],char res[100])   // function to tokenize input and store result in output
{
		char *token;
		char seprator[2] = "/";
		token = strtok(buff, seprator);
		while( token != NULL )
		{
			strcpy(res,token);
			token = strtok(NULL, seprator);
		}
	
}

void printcurrdir()          // function to print current directory
{
		char my_pwd[1024]; 
		char res[100];
	    getcwd(my_pwd, sizeof(my_pwd)); 
	    tokenize(my_pwd,res);
	    printf("%s ", res);
}

int my_cd(char input[100])        // function to change directory to desired input
{
		char s[100];
		int res = chdir(input);
		if(res == 0)
		{
			printf("Directory changed to: %s\n",getcwd(s,100));
		}
		else
		{
			printf("Error!   Path not correct\n");
		}
}

void my_ls1()              // function to print all files/directories in curr working dir ("ls")
{

 	DIR *dir = opendir(".");           // open current working directory
	struct dirent *dir_fd;
	while((dir_fd = readdir(dir)) != NULL)       // read data from directory opened
	{
	    int i=0,flag =0;
	    for(;i<prvt_index;i++)                   // chaeck is curr dir is private ?
		{
			if(!strcmp(stk_private[i].name,dir_fd->d_name) )      
			{
					flag = 1;
			}
		}
		if(!strcmp(".",dir_fd->d_name) || !strcmp("..",dir_fd->d_name))
			flag=1;
		if(flag == 0)                             // print all dir names which are not private
			printf(" %s\n", dir_fd->d_name);
	    
	}
	closedir(dir);
}


int my_ls_search(char * input)   // function to search if input name is in current dir
{
	 int ans =0;
	 DIR *dir = opendir(".");           // open current working directory
	struct dirent *dir_fd;
	while((dir_fd = readdir(dir)) != NULL)     // read data from directory opened
	{
	  	if(!strcmp(dir_fd->d_name,input))
	  		ans = 1;
	}
	closedir(dir);
	return ans;
}



/*
// Function where the piped system commands is executed 
void execArgsPiped(char** parsed, char** parsedpipe) 
{ 
    // 0 is read end, 1 is write end 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCould not execute command 1.."); 
            exit(0); 
        } 
    } else { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
} 
*/





void takeinput()    // function to take input from user and respond accordingly
{
	char buff[100];        // for taking input
	char buff1[100];

     // -------------------     how to use Message  --------------------
	system("clear");
	printf("--------------How to Use--------------\n");
	printf("1)    cd/\"newpath\"      e.g cd/home/xyz\n");
	printf("2)    ls\n");
	printf("----------write \"exit\" to terminate--------");

	// --------------  taking input ---------------------
	while(1)
	{
		printf("\n%s","17L-4010 -"); 
		printcurrdir();
		printf("%s ",">");

		                          // take input
		scanf("%s",buff);
		strcpy(buff1,buff);
		char * sep = "/";
		int flag2=0; 
		if(strstr(buff,"/") != 0)     // separator is /
			flag2=1;
	
		char * in = strtok(buff, sep);
		char * rem = strtok(NULL, "");
		char dest[100] = "/";
		int flag_ls =0;
		
		int flag_private =0;
	
		 
		if(rem != 0 && flag2 == 1)      // if separator "/" found 
		{
			char src[90];
			strcpy(src,rem);   			// adding "/" 
			strcat(dest, src);
		}

		if(!strcmp(in, "ls") && flag_ls == 0)   // simple ls no parimeter("-")
		{
			my_ls1();
		}

		else if(!strcmp(in, "cd"))        // check for cd    
		{
			if(rem==NULL)
    			printf("Error: Please enter new path correctly\n" );
    		else
				my_cd(dest);
		}
		
		else if(!strcmp(in, "pwd"))      //  check for pwd
		{
			char my_pwd[1024]; 
    		getcwd(my_pwd, sizeof(my_pwd)); 
    		printf("%s\n",my_pwd);
		}

		
		
		
		
		else if(!strcmp(buff, "exit"))   // exit program
		{
				break;
		}
		
		
		
		
		else        // if nothing match
		{
			printf("Error: Command not Found\n");
		}
	}
}

// ------------------------------- Main Function ---------------------------------------------
int main(int argc, char* argv[])
{

	takeinput();
	
	
	
	
	

	return 0;
}
