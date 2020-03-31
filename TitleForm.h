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

	void gettingWhiteSpace(enumWhiteSpace typeOfWP, int amountOfSpace)
	{
		if (fileOf.is_open())
		{
			if (typeOfWP == spaces)
			{
				whiteSpace[spaces].resize(amountOfSpace, " ");

				for (int unsigned i = 0; i < whiteSpace[spaces].size(); i++)
				{
					fileOf << whiteSpace[spaces][i];
				}
			}

			if (typeOfWP == newLines)
			{
				whiteSpace[newLines].resize(amountOfSpace, "\n");

				for (int unsigned i = 0; i < whiteSpace[newLines].size(); i++)
				{
					fileOf << whiteSpace[newLines][i];
				}
			}
		}
		else
			cout << "File can not opened";
	}

	string gettingDate()
	{
		time_t now = time(0);
		tm* gotTime = localtime(&now);
		int currYear = 1900 + gotTime->tm_year;

		return to_string(gotTime->tm_mday) + "." + to_string(gotTime->tm_mon)
			+ "." + to_string(currYear);
	}

	void gettingMemoData()
	{
		cout << endl << "Write who you are sending this memorandum: ";
		getline(cin, toWho);

		cout << endl << "Write your surname and initials: ";
		getline(cin, fromWho);

		currDate = gettingDate();

		cout << endl << "Write the subject of the memorandum: ";
		getline(cin, memoSubj);
	}

public:
	void writtingMemo()
	{
		gettingMemoData();
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
			gettingWhiteSpace(spaces, 10);

			fileOf << "writtenTitleForm";

			gettingWhiteSpace(newLines, 20);

			fileOf << "Name:";

			gettingWhiteSpace(spaces, 20);

			fileOf << writtenName;
		}
		else
			cout << "The file can't be opened";

		fileOf.close();

		this_thread::sleep_for(2s);

		cout << "Your title form is writen in" << endl;
	}
};

