#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static char *handleTheseSignals[32];
static char *lastSignals[3];
static int numberOfSameSignals = 0;
static int numberOfSignalsToHandle = 1;
static int signalIsOneOfTheHandledOnes = 0;//0 means false, 1 means true;
static int numberOfSignalsRecieved = 0;
static char *allSignals[] = {
				"THIS INDEX WILL NOT BE USED",
				"HUP",
				"INT",
				"QUIT",
				"ILL",
				"TRAP",
				"ABRT OR IOT",
				"BUS",
				"FPE",
				"KILL",
				"USR1",
				"SEGV",
				"USR2",
				"PIPE",
				"ALRM",
				"TERM",
				"STKFLT",
				"CHLD",
				"CONT",
				"STOP",
				"TSTP",
				"TTIN",
				"TTOU",
				"URG",
				"XCPU",
				"XFSZ",
				"VTALRM",
				"PROF",
				"WINCH",
				"IO",
				"PWR",
				"SYS OR UNUSED",
			};

char* whatSignalIsThis(int theSignal){
	return allSignals[theSignal];
}

void handler(int mySignal)
{
	struct timeval tv;
	double timeInMill = (tv.tv_sec * 1000) + (tv.tv_usec/1000);
	char* theSignalName = whatSignalIsThis(mySignal);
	int i = 1;
	for (; i < numberOfSignalsToHandle; i++) {
		if (strcmp(theSignalName, handleTheseSignals[i]) == 0) {
			printf("SIG%s caught at %.0f\n", theSignalName, timeInMill);
			signalIsOneOfTheHandledOnes = 1;
			break;
		} else {
			signalIsOneOfTheHandledOnes = 0;
		}
	}

	if (numberOfSameSignals == 0) {
		lastSignals[0] = theSignalName;
		numberOfSameSignals++;
	} else {
		if (strcmp(lastSignals[numberOfSameSignals - 1], theSignalName) == 0) {
			lastSignals[numberOfSameSignals] = theSignalName;
			numberOfSameSignals++;
		} else {
			numberOfSameSignals = 1;
			lastSignals[0] = theSignalName;
		}
	}
	
	if (numberOfSameSignals == 3) {
		printf("catcher: Total signals count = %d\n", numberOfSignalsRecieved + 1);
		exit(0);
	}
	
	if (signalIsOneOfTheHandledOnes == 0) {
		exit(0);
	}
}

int pause(void);

int main (int argc, char *argv[])
{
	printf("%d\n", getpid());
	
	numberOfSignalsToHandle = argc;
	int i = 0;
	for (i = 0; i < argc; i++) {
		handleTheseSignals[i] = argv[i];
	}

	for (i = 0; i < 32; i++) {
		signal(i, handler);
	}

	while (1) {
		pause();
		numberOfSignalsRecieved++;
	}

	return 0;
}
