#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <Timer.h>

using namespace std;

void copy(string input, string output) {
    ifstream ifs(input.c_str());
    ofstream ofs(output.c_str());

    char c = ifs.get();

    while (ifs.good()) {
        cout << c;
        ofs.put(c);
        c = ifs.get();
    }
}

void readwrite(string in, string out) {
    char buf[1];

    int fd = open(in.c_str(), O_RDONLY);
    int fdd = open(out.c_str(), O_RDWR);
    int red;
    while (red = read(fd, &buf, 1) != '\0') {
        if (red == -1) {
            perror("Error with read");
        }
        if (write(fdd, &buf, 1) == -1) {
            perror("Error with write");
        }
    }
}
void readwritebuf(string in, string out) {
    char buf[BUFSIZ];

    int fd = open(in.c_str(), O_RDONLY);
    int fdd = open(out.c_str(), O_RDWR);

    if (read(fd, &buf, BUFSIZ)) {
        perror("Error with read");
    }
    if (write(fdd, &buf, BUFSIZ) == -1) {
        perror("Error with write");
    }
}

int main() {
    string in;
    string out;

    cout << "Enter the name of an existing file to copy from: ";
    cin >> in;
    cout << "Enter the name of an existing file to copy to: ";
    cin >> out;

    //copy(in, out);
    readwrite(in, out);
    //readwritebuf(in, out);
    return 0;
}
