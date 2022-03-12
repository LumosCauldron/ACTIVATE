#include <stdio.h>

struct point
{
	double x;
	double y;
	double z;
	char hemisphere;
};
typedef struct point Point;

double squareroot(double n) 
{
   double i, precision = 0.00001;
   for(i = 1; i*i <=n; ++i);           // Integer part
   for(--i; i*i < n; i += precision);  // Fractional part
   return i;
}

double distance2D(Point* ptr1, Point* ptr2)
{
	return squareroot(
				(ptr1->x - ptr2->x) * (ptr1->x - ptr2->x) + 
				(ptr1->y - ptr2->y) * (ptr1->y - ptr2->y)
			 );
}

double distance3D(Point* ptr1, Point* ptr2)
{
	return squareroot(
				(ptr1->x - ptr2->x) * (ptr1->x - ptr2->x) + 
				(ptr1->y - ptr2->y) * (ptr1->y - ptr2->y) + 
				(ptr1->z - ptr2->z) * (ptr1->z - ptr2->z)
			 );
}

int main()
{
	Point one = {4.2,0.201,75,1};
	Point two = {30.1234,1.0,82.0,1};

	printf("%lf\n", distance3D(&one, &two));
}

