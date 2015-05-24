#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ESP 0.0001

    float inverse3[3][3], inverse2[2][2];
    int inv_func(int n);
    int twobytwo();
    int threebythree();
    float jacobian2[2][2];
    float jacobian3[3][3];
//////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    printf("This program works for non linear system \nof 2 or 3 equations with pre-defined functions!\n\n");
    printf("Enter how many equations you want to solve: \n");
    scanf(" %d", &n);
    if(n==2)
        twobytwo();
    else if(n==3)
        threebythree();
    else{
        printf("Error! Can only handle system of 2 or 3 equations!");
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////
    int twobytwo()
{
    //// x= 3, y=2
    ////
float f1(float x,float y)
{
    return (3*x*x*y)+(6*y*y*x)+3;
}
float f1x(float x,float y)
{
    return 6*x*y+6*y*y;
}
float f1y(float x,float y)
{
    return 3*x*x+12*x*y;
}
float f2(float x,float y)
{
    return 2*y*y*x - 4*x*x*y -2;
}
float f2x(float x,float y)
{
    return 2*y*y - 8*x*y;
}
float f2y(float x,float y)
{
    return 4*y*x - 4*x*x;
}

    float x,y;
	float error1 = 0,error2= 0;
    int in=1;
	float iter[2][1],init[2][1],F[2][1],res[2][1], matrix[2][2];
    int i=0;
	printf("Enter Initial guesses for X0 and X1 :\n");
	scanf("%f %f",&x,&y);
	init[0][0]=x;
	init[1][0]=y;


    do
    {

        F[0][0] = f1(init[0][0],init[1][0]);
        F[1][0] = f2(init[0][0],init[1][0]);

        jacobian2[0][0] = f1x(init[0][0],init[1][0]);
        jacobian2[0][1] = f1y(init[0][0],init[1][0]);
        jacobian2[1][0] = f2x(init[0][0],init[1][0]);
        jacobian2[1][1] = f2y(init[0][0],init[1][0]);
        inv_func(2);

////////////////////////////////////////////////////////////////////////
////////////////////////////matrix mult/////////////////////////////////
////////////////////////////////////////////////////////////////////////

  int m, n, p, q, c, d, k1;
  float sum = 0;
  //float first[2][2] , second[2][1]=F, multiply[2][1]=res;

    m=n=2;
  p=2,q=1;

  if (n != p)
    printf("jacobian matrix and F matrix can't be multiplied with each other.\n");
  else
  {
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k1 = 0; k1 < p; k1++) {
          sum = sum + inverse2[c][k1]*F[k1][d];
        }

        res[c][d] = sum;
        sum = 0;
      }
    }
  }
        error1 = iter[0][0];
        error2 = iter[1][0];



        printf("\nIteration No. %d\n",in);
        printf("---------------------\n\n");
        int x1;
        for(x1=0;x1<2;x1++)
        {
           iter[x1][0] = init[x1][0] - res[x1][0];
            printf("X%d root %.4f\n\n",x1,iter[x1][0]);
        }
            printf("===========================================\n");


        int y1;
        for(y1=0;y1<2;y1++)
        {
            init[y1][0] = iter[y1][0];
        }
        in = in+1;
        printf("\n");
	}
    while((fabs(error1-init[0][0])>ESP )&&(fabs(error2 - init[1][0])>ESP));
        printf("\n");
        return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
int threebythree()
{
    /////////// x= 2 y= 3 z= 4
    /////////// x= 3.1921 y= 0.0877 z= -0.9045
    float f1(float x,float y,float z)
    {
        return (x*x)-(y*y)+(z*z)-11;
    }
    float f1x(float x,float y,float z)
    {
        return 2*x;
    }
    float f1y(float x,float y,float z)
    {
        return -2*y;
    }
    float f1z(float x,float y,float z)
    {
        return 2*z;
    }
    //////////////////////////////////////////////
    float f2(float x,float y,float z)
    {
        return (x*y)+(y*y)-(3*z)-3;
    }
    float f2x(float x,float y,float z)
    {
        return y;
    }
    float f2y(float x,float y,float z)
    {
        return x+(2*y);
    }
    float f2z(float x,float y,float z)
    {
        return -3*y;
    }
    /////////////////////////////////////////////
    float f3(float x,float y,float z)
    {
        return x-(x*z)+(y*z)-6;
    }
    float f3x(float x,float y,float z)
    {
        return 1-z;
    }
    float f3y(float x,float y,float z)
    {
        return z;
    }
    float f3z(float x,float y,float z)
    {
        return -1*x+y;
    }
    float x,y,z;
	float error1 = 0,error2= 0,error3=0;;
    int in=0;
	float iter[3][1],init[3][1],F[3][1],res[3][1];
	printf("Enter Initial guesses for X0, X1, X2 :\n");
	scanf("%f %f %f",&x,&y, &z);
	init[0][0]=x;
	init[1][0]=y;
	init[2][0]=z;


    do
    {

        F[0][0] = f1(init[0][0],init[1][0],init[2][0]);
        F[1][0] = f2(init[0][0],init[1][0],init[2][0]);
        F[2][0] = f3(init[0][0],init[1][0],init[2][0]);

        jacobian3[0][0] = f1x(init[0][0],init[1][0],init[2][0]);
        jacobian3[0][1] = f1y(init[0][0],init[1][0],init[2][0]);
        jacobian3[0][2] = f1z(init[0][0],init[1][0],init[2][0]);
        jacobian3[1][0] = f2x(init[0][0],init[1][0],init[2][0]);
        jacobian3[1][1] = f2y(init[0][0],init[1][0],init[2][0]);
        jacobian3[1][2] = f2z(init[0][0],init[1][0],init[2][0]);
        jacobian3[2][0] = f3x(init[0][0],init[1][0],init[2][0]);
        jacobian3[2][1] = f3y(init[0][0],init[1][0],init[2][0]);
        jacobian3[2][2] = f3z(init[0][0],init[1][0],init[2][0]);
        inv_func(3);



////////////////////////////////////////////////////////////////////////
////////////////////////////matrix mult/////////////////////////////////
////////////////////////////////////////////////////////////////////////

  int m, n, p, q, c, d, k1;float sum = 0;
    m=n=3;
  p=3,q=1;

  if (n != p)
    printf("jacobian matrix and F matrix can't be multiplied with each other.\n");
  else
  {
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k1 = 0; k1 < p; k1++) {
          sum = sum + inverse3[c][k1]*F[k1][d];
        }

        res[c][d] = sum;
        sum = 0;
      }
    }
  }

        error1 = iter[0][0];
        error2 = iter[1][0];
        error3 = iter[2][0];


        printf("\nIteration No. %d\n",in+1);
        printf("---------------------\n\n");
        int x1;
        for(x1=0;x1<3;x1++)
        {
            iter[x1][0] = init[x1][0] - res[x1][0];
            printf("X%d root %.4f\n\n",x1,iter[x1][0]);
        }
            printf("===============================================\n");


        int y1;
        for(y1=0;y1<3;y1++)
        {
            init[y1][0] = iter[y1][0];
        }
        in = in+1;
        printf("\n");
	}
    while((fabs(error1-init[0][0])>=ESP )&&(fabs(error2 - init[1][0])>=ESP)&&(fabs(error3-init[2][0])>=ESP));
        printf("\n");
        return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////


int inv_func(int n)
{
    float matrix[10][10], ratio,a;
    int i, j, k;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if (n==2)
                matrix[i][j]=jacobian2[i][j];
            else if(n==3)
                matrix[i][j]=jacobian3[i][j];
        }
    }
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
////////////////copying matrix in inverse of jacobian///////////////
    for(i = 0; i < n; i++){

        for(j = 0; j < n; j++){
            if(n==2)
                inverse2[i][j]=matrix[i][j+n];
            else if(n==3)
                inverse3[i][j]=matrix[i][j+n];
        }

    }
    return 0;
}

/*
/////////// x= -0.922807 y= 1.77438 z= 0.148427
/////////// x= 1.66522 y= 1.10773 z= -1.77294

float f1(float x,float y,float z)

{

    return (x*x)+(z)-1;

}

float f1x(float x,float y,float z)

{

    return 2*x;

}

float f1y(float x,float y,float z)

{

    return 0;

}



float f1z(float x,float y,float z)

{

    return 1;

}

/////////////////////////

float f2(float x,float y,float z)

{

    return (x*x)+(y*y)-4;

}

float f2x(float x,float y,float z)

{

    return 2*x;

}

float f2y(float x,float y,float z)

{

    return 2*y;

}



float f2z(float x,float y,float z)

{

    return 0;

}

/////////////////////////

float f3(float x,float y,float z)

{

    return x+y+z-1;

}

float f3x(float x,float y,float z)

{

    return 1;

}

float f3y(float x,float y,float z)

{

    return 1;

}



float f3z(float x,float y,float z)

{

    return 1;

}
*/
