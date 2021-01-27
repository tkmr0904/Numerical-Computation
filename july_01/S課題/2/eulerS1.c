
#include <stdio.h>
#include <math.h>

double omega = 0.01;

double I(double x, double y)
{
    return 1.0*omega*cos(omega*x)-y;
}

double Q(double x, double y)
{
    return 1.0*sin(omega*x) - y;
}


double euler(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;

    for(int i = 0; i<n; i++)
    {
        y = y + h * df(x, y);
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;
    }
    return y;
}

double modeuler(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;

    for(int i = 0; i<n; i++)
    {
        y = y + h * df(x + 0.5*h, y + 0.5*h*df(x, y));
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;
    }
    return y;
}


double RK(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;
    
    double k1, k2, k3, k4;

    for(int i = 0; i<n; i++)
    {
        k1 = df(x, y);
        k2 = df(x + 0.5*h, y + 0.5*h*k1);
        k3 = df(x + 0.5*h, y + 0.5*h*k2);
        k4 = df(x +     h, y +     h*k3);

        y = y + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;

    }
    return y;
}

#define number 10000  //何分割するか
#define num_omega 25001  //角周波数を何種類用いるか

int main()
{
    /*ここに各々の角運動量についてにの誤差の最大値を格納する*/
    double error_max[2][3][num_omega];

    /************omeを宣言して全部0にする*******************/
    double ome[num_omega];

    
    for(int omeganum = 0; omeganum<num_omega; omeganum++)
    {
        ome[omeganum] = omeganum;
    }
    /****************************************************/

    for(int omeganum = 0; omeganum<num_omega; omeganum++)//全ての角周波数について最大値を求め,error_maxに格納する
    {
        double(*func[3])(double, double, double, int, double[], double[], double(*)(double, double)) = {euler, modeuler, RK};

        omega = ome[omeganum];
        

        double        x[number + 1];
        double        y[2][3][number + 1];
        double solution[2][number + 1];

        double C = 1.0e-6;
        double R = 1.0e+3;
        double E = 1.0;
        double ms = 2.0*M_PI;


        /*******************Iの場合**********************/
        for(int j = 0; j<3; j++)
        {
            func[j](0, 0, ms, number, x, y[0][j], I);
        }

        for(int i = 0; i<number; i++)
        {
            solution[0][i] = omega/(1+omega*omega)*cos(omega*x[i]) + omega*omega/(1+omega*omega)*sin(omega*x[i]) - omega/(1+omega*omega)*exp(-x[i]);
        }
        /*************************************************/

    
        /*******************Qの場合***********************/
        for(int j = 0; j<3; j++)
        {
            func[j](0, 0, ms, number, x, y[1][j], Q);
        }

        for(int i = 0; i<number; i++)
        {
            solution[1][i] = 1/(1+omega*omega)*sin(omega*x[i]) - omega/(1+omega*omega)*cos(omega*x[i]) + omega/(1+omega*omega)*exp(-x[i]);
        }
        /*************************************************/

        

        for(int k = 0; k<2; k++)
        {
            for(int j = 0; j<3; j++)
            {
                error_max[k][j][omeganum] = 0;
                for(int i = 0; i<number; i++)
                {
                    if(error_max[k][j][omeganum]<fabs(y[k][j][i]-solution[k][i]))
                    {
                        error_max[k][j][omeganum] = fabs(y[k][j][i]-solution[k][i]);
                    }
                }
            }
        }
    }


        

    
    {
        /************作成するファイルに関するものたち*********/
        char *method[3] = {"euler", "modeuler", "RK"};
        char *I_Q[2] = {"I", "Q"};
        char filename[100];
        FILE* fp;
        /************************************************/

        for(int k = 0; k<2; k++)//I, Q
        {
            for(int j = 0; j<3; j++)//euler modeuler RK
            {
                /*ファイル名を作る*/
                snprintf(filename, 100, "double_%s%s%s", "errormax_", method[j], I_Q[k]);

                /***************最大値をファイルに書き出す****************************************/
                fp = fopen(filename, "w");
                for(int omeganum = 0; omeganum<num_omega; omeganum++)
                {
                    fprintf(fp, "%.15e %.15e\n", ome[omeganum], error_max[k][j][omeganum]);
                }
                fclose(fp);
                /****************************************************************************/
            }
        }
    }



}