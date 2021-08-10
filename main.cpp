#include <iostream>
#include <cmath>



using namespace std;


#define pi 3.14159265359


class bicycle
{
private:
public:
    
    float beta,theta_dot,theta,theta_dot_prev,lr,l,sample_time,x_cg_dot,x_cg_dot_prev,y_cg_dot,y_cg_dot_prev, input[3],output[3];
    float count;
    bicycle();
    ~bicycle();
    void forward_kinematics(float input[]);
    void print_output();
};

bicycle::bicycle()
{
 beta=0;     //slipping angel
 theta_dot=0; 
 theta=0;    
 theta_dot_prev=0;
 lr=0.5;
 l=1;
 sample_time=0.01;
 //input[]={0,0,0};
 //output[]={0,0,0};
count=0;
}

bicycle::~bicycle()
{
}
void bicycle::forward_kinematics(float input[])
{
//beta=atan(   (  lr*(tan(input[2])/l)  )  );
//theta_dot=input[0]*cos(beta)*tan(input[2])/l;
//theta=(theta_dot+theta_dot_prev)*sample_time;
//theta_dot_prev=theta_dot;
//x_cg_dot=input[0]*cos(theta+beta);
//output[0]=(x_cg_dot+x_cg_dot_prev)*sample_time;
// x_cg_dot_prev=x_cg_dot;
//y_cg_dot=input[0]*sin(theta+beta);
//output[1]=(y_cg_dot+y_cg_dot_prev)*sample_time;
//y_cg_dot_prev=y_cg_dot;
//output[2]=theta;

beta=atan(   (  lr*(tan(input[2])/l)  )  );
x_cg_dot=input[0]*cos(theta+beta);
y_cg_dot=input[0]*sin(theta+beta);
theta_dot=input[0]*cos(beta)*tan(input[2])/l;      
output[0]+=x_cg_dot*sample_time;      
output[1]+=y_cg_dot*sample_time;      
theta+=theta_dot*sample_time;
output[2]=theta;
output[2]=remainder(theta,2*pi);

}

void bicycle::print_output()
{   
    cout<<"------"<<count++<<"------"<<endl;
    cout<<"x= "<<output[0]<<endl;
    cout<<"y= "<<output[1]<<endl;
    cout<<"theta= "<<output[2]<<endl;

   

}



float w=10;    //let angluer velocity = 10r/s
float r=0.25;  //let wheel radius = 0.25 m

int main(){


bicycle bike1;

bike1.input[0]=r*w;      //v = rw , and asume the bicycle velocity is the rare wheel velocity
bike1.input[1]={0};
bike1.input[2]={(pi/6 )};

for (int i = 0; i < 200; i++) //test 50 iteration
{
bike1.forward_kinematics(bike1.input);
bike1.print_output();
}
    return 0;
}