#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <iostream>
#include <stdio.h>

using namespace std;

void parse(char *cmd, vector<string> &cmdout){

	char *pch;
	pch = strtok(cmd, " ");
	while(pch != NULL){
		cout << "token: " << pch << endl;
		pch = strtok(NULL, " ");
	}
}

int main()
{

	string command;
	

	while (command != "exit"){
		cout << "tran$hell -> ";
		getline(cin, command);	
//		parse(command.c_str());

		int pid = fork();

		if (pid==0){

			for(int i = 0; i  < command.size() ; ++i)
			{
				char *argv[command.size()];
				argv[0] = new char[command.size()];
				strcpy(argv[i], command.c_str());
				argv[command.size()-1] = NULL;
				parse(argv[i], argv[i]);
				perror("");

				execvp(command.c_str(), argv);
			}
		
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
		}		

	}

	return 0;
}
