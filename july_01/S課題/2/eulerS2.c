
#include <stdio.h>
#include <math.h>

float omega = 0.01f;

float I(float x, float y)
{
    return 1.0f*omega*cos(omega*x)-y;
}

float Q(float x, float y)
{
    return 1.0f*sin(omega*x) - y;
}


float euler(float x0, float y0, float xf, int n, float arrayx[], float arrayy[], float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;

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

float modeuler(float x0, float y0, float xf, int n, float arrayx[], float arrayy[], float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;

    arrayx[0] = x;
    arrayy[0] = y;

    for(int i = 0; i<n; i++)
    {
        y = y + h * df(x + 0.5f*h, y + 0.5f*h*df(x, y));
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;
    }
    return y;
}


float RK(float x0, float y0, float xf, int n, float arrayx[], float arrayy[], float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;

    arrayx[0] = x;
    arrayy[0] = y;
    
    float k1, k2, k3, k4;

    for(int i = 0; i<n; i++)
    {
        k1 = df(x, y);
        k2 = df(x + 0.5f*h, y + 0.5f*h*k1);
        k3 = df(x + 0.5f*h, y + 0.5f*h*k2);
        k4 = df(x +     h, y +     h*k3);

        y = y + (h/6.0f)*(k1 + 2*k2 + 2*k3 + k4);
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
    float error_max[2][3][num_omega];

    /************omeを宣言して全部0にする*******************/
    float ome[num_omega];

    
    for(int omeganum = 0; omeganum<num_omega; omeganum++)
    {
        ome[omeganum] = omeganum;
    }
    /****************************************************/

    for(int omeganum = 0; omeganum<num_omega; omeganum++)//全ての角周波数について最大値を求め,error_maxに格納する
    {
        float(*func[3])(float, float, float, int, float[], float[], float(*)(float, float)) = {euler, modeuler, RK};

        omega = ome[omeganum];
        

        float        x[number + 1];
        float        y[2][3][number + 1];
        float solution[2][number + 1];

        float C = 1.0e-6f;
        float R = 1.0e+3f;
        float E = 1.0f;
        float ms = 2.0f*(float)M_PI;


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
                snprintf(filename, 100, "float_%s%s%s", "errormax_", method[j], I_Q[k]);

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