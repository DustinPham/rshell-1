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
    int fdd = open(out, O_RDWR);
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
    int fdd = open(out, O_RDWR);

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
    string first = argv[1];
    string second = argv[2];

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
