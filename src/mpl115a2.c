/*
 * @author 	Alexander Rüedlinger <a.rueedlinger@gmail.com>
 * @date 	07.03.2015
 *
 * A C driver for the sensor MPL115A2.
 *  
 */

/*
 * @author 	Alexander Rüedlinger <a.rueedlinger@gmail.com>
 * @date 	07.03.2015
 *
 * A C driver for the sensor MPL115A2.
 *  
 */


#ifndef __MPL115A2__
#define __MPL115A2__
#include <stdint.h>
#include "mpl115a2.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <math.h>
#endif


/**
 * Creates a MPL115A2 sensor object.
 *
 * @param i2c device address
 * @param i2c device file path
 * @return mpl115a2 sensor
 */
void *mpl115a2_init(int address, const char* i2c_device_filepath) {
	//TODO
	return NULL;
}



/**
 * Closes a MPL115A2 object.
 * 
 * @param mpl115a2 sensor
 */
void mpl115a2_close(void *_mpl) {
	//TODO
}



/**
 * Returns the measured pressure in pascal.
 * 
 * @param mpl115a2 sensor
 * @return pressure
 */
long mpl115a2_pressure(void *_mpl) {
	return 0; //TODO
}



/**
 * Returns the measured temperature in celsius.
 * 
 * @param mpl115a2 sensor
 * @return temperature
 */
float mpl115a2_temperature(void *_mpl) {
	return 0; //TODO
}



