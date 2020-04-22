// Tom Jungnickel 18.5.19 Semniar 3

// holla

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define AU 1
#define STARTX 0.47
#define STARTY 0
#define STARTT 0
#define ENDT 100

#define STARTVX 0
#define STARTVY 8.2
#define TUMLAUF 1
#define dt 0.001
#define MECURYM 0.055
#define GM M_PI *M_PI * 4 * AU / pow(TUMLAUF, 2)
#define ALPHA 0.00011

#define X_OLD 0
#define Y_OLD 1
#define VX_OLD 2
#define VY_OLD 3
#define X_NEW 4
#define Y_NEW 5
#define VX_NEW 6
#define VY_NEW 7

typedef struct
{
    long double x;
    long double y;
    long double vx;
    long double vy;
} pandv;

typedef struct
{
    long double ax;
    long double ay;
} avek;

typedef struct
{
    long double kx;
    long double ky;
    long double kvx;
    long double kvy;
} kvektor;
avek Merkur(long double x, long double y)
{
    avek a;
    long double r;
    a.ax = a.ay = 0;
    r = x * x + y * y;
    a.ax = -GM * x / (pow(sqrt(r), 3)) * (1.00 + (ALPHA / (r)));
    a.ay = -GM * y / (pow(sqrt(r), 3)) * (1.00 + (ALPHA / (r)));
    return a;
}

avek Gravpot(long double x, long double y)
{
    avek a;
    a.ax = a.ay = 0;
    a.ax = -GM * x / (pow(sqrt(x * x + y * y), 3));
    a.ay = -GM * y / (pow(sqrt(x * x + y * y), 3));
    return a;
}
long double distance(long double x2, long double x1, long double y2, long double y1, long double difft)
{
    long double diff;
    diff = 0;
    diff = ((sqrt(x1 * x1 + y1 * y1) - sqrt(x2 * x2 + y2 * y2))) / (2.0 * difft);
    return diff;
}

void RungeKutta(long double *p, long double difft)
{
    kvektor k1;
    kvektor k2;
    kvektor k3;
    kvektor k4;

    avek pot = Merkur(p[X_OLD], p[Y_OLD]);
    k1.kx = p[VX_OLD];
    k1.ky = p[VY_OLD];
    k1.kvx = pot.ax;
    k1.kvy = pot.ay;

    pot = Merkur(p[X_OLD] + k1.kx * difft / 2.0, p[Y_OLD] + k1.ky * difft / 2.0);
    k2.kx = k1.kvx * difft / 2.0 + p[VX_OLD];
    k2.ky = k1.kvy * difft / 2.0 + p[VY_OLD];
    k2.kvx = pot.ax;
    k2.kvy = pot.ay;

    pot = Merkur(p[X_OLD] + k2.kx * difft / 2.0, p[Y_OLD] + k2.ky * difft / 2.0);
    k3.kx = k2.kvx * difft / 2.0 + p[VX_OLD];
    k3.ky = k2.kvy * difft / 2.0 + p[VY_OLD];
    k3.kvx = pot.ax;
    k3.kvy = pot.ay;

    pot = Merkur(p[X_OLD] + k3.kx * difft, p[Y_OLD] + k3.ky * difft);
    k4.kx = k3.kvx * difft + p[VX_OLD];
    k4.ky = k3.kvy * difft + p[VY_OLD];
    k4.kvx = pot.ax;
    k4.kvy = pot.ay;

    p[X_NEW] = p[X_OLD] + (difft / 6.0) * (k1.kx + 2 * k2.kx + 2 * k3.kx + k4.kx);
    p[Y_NEW] = p[Y_OLD] + (difft / 6.0) * (k1.ky + 2 * k2.ky + 2 * k3.ky + k4.ky);
    p[VX_NEW] = p[VX_OLD] + (difft / 6.0) * (k1.kvx + 2 * k2.kvx + 2 * k3.kvx + k4.kvx);
    p[VY_NEW] = p[VY_OLD] + (difft / 6.0) * (k1.kvy + 2 * k2.kvy + 2 * k3.kvy + k4.kvy);
    /*
    p[VX_NEW] = p[VX_OLD]  + difft/6.0   * (k1[1] + 2.0 * k2[1] + 2.0*k3[1]+ k4[1]);
    p[VY_NEW] = p[VY_OLD]  + difft/6.0   * (k1[2] + 2.0 * k2[2] + 2.0*k3[2]+ k4[2]);
    p[X_NEW]  = p[X_OLD]  + difft/6.0   * (k1[3] + 2.0 * k2[3] + 2.0*k3[3]+ k4[3]);  
    p[Y_NEW]  = p[Y_OLD]  + difft/6.0   * (k1[4] + 2.0 * k2[4] + 2.0*k3[4]+ k4[4]); 
    
*/
}
int main()
{
    FILE *fp;
    fp = fopen("Merkur.txt", "w+");
    int timesteps = (STARTT - ENDT) / dt, n;
    n = 0;
    long double t = STARTT, Ekin, Epot, Eges, derivation, newangle, angle, absshift, diffangle;
    newangle = angle = diffangle = absshift = 0;
    derivation = 0;
    long double *p, *q;
    p = calloc(8, sizeof(long double));
    q = calloc(2, sizeof(long double));
    p[X_OLD] = STARTX;
    p[Y_OLD] = STARTY;
    p[VX_OLD] = STARTVX;
    p[VY_OLD] = STARTVY;
    //fprintf(fp,"t \t\t\t x \t\t\t y \t\t\t vx \t\t\t vy \t\t\t Ekin \t\t\t Epot \t\t\t Ekges \n");
    while (t <= ENDT)
    {
        Ekin = +(pow(p[VX_NEW], 2) + pow(p[VY_NEW], 2)) / 2.0;
        Epot = -GM / sqrt(pow(p[X_OLD], 2) + pow(p[Y_OLD], 2));
        Eges = Epot + Ekin;
        fprintf(fp, "%.9Lf \t%.9Lf \t%.9Lf \t%.9Lf \t%.9Lf \t%.9Lf \t%.9Lf \t%.9Lf  \n", t, p[0], p[1], p[2], p[3], Ekin, Epot, Eges);
        RungeKutta(p, dt);
        t = t + dt;
        newangle = atan2l(p[Y_OLD], p[X_OLD]) * (180.000000 / M_PI);
        //printf("%.9Lf\t%.9Lf\n",angle,newangle);
        diffangle = newangle - angle;
        angle = newangle;
        if ((derivation > 0) && (distance(q[0], p[4], q[1], p[5], dt) < 0))
        {
            if (n == 0)
            {
                printf("First Perihelion:%.9Lf\n", (diffangle));
                n++;
            }
            else
            {
                absshift = absshift + diffangle;
                printf("Perihelion:%.9Lf \t Pherihelion Shift:%.9Lf\n", newangle, diffangle);
            }
        }
        derivation = distance(q[0], p[4], q[1], p[5], dt);
        q[0] = p[X_OLD];
        q[1] = p[Y_OLD];
        p[X_OLD] = p[X_NEW];
        p[Y_OLD] = p[Y_NEW];
        p[VX_OLD] = p[VX_NEW];
        p[VY_OLD] = p[VY_NEW];
    }
    free(p);
    free(q);
}