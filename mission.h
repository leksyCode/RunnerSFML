#include <SFML/Graphics.hpp>
using namespace std;

int getCurrentMission(int countLvl) {
	int mission = 0;
	switch (countLvl)
	{
	case 0: {
		mission = 0;  break;
	}
	case 1: {
		mission = 1;  break;
	}
	case 2: {
		mission = 2;  break;
	}
	case 3: {
		mission = 3;  break;
	}
	}
	return mission;
}


