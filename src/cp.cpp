#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Timer.h"

using namespace std;

void copy(char in[], char out[]) {
    ifstream ifs(in);
    ofstream ofs(out);

    char c = ifs.get();

    while (ifs.good()) {
        ofs.put(c);
        c = ifs.get();
    }
}

void readwrite(char in[], char out[]) {
    char buf[1];

    int fd = open(in, O_RDONLY);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }

    int fdd = open(out, O_WRONLY);
    if (fdd == -1) {
        perror("Error with open");
        exit(1);
    }

    int red;
    while (red = read(fd, &buf, 1) != '\0') {
        if (red == -1) {
            perror("Error with read");
            exit(1);
        }
        if (write(fdd, &buf, 1) == -1) {
            perror("Error with write");
            exit(1);
        }
    }
}
void readwritebuf(char in[], char out[]) {
    char buf[BUFSIZ];

    int fd = open(in, O_RDONLY);
    if (fd == -1) {
        perror("Error with open");
        exit(1);
    }

    int fdd = open(out, O_WRONLY);
    if (fdd == -1) {
        perror("Error with open");
        exit(1);
    }

    if (read(fd, &buf, BUFSIZ) == -1) {
        perror("Error with read");
        exit(1);
    }
    if (write(fdd, &buf, BUFSIZ) == -1) {
        perror("Error with write");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    string temp;
    char* tmp = 0;
    struct stat s;

    if (argv[1][0] == '-' && argv[1][1] == 'f') {
            tmp = argv[1];
            argv[1] = argv[2];
            argv[2] = tmp;
    }
    if (argv[2][0] == '-' && argv[2][1] == 'f') {
        tmp = argv[2];
        argv[2] = argv[3];
        argv[3] = tmp;
    }

    string first = argv[1];
    string second = argv[2];

    if (first.at(0) != '.' && first.at(1) != '/') {
        temp = "./";
        first = temp + first;

        if (stat(first.c_str(), &s) == -1) {
            perror("Error with stat");
            exit(1);
        }
        if (s.st_mode & S_IFDIR) {
            cout << "First argument is a directory" << endl;
            exit(1);
        }
    }
    else {
        if (stat(argv[1], &s) == -1) {
            perror("Error with stat");
            exit(1);
        }
        if(s.st_mode & S_IFDIR) {
            cout << "First argument is a directory" << endl;
        }
    }

    if (ifstream(argv[2])) {
        cout << "Error: Second argument already exists as a file or folder." << endl;
        exit(1);
    }
    else if (!ifstream(argv[2])) {
        if (argc == 4) {
            if (argv[3][1] != 'f') {
                cout << "Invalid flag." << endl;
            }
            else if (argv[3][1] == 'f') {
                ofstream make(argv[2]);
                if (!make.good()) {
                    cout << "Cannot open file" << endl;
                    exit(1);
                }
                make.close();
            }
        }
        else if (argc == 3) {
            ofstream make(argv[2]);
            if (!make.good()) {
                cout << "Cannot open file" << endl;
                exit(1);
            }
            make.close();
        }
    }

    if (second.at(0) != '.' && second.at(1) != '/') {
        temp = "./";
        second = temp + second;

        if (stat(second.c_str(), &s) == -1) {
            perror("Error with stat");
            exit(1);
        }
        if (s.st_mode & S_IFDIR) {
            cout << "Second argument is a directory" << endl;
            exit(1);
        }
    }
    else {
        if (stat(argv[2], &s) == -1) {
            perror("Error with stat");
            exit(1);
        }
        if (s.st_mode & S_IFDIR) {
            cout << "Second argument is a directory" << endl;
            exit(1);
        }
    }

    if (argc > 4 || argc < 3) {
        cout << "Error: Need 2 or 3 arguments." << endl;
        exit(1);
    }

    Timer t;
    double eTime;

    if (argc == 3) {
        t.start();
        readwritebuf(argv[1], argv[2]);

        cout << "Time for Method 3" << endl;
        t.elapsedWallclockTime(eTime);
        cout << "Wallclock time: " << eTime << endl;
        t.elapsedUserTime(eTime);
        cout << "User time: " << eTime << endl;
        t.elapsedSystemTime(eTime);
        cout << "System time: " << eTime << endl;
    }
    else if (argc == 4) {

        cout << "No third argument, running all methods:" << endl << endl;

        t.start();
        copy(argv[1], argv[2]);

        cout << "Time for Method 1" << endl;
        t.elapsedWallclockTime(eTime);
        cout << "Wallclock time: " << eTime << endl;
        t.elapsedUserTime(eTime);
        cout << "User time: " << eTime << endl;
        t.elapsedSystemTime(eTime);
        cout << "System time: " << eTime << endl << endl;

        t.start();
        readwrite(argv[1], argv[2]);

        cout << "Time for Method 2" << endl;
        t.elapsedWallclockTime(eTime);
        cout << "Wallclock time: " << eTime << endl;
        t.elapsedUserTime(eTime);
        cout << "User time: " << eTime << endl;
        t.elapsedSystemTime(eTime);
        cout << "System time: " << eTime << endl << endl;

        t.start();
        readwritebuf(argv[1], argv[2]);

        cout << "Time for Method 3" << endl;
        t.elapsedWallclockTime(eTime);
        cout << "Wallclock time: " << eTime << endl;
        t.elapsedUserTime(eTime);
        cout << "User time: " << eTime << endl;
        t.elapsedSystemTime(eTime);
        cout << "System time: " << eTime << endl << endl;
    }
    return 0;
}
