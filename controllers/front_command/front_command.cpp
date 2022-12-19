// File:          front_command.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/DistanceSensor.hpp>
#define TIME_STEP 64;

// All the webots classes are defined in the "webots" namespace
// using namespace std;
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {

  // create the Robot instance.
  Robot *robot = new Robot();

  // create the Robot instance.
  Keyboard kb;

  // create the Robot instance.
  DistanceSensor *ds[2];
  char dsNames[2][10] = {"distance_sensor_1", "distance_sensor_2"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
    
  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // get the motor devices
  Motor *yawMotor = robot->getMotor("yaw motor");
  Motor *swayMotor = robot->getMotor("sway motor");
  Motor *surgeMotor = robot->getMotor("surge motor");
  Motor *heaveMotor = robot->getMotor("heave motor");

  // set the target positions of the motors
  yawMotor->setPosition(INFINITY);
  swayMotor->setPosition(INFINITY);
  surgeMotor->setPosition(INFINITY);
  heaveMotor->setPosition(INFINITY);

  // set the target velocities of the motors
  yawMotor->setVelocity(0.0);
  swayMotor->setVelocity(0.0);
  surgeMotor->setVelocity(0.0);
  heaveMotor->setVelocity(0.0);
  
  // initial velocities
  int yawVel = 0;
  int swayVel = 0;
  int surgeVel = 0;
  int heaveVel = 0;
    
  std::cout << '"UP" turns up Yaw' << endl;
  std::cout << '"DOWN" turns down Yaw' << endl;
  std::cout << '"LEFT" turns up Sway' << endl;
  std::cout << '"RIGHT" turns down Yaw' << endl;
  std::cout << '"A" turns up Surge' << endl;
  std::cout << '"D" turns down Surge' << endl;
  std::cout << '"W" turns up Heave' << endl;
  std::cout << '"S" turns down Heave' << endl;
  
  int avoidObstacleCounter = 0;
  int current_x, current_y, current_z;
  
  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while ((current_x != robot.x) && (current_y != robot.y) && (current_z != robot.z)){
    if (avoidObstacleCounter > 0) {
      avoidObstacleCounter--;
      yawVel = 1.0;
      swayVel = -1.0;
      surgeVel = 1.0;
      heaveVel = -1.0;
    }
    // read sensors
    else { 
      for (int i = 0; i < 2; i++) {
        if (ds[i]->getValue() < 950.0)
          avoidObstacleCounter = 100;
      }
    }
  
    yawMotor->setVelocity(yawVel)
    swayMotor->setVelocity(swayVel)
    surgeMotor->setVelocity(surgeVel)
    heaveMotor->setVelocity(heaveVel)
    
    int key=kb.getKey();
    
    if (key==kb.UP){
      yawVel += 0.25;
      std::cout << 'Yaw + 0.05. Total Yaw velocity:' << yawVel << endl;
    }
    if (key==kb.DOWN){
      yawVel -= 0.25;
      std::cout << 'Yaw - 0.05. Total Yaw velocity:' << yawVel << endl;
    }
    if (key==kb.LEFT){
      swayVel += 0.25;
      std::cout << 'Sway + 0.05. Total Sway velocity:' << swayVel << endl;
    }
    if (key==kb.RIGHT){
      swayVel -= 0.25;      
      std::cout << 'Sway - 0.05. Total Sway velocity:' << swayVel << endl;
    }
    if (key==ord('A')){
      surgeVel += 0.25;
      std::cout << 'Surge + 0.05. Total Surge velocity:' << surgeVel << endl;
    }  
    if (key==ord('D')){
      surgeVel -= 0.25;
      std::cout << 'Surge - 0.05. Total Surge velocity:' << surgeVel << endl;
    }
    if (key==ord('W')){
      heaveVel += 0.25;
      std::cout << 'Heave + 0.05. Total Heave velocity:' << HeaveVel << endl;
    }
    if (key==ord('S')){
      heaveVel -= 0.25;
      std::cout << 'Heave - 0.05. Total Heave velocity:' << HeaveVel << endl;
    }
       
  };

  delete robot;

  return 0;
}
