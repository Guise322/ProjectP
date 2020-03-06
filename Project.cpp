#include <iostream>
#include <fstream>
#include <array>

using namespace std;

int main()
{
    int valueForEnter;
    string takenText = "";

    string writenText;

    ofstream fileOf;

        fileOf.open ("text.txt");
        cout<< "Write some text below endl";
        getline(cin, writenText);
        fileOf << writenText;
        fileOf.close();

    ifstream fileIf;
    fileIf.open ("text.txt");
        cout << "Words:";
    int cnt=0;
    string word[16];

    while(fileIf >> takenText)
    {
        //a straintforward sequence of statements don't worked because char is not printable type, 
        //introduce the below transformation sequence
        word[cnt] = takenText;
        cnt++;
    }
for (int i = 0; i < 16; i++)
{
    cout<<word[i]<<endl;
}

    
    
        //Statement for breaking the execution
        cout<< "\nPress enter for exit";
        cin>>valueForEnter;

    return 0;
}