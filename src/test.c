#include "mpl115a2.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-2";
	int address = 0x60;
	
	void *mpl = mpl115a2_init(address, i2c_device);
	
	if(mpl != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			float t = mpl115a2_temperature(mpl);
			float p = mpl115a2_pressure(mpl);
			printf("temperature: %0.2f, pressure: %0.2f\n", t, p);
			usleep(2 * 1000 * 1000);
		}
	
		mpl115a2_close(mpl);
	}
	
	return 0;
}
