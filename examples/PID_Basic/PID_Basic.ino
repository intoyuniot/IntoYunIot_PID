/********************************************************
 * 读取模拟量的值从而控制PWM输出
 ********************************************************/

#include <PID.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 3

//定义变量
double Setpoint, Input, Output;

//初始化参数
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

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
    myPID.Compute();
    analogWrite(PIN_OUTPUT, Output);
}
