#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define sgn(X) ((X>0)? 1:((X<0)? (-1):(0)))
#define D_IS_NEGATIVE -1
#define ROOT_FOUND 0

double quart( double, double, double, double );
double cubic( double, double, double, double );
int quadr( double, double, double, double *, double * );


int main(int argc, char *argv[])
{
    // x^4 + ax^3 + bx^2 + cx + d = 0
    double a, b, c, d;

    a = -67.0/584.0;
    b = 56/584.0;
    c = -54/584.0;
    d = 5/584.0;
    quart( a, b, c, d );
    printf( "\n=============================\n" );
    a = 4;
    b = -4;
    c = -20;
    d = -5;
    quart( a, b, c, d );
    getch();
    return 0;
}
// решение уравнения 4й степени
double quart( double a, double b, double c, double d )
{
    double p, q, r;
    double x1, x2, x3, x4;
    p = b - 3.0*a*a/8.0;
    q = a*a*a/8.0 - a*b/2.0 + c;
    r = -3*a*a*a*a/256.0 + a*a*b/16.0 - c*a/4.0 + d;
    // преаброзуем к виду
    // y^4 + py^2 + qy + r = 0;
    // 2s^3 - ps^2 - 2rs + rp - q^2/4 = 0;
    // s^3 - (p/2)s^2 - rs + ( rp/2 - q^2/8 ) = 0;
    double s = cubic( 1.0, -p/2.0, -r, ( r*p/2.0 - q*q/8.0 ) );
    printf( "\n=================\n" );
    printf( "s = %f\n", s );
    //y^2 + y*sqrt(2s-p) - q/(2*sqrt(2s-p)) + s
    if( quadr( 1.0, -sqrt( 2.0*s-p ), ( s + q/( 2.0*sqrt( 2.0*s-p ) )), &x1, &x2 ) == ROOT_FOUND )
        printf( "x1 = %f\nx2 = %f\n", x1 - a/4, x2 - a/4 );
    if( quadr( 1.0,  sqrt( 2.0*s-p ), ( s - q/( 2.0*sqrt( 2.0*s-p ) )), &x3, &x4 ) == ROOT_FOUND )
        printf( "x3 = %f\nx4 = %f\n", x3 - a/4, x4 - a/4 );
    return 0.;
}

int quadr( double a, double b, double c, double *x1, double *x2 )
{
    double d;
    d = b*b - 4.0*a*c;
    if( d >= 0 ) {
        d = sqrt( d );
        *x1 = ( - b - d )/( 2.0*a );
        *x2 = ( - b + d )/( 2.0*a );
        return ROOT_FOUND;
    }
    else {
        return D_IS_NEGATIVE;
    }
}

double cubic( double a, double b, double c, double d )
{
    double D, q, r;
    double x1, x2, x3;

    if( !a ) {
        if( !quadr( b, c, d, &x1, &x2 ) ) {
            return x1;
        }
    }

    b /= a;
    c /= a;
    d /= a;

    q = ( 3.0*c - b*b ) / 9.0;
    r = ( b*( 9.0*c - 2.0*b*b ) - ( 27.0*d ) ) /54.0;

    D = q*q*q + r*r;
    b /= 3.0;

    if( D > 0 ) {
        q = r + sqrt( D );
        q = ( (q < 0) ? -pow( -q, ( 1.0/3.0 ) ) : pow( q, ( 1.0/3.0 ) ) );
        r = r - sqrt(D);
        r = ( (r < 0) ? -pow( -r, ( 1.0/3.0 ) ) : pow( r, ( 1.0/3.0 ) ) );
        x1 = -b + q + r;
        return x1;
    }

    if( D == 0 ) {
        r = ( ( r < 0 ) ? -pow( -r, ( 1.0/3.0 ) ) : pow( r, ( 1.0/3.0 ) ) );
        x1 = -b + 2.0*r;
        x2 = x3 = -( r + b );
        return x1 > 0? x1 : x2;
    }

    q = -q;
    D = q*q*q;
    D = acos( r / sqrt( D ) );
    q = 2.0 * sqrt( q );
    x1 = -b + q * cos( D/3.0 );
    x2 = -b + q * cos( ( D + 2.0*M_PI )/3.0 );
    x3 = -b + q * cos( ( D + 4.0*M_PI )/3.0 );
    return ( ( x1>0 )? x1 : ( ( x2>0 )? x2 : x3 ) );
}
