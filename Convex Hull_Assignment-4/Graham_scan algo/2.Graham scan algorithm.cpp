#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;
 
struct Point
{
    int x, y;
}p0;
 

Point next(stack<Point> &S)       // stack operation ... 
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

int swap(Point &p1, Point &p2)          // swap fn called in convexHull_graham ...
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
 
int dist(Point p1, Point p2)                   // distance btw two points...
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
 
int orientation(Point p, Point q, Point r)   // orientation fn similar in gift wrapping...
{
    int a = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (a == 0) return 0;                  // colinear points ...
    return (a > 0)? 1: 2;                // clock or counterclock wise ...
}
 
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   int O = orientation(p0, *p1, *p2);          // Check orientation ....
   if (O == 0)
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
 
   return (O == 2)? -1: 1;
}

void convexHull_graham(Point points[], int n)
{
   int ymin = points[0].y, min = 0;                   // bottom-most point...
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     if ((y < ymin) || (ymin == y &&               // if tie then take lesser x... 
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }
 
   swap(points[0], points[min]);             // bottom-most point is first point ... 

   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);    // sorting acc. to angle ... 
                                                     // stdlib library ... 
                                                     // O(nlogn) for sorting points ...
   int m = 1; 
   for (int i=1; i<n; i++)                          // O(n) time complexity ... 
   {                                                 // remove elements with same angle .. 
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;
 
 
       points[m] = points[i];
       m++;  
   }
 
   if (m < 3) return;                     // min element 3 required .... 
 
   stack<Point> S;                        // stack having solution ...
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
 
   for (int i = 3; i < m; i++)                 //removing element making orientation clockwise...
   {                                          // worst case nearly O(n)
      while (orientation(next(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
 
   while (!S.empty())
   {
       Point p = S.top();
       cout << "(" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}
 
int main()
{                                            // thus, time complexity O(nlogn) ... 
    int n;
    cout<<"Enter number of Points"<<endl;
    cin>>n;
    Point points[n];
    cout<<"Enter the Point coordinates"<<endl;
    for(int i=0;i<n;i++)
    {
    	cout<<i+1<<"th coordinates"<<endl;
    	cin>>points[i].x>>points[i].y ;
	}
    convexHull_graham(points, n);
    return 0;
}
