/*
Programmed by: Justin Stewart (scubastew@csu.fullerton.edu)
*/

#include <glib.h>

#include "car.h"

/* Vtable Functions */
double _car_mph(void* this);
char*  _car_model_name(void* this);
char*  _car_license(void* this);
void   _car_destroy(void* this);

/*Declare Car's vtable, which is private. */
TravelerVTable _car_vtable = {
  .speed = _car_mph,
  .name = _car_model_name,
  .license = _car_license,
  .destroy = _car_destroy
};

/* Definition of the constructor declared in car.h */
Traveler* car_create(char* model_name, char* license, double mph) {
  Car* members = g_new(Car, 1);

  members->model_name = g_strdup(model_name);
  members->license = g_strdup(license);
  members->mph = mph;

  return traveler_create(members, &_car_vtable);
}

/* Definitions for vtable functions */
double _car_mph(void* this) {
  Car* real_this = (Car*) this;
  return real_this->mph;
}

char*  _car_model_name(void* this) {
  Car* real_this = (Car*) this;
  return real_this->model_name;
}

char*  _car_license(void* this) {
  Car* real_this = (Car*) this;
  return real_this->license;
}

void   _car_destroy(void* this) {
  Car* real_this = (Car*) this;
  g_free(real_this->model_name);
  g_free(real_this->license);
  g_free(this);
}
