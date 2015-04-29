
#ifndef _CAR_H
#define _CAR_H

#include "traveler.h"

/*Car - Data structure to hold car variables. A miles per hour (mph)
  variable declared as a double, a model name string and a license string */
typedef struct Car {
  double mph;
  char*  model_name;
  char*  license;
} Car;

/* Constructor for car class. Only public function. */
Traveler* car_create(char* model_name, char* license, double mph);

#endif
