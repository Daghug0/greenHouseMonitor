#pragma once
#ifndef GHMFUNCTIONS_H
#define GHMFUNCTIONS_H
#include <LiquidCrystal.h>
#include <DHT.h>
#include <PinChangeInt.h>
#include <string.h>
#include <avr/sleep.h>

void displayData();
void refresh();
void scroll();
void calibration();
void goToSleep();
void wakeUp();
#endif
