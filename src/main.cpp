#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{

	string command;

	while (command != "exit")	
	{
		cout << "tran$hell -> ";
		getline(cin, command);

		if(command=="exit"){
			break;
		}
		int pid = fork();
		if (pid==0){

			char *argv[command.size()+1];
			
			int i = 0;
			while(i <= command.size())
			{
				argv[i] = new char[command.size()];
				strcpy(argv[i], command.c_str());
				i  = i+1;
			}
			execvp(command.c_str(), argv);
			cout << "after" << endl;
			break;
		}
		else if(pid == -1) {
			wait(NULL);
			perror("Child failed!");
			break;
		}
			
		else {
			wait(NULL);
			cout << "parent" << endl;
		}		
	}

	/*int pid=fork();
	if (pid==0) {

		cout << "child" << endl;

		char *argv[3];
		cout << pid;

		argv[0]=new char[3];
		strcpy(argv[0], "ls");	

		argv[1]=new char[3];
		strcpy(argv[1], "-a");

		argv[2]=new char[3];
		strcpy(argv[2], "-l");	

		cout << " before" << endl;
		execvp("ls", argv);
		cout << " after" << endl;

	}
	else {
		wait(0);
		cout << "parent" << endl;
	}*/
	return 0;
}
