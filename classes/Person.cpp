/*
 * Person.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */
#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <chrono> // this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));

//TODO your includes here 
#include "../includes/Person.h"
#include "../includes/externs.h"
using namespace std;

//TODO your implementation here

	Person::Person(int personID):personID(personID), numbBowlsSoupEaten(0), numbDrinksDrunk(0){};
	/***
	 * gets soup and drinks until SoupLine runs out of both then exits
	 *
	 * runs a loop repeatedly asking for soup and drinks from msl, the soupline global
	 * calls msl.getSoup(personID)
	 * If call returns NOT_YOUR_TURN then gives other threads a chance by waiting MILLI_SECONDS_TO_WAIT
	 * If call returns BOWL_OF_SOUP then increment numbBowlsSoupEaten
	 * If call returns OUT_OF_SOUP then stop asking for soup
	 *
	 * calls msl.getDrink(personID)
	 * If call returns NOT_YOUR_TURN then gives other threads a chance by waiting MILLI_SECONDS_TO_WAIT
	 * If call returns DRINK then increment numbDrinksDrunk
	 * If call returns OUT_OF_DRINKS then stop asking for drinks
	 *
	 * If soupline is out of both soup and drinks this function exits
	 * @return void
	 */
	void Person::eatlunch(){
		bool hasSoup = true;
		bool hasDrink = true;
		while (hasSoup == true || hasDrink == true) {
			int soupResponse;
			int drinkResponse;

			if (hasSoup){
				soupResponse = msl.getSoup(personID);
			}
			if (hasDrink) {
				drinkResponse = msl.getDrink(personID);
			}
			if (soupResponse == NOT_YOUR_TURN || drinkResponse == NOT_YOUR_TURN) {
				this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));
			}
			if (soupResponse == OUT_OF_SOUP) {
				hasSoup = false;
			}
			if (drinkResponse == OUT_OF_DRINKS) {
				hasDrink = false;
			}
			if (soupResponse == BOWL_OF_SOUP) {
				numbBowlsSoupEaten++;
			}
			if (soupResponse == DRINK) {
				numbDrinksDrunk++;
			}

			this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));

		}

	};
