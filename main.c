
#include <glib.h>
#include <stdio.h>

#include "car.h"
#include "ped.h"
#include "traveler.h"

void destroy_callback(gpointer data);
void print_callback(gpointer data, gpointer user_data);

int main() {

  /* Create an array of pointers to different kinds of Traveller
     subclasses. */
  GPtrArray* everyone = g_ptr_array_new_with_free_func(destroy_callback);
  g_ptr_array_add(everyone, ped_create(PED_WALK, "Carol"));
  g_ptr_array_add(everyone, ped_create(PED_JOG, "Tony"));
  g_ptr_array_add(everyone, car_create("Ford Focus", "RKN710", 30.0));
  g_ptr_array_add(everyone, car_create("Subaru WRX", "4BAT91", 15.0));

  /* Print out the status of each traveler. */
  printf("All visible travelers:\n");
  g_ptr_array_foreach(everyone, print_callback, NULL);

  /* Free memory. Note that we set traveler_destroy as the
     element_free_func, so it is automatically called to free each
     Traveler instance. */
  g_ptr_array_free(everyone, TRUE);

  return 0;
}

void destroy_callback(gpointer data) {
  traveler_destroy((Traveler*) data);
}

void print_callback(gpointer data, gpointer user_data) {
  g_assert(data != NULL);
  /* ignore user_data */

  Traveler* t = data;
  printf("    %s moving at %lf mph, ",
	 traveler_name(t),
	 traveler_speed(t));

  char* license = traveler_license(t);
  if (license != NULL) {
    printf("license plate %s is visible", license);
  } else {
    printf("no license is visible");
  }

  printf("\n");
}
