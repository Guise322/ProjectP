#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

class TitleForm
{
private:
	string writtenName = "";
	string title = "TitleOfForm";
	vector<string> whiteSpace[2];
	ofstream fileOf;
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

				for (int i = 0; i < whiteSpace[spaces].size(); i++)
				{
					fileOf << whiteSpace[spaces][i];
				}
			}

			if (typeOfWP == newLines)
			{
				whiteSpace[newLines].resize(amountOfSpace, "\n");

				for (int i = 0; i < whiteSpace[newLines].size(); i++)
				{
					fileOf << whiteSpace[newLines][i];
				}
			}
		}
		else
			cout << "File can not opened";
	}

public:
	void writeIntoFile()
	{

	}

	bool writeTitleForm()
	{
		cout << "Write your name: ";
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
		
		return true;
	}
};

