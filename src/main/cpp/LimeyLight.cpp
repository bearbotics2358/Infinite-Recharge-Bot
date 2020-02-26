#ifndef LAPTOP
#include "LimeyLight.h"

LimeyLight::LimeyLight ()
: table(nt::NetworkTableInstance::GetDefault()),
lemonLight(0.05, 0.0, 0.0)
{
    for (int i = 0; i < LOOKUP_TABLE_LEN - 1; i ++)
    {
        tableSlope[i].dist = tableVals[i].dist;
        tableSlope[i].value = (tableVals[i + 1].value - tableVals[i].value) / (tableVals[i + 1].dist - tableVals[i].dist);
    }
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
    // distance in feet
    float temp = GET_LIMELIGHT_VALUE(table, "ts") * (M_PI / 180.0f);
    return ((58.0f / (GET_LIMELIGHT_VALUE(table, "thor"))) / cos(temp)) * 191.0f; //Temporary Constants
}

float LimeyLight::getXAngleShooter (const std::vector<float> velocity, const float gyro) const
{
    float diff = gyro + getAngleX();
    diff = diff < 0 ? 360 + diff : diff;
    return diff;
}

float LimeyLight::getYAngleShooter () const
{
    return 0.0f;
}

float LimeyLight::getVelocityShooter () const
{
    float dist = getDist ();
    int i = 0;
    while (dist < tableVals[i].dist && i < LOOKUP_TABLE_LEN)
    {
        i ++;
    }
    int tempi = i > LOOKUP_TABLE_LEN - 1 ? LOOKUP_TABLE_LEN - 2 : i;
    return tableVals[i].dist + (tableSlope[tempi].value * (dist - tableVals[i].dist));
}

bool LimeyLight::isTarget () const
{
    return GET_LIMELIGHT_VALUE(table, "tv") == 1;
}

float LimeyLight::getAngleX () const
{
    return GET_LIMELIGHT_VALUE(table, "tx");
}

float LimeyLight::getAngleY () const
{
    return GET_LIMELIGHT_VALUE(table, "ty") + SHOOTER_ANGLE;
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

float LimeyLight::calcZAxis() {
    if(isTarget())
    {
        float rowlet = getAngleX();
        float shinyRowlet = -1 * std::clamp(lemonLight.Calculate(0.0, rowlet), -0.4, 0.4);
        return shinyRowlet;
    }
    return 0;
}

void LimeyLight::setTableVal (const int index, const float dist, const float value)
{
    tableVals[index].dist = dist;
    tableVals[index].value = value;
}
#endif