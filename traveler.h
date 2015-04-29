
#ifndef _TRAVELER_H
#define _TRAVELER_H

typedef struct TravelerVTable {
  double (*speed)(void* this);
  char* (*name)(void* this);
  char* (*license)(void* this);
  void (*destroy)(void* this);
} TravelerVTable;

typedef struct Traveler {
  void* this; // pointer to all member variables
  TravelerVTable* vtable;
} Traveler;

/* Constructor */
Traveler* traveler_create(void* this, TravelerVTable* vtable);

/* Destructor */
void traveler_destroy(Traveler* t);

/* getter for the traveler's speed in miles per hour (mph) */
double traveler_speed(Traveler* t);

/* getter for the traveler's name */
char* traveler_name(Traveler* t);

/* getter for the traveler's license plate number, or NULL if the
   traveler has no visible license */
char* traveler_license(Traveler* t);

#endif
