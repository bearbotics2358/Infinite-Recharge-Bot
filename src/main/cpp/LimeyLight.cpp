#include "LimeyLight.h"

 //std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

LimeyLight::LimeyLight ()
: table(nt::NetworkTableInstance::GetDefault())
{

}

LimeyLight::~LimeyLight ()
{

}

/* 
        tv: are there any valid targets? 
            - returns 0 or 1
        tx: horizontal offset: how much of the target can the robot see? 
            - -27 to 27 degrees
        ty: vertical offset: how much of the target can the robot see? 
            - -20.5 to 20.5
        ta: target area: distance to the target
            - 0% to 100% of image 
        thor: gets width of target 
            - returns a float
*/   

float LimeyLight::getDist () const
{
    float temp = GET_LIMELIGHT_VALUE(table, "ts") * (M_PI / 180.0f);
    return ((58.0f / (GET_LIMELIGHT_VALUE(table, "thor"))) / cos(temp)) * 191.0f; //Temporary Constants
}


float LimeyLight::getAngleShooter () const
{
    return 0.0f;
}

float LimeyLight::getAngleX () const
{
    return GET_LIMELIGHT_VALUE(table, "tx");
}

float LimeyLight::getAngleY () const
{
    return GET_LIMELIGHT_VALUE(table, "ty");
}

float LimeyLight::getArea () const
{
    return GET_LIMELIGHT_VALUE(table, "ta");
}

float LimeyLight::getAngleTarget () const
{
    return GET_LIMELIGHT_VALUE(table, "ts");
}

float LimeyLight::getWidth () const
{
    return GET_LIMELIGHT_VALUE(table, "thor");
}

/* 
    LED Mode Number Meanings: 
    0: LED is set to current pipeline
    1: Turn LED Off 
    2: LED Blink
    3: Turn LED On
*/ 

void LimeyLight::ledOff () 
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); 
}

void LimeyLight::ledOn ()
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}

void LimeyLight::cameraMode(int whichCam) 
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", whichCam);
} 

void LimeyLight::printValues () 
{
    // reading values form the lime light
    double angleX = getAngleX(); // offset in degrees (x)
    double angleY = getAngleY(); // offset in degrees (y)
    double targetArea = getArea(); // <- Target area, between 0 and 100 (how much of the target can be seen)
    double targetSkew = getAngleTarget(); // <- Rotation of target 
    double width = getWidth(); // width of the target box **not the actual target

    frc::SmartDashboard::PutNumber("Horizontal Offset: ", angleX); 
    frc::SmartDashboard::PutNumber("Vertical Offset: ",  angleY); 
    frc::SmartDashboard::PutNumber("Target Area: ", targetArea); 
    frc::SmartDashboard::PutNumber("Target Skew: ", targetSkew); 
    frc::SmartDashboard::PutNumber("Target Width: ", width); 

}