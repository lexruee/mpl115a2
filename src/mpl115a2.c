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
	
	/* coefficients */
	int16_t a0;
	int16_t b1;
	int16_t b2;
	int16_t c12;
		
} mpl115a2_t;

#define MPL115A2_REG_PRESSURE_MSB	 0x00
#define MPL115A2_REG_TEMPERATURE_MSB	 0x02

/*
 * Coefficients
 */
#define MPL115A2_REG_A0_MSB		 0x04
#define MPL115A2_REG_B1_MSB		 0x06
#define MPL115A2_REG_B2_MSB		 0x08
#define MPL115A2_REG_C12_MSB		 0x0A


#define TO_S(x)	(mpl115a2_t*) x

#define __MPL115A2__DEBUG__
#ifdef __MPL115A2__DEBUG__				
#define DEBUG(...)	printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


/*
 * Helper function prototypes.
 */

void mpl115a2_read_coeff(void *_s) {
	mpl115a2_t *s = TO_S(_s);

	uint8_t a0_msb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_A0_MSB);
	uint8_t a0_lsb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_A0_MSB + 1);
	
	uint8_t b1_msb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_B1_MSB);
	uint8_t b1_lsb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_B1_MSB + 1);
	
	uint8_t b2_msb = (uint8_t) i2c_smbus_read_word_data(s->file, MPL115A2_REG_B2_MSB);
	uint8_t b2_lsb = (uint8_t) i2c_smbus_read_word_data(s->file, MPL115A2_REG_B2_MSB + 1);
		
	uint8_t c12_msb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_C12_MSB);		
	uint8_t c12_lsb = (uint8_t) i2c_smbus_read_byte_data(s->file, MPL115A2_REG_C12_MSB + 1);

	s->a0 = (a0_msb<<8) + a0_lsb;
	s->b1 = (b1_msb<<8) + b1_lsb;
	s->b2 = (b2_msb<<8) + b2_lsb;
	s->c12 = (c12_msb<<6) + (c12_lsb>>2);
	
	
	printf("a0_msb: %#x, a0_lsb: %#x\n ", a0_msb, a0_lsb);
	printf("b1_msb: %#x, b1_lsb: %#x\n ", b1_msb, b1_lsb);
	printf("b2_msb: %#x, b2_lsb: %#x\n ", b2_msb, b2_lsb);
	printf("c12_msb: %#x,c12_lsb: %#x\n ", c12_msb, c12_lsb);

	printf("a1: %i\n ", s->a0);
	printf("b1: %i\n ", s->b1);
	printf("b2: %i\n ", s->b2);
	printf("c12: %i\n ", s->c12);
}


/*
 * Sets the address for the i2c device file.
 */
int mpl115a2_set_addr(void *_s) {
	mpl115a2_t* s = TO_S(_s);
	int error;

	if((error = ioctl(s->file, I2C_SLAVE, s->address)) < 0)
		DEBUG("error: ioctl() failed\n");

	return error;
}


/*
 * Implementation of the interface functions.
 */

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
	if(mpl115a2_set_addr(s) < 0)
		return NULL;
	mpl115a2_read_coeff(s);

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



