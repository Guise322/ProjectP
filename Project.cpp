#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream file;
    file.open ("text.txt");
    file << "Some text";
    file.close();
    return 0;
}