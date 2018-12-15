#include <Servo.h>  //声明Arduino自带的舵机控制库,可以方便我们对舵机进行控制,下面涉及到的出现"myservo"都是这个库里的函数.通常我们只需要知道怎么使用函数即可,不必知道函数的操作细节.
Servo myservo;//初始化舵机控制,把舵机叫做了"myservo",最多可以连接8个舵机

int trig = 2;//Arduino连接超声波Trig的引脚 此处假设连接的引脚为D2
int echo = 3; //Arduino连接超声波Echo的引脚 此处假设连接的引脚为D3
//在Arduino中,"数字"接口引脚前只以数字代替即可 而如果是模拟接口,则需要以"A"加数字作为描述,如A1
double distance;//定义距离变量

//以下为初始化代码,仅执行一次
void setup(){
  Serial.begin (9600);//为调试过程方便,增添串口,此处初始化串口,设置其波特率为9600bps 即9600bits per second
  pinMode(trig,OUTPUT);//定义trig引脚为输出端口,用于Arduino对超声波模块输出指令,进行控制
  pinMode(echo,INPUT);//定义echo引脚为输入端口,接收Arduino返回的信息,即距离
  
  myservo.attach(9);//定义D9连接到舵机的控制端
  
  Serial.println("Setup Finished");//此处仅为为调试方便所添加,确保单片机已执行完此段初始化代码
}

//以下为主程序代码,循环执行
void loop(){
   Chaoshengbo(); //执行超声波控制代码
   if (distance < 10) //当距离小于10cm时
     Duoji(); //执行舵机控制代码
}

//以下为超声波控制代码
void Chaoshengbo(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
//将trig端拉低,因为引脚暴露在环境中,为了排除外界环境干扰,将其拉低减小误差.延时2ms是为了避免与下面的控制冲突.
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
//讲trig端拉高10ms后拉低,即发射10ms的超声波
  
  distance = (pulseIn(echo,HIGH) )/ 58.0; //距离=(高电平时间*声速(340m/s))/2
//公式已附,可不必深究,直接用就行了

  Serial.print(distance);
  Serial.println("cm");
//此处为方便调试添加,把距离信息传输回电脑已验证功能是否正常
}

//以下为舵机控制代码
void Duoji(){
  myservo.write(90); //控制舵机转到90度
  delay(500);//延迟半秒,确保电机转到位,可以根据实际情况调整
}
