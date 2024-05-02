#include "priorityQ.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>



struct mercType
{
	int zombies;
	int spiders;
	int drainDeimos;
	int zombieDogs;
	int hunters;
	int nemesis;
	int civilians;

	mercType()
	{
		zombies = 0;
		spiders = 0;
		drainDeimos = 0;
		zombieDogs = 0;
		hunters = 0;
		nemesis = 0;
		civilians = 0;
	}

	mercType operator+=(const mercType& rhs)
	{
		this->zombies = zombies + rhs.zombies;
		this->spiders = spiders + rhs.spiders;
		this->drainDeimos = drainDeimos + rhs.drainDeimos;
		this->zombieDogs = zombieDogs + rhs.zombieDogs;
		this->hunters = hunters + rhs.hunters;
		this->nemesis = nemesis + rhs.nemesis;
		this->civilians = civilians + rhs.civilians;

		return *this;
	}

	bool operator>(const mercType& rhs) const
	{
		double priorityL, priorityR;

		priorityL = zombies + 1.1 * spiders + 1.2 * drainDeimos 
				+ 1.3 * zombieDogs + 1.4 * hunters
				+ 1.5 * nemesis + 2.0 * civilians;

		priorityR = rhs.zombies + 1.1 * rhs.spiders + 1.2 * rhs.drainDeimos 
				+ 1.3 * rhs.zombieDogs + 1.4 * rhs.hunters
				+ 1.5 * rhs.nemesis + 2.0 * rhs.civilians;

		return priorityL > priorityR;
	}

	double getScore() const
	{
		return zombies + 1.1 * spiders + 1.2 * drainDeimos 
				+ 1.3 * zombieDogs + 1.4 * hunters
				+ 1.5 * nemesis + 2.0 * civilians;
	}
};

int main()
{
	priorityQ<std::string, mercType> mercenaries;
	std::ifstream infile;
	std::string filename, mercName;
	std::string character;
	int amount;
	double leaderScore;
	std::string currentLeader, previousLeader;

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "\nEnter mercenaries file: ";
	std::cin >> filename;

	std::cout << "\n";

	infile.open(filename.c_str());

infile >> mercName;

	while (!infile.eof())
	{
		mercenaries.push_back( mercName, mercType() );

		infile >> mercName;
	}

	infile.close();

	std::cout << "\nEnter simulation file: ";
	std::cin >> filename;

	infile.open(filename.c_str());

	infile >> mercName >> character >> amount;

	while (!infile.eof())
	{
		mercType update;

		if (character == "zombies")
			update.zombies += amount;

		if (character == "zombieDogs")
			update.zombieDogs += amount;

		if (character == "drainDeimos")
			update.drainDeimos += amount;

		if (character == "spiders")
			update.spiders += amount;

		if (character == "hunters")
			update.hunters += amount;

		if (character == "nemesis")
			update.nemesis += amount;

		if (character == "civilians")
			update.civilians += amount;

		mercenaries.increaseKey(mercName, update);

		currentLeader = mercenaries.get_front_key();
		leaderScore = mercenaries.get_front_priority().getScore();

		if (currentLeader != previousLeader)
		{
			std::cout << "\nWe have a new leader: " << currentLeader;
			std::cout << " Score: " << leaderScore << "\n";

			previousLeader = currentLeader;
		}


		infile >> mercName >> character >> amount;
	}


	infile.close();

	int rank = 1;

	while (!mercenaries.isEmpty())
	{
		std::cout << "Rank " << rank << "\n";
		std::cout << "Name: " << mercenaries.get_front_key();
		std::cout << " Score: " << mercenaries.get_front_priority().getScore();
		std::cout << "\n\n";

		rank++;
		mercenaries.pop_front(); 
	}

	return 0;
}