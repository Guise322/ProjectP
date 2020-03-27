#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class TitleForm
{
private:
	string title = "TitleOfForm";
	vector<string> whiteSpace[2];
public:
	void writeIntoFile()
	{

	}

	bool writeTitleForm()
	{
		ofstream fileOf("title.txt", ios::in);

		if (fileOf.is_open())
		{
			whiteSpace[0].resize(5, "\n");
			whiteSpace[1].resize(5, " ");

			fileOf << "writtenTitleForm";

			for (int i = 0; i < whiteSpace[0].size(); i++)
			{
				fileOf << whiteSpace[0][i];
			}

			for (int i = 0; i < whiteSpace[1].size(); i++)
			{
				fileOf << whiteSpace[1][i];
			}

			fileOf << "writtenTitleForm";
		}
		else
			cout << "File could not opened";

		fileOf.close();
		
		return true;
	}
};

