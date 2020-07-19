//Use this preprocessor statement because of getting the 'localtime' error in TitleForm.h
#pragma warning(disable : 4996)
#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include <limits>
#include <string>

class WriteTitleForm
{
private:
	std::string title = "TitleOfForm";
	std::vector<std::string> whiteSpace[2];
	std::ofstream fileOf;

	//variables for a memorandum
	std::string toWho = "";
	std::string fromWho = "";
	std::string currDate = "";
	std::string memoSubj = "";
	std::string memoGreeting = "";

	enum enumWhiteSpace
	{
		spaces = 0,
		newLines = 1
	};

	std::string gettingWhiteSpace(enumWhiteSpace typeOfWP, int amountOfSpace)
	{
		std::string newSpace = "";

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

	std::string gettingDate()
	{
		time_t now = time(0);
		tm* gotTime = localtime(&now);
		int currYear = 1900 + gotTime->tm_year;
		
		//These statements do processing to occur the more readable form of the date
		std::string day = gotTime->tm_mday < 10 ? "0" + std::to_string(gotTime->tm_mday)
			: std::to_string(gotTime->tm_mday);
		std::string month = gotTime->tm_mon < 10 ? "0" + std::to_string(gotTime->tm_mon + 1)
			: std::to_string(gotTime->tm_mon + 1);

		return day + "." + month + "." + std::to_string(currYear);
	}

	void gettingMemoData()
	{	
		std::cout << std::endl << "Write the name who you are sending this memorandum: ";
		std::getline(std::cin, toWho);

		std::cout << std::endl << "Write your name: ";
		std::getline(std::cin, fromWho);

		currDate = gettingDate();

		std::cout << std::endl << "Write the subject of the memorandum: ";
		std::getline(std::cin, memoSubj);

		std::cout << std::endl << "Write the greeting: ";
		std::getline(std::cin, memoGreeting);
	}

	std::string writingParagraphs()
	{
		std::string firstParagraph = gettingWhiteSpace(spaces, 1)
			+ "First paragraf: here you'll want to deliver your " 
			+ "most critical information upfront.\n";
		std::string secondParagraph = gettingWhiteSpace(spaces, 1)
			+ "Second paragraph: here you'll want to provide " 
			+ "context or supporting evidence.\n";
		std::string thirdParagraph = gettingWhiteSpace(spaces, 1)
			+ "Third paragraph: here you'll want to include "
			+ "your specific request to who you send this memo.\n";
		return firstParagraph + secondParagraph + thirdParagraph;
	}

public:
	void writeMemo()
	{
		gettingMemoData();

		std::ofstream fileOf;

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
			std::cout << "The file can't be opened";
		fileOf.close();

		std::cout << std::endl << "The memorandum template has been written" << std::endl;
	}

	void writeTitleForm()
	{
		std::cout << "Write your name: ";
		std::string writtenName = "";
		//Use the below statement because getline takes the /n symbol from the previous writing 
		//cin.ignore(1, '/n');
		std::getline(std::cin, writtenName);
		std::cout << std::endl;

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
			std::cout << "The file can't be opened";

		fileOf.close();

		std::cout << std::endl << "Your title form is writen in" << std::endl << endl;
	}
};

