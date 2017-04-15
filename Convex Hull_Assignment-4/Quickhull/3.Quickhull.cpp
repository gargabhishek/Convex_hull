#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
 
struct Point
{
    int x, y;
};
bool isLeft(Point a, Point b, Point c)          //check for c ... 
{
     return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
double perdist(double x1, double y1, double x2, double y2, double pointX, double pointY)
{
    double diffX = x2 - x1;
    float diffY = y2 - y1;
    if ((diffX == 0) && (diffY == 0))
    {
        diffX = pointX - x1;
        diffY = pointY - y1;
        return sqrt(diffX * diffX + diffY * diffY);
    }

    float t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

    if (t < 0)
    {
        //point is nearest to the first point i.e x1 and y1
        diffX = pointX - x1;
        diffY = pointY - y1;
    }
    else if (t > 1)
    {
        //point is nearest to the end point i.e x2 and y2
        diffX = pointX - x2;
        diffY = pointY - y2;
    }
    else
    {
        //if perpendicular line intersect the line segment.
        diffX = pointX - (x1 + t * diffX);
        diffY = pointY - (y1 + t * diffY);
    }

    //returning shortest distance
    return sqrt(diffX * diffX + diffY * diffY);
} 
void findhull(vector<Point> hull,vector<Point> S1,Point A, Point B)
{
	if (S1.size() == 0)
		return;
	int k=0,m;	
	for(int i=0;i<S1.size();i++)
	{
		int d=perdist(A.x,A.y,B.x,B.y,S1[i].x,S1[i].y);
		if (k<d)
		{
			k=d;
			m=i;	
		}		
	}
	hull.push_back(S1[m]);
	findhull(hull,S1,A,S1[m]);
	findhull(hull,S1,S1[m],B);
	
 } 
void quickHull(Point points[], int n)
{
	if (n < 3) return;                     // min 3 points required for convex hull....
	vector<Point> hull;        // vector result.... 
	int l = 0,r=0;
    for (int i = 1; i < n; i++) 
	{           // leftmost and rightmost point....O(n)
        if (points[i].x < points[l].x)
            l = i;
        if (points[i].x > points[l].x)
            r = i;
    }
    hull.push_back(points[l]);
    hull.push_back(points[r]);
    
    vector<Point> S1;
    vector<Point> S2;
    for(int i=0;i<n;i++)
    {
    	if(isLeft(points[l],points[r],points[i]))
    		S1.push_back(points[i]);
    	else
    		S2.push_back(points[i])	;
    		
	}
	findhull(hull,S1,points[l],points[r]);
	findhull(hull,S2,points[r],points[l]);
	
	for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
              << hull[i].y << ")\n";
	
}
 
 
int main()
{   
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
    
    quickHull(points, n);
    return 0;
}
