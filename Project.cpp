#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <cctype>


using namespace std;

int main()
{
    int cnt = 0;
    int valueForEnter;
    int amountOfWords = 0;
    
    string wordNumber = "";
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
            transform(word[i].begin(), word[i].end(), word[i].begin(), ::tolower);
            cout << word[i] << endl;
        }

        fileIf.close();
    }
    else
        cout << "File could not open" << endl;
    
    cout << "Write word for searching" << endl;
    getline(cin, wordForSearching);

    //This statement converting upper case letters to lower case letters is occured below
    transform(wordForSearching.begin(), wordForSearching.end(), wordForSearching.begin(), ::tolower);

    for (int i = 0; i < cnt; i++)
    {
        if (wordForSearching.compare(word[i]) == 0)
        {
            string some = to_string(i+1);
            if (i==(cnt-1))
            {
                wordNumber += some + ". ";
                amountOfWords++;
            }
            else
            {
                wordNumber += some + ", ";
                amountOfWords++;
            }
        }
    }
    cout << "The word number is " << wordNumber << endl;
    cout << "Amount of words is " << amountOfWords << endl;

   
    //Statement for breaking the execution
    cout<< "Press any kay and then Enter for exit";
    cin>>valueForEnter;

    return 0;
}