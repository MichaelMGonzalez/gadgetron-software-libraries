#ifndef GADGET_MANAGER
#define GADGET_MANAGER

class ServoMotor;
class Motor;
// These are state bits for any part
#define HAS_SETUP 1
#define ATTACHED 2
#define BLOCKED 0x80

// State Macros
#define IS_BLOCKED (state & BLOCKED) 


#include <Arduino.h>
#include "ServoMotor.h"

/**
 * Filename: GadgetManager.h \n 
 * Author: Michael Gonzalez \n
 * Description: This class managers critical resources in Gadgetron Robots.\n
 * Currently, its primary function is to allow the motor drivers to reclaim \n
 * PWM pins if servos have control over them. 
 */

class GadgetManager {
    friend class ServoMotor;
    friend class Motor;
    private:
        /*
         * Registers a servo with the GadgetManager.
         */
        static void registerServo( ServoMotor * servo );
        /*
         * Allows the calling class to use a list of pins. \n
         * pins is the list of pins to free \n
         * number is the number of pins in pins \n
         */
        static void freePins(int pins[], int number );
        /*
         * Allows the original holder of a pin to have access to it again \n
         * pins is the list of pins to restore \n
         * number is the number of pins in pins \n
         */
        static void reenablePins(int pins[], int number );
        // Only one GadgetManger should ever exist at a time! DO NOT MODIFY
        static GadgetManager * singleton;
        // Helper function to freePins and reenable pins
        static void modifyPins(int pins[], int number, bool shouldFree );
        // Can call block and disable on entire servo list
        // If should block is true,
        // Then this function calls block on the whole list
        // Else, this function calls enable on the whole list
        static void modifyServo(bool shouldBlock);
        ServoMotor * servoList = 0;
};


#endif
