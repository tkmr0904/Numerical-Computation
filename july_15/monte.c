#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define num_samples 256

int irand(int ri, int a, int c, int m)
{
    return (ri*a + c)%m;
}

int main()
{
    FILE* fp;
    int i;


    {
        int r0, r;
        int a;
        int c;
        int m;
        int data[2][num_samples+1];



        /******************************************************/
        r0 = 10;
        a = 57;
        c = 1;
        m = 256;

        r = r0;
        for(i = 0; i<num_samples+1; i++)
        {
            data[0][i] = r;
            r = irand(r, a, c, m);
            data[1][i] = r;
        }

        fp = fopen("rand1", "w");
        for(i = 0; i<num_samples + 1; i++)
        {
            fprintf(fp, "%d %d\n", data[0][i], data[1][i]);
        }
        fclose(fp);
        /******************************************************/



        /******************************************************/
        r0 = 1;
        a = 12869;
        c = 6925;
        m = 32768;

        r = r0;
        for(i = 0; i<num_samples+1; i++)
        {
            data[0][i] = r;
            r = irand(r, a, c, m);
            data[1][i] = r;
        }

        fp = fopen("rand2", "w");
        for(i = 0; i<num_samples+1; i++)
        {
            fprintf(fp, "%d %d\n", data[0][i], data[1][i]);
        }
        fclose(fp);
        /******************************************************/
    }



    {
        double ddata[2][num_samples+1];
        double dr;

        int seed = 1533627;
        srand48(seed);

        dr = drand48();

        for(i = 0; i<num_samples+1; i++)
        {
            ddata[0][i] = dr;
            dr = drand48();
            ddata[1][i] = dr;
        }

        fp = fopen("rand3", "w");
        for(i = 0; i<num_samples+1; i++)
        {
            fprintf(fp, "%f %f\n", ddata[0][i], ddata[1][i]);
        }
        fclose(fp);
    }


    #undef num_samples
    #define num_samples 4096

    {
        double samples[3][num_samples];


        /*********0から1の乱数を求める******************/
            {
                int r0, r;
                int a;
                int c;
                int m;
                int data[num_samples];

                /******************************************************/
                r0 = 10;
                a = 57;
                c = 1;
                m = 256;

                r = r0;

                for(i = 0; i<num_samples; i++)
                {
                    r = irand(r, a, c, m);
                    data[i] = r;
                }

                for(i = 0; i<num_samples; i++)
                {
                        samples[0][i] = data[i]/(double)m;
                }
                /*****************************************/





                /******************************************************/
                r0 = 1;
                a = 12869;
                c = 6925;
                m = 32768;

                r = r0;

                for(i = 0; i<num_samples; i++)
                {
                    r = irand(r, a, c, m);
                    data[i] = r;
                }

                for(i = 0; i<num_samples; i++)
                {
                        samples[1][i] = data[i]/(double)m;
                }
                /*****************************************/
            }

            {
                double dr;
                int seed = 1533627;
                srand48(seed);


                for(i = 0; i<num_samples; i++)
                {
                    dr = drand48();
                    samples[2][i] = dr;
                }
            }
        /*********************************************/

        char filename[100];

        /***********平均値と誤差を求める************/
            /**********n乗の積分**************/
                {
                    double sum;
                    double average[3][num_samples];

                    for(int j = 0; j<3; j++)
                    {
                        sum = 0;
                        for(i = 0; i<num_samples; i++)
                        {
                            sum += samples[j][i];
                            average[j][i] = sum/(i+1);
                        }

                        snprintf(filename, 100, "average1_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, average[j][i]);
                        }
                        fclose(fp);

                        snprintf(filename, 100, "error1_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, fabs(average[j][i]-1/2.0));
                        }
                        fclose(fp);
                    }

                    for(int j = 0; j<3; j++)
                    {
                        sum = 0;
                        for(i = 0; i<num_samples; i++)
                        {
                            sum += samples[j][i]*samples[j][i]*samples[j][i];
                            average[j][i] = sum/(i+1);
                        }

                        snprintf(filename, 100, "average3_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, average[j][i]);
                        }
                        fclose(fp);

                        snprintf(filename, 100, "error3_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, fabs(average[j][i]-1/4.0));
                        }
                        fclose(fp);
                    }

                    for(int j = 0; j<3; j++)
                    {
                        sum = 0;
                        for(i = 0; i<num_samples; i++)
                        {
                            sum += samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i];
                            average[j][i] = sum/(i+1);
                        }

                        snprintf(filename, 100, "average5_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, average[j][i]);
                        }
                        fclose(fp);

                        snprintf(filename, 100, "error5_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, fabs(average[j][i]-1/6.0));
                        }
                        fclose(fp);
                    }

                    for(int j = 0; j<3; j++)
                    {
                        sum = 0;
                        for(i = 0; i<num_samples; i++)
                        {
                            sum += samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i]*samples[j][i];
                            average[j][i] = sum/(i+1);
                        }

                        snprintf(filename, 100, "average7_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, average[j][i]);
                        }
                        fclose(fp);

                        snprintf(filename, 100, "error7_%d", j+1);
                        fp = fopen(filename, "w");
                        for(i = 0; i<num_samples; i++)
                        {
                            fprintf(fp, "%d %.15f\n", i+1, fabs(average[j][i]-1/8.0));
                        }
                        fclose(fp);
                    }
                }
            /********************************/
        /****************************************/
    }

    #undef num_samples
    #define num_samples 65536

    /*****3次元球の体積(drand48を用いる)********/
        {
            double average[4][num_samples];
            {
                int seed = 1533627;
                srand48(seed);

                double x1, x2, x3;
                int number = 0;
                for(i = 0; i<num_samples; i++)
                {
                    x1 = drand48();
                    x2 = drand48();
                    x3 = drand48();
                    if(x1*x1 + x2*x2 + x3*x3 < 1)
                    {
                        number++;
                    }

                    average[0][i] = number/(double)(i+1);
                }
            }

            {
                int seed = 1533627;
                srand48(seed);

                double x1, x2, x3, x4;
                int number = 0;
                for(i = 0; i<num_samples; i++)
                {
                    x1 = drand48();
                    x2 = drand48();
                    x3 = drand48();
                    x4 = drand48();
                    if(x1*x1 + x2*x2 + x3*x3 + x4*x4 < 1)
                    {
                        number++;
                    }
                    
                    average[1][i] = number/(double)(i+1);
                }

            }

            {
                
                int seed = 1533627;
                srand48(seed);

                double x1, x2, x3, x4, x5;
                int number = 0;
                for(i = 0; i<num_samples; i++)
                {
                    x1 = drand48();
                    x2 = drand48();
                    x3 = drand48();
                    x4 = drand48();
                    x5 = drand48();
                    if(x1*x1 + x2*x2 + x3*x3 + x4*x4 + x5*x5 < 1)
                    {
                        number++;
                    }

                    average[2][i] = number/(double)(i+1);
                }
            }

            {
                int seed = 1533627;
                srand48(seed);

                double x1, x2, x3, x4, x5, x6;
                int number = 0;
                for(i = 0; i<num_samples; i++)
                {
                    x1 = drand48();
                    x2 = drand48();
                    x3 = drand48();
                    x4 = drand48();
                    x5 = drand48();
                    x6 = drand48();
                    if(x1*x1 + x2*x2 + x3*x3 + x4*x4 + x5*x5 + x6*x6 < 1)
                    {
                        number++;
                    }
                    
                    average[3][i] = number/(double)(i+1);
                }
            }

            char filename[100];
            double solution[4] = {(4/3.0)*M_PI, (1/2.0)*M_PI*M_PI, (8/15.0)*M_PI*M_PI, (1/6.0)*M_PI*M_PI*M_PI};

            for(int j = 0; j<4; j++)
            {
                snprintf(filename, 100, "%dDsphere", j+3);
                fp = fopen(filename, "w");
                for(i = 0; i<num_samples; i++)
                {
                    fprintf(fp, "%d %.15f\n", (i+1), average[j][i]*pow(2, j+3));
                }
                fclose(fp);


                snprintf(filename, 100, "error_%dDsphere", j+3);
                fp = fopen(filename, "w");
                for(i = 0; i<num_samples; i++)
                {
                    fprintf(fp, "%d %.15f\n", (i+1), fabs(average[j][i]*pow(2, j+3) - solution[j]));
                }
                fclose(fp);

                snprintf(filename, 100, "100to1000_%dDsphere", j+3);
                fp = fopen(filename, "w");
                fprintf(fp, "%.15e\n",    fabs(average[j][1000]*pow(2, j+3) - solution[j]) / fabs(average[j][100]*pow(2, j+3) - solution[j]));
                fclose(fp);
            }
        }
    /*************************************/
    
}



