
#include <glib.h>

#include "traveler.h"

Traveler* traveler_create(void* this, TravelerVTable* vtable) {
  Traveler* t = g_new(Traveler, 1);

  t->this = this;
  t->vtable = vtable;

  return t;
}

void traveler_destroy(Traveler* t) {
  t->vtable->destroy(t->this);
  g_free(t);
}

double traveler_speed(Traveler* t) {
  return t->vtable->speed(t->this);
}

char* traveler_name(Traveler* t) {
  return t->vtable->name(t->this);
}

char* traveler_license(Traveler* t) {
  return t->vtable->license(t->this);
}
