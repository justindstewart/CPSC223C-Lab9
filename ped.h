
#ifndef _PED_H
#define _PED_H

#include "traveler.h"

/* A pedestrian is in one of three states: standing, walking, or
   jogging */
enum PedStanceEnum { PED_STAND, PED_WALK, PED_JOG };

/* Make it so we don't have to write "enum" every time we reference
   this data type */
typedef enum PedStanceEnum PedStance;

typedef struct Ped {
  PedStance stance;
  char* name;
} Ped;

/* Constructor. Note that this is the only public function that is
   specific to the Ped class. This is intentional, we want to
   encapsulate (hide) all the other details of how Ped is
   implemented. */
Traveler* ped_create(PedStance stance, char* name);

#endif
