#include<iostream>
#include<vector>
using namespace std;
 
struct Pointcoordinates
{
    int x, y;
};
 
int orientation(Pointcoordinates p, Pointcoordinates q, Pointcoordinates r)
{
    int a = (q.y - p.y) * (r.x - q.x) -     // using slope of two lines ... 
              (q.x - p.x) * (r.y - q.y);
 
    if (a == 0) return 0;                  // p,q,r are colinear...
    return (a > 0)? 1: 2;                 // p,q,r are clock or counterclock wise...
}
 
void convexHull(Pointcoordinates Pointcoordinatess[], int n)
{
    
    if (n < 3) return;                     // min 3 points required for convex hull....
 
    vector<Pointcoordinates> hull;        // vector result....
 
    int l = 0;
    for (int i = 1; i < n; i++)            // leftmost point....O(n)
        if (Pointcoordinatess[i].x < Pointcoordinatess[l].x)
            l = i;
 
    int p = l, q;
    do
    {
        hull.push_back(Pointcoordinatess[p]);          // point p added to result vector..
 
        q = (p+1)%n;                                  // q point selected ...
        for (int i = 0; i < n; i++)
        {
           if (orientation(Pointcoordinatess[p], Pointcoordinatess[i], Pointcoordinatess[q]) == 2)
               q = i;
        }
 
        p = q;
 
    } while (p != l);                 // While we don't come to first Point p...
 
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
              << hull[i].y << ")\n";
}                                     // worst case --> all points included in convexHull
                                 // thus, O(n^2) complexity .. 

int main()
{   
    int n;
    cout<<"Enter number of Points"<<endl;
    cin>>n;
    Pointcoordinates Pointcoordinatess[n];
    cout<<"Enter the Point coordinates"<<endl;
    for(int i=0;i<n;i++)
    {
    	cout<<i+1<<"th coordinates"<<endl;
    	cin>>Pointcoordinatess[i].x>>Pointcoordinatess[i].y ;
	}
    
   
    convexHull(Pointcoordinatess, n);
    return 0;
}
