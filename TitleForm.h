#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>

class TitleForm
{
private:
	string title = "TitleOfForm";
	vector<string> whiteSpace[2];
	ofstream fileOf;

	//variables for a memorandum
	string toWho = "";
	string fromWho = "";
	string currDate = "";
	string memoSubj = "";

	enum enumWhiteSpace
	{
		spaces = 0,
		newLines = 1
	};

	string gettingWhiteSpace(enumWhiteSpace typeOfWP, int amountOfSpace)
	{
		if (typeOfWP == spaces)
		{
			whiteSpace[spaces].resize(amountOfSpace, " ");

			string writtenSpaces = "";

			for (int unsigned i = 0; i < whiteSpace[spaces].size(); i++)
			{
				 writtenSpaces += whiteSpace[spaces][i];
			}
			return writtenSpaces;
		}

		if (typeOfWP == newLines)
		{
			whiteSpace[newLines].resize(amountOfSpace, "\n");

			string writtenNewLines = "";

			for (int unsigned i = 0; i < whiteSpace[newLines].size(); i++)
			{
				writtenNewLines += whiteSpace[newLines][i];
			}
			return writtenNewLines;
		}
	}

	string gettingDate()
	{
		time_t now = time(0);
		tm* gotTime = localtime(&now);
		int currYear = 1900 + gotTime->tm_year;
		
		//These statements do processing to occur the more readable form of the date
		string day = gotTime->tm_mday < 10 ? "0" + to_string(gotTime->tm_mday) 
			: to_string(gotTime->tm_mday);
		string month = gotTime->tm_mon < 10 ? "0" + to_string(gotTime->tm_mon) 
			: to_string(gotTime->tm_mon);

		return day + "." + month + "." + to_string(currYear);
	}

	void gettingMemoData()
	{	
		cout << endl << "Write name who you are sending this memorandum: ";
		getline(cin, toWho);

		cout << endl << "Write your surname and initials: ";
		getline(cin, fromWho);

		currDate = gettingDate();

		cout << endl << "Write the subject of the memorandum: ";
		getline(cin, memoSubj);
	}

public:
	void writingMemo()
	{
		gettingMemoData();

		ofstream fileOf;

		fileOf.open("Your memorandum template.txt");

		if (fileOf.is_open())
		{
			fileOf << gettingWhiteSpace(spaces, 50);
			fileOf << "TO: " + toWho;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 50);
			fileOf << "FROM: " + fromWho;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 50);
			fileOf << "DATE: " + currDate;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 50);
			fileOf << "SUBJECT: " + memoSubj;
			fileOf << gettingWhiteSpace(newLines, 1);
		}
		else
			cout << "The file can't be opened";
		fileOf.close();

		cout << endl << "The memorandum template has been written" << endl;
	}

	void writeTitleForm()
	{
		cout << "Write your name: ";
		string writtenName = "";
		getline(cin, writtenName);
		cout << endl;

		fileOf.open("title.txt");

		if (fileOf.is_open())
		{
			fileOf << gettingWhiteSpace(spaces, 10);

			fileOf << "writtenTitleForm";

			fileOf << gettingWhiteSpace(newLines, 20);

			fileOf << "Name:";

			fileOf << gettingWhiteSpace(spaces, 20);

			fileOf << writtenName;
		}
		else
			cout << "The file can't be opened";

		fileOf.close();

		cout << endl << "Your title form is writen in" << endl << endl;
	}
};

