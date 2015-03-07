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

typedef struct {
	/* file descriptor */
	int file;
	
	/* i2c device address */
	int address;
	
	/* i2c device file path */
	char *i2c_device;
	
} mpl115a2_t;


#define TO_S(x)	(mpl115a2_t*) x

#define __MPL115A2__DEBUG__
#ifdef __MPL115A2__DEBUG__				
#define DEBUG(...)	printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif




/**
 * Creates a MPL115A2 sensor object.
 *
 * @param i2c device address
 * @param i2c device file path
 * @return mpl115a2 sensor
 */
void *mpl115a2_init(int address, const char* i2c_device_filepath) {
	DEBUG("device: init using address %#x and i2cbus %s\n", address, i2c_device_filepath);
	
	void *_s = malloc(sizeof(mpl115a2_t));
	if(_s == NULL)  {
		DEBUG("error: malloc returns NULL pointer\n");
		return NULL;
	}

	mpl115a2_t *s = TO_S(_s);
	s->address = address;

	s->i2c_device = (char*) malloc(strlen(i2c_device_filepath) * sizeof(char));
	if(s->i2c_device == NULL) {
		DEBUG("error: malloc returns NULL pointer!\n");
		return NULL;
	}

	// copy string
	strcpy(s->i2c_device, i2c_device_filepath);
	
	// open i2c device
	int file;
	if((file = open(s->i2c_device, O_RDWR)) < 0) {
		DEBUG("error: %s open() failed\n", s->i2c_device);
		return NULL;
	}
	s->file = file;

	DEBUG("device: open ok\n");
	return _s;
}



/**
 * Closes a MPL115A2 object.
 * 
 * @param mpl115a2 sensor
 */
void mpl115a2_close(void *_s) {
	DEBUG("close device\n");
	mpl115a2_t *s = TO_S(_s);
	
	if(close(s->file) < 0)
		DEBUG("error: %s close() failed\n", s->i2c_device);
	
	free(s->i2c_device); // free string
	s->i2c_device = NULL;
	free(s); // free structure
	_s = NULL;
}



/**
 * Returns the measured pressure in pascal.
 * 
 * @param mpl115a2 sensor
 * @return pressure
 */
long mpl115a2_pressure(void *_s) {
	return 0; //TODO
}



/**
 * Returns the measured temperature in celsius.
 * 
 * @param mpl115a2 sensor
 * @return temperature
 */
float mpl115a2_temperature(void *_s) {
	return 0; //TODO
}



