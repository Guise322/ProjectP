#pragma once
#include <iostream>
#include <string>

class RepeatProcess
{
private:
	bool repeatRP = false;
    std::string check = "";

public:
	bool repeat(std::string title)
	{
        bool intEndOfMode = false;
        do
        {
            std::cout << std::endl << title + " [y/n]" << std::endl << std::endl;

            std::cin >> check;

            if (check == "y")
            {
                repeatRP = true;
                intEndOfMode = false;
            }
            else if (check != "n")
            {
                std::cout << std::endl << "Error!" << std::endl << std::endl << "Repeate the command" << std::endl;
                repeatRP = false;
                intEndOfMode = false;
            }
            else
            {
                repeatRP = true;
                intEndOfMode = true;
            }
        } while (!repeatRP);
        
        return intEndOfMode;
	}
};