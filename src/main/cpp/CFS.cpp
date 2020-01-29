
#include "CFS.h"



CFS::CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot):
    a_ShootLeft(shoot1),
    a_ShootRight(shoot2),
    a_FeedTop(feed1),
    a_FeedBot(feed2),
    a_Collector(collect),
    a_Pivot(pivot)
    {

        a_ShootLeft.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);

        a_ShootRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);

    }

    void CFS::Shoot() {
        a_ShootLeft.Set(ControlMode::PercentOutput, SHOOT_SPEED);
        a_ShootRight.Set(ControlMode::PercentOutput, SHOOT_SPEED);
    }

    void CFS::Shoot(float speed) {
        a_ShootLeft.Set(ControlMode::PercentOutput, speed);
        a_ShootRight.Set(ControlMode::PercentOutput, speed);
    }