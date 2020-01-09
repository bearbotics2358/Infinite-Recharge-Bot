
#include "SwerveModule.h"

SwerveModule::SwerveModule(int driveID, int steerID, int driveEncID, int steerEncID):
driveMotor(driveID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
steerMotor(steerID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
rawDriveEnc(driveEncID),
rawSteerEnc(steerEncID),
driveEnc(rawDriveEnc),
steerEnc(rawSteerEnc),

{ // WIP

}