
#include <glib.h>

#include "ped.h"

/* Declare the functions that will go in the vtable, so their
   identifiers are in scope when we declare the vtable next. */
double _ped_speed(void* this);
char* _ped_name(void* this);
char* _ped_license(void* this);
void _ped_destroy(void* this);

/* Declare Ped's vtable, private to this one .c file. */
TravelerVTable _ped_vtable = {
  .speed = _ped_speed,
  .name = _ped_name,
  .license = _ped_license,
  .destroy = _ped_destroy
};

/* Definition of the constructor declared in ped.h */
Traveler* ped_create(PedStance stance, char* name) {
  Ped* members = g_new(Ped, 1);

  members->stance = stance;
  members->name = g_strdup(name);

  return traveler_create(members, &_ped_vtable);
}

/* Definitions for the vtable functions */

double _ped_speed(void* this) {
  Ped* real_this = (Ped*) this;
  switch (real_this->stance) {
  case PED_STAND:
    return 0.0;
  case PED_WALK:
    return 2.0;
  case PED_JOG:
    return 5.0;
  }	
}

char* _ped_name(void* this) {
  Ped* real_this = (Ped*) this;
  return real_this->name;
}

char* _ped_license(void* this) {
  /* pedestrians never have license plates */
  return NULL;
}

void _ped_destroy(void* this) {
  Ped* real_this = (Ped*) this;
  g_free(real_this->name);
  g_free(this);
}
