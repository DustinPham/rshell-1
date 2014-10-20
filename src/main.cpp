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
		cin >> command;

		int pid = fork();
		if (pid==0){

			wait(NULL);	
			char *argv[4];
			
			argv[0]=new char[5];
			strcpy(argv[0], command.c_str());
			
			execvp(command.c_str(), argv);
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
