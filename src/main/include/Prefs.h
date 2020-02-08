
#pragma once // only add this code once; saves space by removing redundancy

// Declare constants such as CAN IDs here 


/*====== MOTOR CONTROLLER IDS ======*/
#define FL_STEER_ID 1
#define FL_DRIVE_ID 2

#define FR_STEER_ID 11
#define FR_DRIVE_ID 12

#define BL_STEER_ID 21
#define BL_DRIVE_ID 22

#define BR_STEER_ID 31
#define BR_DRIVE_ID 32

#define PI 3.14159265



/*
// Module CAN IDs FL, FR, BL, BR
FL:
 Module 1 Turn - 1
 Module 1 Drive - 2

FR:
 Module 2 Turn - 11
 Module 2 Drive - 12

BL:
 Module 3 Turn - 21
 Module 3 Drive - 22

BR:
 Module 4 Turn - 31
 Module 4 Drive - 32
*/




/* ========== Joystick Ports ========= */
#define JOYSTICK_PORT 1
#define JOYSTICK_DEADZONE 0.15

#define BUTTON_BOX 3
#define XBOX_CONTROLLER 5

#define TICKS_STEERING 18.0 // roughly 18 "position" units per steering rotation

/* ====== ASCII ART ======= */
//   <====[-<('-'<)


/* ============ GEAR RATIOS ======== */
// drive motor -> wheel = 10:1 (10 drive rotations for one wheel rotation)
// radius of wheel = 2 inches
// circumfrence = 4 Pi inches
// 10 ticks = 4 Pi inches
#define INCHES_PER_TICK (2.0 / 5) * PI // inches

/* ============= AUTO VALUES 4 Jason yoyoyo =========== */
#define ARBITRARY_DIST_BACKWARDS 20.0 // inches
#define TOF_TO_WALL 27.0 // inches
#define LINE_TO_BALL_FAR 192.66 // inches

#define ARM_DEFAULT_POSITION 90 //degrees???? CHANGE WHEN ACTUALLY FOUND

#define SHOOT_VOLTS .7
#define SHOOT_VELOCITY 4000
#define COLLECT_SPEED .5
#define FEED_SPEED .23

#define SHOOT_1 41
#define SHOOT_2 42
#define FEED_1 43
#define FEED_2 44
#define COLLECT 45
#define PIVOT 46

// int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot

#define BEAM_BREAK1 2
#define BEAM_BREAK2 3