#include <iostream>
#include <fstream>
#include <array>
#include <string>

using namespace std;

int main()
{
    int cnt = 0;
    int valueForEnter;
    string word[5000];
    string takenText = "";
    string writenText = "";
    string wordForSearching = "";
    string resultOfsearching = "";

    ofstream fileOf;

    fileOf.open ("text.txt");
    if (fileOf.is_open())
    {
        cout << "Write some text below \n";
        getline(cin, writenText);
        fileOf << writenText;
        fileOf.close();
    }
    else
        cout << "File could not open";

    ifstream fileIf;
    fileIf.open ("text.txt");

    if (fileIf.is_open())
    {
        //....getline() and ....get() these functions don't had worked, because of that, prefere next method
        while (fileIf >> takenText)
        {
            //a straintforward sequence of statements don't worked because char is not printable type, 
            //introduce the below transformation sequence
            word[cnt] = takenText;
            cnt++;
        }

        cout << "Words:" << endl;

        for (int i = 0; i < cnt; i++)
        {
            cout << word[i] << endl;
        }

        fileIf.close();
    }
    else
        cout << "File could not open" << endl;
    
    cout << "Write word for searching" << endl;
    getline(cin, wordForSearching);

    resultOfsearching; //Write a statement for searching the word

    cout << "Result of the searching:" << endl;
    cout << resultOfsearching << endl;


    //Statement for breaking the execution
    cout<< "Press any kay and then Enter for exit";
    cin>>valueForEnter;

    return 0;
}