
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*
 *
 *    Linked List lab.
 *    - Build a library for singly linked list.
 *    - Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

#include "slist.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

// NEED TO CONVERT KILOMETERS TO MILES AFTERWARDS BC DISTANCE EARTH RETURNS IN
// KILOMETERS

using namespace std;

class Airport {
public:
  char code[5];
  double longitude;
  double latitude;
  double dist;
  Airport *next;
};

void simpleSortTotal(Airport *p1, Airport *ref);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  ifstream infile;
  int i = 0;
  char cNum[12];
  char airports[1000];
  Airport *head = new Airport();
  int airportCount;

  infile.open("airport-codes_US.csv", ifstream::in);
  Airport *prev = head;
  if (infile.is_open()) {
    int c = 0;
    while (infile.good()) {
      Airport *airport = new Airport();
      infile.getline(airport->code, 256, ',');
      infile.getline(airports, 256, ',');
      if (!strstr(airports, "airport")) {
        infile.getline(airports, 256, '\n');
        continue;
      }                                   // check if it is an airport
      infile.getline(airports, 256, ','); // get past the name
      infile.getline(cNum, 256, ',');
      airport->longitude = atof(cNum);
      infile.getline(cNum, 256, ',');
      airport->latitude = atof(cNum);
      infile.getline(airports, 256, '\n');

      // Add new airport to list
      prev->next = airport;
      prev = airport;

      i++;
      c++;
    }
    airportCount = c - 1;
    // Skip header
    // head->next = head->next->next;
    infile.close();

    Airport *ref;
    // Find reference airprt
    prev = head;
    while (prev->next) {
      if (strncmp(prev->next->code, "KAUS", 4) == 0) {
        ref = prev->next;
        break;
      }
      prev = prev->next;
    }
    if (ref == NULL) {
      cout << "REF NEVER MADE";
      exit(1);
    }

    prev = head;
    while (prev->next) {
      prev->next->dist =
          distanceEarth(prev->next->latitude, prev->next->longitude,
                        ref->latitude, ref->longitude);
      prev = prev->next;
    }

    // Sort linked list
    simpleSortTotal(head, ref);

    // Check if sorted and still have everything
    prev = head;
    while (prev->next->next != NULL) {
      if (prev->next->dist > prev->next->next->dist)
        cout << "ERROR "
             << distanceEarth(prev->next->latitude, prev->next->longitude,
                              ref->latitude, ref->longitude) -
                    distanceEarth(prev->next->next->latitude,
                                  prev->next->next->longitude, ref->latitude,
                                  ref->longitude)
             << endl;
      prev = prev->next;
    }

    // // Find Farthest airport
    prev = head;
    while (prev->next != NULL)
      prev = prev->next;
    cout << prev->code << " long: " << prev->longitude
         << " lat: " << prev->latitude << " dist: "
         << distanceEarth(prev->latitude, prev->longitude, ref->latitude,
                          ref->longitude)
         << endl;

    // // Print all airports within 100 miles radius
    prev = head->next;
    ofstream in100("within100miles.csv");
    if (in100.is_open()) {
      while (prev != NULL && prev->dist <= 100) {
        in100 << prev->code << " long: " << prev->longitude
              << " lat: " << prev->latitude << " dist: " << prev->dist << endl;
        prev = prev->next;
      }
    }
    in100.close();

    // Print all the airports
    prev = head->next;
    while (prev != NULL) {
      cout << prev->code << " long: " << prev->longitude
           << " lat: " << prev->latitude << " dist: "
           << distanceEarth(prev->latitude, prev->longitude, ref->latitude,
                            ref->longitude)
           << endl;
      prev = prev->next;
    }

  } else {
    cout << "Error opening file";
  }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  double toMile = 0.621371;
  return 2.0 * earthRadiusKm * toMile *
         asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
Provide sort routine on linked list
*/
void simpleSortTotal(Airport *p1, Airport *ref) {
  Airport *temp;
  Airport *
      p2; // p2->next and p2->next->next are the two things that will be swapped
  int count = 0;
  bool swapped = true;
  while (swapped) {
    swapped = false;
    p2 = p1; // Keeping the head
    while (p2->next->next != NULL) {
      if (p2->next->dist > p2->next->next->dist) {
        temp = p2->next;
        p2->next = p2->next->next;
        temp->next = p2->next->next;
        p2->next->next = temp;
        swapped = true;
      }
      p2 = p2->next;
    }
  }
}