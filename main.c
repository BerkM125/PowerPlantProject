#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "powerplant_specifications.h"

#define BUDGET 2000
#define REQUIRED_POWER 1500
#define MAXIMUM_ENVIRONMENTAL_IMPACT 299

typedef struct powerplant_struct {
	float cost;
	int capacity;
	int environmental_impact;
} powerplant;
typedef powerplant plant_totals;

powerplant windfarm;
powerplant hydroplant;
powerplant solarenergy;
powerplant coalplant;
powerplant nuclearplant;

powerplant *init_powerplant (powerplant *p, float cost, int capacity, int environmental_impact) {
	p->capacity = capacity;
	p->cost = cost;
	p->environmental_impact = environmental_impact;
	return(p);
}

plant_totals calculate_totals (int windcount, int hydrocount, int solarcount, int coalcount, int nuclearcount) {
	plant_totals wind;
	plant_totals hydro;
	plant_totals solar;
	plant_totals coal;
	plant_totals nuclear;
	plant_totals totalstruct;
	float totalcost;
	int totalcapacity;
	int totalei;

	if(windcount > WINDFARM_MAXIMUM || hydrocount > HYDROPLANT_MAXIMUM || solarcount > SOLARPOWER_MAXIMUM) {
		printf("\nPOWERPLANT COUNT EXCEEDS LIMIT.\n");
		return totalstruct;
	}

	wind.capacity = (windfarm.capacity*windcount); 
	wind.cost = (windfarm.cost*(float)windcount);
	wind.environmental_impact = (windfarm.environmental_impact*windcount);

	hydro.capacity = (hydroplant.capacity*hydrocount); 
	hydro.cost = (hydroplant.cost*(float)hydrocount);
	hydro.environmental_impact = (hydroplant.environmental_impact*hydrocount);

	solar.capacity = (solarenergy.capacity*solarcount); 
	solar.cost = (solarenergy.cost*(float)solarcount);
	solar.environmental_impact = (solarenergy.environmental_impact*solarcount);

	coal.capacity = (coalplant.capacity*coalcount); 
	coal.cost = (coalplant.cost*(float)coalcount);
	coal.environmental_impact = (coalplant.environmental_impact*coalcount);

	nuclear.capacity = (nuclearplant.capacity*nuclearcount); 
	nuclear.cost = (nuclearplant.cost*(float)nuclearcount);
	nuclear.environmental_impact = (nuclearplant.environmental_impact*nuclearcount);
	
	totalcost = wind.cost+hydro.cost+solar.cost+coal.cost+nuclear.cost;
	totalcapacity = wind.capacity+hydro.capacity+solar.capacity+coal.capacity+nuclear.capacity;
	totalei = wind.environmental_impact+hydro.environmental_impact+solar.environmental_impact+coal.environmental_impact+nuclear.environmental_impact;

	printf("Wind Total MW: %d \nWind Total Cost: %f \nWind Total Impact: %d\n\n", wind.capacity, wind.cost, wind.environmental_impact);
	printf("Hydro Total MW: %d \nHydro Total Cost: %f \nHydro Total Impact: %d\n\n", hydro.capacity, hydro.cost, hydro.environmental_impact);
	printf("Solar Total MW: %d \nSolar Total Cost: %f \nSolar Total Impact: %d\n\n", solar.capacity, solar.cost, solar.environmental_impact);
	printf("Coal Total MW: %d \nCoal Total Cost: %f \nCoal Total Impact: %d\n\n", coal.capacity, coal.cost, coal.environmental_impact);
	printf("Nuclear Total MW: %d \nNuclear Total Cost: %f \nNuclear Total Impact: %d\n\n", nuclear.capacity, nuclear.cost, nuclear.environmental_impact);
	printf("Total Cost: %f\nTotal MW: %d\nTotal Environmental Impact: %d\n", totalcost, totalcapacity, totalei);

	if(totalcost > BUDGET) printf("\n\nCOST EXCEEDS LIMIT\n");
	if(totalcapacity < REQUIRED_POWER) printf("\n\nINSUFFICIENT POWER\n");
	totalstruct.capacity = totalcapacity;
	totalstruct.cost = totalcost;
	totalstruct.environmental_impact = totalei;
	return totalstruct;
}

int main (void) {
	int windnum, hydronum, solarnum, coalnum, nuclearnum;
	plant_totals totals;
	init_powerplant (&windfarm, WINDFARM_COST, WINDFARM_CAPACITY, WINDFARM_EI);
	init_powerplant (&hydroplant, HYDROPLANT_COST, HYDROPLANT_CAPACITY, HYDROPLANT_EI);
	init_powerplant (&solarenergy, SOLARPOWER_COST, SOLARPOWER_CAPACITY, SOLARPOWER_EI);
	init_powerplant (&coalplant, COAL_COST, COAL_CAPACITY, COAL_EI);
	init_powerplant (&nuclearplant, NUCLEAR_COST, NUCLEAR_CAPACITY, NUCLEAR_EI);
	/*while(1) {
		printf("Wind Plant Count: ");
		scanf("%d", &windnum);
		printf("Hydro Plant Count: ");
		scanf("%d", &hydronum);
		printf("Solar Plant Count: ");
		scanf("%d", &solarnum);
		printf("Coal Plant Count: ");
		scanf("%d", &coalnum);
		printf("Nuclear Plant Count: ");
		scanf("%d", &nuclearnum);
		calculate_totals (windnum, hydronum, solarnum, coalnum, nuclearnum);
	}*/
	while (totals.environmental_impact > MAXIMUM_ENVIRONMENTAL_IMPACT || totals.capacity < REQUIRED_POWER || totals.cost > BUDGET) {
		windnum = rand() % WINDFARM_MAXIMUM+1;
		hydronum = rand() % HYDROPLANT_MAXIMUM+1;
		solarnum = rand() % SOLARPOWER_MAXIMUM+1;
		nuclearnum = rand() % 15;
		coalnum = 0;
		printf("\nWind Farms: %d\nHydro Plants: %d\nSolar Plants: %d\nNuclear Plants: %d\nCoal Factories: %d\n", windnum, hydronum, solarnum, nuclearnum, coalnum);
		totals = calculate_totals (windnum, hydronum, solarnum, coalnum, nuclearnum);
	}
	return (0);
}
