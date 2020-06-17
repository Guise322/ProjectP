#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include <limits>

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
	string memoGreeting = "";

	enum enumWhiteSpace
	{
		spaces = 0,
		newLines = 1
	};

	string gettingWhiteSpace(enumWhiteSpace typeOfWP, int amountOfSpace)
	{
		string newSpace = "";

		if (typeOfWP == spaces)
		{
			whiteSpace[spaces].resize(amountOfSpace, " ");

			for (int unsigned i = 0; i < whiteSpace[spaces].size(); i++)
			{
				 newSpace += whiteSpace[spaces][i];
			}
		}

		if (typeOfWP == newLines)
		{
			whiteSpace[newLines].resize(amountOfSpace, "\n");

			for (int unsigned i = 0; i < whiteSpace[newLines].size(); i++)
			{
				newSpace += whiteSpace[newLines][i];
			}
		}
		return newSpace;
	}

	string gettingDate()
	{
		time_t now = time(0);
		tm* gotTime = localtime(&now);
		int currYear = 1900 + gotTime->tm_year;
		
		//These statements do processing to occur the more readable form of the date
		string day = gotTime->tm_mday < 10 ? "0" + to_string(gotTime->tm_mday) 
			: to_string(gotTime->tm_mday);
		string month = gotTime->tm_mon < 10 ? "0" + to_string(gotTime->tm_mon + 1) 
			: to_string(gotTime->tm_mon + 1);

		return day + "." + month + "." + to_string(currYear);
	}

	void gettingMemoData()
	{	
		cout << endl << "Write the name who you are sending this memorandum: ";
		getline(cin, toWho);

		cout << endl << "Write your name: ";
		getline(cin, fromWho);

		currDate = gettingDate();

		cout << endl << "Write the subject of the memorandum: ";
		getline(cin, memoSubj);

		cout << endl << "Write the greeting: ";
		getline(cin, memoGreeting);
	}

	string writingParagraphs()
	{
		string firstParagraph = gettingWhiteSpace(spaces, 1) 
			+ "First paragraf: here you'll want to deliver your " 
			+ "most critical information upfront.\n";
		string secondParagraph = gettingWhiteSpace(spaces, 1)
			+ "Second paragraph: here you'll want to provide " 
			+ "context or supporting evidence.\n";
		string thirdParagraph = gettingWhiteSpace(spaces, 1)
			+ "Third paragraph: here you'll want to include "
			+ "your specific request to who you send this memo.\n";
		return firstParagraph + secondParagraph + thirdParagraph;
	}

public:
	void writingMemo()
	{
		gettingMemoData();

		ofstream fileOf;

		fileOf.open("Your memorandum template.txt");

		if (fileOf.is_open())
		{
			fileOf << gettingWhiteSpace(spaces, 100);
			fileOf << "TO: " + toWho;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 100);
			fileOf << "FROM: " + fromWho;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 100);
			fileOf << "DATE: " + currDate;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 100);
			fileOf << "SUBJECT: " + memoSubj;
			fileOf << gettingWhiteSpace(newLines, 1);
			fileOf << gettingWhiteSpace(spaces, 50);
			fileOf << memoGreeting;
			fileOf << gettingWhiteSpace(newLines, 2);
			fileOf << writingParagraphs();
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
		//Use the below statement because getline takes the /n symbol from the previous writing 
		//cin.ignore(1, '/n');
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

