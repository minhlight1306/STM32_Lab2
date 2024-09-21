
#include "software_timer.h"
# define MAX_COUNTER 10

int timerCounter[MAX_COUNTER];
int timerFlag[MAX_COUNTER];

void setTimer(int index, int counter){
	timerCounter[index] = counter/10;
	timerFlag[index] = 0;
}
void timerRun(){
	for(int i = 0; i < MAX_COUNTER; i++){
		if(timerCounter[i] >= 0){
			timerCounter[i]--;
		}
		if(timerCounter[i] <= 0){
			timerFlag[i] = 1;
		}
	}
}
int isTimerExpired(int index){
	if(timerFlag[index] == 1){
		timerFlag[index] = 0;
		return 1;
	}
	return 0;
}
