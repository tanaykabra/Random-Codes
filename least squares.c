#include<stdio.h>
#include<stdlib.h>

float coeff[4][4];
float inverse[4][4];
int inv_func(int n);

main()
{
    float x[8]= {1,2,3,4,5,6,7,8};
    float fx[8]= {6,5,7,10,7,3,2,5};
    float wx[5] = {1,1,1,1,1};
    float b_mat[4][1];

    float a_mat [4][1];
    int n = 3;


    int i;
    float w=0,x1=0,x2=0,x3=0,x4=0,x5=0,x6=0,f=0,xf=0,x2f=0,x3f=0;

    for(i=0;i<(sizeof(x)/sizeof(float));i++){
        w += wx[i];
        x1 += wx[i]*x[i];
        x2 += wx[i]*x[i]*x[i];
        x3 += wx[i]*x[i]*x[i]*x[i];
        x4 += wx[i]*x[i]*x[i]*x[i]*x[i];
        x5 += wx[i]*x[i]*x[i]*x[i]*x[i]*x[i];
        x6 += wx[i]*x[i]*x[i]*x[i]*x[i]*x[i]*x[i];
        f += wx[i]*fx[i];
        xf += wx[i]*x[i]*fx[i];
        x2f += wx[i]*x[i]*x[i]*fx[i];
        x3f += wx[i]*x[i]*x[i]*x[i]*fx[i];
    }

    coeff[0][0] = w;
    coeff[0][1] = coeff[1][0] = x1;
    coeff[0][2] = coeff[1][1] = coeff[2][0] = x2;
    coeff[0][3] = coeff[1][2] = coeff[2][1] = coeff[3][0] = x3;
    coeff[1][3] = coeff[2][2] = coeff[3][1] = x4;
    coeff[2][3] = coeff[3][2] = x5;
    coeff[3][3] =  x6;
    b_mat[0][0] = f;
    b_mat[1][0] = xf;
    b_mat[2][0] = x2f;
    b_mat[3][0] = x3f;

   inv_func(4);


    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int m, n1, p, q, c, d, k1;
    float sum = 0;

    m=n1=4;
    p=4,q=1;

  if (n1 != p)
    printf("Matrix multiplication not possible.\n");
  else
  {
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k1 = 0; k1 < p; k1++) {
          sum = sum + inverse[c][k1]*b_mat[k1][d];
        }

        a_mat[c][d] = sum;
        sum = 0;
      }
    }
  }

    printf("The PnX approximation of f(x) is:\n\n");
    printf("Pnx = %f + %f*(X) + %f*(X^2) + %f*(X^3)\n\n",a_mat[0][0],a_mat[1][0],a_mat[2][0],a_mat[3][0]);


}


int inv_func(int n)
{

    float matrix[10][10], ratio,a;

    int i, j, k;


    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){

            matrix[i][j]=coeff[i][j];

        }

    }

    ///////////////////
    ///////////////////


    for(i = 0; i < n; i++){

        for(j = n; j < 2*n; j++){

            if(i==(j-n))

                matrix[i][j] = 1.0;

            else

                matrix[i][j] = 0.0;

        }

    }

    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){

            if(i!=j){

                ratio = matrix[j][i]/matrix[i][i];

                for(k = 0; k < 2*n; k++){

                    matrix[j][k] -= ratio * matrix[i][k];

                }

            }

        }

    }

    for(i = 0; i < n; i++){

        a = matrix[i][i];

        for(j = 0; j < 2*n; j++){

            matrix[i][j] /= a;

        }

    }


    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){

            inverse[i][j]=matrix[i][j+n];

        }

    }

    return 0;

}
