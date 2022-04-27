

#include <iostream>
#include "scanner.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    string filelocation;
    cout<<"Input file location: ";
    cin>>filelocation;
    lexicalAnalyze(filelocation); //Applications/lab3_test/lab3_test/lab3.txt
    return 0;
}
