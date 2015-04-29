
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Traveler* traveler_create(void* this, TravelerVTable* vtable) {
	Traveler* t = malloc(sizeof(Traveler));
	if (!t)
		return NULL;
	t->this = this;
	t->vtable = vtable;
	return t;
}

void traveler_destroy(Traveler* t) {
	t->vtable->destroy(t->this);
	free(t);
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

enum _PedStance { PED_STAND, PED_WALK, PED_JOG };
typedef enum _PedStance PedStance;

typedef struct Ped {
	PedStance stance;
	char* name;
} Ped;

double _ped_speed(void* this);
char* _ped_name(void* this);
char* _ped_license(void* this);
void _ped_destroy(void* this);

TravelerVTable _ped_vtable = {
	.speed = _ped_speed,
	.name = _ped_name,
	.license = _ped_license, 
	.destroy = _ped_destroy
};

Traveler* ped_create(PedStance stance, char* name) {
	Ped* members = malloc(sizeof(Ped));
	if (!members)
		return NULL;

	members->stance = stance;
	members->name = strdup(name);

	return traveler_create(members, &_ped_vtable);
}

double _ped_speed(void* this) {
	Ped* real_this = (Ped*) this;
	switch (real_this->stance) {
		case PED_STAND:
			return 0;
		case PED_WALK:
			return 2;
		case PED_JOG:
			return 5;
	}	
}

char* _ped_name(void* this) {
	Ped* real_this = (Ped*) this;
	return real_this->name;
}

char* _ped_license(void* this) {
	return NULL;
}

void _ped_destroy(void* this) {
	Ped* real_this = (Ped*) this;
	free(real_this->name);
	free(this);
}

int main() {

	Traveler* everyone[] = {
		ped_create(PED_WALK, "Carol"),
		ped_create(PED_JOG, "Tony")
		};

	for (int i = 0; i < 2; i++) {
		Traveler* t = everyone[i];
		printf("%s is moving at %lf mph\n",
		       traveler_name(t),
		       traveler_speed(t));  
		traveler_destroy(t);
	}

	return 0;
}


