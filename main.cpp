#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <graphics.h>
#include <stack>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct point
{
    float x;
    float y;

};

void circle_points(vector <point> initial_center, vector <point> &on_circle_round, int number_of_center, int number_of_points, float viscinity)
{
    point on_circle;
    point circle_center;
    	
    for (int i =0; i<number_of_center ; i++)
    {
        circle_center.x = initial_center[i].x;
        circle_center.y = initial_center[i].y;
        for ( int j = 0; j<number_of_points; j++)
        {
            on_circle.x = viscinity*cos((M_PI)*((j+1.0)/6.0)) + circle_center.x;
            on_circle.y = viscinity*sin((M_PI)*((j+1.0)/6.0)) + circle_center.y;
            on_circle_round.push_back(on_circle);
        } 
    }
}

// The orientation function returns : 
// 0 for p, q and r are colinear 
// 1 for Clockwise 

// 2 for Counterclockwise


int orientation (point p, point q, point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val==0) return 0;
    return (val > 0)? 1:2;
}

void Jarvis_March (vector <point> on_circle_round, vector <point> &jarvis_boundary, int number_of_center, int number_of_points)
{
    int leftmost = 0;
    int total_points = on_circle_round.size();
    point a;
    point b;
    point c;
    
    for (int i = 0; i<total_points; i++)
    {
        if(on_circle_round[i].x < on_circle_round[leftmost].x)
        {
            leftmost = i;
        }
    }
    
    int p =leftmost;
    int q;
    
    do
    {
        a.x = on_circle_round[p].x;
        a.y = on_circle_round[p].y;
        jarvis_boundary.push_back(a);
        q = ( p + 1 ) % total_points;
        
        for( int i =0 ; i<total_points ; i++ )
        {
            a.x = on_circle_round[p].x;
            a.y = on_circle_round[p].y;
            b.x = on_circle_round[i].x;
            b.y = on_circle_round[i].y;
            c.x = on_circle_round[q].x;
            c.y = on_circle_round[q].y;
            if (orientation( a , b , c ) == 2)
            {
                q = i;
            }
        }

        p = q;
    } while (p != leftmost);
}
point p0;  //for compare function qsort()

point next_top(stack <point> &S)
{
	point p = S.top();
	S.pop();
	point res = S.top();
	S.push(p);
	return res;
}

int dist_square(point p1, point p2)
{
	return (p1.x - p2.x)*(p1.y - p2.y) + (p1.y - p2.y)*(p1.y - p2.y);
}

int compare(const void *vp1, const void *vp2)  //used by qsort()
{
	point *p1 = (point *)vp1;
	point *p2 = (point *)vp2;
	
	int o = orientation(p0, *p1, *p2);
	if(o == 0)
	{
		return (dist_square(p0, *p2) >= dist_square(p0, *p1))? -1 : 1;
	}
	return (o == 2)? -1 : 1;
}

void Graham_Scan(vector <point> on_circle_round, vector <point> &graham_boundary, int number_of_center, int number_of_points)
{
	int y_min = on_circle_round[0].y;
	int min_index = 0;
	int total_points = on_circle_round.size();
	
	for (int i = 0; i < total_points; i++)
	{
		int y = on_circle_round[i].y;
		
		if ((y < y_min) || (y_min == y && on_circle_round[i].x < on_circle_round[min_index].x))
		{
			y_min = on_circle_round[i].y;
			min_index = i;
		}
	}
	swap(on_circle_round[0], on_circle_round[min_index]);
	p0 = on_circle_round[0];
	qsort(&on_circle_round[1], total_points-1, sizeof(point), compare);
	int m = 1;
	for (int i = 1; i < total_points; i++)
	{
		while (i < total_points - 1 && orientation(p0, on_circle_round[i], on_circle_round[i+1]) == 0)
		{
			i++;
		}
		
		on_circle_round[m] = on_circle_round[i];
		m++;
	}
	stack <point> boundary;
	boundary.push(on_circle_round[0]);
	boundary.push(on_circle_round[1]);
	boundary.push(on_circle_round[2]);
	for (int i = 3; i < m ; i++)
	{
		while(orientation(next_top(boundary), boundary.top(), on_circle_round[i]) != 2)
		{
			boundary.pop();
		}
		
		boundary.push(on_circle_round[i]);
	}
	while (!boundary.empty()) 
	{ 
       point p = boundary.top(); 
       graham_boundary.push_back(p);
       boundary.pop(); 
   	} 
}

float area_total(vector <point> vertices)
{
	float area = 0.0f;

	for (int i = 0; i < vertices.size() - 1; ++i)
	{
		area += vertices[i].x * vertices[i+1].y - vertices[i+1].x * vertices[i].y;
	}
	area += vertices[vertices.size()-1].x * vertices[0].y - vertices[0].x * vertices[vertices.size()-1].y;

	area = abs(area) / 2.0f;
	
	return area;
}
int main()
{
    vector <point> initial_center;
    vector <point> on_circle_round;
    vector <point> jarvis_boundary;
    vector <point> graham_boundary;
    point center;
    
    int number_of_center;
    int x;
    int y;
    int number_of_points;
    float viscinity;
    float area;
    
    while(1)
    {
    	cout<<"****************************************************************"<<endl;
    	cout<<"1. Jarvis March Algorithm"<<endl<<"2. Graham Scan"<<endl<<"3. Exit"<<endl;
    	cout<<"****************************************************************"<<endl;
    	int choice;
    	cout<<endl<<"Enter your choice : ";
    	cin>>choice;
    	switch(choice)
    	{
    		case(1):
    			
    			initwindow(500,500,"ConvexHull");
    			cout<<"Enter the number of points : ";
    			cin>>number_of_center;
    			if (number_of_center < 2)
    			{
    				cout<<"You entered less than 2 points, using default 2 points."<<endl;
    				number_of_center = 2;
				}
    			cout<<"Enter the number of points to be taken on each circle (WARNING : Enter more than 12):"<<endl;
    			cin>>number_of_points;
    			if (number_of_points < 12)
    			{
    				cout<<"You Entered less than 12 points, using default 12 points."<<endl;
    				number_of_points = 12;
				}
				cout<<"Enter the viscinity of virus-spread (Enter above 5) : ";
				cin>>viscinity;
				if (viscinity < 5)
				{
					cout<<"Your entered viscinity is too low, setting default 5"<<endl;
					viscinity = 5.0;
				}
    			for (int i = 0 ; i<number_of_center ;i++)
    			{
        			cout<<"Enter the X-Axis for "<<i<<"th center : ";
        			cin>>center.x;
        			cout<<"Enter the Y-Axis for "<<i<<"th center : ";
        			cin>>center.y;
        			initial_center.push_back(center);
        			putpixel( ( 250 + ( center.x ) * 10 ) , ( 250 - ( center.y ) * 10 ) , WHITE );
        			setcolor(RED);
        			circle((250+(center.x)*10),(250-(center.y)*10),viscinity * 10);
    			}
    			circle_points( initial_center , on_circle_round , number_of_center , number_of_points , viscinity);
    			Jarvis_March(on_circle_round, jarvis_boundary, number_of_center, number_of_points);
				area = area_total(jarvis_boundary);
    			if (jarvis_boundary.size() != 0 )
    			{
	    			for (int i = 0; i<jarvis_boundary.size() ; i++)
	    			{
	        			putpixel((250+(jarvis_boundary[i].x)*10),(250-(jarvis_boundary[i].y)*10),YELLOW);
						cout<<i+1<<" . "<<"\t\t";
	       				cout<<"X-Axis : "<<jarvis_boundary[i].x<<"\t\t\t";
	        			cout<<"Y-Axis : "<<jarvis_boundary[i].y<<endl<<endl;
					}
					
					cout<<"Total Area Coverd by these points is : "<<area<<endl;
	    			for (int i = 1; i<jarvis_boundary.size() ; i++)
	    			{
	    				setcolor(MAGENTA);
	    				line((250+(jarvis_boundary[i-1].x)*10),(250-(jarvis_boundary[i-1].y)*10),(250+(jarvis_boundary[i].x)*10),(250-(jarvis_boundary[i].y)*10));
					}
					line((250+(jarvis_boundary[0].x)*10),(250-(jarvis_boundary[0].y)*10),(250+(jarvis_boundary[jarvis_boundary.size()-1].x)*10),(250-(jarvis_boundary[jarvis_boundary.size()-1].y)*10));
    				setcolor(WHITE);
    				line(250,0,250,500);
    				line(0,250,500,250);
    				getch();
				}
				initial_center.clear();
    			on_circle_round.clear();
    			jarvis_boundary.clear();
				break;
			
			case(2):
				initwindow(500,500,"ConvexHull");
    			cout<<"Enter the number of points : ";
    			cin>>number_of_center;
    			if (number_of_center < 2)
    			{
    				cout<<"You entered less than 2 points, using default 2 points."<<endl;
    				number_of_center = 2;
				}
    			cout<<"Enter the number of points to be taken on each circle (WARNING : Enter more than 12): ";
    			cin>>number_of_points;
    			if (number_of_points < 12)
    			{
    				cout<<"You Entered less than 12 points, using default 12 points."<<endl;
    				number_of_points = 12;
				}
				cout<<"Enter the viscinity of virus-spread (Enter above 5) : ";
				cin>>viscinity;
				if (viscinity < 5)
				{
					cout<<"Your entered viscinity is too low, setting default 5"<<endl;
					viscinity = 5.0;
				}
    			for (int i = 0 ; i<number_of_center ;i++)
    			{
        			cout<<"Enter the X-Axis for "<<i<<"th center : ";
        			cin>>center.x;
        			cout<<"Enter the Y-Axis for "<<i<<"th center : ";
        			cin>>center.y;
        			initial_center.push_back(center);
        			putpixel( ( 250 + ( center.x ) * 10 ) , ( 250 - ( center.y ) * 10 ) , WHITE );
        			setcolor(RED);
        			circle((250+(center.x)*10),(250-(center.y)*10),viscinity * 10);
    			}
    			circle_points( initial_center , on_circle_round , number_of_center , number_of_points, viscinity );
				Graham_Scan( on_circle_round, graham_boundary, number_of_center, number_of_points );
				area = area_total(graham_boundary);
				if (graham_boundary.size() != 0 )
				{
					for (int i = 0; i<graham_boundary.size() ; i++)
	    			{
	        			putpixel((250+(graham_boundary[i].x)*10),(250-(graham_boundary[i].y)*10),YELLOW);
						cout<<i+1<<" . "<<"\t\t";
	       				cout<<"X-Axis : "<<graham_boundary[i].x<<"\t\t\t";
	        			cout<<"Y-Axis : "<<graham_boundary[i].y<<endl<<endl;
					}
					
					cout<<"Total Area Coverd by these points is : "<<area<<endl;
	    			for (int i = 1; i<graham_boundary.size() ; i++)
	    			{
	    				setcolor(MAGENTA);
	    				line((250+(graham_boundary[i-1].x)*10),(250-(graham_boundary[i-1].y)*10),(250+(graham_boundary[i].x)*10),(250-(graham_boundary[i].y)*10));
					}
					line((250+(graham_boundary[0].x)*10),(250-(graham_boundary[0].y)*10),(250+(graham_boundary[graham_boundary.size()-1].x)*10),(250-(graham_boundary[graham_boundary.size()-1].y)*10));	
					setcolor(WHITE);
    				line(250,0,250,500);
    				line(0,250,500,250);
    				getch();
				}
				initial_center.clear();
    			on_circle_round.clear();
    			graham_boundary.clear();
    			break;
    		case(3):
				exit(0);
    		default:
    			cout<<"Error! You enetered wrong number";
    			break;		
		}
	}
}
