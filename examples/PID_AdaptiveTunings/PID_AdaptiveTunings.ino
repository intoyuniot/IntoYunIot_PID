#include <PID.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 3

//定义变量
double Setpoint, Input, Output;

//定义激进和保守的调整参数
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

//初始化调整参数
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void setup()
{
    //初始化变量
    Input = analogRead(PIN_INPUT);
    Setpoint = 100;

    //打开PID
    myPID.SetMode(AUTOMATIC);
}

void loop()
{
    Input = analogRead(PIN_INPUT);

    double gap = abs(Setpoint-Input); //判断与设定值的距离
    if (gap < 10)
    {  //关闭设定值，使用保守的调整参数
        myPID.SetTunings(consKp, consKi, consKd);
    }
    else
    {
        //偏离设定值太多,用激进的调整参数
        myPID.SetTunings(aggKp, aggKi, aggKd);
    }

    myPID.Compute();
    analogWrite(PIN_OUTPUT, Output);
}
