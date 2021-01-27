#include <stdio.h>
#include <math.h>
#include <stdlib.h> /*system*/ /*strtol*/
#include <unistd.h> /*sleep usleep*/
#include <string.h> /*strlen*/
#include <errno.h>  /*エラー判定*/

        /*データを読み込む配列の長さ*/
#define ndatamax 10
        /*色々な配列の長さ(データを除く)*/
#define nmax 1000

   /*1ならclearモードがオン*/
int isclear;

char str_input[nmax];


/*掃き出し法*/   /*今回は掃き出し法を用いて最小二乗法の係数を求める*/  /*代入されたpmatの参照先がn×n+1のdouble型2次元配列でなければならない*/
int sweeping_out(void* pmat, int n)
{
    /*行列を表す配列のポインタとして使う*/
    double (*matrix)[n][n+1] = pmat;

    for(int col = 0; col<n; col++) //列ごとに対角成分以外0にする　これを1~n列に渡って行う
    {
        /*対角成分が0ならエラー*/
        if((*matrix)[col][col] == 0)
        {
            return 1;
        }

        /*対角成分が0でなければ、col列の対角成分が1になるようにcol行を定数倍する*/
        for(int j = col+1; j<n+1; j++)
        {
            (*matrix)[col][j] /= (*matrix)[col][col];
        }
        (*matrix)[col][col] = 1; // /= (*matrix)[col][col]  値が失われるのでforの後で計算する

        /*col行の定数倍を他の行に加えてcol列の対角成分以外0にする*/
        for(int i = 0; i<n; i++)//
        {
            if(i != col) //col行以外なら計算する
            {
                /*i行にcol行の定数倍を加える 第col行以外のcol列の成分が0になるように*/
                /*第col行のcol列より左の部分は全部0だから計算する必要がない*/
                for(int j = col+1; j<n+1; j++)
                {
                    (*matrix)[i][j] -= (*matrix)[col][j] * (*matrix)[i][col];
                }
                (*matrix)[i][col] = 0; // -= (*matrix)[col][col] * (*matrix)[i][col]  値が失われるのでforの後で計算する
            }
            else
            {
                /*col行の場合計算しない*/
            }
            
        }
    }

    return 0;
}

long conv_s_i(char str[], int* ptr)
{

    int len = strlen(str);

    char* end;
    *ptr = (int)strtol(str, &end, 10);

    if(errno == ERANGE)
    {
        /*表現可能な値の範囲外の場合*/
        return 1;
    }
    else if(end != str+len)
    {
        /*strが整数でなかった場合*/
        return 1;
    }
    else
    {
        /*正しく変換できた場合*/
        return 0;
    }
    
}



/*カウントダウンする*/
int countdown(double sec)
{
    /*終わりの線を表示*/ /*白で埋める*/ /*最後に青色の出力に変更する*/
    printf("\x1b[37m██████████\x1b[34m");

    /*キャリッジリターン*/
    printf("\r");

    /*文字を画面上に反映させる*/
    fflush(stdout);


    /*今は全時間の何割なのかを整数とした値が格納される*/
    int i = 0;

    /*iの増分*/
    int di;

    for(double d = 0; d<sec; d+=0.1)
    {
        /*iの増分を計算*/
        di = (int)(d/sec*10) - i;
        i += di;

        /*iが増加したら増分だけ█で埋まる*/
        for(int k = 0; k<di; k++)
        {
            printf("█");
        }
        /*文字を表示させる*/
        fflush(stdout);

        /*0.1秒待機*/
        usleep(100000);
    }

    /*10回目を表示して改行する*/ /*最後に白色の出力に戻す*/
    printf("█\x1b[37m\n");

    return 0;
}

/*clearモードがonなら文字を消す*/
int clear()
{
    if(isclear == 1) 
    {
        system("clear");
    }


    return 0;
}

/*最小二乗法*/   /*xdataとydataを用いて近似関数の係数を求め、cに格納する   nd:データの個数   nc:係数の個数(次数+1)*/
int least_square(double x[], double y[], double c[], int nd, int nc)
{
    /*nc行nc+1列の行列   第nc+1列を除けば実対称行列*/  /*ただの対称行列ではなく、行番号と列番号の和が等しければ値は等しい*/
    double matrix[nc][nc+1];

    /*対称行列の部分には0乗和から(次数*2)乗和まで合計(2*(nc-1)+1)種類値が存在する*/
    double sum[2*(nc-1)+1];

    /*第nc+1列の値 下から順番*/
    double sum_xy[nc];

    /*sumの値*/
    for(int i = 0; i<2*(nc-1)+1; i++)
    {
        sum[i] = 0;
        for(int j = 0; j<nd; j++)
        {
            sum[i] += pow(x[j], i);
        }
    }

    /*sum_xyの値*/
    for(int i = 0; i<nc; i++)
    {
        sum_xy[i] = 0;
        for(int j = 0; j<nd; j++)
        {
            sum_xy[i] += y[j] * pow(x[j], i);
        }
    }

    /*行列の1列目からnc列目まで値をセット*/
    for(int i = 0; i<nc; i++)
    {
        for(int j = 0; j<nc; j++)
        {
            matrix[i][j] = sum[2*(nc-1) - (i+j)];
        }
    }
    
    /*最後に第nc+1列の値をセット*/
    for(int i = 0; i<nc; i++)
    {
        matrix[i][nc] = sum_xy[nc-1-i];
    }
    
    /*もし掃き出し法が成功したら*/
    if(sweeping_out(&matrix, nc) == 0)
    {
        for(int i = 0; i<nc; i++)
        {
            /*掃き出し法で第nc+1列に解が現れるのでそこから解を取り出す*/    /*下から取り出す*/ 
            c[i] = matrix[nc-1-i][nc];
        }
        /*成功を示す0*/
        return 0;
    }
    /*掃き出し法に失敗したら*/
    else
    {
        /*失敗を示す1*/
        return 1;
    }
    
}

/*末尾が.pngなら1を、そうでなければ0を返す*/
int ispng(char filename[])
{
    int len = strlen(filename);

    /*ファイル名が4文字未満なら末尾が.pngであることはあり得ない*/
    if(len < 4)
    {
        return 0;
    }
    else 
    {
        /*末尾が.pngの場合にptrはドットの位置にある*/
        char* ptr = filename + len-4;

        /*末尾が.pngなら*/
        if((ptr[0]=='.') && (ptr[1]=='p') && (ptr[2]=='n') && (ptr[3]=='g'))
        {
            return 1;
        }
        /*そうでなければ*/
        else
        {
            return 0;
        }
    }
}

int plot()
{
    /*ファイルポインタ*/
    FILE* fp;

    /*xの値とyの値*/
    double xdata[ndatamax], ydata[ndatamax];

    /*データ点の個数*/
    int n;

    /*係数の個数(次数+1)*/
    int nc;

    /*文字列を格納(色々なことに使う)*/
    char str[nmax];
    
    /*ファイル名を格納*/
    char filename[nmax];

    clear();
    printf("これからデータを用いて近似関数を求めます\n");
    printf("読み込みたいデータのファイル名を入力してください\n");
    scanf("%s", filename);

    /****ファイルからデータ点を読み込む  ついでにnにデータの個数を保存する***********/
    fp = fopen(filename, "r");

    /*オープンできかったら終了*/
    if(fp == NULL)
    {
        clear();
        printf("ファイル\"%s\"を開くことができません\n", filename);
        countdown(2);
        return 1;
    }

    /*オープンに成功しないとここに到達できない*/

    /*オープンに成功した場合*/
    clear();
    printf("%sのオープンに成功しました\n", filename);
    countdown(2);



    /*nに0をセットし、これから加算していく*/
    n = 0;

    while(1)
    {
        /*データを1行だけ読み込んでstrに格納する*/
        /*読んでいないデータが存在すれば*/
        if(fgets(str, nmax, fp) != NULL)
        {
            /*データの配列にまだ空きがあれば*/
            if(n < ndatamax)
            {
                /*データを数値に変換してx, yの配列に格納するついでに数値に変換できているかを判定する*/
                if(sscanf(str, "%lf %lf", &(xdata[n]), &(ydata[n])) == 2)
                {
                    n++;
                }
                else
                {
                    printf("データを適切に読み込めませんでした\n");
                    countdown(2);
                    return 1;
                }
                
            }
            /*x, yの配列に空きがなければ読み込み終了*/
            else
            {
                clear();
                printf("データを読み込める最大個数が%d個です\n最大個数に達したので、データの読み込みを打ち切ります\nすでに読み込まれている%d個のデータのみを使って近似関数を求めます\n", ndatamax, ndatamax);
                countdown(10);
                break;
            }
        }
        /*データを読み切ってしまえば読み込み終了*/
        else
        {
            break;
        }
    }
    fclose(fp);
    /*********************************************************************/

    clear();
    printf("データの読み込みが完了しました\n");
    printf("これから%sの近似関数を求めます\n", filename);
    printf("次数(0以上の整数)を入力してください\n");
    scanf("%s", str);  //この時点でncには次数が入っている


    if(conv_s_i(str, &nc) != 0)
    {
        clear();
        printf("%sが入力されました  これは次数の値として適切ではありません\n", str);
        countdown(5);
        return 1;
    }



    if(nc < 0)
    {
        clear();
        printf("次数に%dが入力されましたが、この値は負数なので適切ではありません\n", nc);
        countdown(5);
        return 1;
    }

    /*1を足して係数の個数にする*/
    nc++;

    /*最小二乗法で求める係数をここに格納*/
    double c[nc];

    /*最小二乗法で係数を求めるのに成功したら*/
    if(least_square(xdata, ydata, c, n, nc) == 0)
    {

        /*****************gnuplotでプロットするときに用いられるコマンドを作っておく****************************/
        /*plotの先頭部分*/               /*    plot "ファイル名" using 1:2 title "data",     */
        sprintf(str, "plot \"%s\" every ::::%d using 1:2 title \"data\" pt 7 ps 2, ", filename, n-1);

        /* 後ろにa0*x**0+a1*x**2+a2*x**2+...を連結*/     /* +-となったらマイナスと判定してくれるので大丈夫 */
        for(int i = 0; i<nc; i++)
        {
            sprintf(str, "%s+%f*x**%d", str, c[i], i);
        }

        /* title "fit"を追記 */
        sprintf(str, "%s title \"fit\"", str);
        /*********************************************************************************************/

        /*gnuplotの実行*/
        fp = popen("gnuplot -persist", "w");

        /*x軸の名前をxにする*/
        fprintf(fp, "set xlabel \"x\"\n");

        /*y軸の名前をyにする*/
        fprintf(fp, "set ylabel \"y\"\n");

        /*x軸ラベルのフォントサイズの設定*/
        fprintf(fp, "set xlabel font \"Arial,20\"\n");

        /*y軸ラベルのフォントサイズの設定*/
        fprintf(fp, "set ylabel font \"Arial,20\"\n");

        /*目盛りのフォントサイズの設定*/
        fprintf(fp, "set tics font \"Arial,15\"\n");

        /*凡例のフォントサイズの設定*/
        fprintf(fp, "set key font \"Arial,15\"\n");

        /*y軸の余白の設定*/
        fprintf(fp, "set lmargin 10\n");

        /*x軸の余白の設定*/
        fprintf(fp, "set bmargin 5\n");


        clear();
        printf("%sのデータを%d次式で近似しました\n", filename, nc-1);
        printf("このグラフをpngファイルに書き出しますか? それともウィンドウに表示しますか?\n");
        printf("1文字だけ入力してください\n");
        printf("書き出す場合はaを、書き出さずにウィンドウとして表示する場合はa以外を入力してください\n");

        /*ここに1文字を入力してaかどうか判定する*/
        scanf("%s", str_input);

        if(strlen(str_input) != 1)
        {
            clear();
            printf("%sが入力されました  これは1文字ではないので適切ではありません\n", str_input);
            countdown(5);
            return 1;
        }

        /*aが入力されれば*/
        if(str_input[0] == 'a')
        {
            /*pngモードに変更する*/
            fprintf(fp, "set term png\n");

            clear();
            printf("%sのデータを%d次式で近似しました\n", filename, nc-1);
            printf("pngファイルの名前を入力してください\n");
            printf("名前の末尾には拡張子(.png)を付けてください\n");
            scanf("%s", filename);

            if(ispng(filename) == 0)
            {
                clear();
                printf("ファイル名%sは末尾が(.png)ではないので末尾に.pngを追加します\n", filename);
                countdown(5);
                sprintf(filename, "%s.png", filename);
            }

            /*pngファイルに書き出す*/
            fprintf(fp, "set output \"%s\"\n", filename);
        }

        /*データと近似関数をプロットする*/
        fprintf(fp, "%s\n", str);


        pclose(fp);

        return 0;
    }
    /*もし最小二乗法で係数を求めるのに失敗したら*/
    else
    {
        printf("最小二乗法に失敗しました\n");
        countdown(2);
        return 1;
    }
}


int main()
{

    /*1文字が入力されるまで繰り返す*/
    while(1)
    {
        printf("clearモードをオンにしますか?");
        printf("  オンにすればコマンドライン上の余計な文字が消えるので、出力される文字が見やすくなります\n");
        printf("1文字だけ入力してください\n");
        printf("オンにする場合はaを、オフにする場合はa以外を入力してください\n");
        scanf("%s", str_input);

        if(strlen(str_input) != 1)
        {
            printf("%sが入力されました  これは1文字ではないので適切ではありません\n", str_input);
            countdown(5);
        }
        else
        {
            break;
        }
    }

    if(str_input[0] == 'a')
    {
        isclear = 1;
        clear();
        printf("clearモードをオンにしました\n");
        countdown(2);
    }
    else
    {
        isclear = 0;
        printf("clearモードをオフにしました\n");
        countdown(2);
    }


    while(1)
    {
        plot();

        /*1文字が入力されるまで繰り返す*/
        while(1)
        {
            clear();
            printf("プロットをやり直しますか?\n");
            printf("1文字だけ入力してください\n");
            printf("プロットをやり直す場合はaを、終わる場合はa以外を入力してください\n");
            scanf("%s", str_input);

            if(strlen(str_input) != 1)
            {
                clear();
                printf("%sが入力されました  これは1文字ではないので適切ではありません\n", str_input);
                countdown(5);
            }
            else
            {
                break;
            }
        }
        /*a以外が入力されれば終了*/
        if(str_input[0] != 'a')
        {
            break;
        }
    }



    return 0;
}