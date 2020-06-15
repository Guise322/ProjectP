#pragma once
#include <iostream>
#include <string>

class RepeatProcess
{
private:
	bool repeatRP = false;
    std::string check = " ";

public:
	bool repeat(std::string title)
	{
        bool intEndOfMode = false;
        do
        {
            std::cout << std::endl << title + " [Y/n]" << std::endl << std::endl;

            //std::cin.ignore(1, '/n');
            std::getline(std::cin, check);

            if (check == "y" || check == "Y" || check == "")
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