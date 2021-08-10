/*
dummiest way to write A* algorithm, but that what we get when coding at 3 AM with heavy eyes XD .

ps: there is a lot of checks, enum, lists that has been ignored for lack of time.
*/





#include  <iostream>
#include <algorithm>
#include <math.h>
#include <cfloat>

using namespace std;

struct cell   //to hold all cell informatios 
{         
    int x_y[2];
    float f, g, h;    //f=g+h
    int availabilty;  // 0 for free - 1 for obstcle - 2 for checked - 
};

class a_star
{
private:
    
public:
    a_star(int start[2],int goal[2]);
    ~a_star();
    float calc_huristic(int x, int y,cell goal);    // based on  Diagonal Distance  huristic calc
    float calc_g(int side_or_corner);               // a dummy way to estimate the g value
    bool search(cell start,cell goal);              //the main search
    float calc_f(int x, int y,cell goal, int side_or_corner);     //calc f, f=g+h
    bool is_goal(cell current_cell,cell goal);      //check if tge goal is reached
    int grid[5][5]={0};
    cell start_cell,goal_cell;
    cell grid_cell[5][5];


};

a_star::a_star(int start[2],int goal[2])
{
    
    //grid[2][0]={1};  
    //grid[2][1]={1};
    //grid[2][2]={1};

    start_cell.x_y[0]=start[0];
    start_cell.x_y[1]=start[1];
    goal_cell.x_y[0]=goal[0];
    goal_cell.x_y[1]=goal[1];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            grid_cell[i][j].f = FLT_MAX;
            grid_cell[i][j].g = FLT_MAX;
            grid_cell[i][j].h = FLT_MAX;
            grid_cell[i][j].x_y[0] = -1;
            grid_cell[i][j].x_y[1] = -1;
            grid_cell[i][j].availabilty=0;
        }
    }
    

    grid_cell[2][0].availabilty={1};  //obstacle
    grid_cell[2][1].availabilty={1};  //obstacle
    grid_cell[2][2].availabilty={1};  //obstacle

}

a_star::~a_star()
{
}

float a_star::calc_f(int x, int y,cell goal, int side_or_corner)
{
   return calc_huristic(x,y,goal)+calc_g(side_or_corner);
}

float a_star::calc_g(int side_or_corner ) // if side cell pass 1 
{
    return side_or_corner==1 ? 1 : 1.2;   
}

float a_star::calc_huristic(int x, int y,cell goal)
{
int dx = abs(x - goal.x_y[0]);
int dy = abs(y - goal.x_y[1]);
 
return   1 * (dx + dy) + (1.41 - 2 * 1) * min(dx, dy) ;
 
}

bool a_star::is_goal(cell current_cell,cell goal)
{
    if (current_cell.x_y[0]==goal.x_y[0]&&current_cell.x_y[1]==goal.x_y[1])
    {
        return true;
    }
    return false;
    
}

bool a_star::search(cell start,cell goal)
{
    cell current_cell=start_cell;
    cell check_cell=current_cell;
    float f=0;
    /*
		Generating all the 8 successor of this cell

			  N.W N N.E
			    \ | /
				\ | /
			W----Cell----E
				/ | \
				/ | \
			  S.W S S.E

		Cell-->Popped Cell (i, j)
		N --> North	 (i-1, j)
		S --> South	 (i+1, j)
		E --> East	 (i, j+1)
		W --> West		 (i, j-1)
		N.E--> North-East (i-1, j+1)
		N.W--> North-West (i-1, j-1)
		S.E--> South-East (i+1, j+1)
		S.W--> South-West (i+1, j-1)*/
cout<<"-----------------------------------"<<endl;
while (!is_goal(current_cell,goal_cell))
{


    cout<<"("<<current_cell.x_y[0]<<","<<current_cell.x_y[1]<<")"<<">>";   

    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]].f= calc_f(current_cell.x_y[0]-1,current_cell.x_y[1],goal_cell,1);
    f=grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]].f;
    if (grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]].f;
    check_cell.x_y[0]=current_cell.x_y[0]-1;
    check_cell.x_y[1]=current_cell.x_y[1];
    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]].availabilty=2;
    }

    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]].f= calc_f(current_cell.x_y[0]+1,current_cell.x_y[1],goal_cell,1);
    if (grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]].f<f&&grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]].f;
    check_cell.x_y[0]=current_cell.x_y[0]+1;
    check_cell.x_y[1]=current_cell.x_y[1];
    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]].availabilty=2;
    }
    

    grid_cell[current_cell.x_y[0]][current_cell.x_y[1]+1].f= calc_f(current_cell.x_y[0],current_cell.x_y[1]+1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]][current_cell.x_y[1]+1].f<f&&grid_cell[current_cell.x_y[0]][current_cell.x_y[1]+1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]][current_cell.x_y[1]+1].f;
    check_cell.x_y[0]=current_cell.x_y[0];
    check_cell.x_y[1]=current_cell.x_y[1]+1;
    grid_cell[current_cell.x_y[0]][current_cell.x_y[1]+1].availabilty=2;
    }
    
    grid_cell[current_cell.x_y[0]][current_cell.x_y[1]-1].f= calc_f(current_cell.x_y[0],current_cell.x_y[1]-1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]][current_cell.x_y[1]-1].f<f&&grid_cell[current_cell.x_y[0]][current_cell.x_y[1]-1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]][current_cell.x_y[1]-1].f;
    check_cell.x_y[0]=current_cell.x_y[0];
    check_cell.x_y[1]=current_cell.x_y[1]-1;
    grid_cell[current_cell.x_y[0]][current_cell.x_y[1]-1].availabilty=2;
    }
    
    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]+1].f= calc_f(current_cell.x_y[0]-1,current_cell.x_y[1]+1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]+1].f<f&&grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]+1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]+1].f;
    check_cell.x_y[0]=current_cell.x_y[0]-1;
    check_cell.x_y[1]=current_cell.x_y[1]+1;
    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]+1].availabilty=2;
    }
    
    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]-1].f= calc_f(current_cell.x_y[0]-1,current_cell.x_y[1]-1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]-1].f<f&&grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]-1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]-1].f;
    check_cell.x_y[0]=current_cell.x_y[0]-1;
    check_cell.x_y[1]=current_cell.x_y[1]-1;
    grid_cell[current_cell.x_y[0]-1][current_cell.x_y[1]-1].availabilty=2;
    }
    
    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]+1].f= calc_f(current_cell.x_y[0]+1,current_cell.x_y[1]+1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]+1].f<f&&grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]+1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]+1].f;
    check_cell.x_y[0]=current_cell.x_y[0]+1;
    check_cell.x_y[1]=current_cell.x_y[1]+1;
    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]+1].availabilty=2;
    }
    
    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]-1].f= calc_f(current_cell.x_y[0]+1,current_cell.x_y[1]-1,goal_cell,1);
    if (grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]-1].f<f&&grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]-1].availabilty==0)
    {f=grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]-1].f;
    check_cell.x_y[0]=current_cell.x_y[0]+1;
    check_cell.x_y[1]=current_cell.x_y[1]-1;
    grid_cell[current_cell.x_y[0]+1][current_cell.x_y[1]-1].availabilty=2;
    }
    
 current_cell=check_cell;

 }
 


if (is_goal(current_cell,goal_cell))
{
    cout<<"("<<goal_cell.x_y[0]<<","<<goal_cell.x_y[1]<<")"<<endl<<"-----------------------------------"<<endl;
return true;
}else
{
    return false;
}



}



int main()
{
    int start[2]={1,1};
    int goal[2]={4,1};
a_star a_star1(start,goal); //defualt start & goal passed to constructor for testing
a_star1.search(a_star1.start_cell,a_star1.goal_cell); //use the defualt star&goal for searching


    return 0;
}
