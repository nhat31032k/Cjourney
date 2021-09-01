#ifndef __DEFS__
#define __DEFS__

const int EVENT_SIZE = 1001;
const int MAX_CHARACTER_EACH_LINE = 5001;

struct musketeer 
{
	int ID; 
	int HP; // the initial health point
	int nHealthPoint; // the current heath point
	int nGoldCoin; // the current number of gold coins
	int nRedDiamonds, nBlueDiamonds; // the current number of diamonds		
};

#endif
