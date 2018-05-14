all:
	microscheme -m LEO -d /dev/ttyACM0 -auc main.ms -w motors.c
