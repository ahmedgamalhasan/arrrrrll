#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
    
Matrix<float , 2 , 1 >X_predected;
Matrix<float , 2 , 1 >X_corrected;

class kalman_filter
{
private:
    /* data */
public:
    void compute();
    void print();
    kalman_filter();
    ~kalman_filter();

    Matrix<float,2,2>P_predected;
    Matrix<float,2,1>K;

    float U_k;
    float R_k;
    float Y_k;
    
    Matrix<float,2,2>P_k_corrected;
    Matrix<float,2,2>Q_k;
    Matrix<float,2,1>X_k_predected;
    Matrix<float,2,2>F_k;
    Matrix<float,2,1>X_k;
    Matrix<float,2,1>G_k;
    Matrix<float,1,2>H_k;

    

};

kalman_filter::kalman_filter()
{   
    U_k=-2;
    R_k=0.05;
    Y_k=2.2;

    H_k<<1,0;
    F_k<<1,0.5,0,1;
    X_k<<0,5;
    G_k<<0,0.5;
    P_k_corrected<<0.01,0,0,1;
    Q_k<<0.1,0,0,0.1;
}

kalman_filter::~kalman_filter()
{
}

void  kalman_filter::compute()
{
    /*-----------predection-------------*/
    X_predected=(F_k*X_k)+(G_k*(U_k));

    P_predected=F_k*P_k_corrected*F_k.transpose()+Q_k;
    /*----------------------------------*/

    /*----------correction--------------*/
    K=P_predected*H_k.transpose()*pow((H_k*P_predected*H_k.transpose()+R_k),-1);

    X_corrected=X_predected+K*(Y_k-(H_k*X_predected));
    /*----------------------------------*/
}
void kalman_filter::print()
{
    cout<<"-----------------"<<endl<<X_corrected<<endl<<"-----------------"<<endl;
}


int main()
{
    kalman_filter k_filter1;    //the defualt paramters passed to constructor as in example.
                                //,and we can change(update) it any time . 
    k_filter1.compute();
    k_filter1.print();


    return 0;
}   
