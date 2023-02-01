// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT6L 
// Names: Flavian Navin Wenceslas | Ahbinesh a/L Parthasarthy | Nur Sarah Sabrina binti Nazli 
// IDs: 1221304026 | 1221303983 | 1221303683 
// Emails: 1221304026@student.mmu.edu.my | 1221303983@student.mmu.edu.my | 1221303683@student.mmu.edu.my 
// Phones: 017-7625240 | 014-3272618 | 012-3435764 
// ********************************************************* 

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime> // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <Windows.h> //system
#include <stdio.h> //printf
#include <conio.h>
#include<unistd.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;



class Mars
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_;          // underscore(_) to indicate private data
public:
    Mars(int dimX = 15, int dimY = 5); // Constructor don't have return value
    void init(int dimX, int dimY);
    void display() const;
    int getDimX() const;
    int getDimY() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);
    
};

Mars::Mars(int dimX, int dimY) // Constructor have same name as class
{
    init(dimX, dimY);
}

class Rover
{
private:
    int x_, y_;
    char heading_; // either '^', '>', '<' or 'v'
public:
    Rover();
    void land(Mars &mars);
    int getX() const;
    int getY() const;
    char getHeading() const;
    void turnRight(Mars &mars);
    void turnLeft(Mars &mars);
    char move(Mars &mars);
    //void test2_2();

};

Rover::Rover()
{
}

int Rover::getY() const
{
    return y_;
}
char Rover::getHeading() const
{
    return heading_;
}
void test2_1()
{
    Mars mars;
    Rover curiosity;
    curiosity.land(mars);
    mars.display();
    cout << "Status of the Alien:" << endl
         << " Location: (" << curiosity.getX() << ", " << curiosity.getY() << ")"

         << endl

         << " Heading: " << curiosity.getHeading() << endl;
}

void Rover::land(Mars &mars)
{
    Rover curiosity;
    char possibleHeading[] = {'A', '>', '<', 'V'};
    x_ = rand() % mars.getDimX() + 1;
    y_ = rand() % mars.getDimY() + 1;
    heading_ = possibleHeading[rand() % 4];
    mars.setObject(x_, y_, heading_);
}
int Rover::getX() const
{
    return x_;
}

void Rover::turnLeft(Mars &mars)

{

char possibleHeading[] = {'A', '>', '<', 'V'};
heading_ = possibleHeading[(heading_+3-1)%4];


mars.setObject(x_,y_, heading_);
}
void Rover::turnRight(Mars &mars)
{
char possibleHeading[] = {'A', '>', '<', 'V'};

heading_ = possibleHeading[(heading_+2)%4];;
//others code if heading_ >3, minus 4
 
mars.setObject(x_, y_, heading_);
}

char Rover::move(Mars &mars)

{
   
    Rover curiosity;
  
    if (heading_ =='A' )
    {
        mars.setObject((x_+3) , y_ , heading_);
      

         mars.setObject(x_ , y_ ,' ');
    }
    else if(heading_ == '<')
    {
        mars.setObject(x_- 3, y_ , heading_);
        mars.setObject(x_ , y_ ,' ');
    }
    else if (heading_ == '>')
    {
        mars.setObject(x_, y_+ 3 , heading_);
        mars.setObject(x_ , y_ ,' ');
    }
    else
    {
        mars.setObject(x_, y_- 3 , heading_);
        mars.setObject(x_ , y_ ,' ');
        
    }
    return 0;
}

bool Mars::isEmpty(int x, int y)
{
    if ((map_[-(y - 5)][x - 1]) == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mars::isInsideMap(int x, int y)
{
    if ((x > dimX_) || (x < dimX_) && (y > dimY_) || (y < dimY_))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Mars::setObject(int x, int y, char ch)
{
    map_[-(y - 5)][x - 1] = ch;
}



char Mars::getObject(int x, int y) const
{
    return map_[-(y - 5)][x - 1];
}

int Mars::getDimX() const
{
    return dimX_;
}
int Mars::getDimY() const
{
    return dimY_;
}

void Mars::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', 'h', 'p', 'R'};
    int noOfObjects = 8; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void Mars::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    cout << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "  = Welcome to Aliens vs Zombies =" << endl;
    cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (dimY_ - i);

        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void test2_2()
{
Mars mars;
Rover curiosity;
curiosity.land(mars);


mars.display();
cin.get();
//system("pause");

int a;
cout<<" \n Turn= ";
cin>>a;

if (a<2)
{
   curiosity.turnLeft(mars); 
   mars.display();
   cin.get();
    curiosity.move(mars); 
   mars.display();
   cin.get();
  
 
}
else 
{
    curiosity.turnRight(mars);
    mars.display();
    cin.get();
     curiosity.move(mars); 
   mars.display();
   cin.get();
}
 curiosity.move(mars); 
   mars.display();
   cin.get();
    curiosity.move(mars); 
   mars.display();
   cin.get();
   

}

void ani(char a[1000])
{
  for (int i = 0; a[i] !='\0';i++)
  {
    for (int j = 0; j < 1000000; j++);
    cout << a[i];
  }
}



int main()
{


{
 system ("color b");
 ani("        <<<<<                                                   >>>>>\n");
 ani("        <<<<<                                                   >>>>>\n");
 ani("        >>>>>                                                   <<<<<\n");
 ani("        <<<<<        !!! Welcome to Aliens VS Zombies !!!       >>>>>\n");
 ani("        >>>>>                                                   <<<<<\n");
 ani("        <<<<<                                                   >>>>>\n");
 ani("                                       ***\n");
 ani("                                       ***\n");
 ani("                                       ***\n");
 ani("                                       ***\n");
 ani("                                       ***\n");
 ani("                                       ***\n");
 ani("                                    *********\n");
 ani("                                     *******\n");
 ani("                                      *****\n");
 ani("                                       ***\n");
 ani("                                        * \n");   

}
 
char n[30],c[50],ad[100];
int a,p;
cout<<"";
cout<<"                        Enter Your Name: ";
cin>>n;

    system("COLOR b");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\t\t\t\tLoading:) . . .";
    cout << "\n\n\n\t\t\t\t";

    for(int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 25; i++)
    {
        cout << (char)bar2;
        Sleep(150);
    }

    cout<<"\n\t\t\t\t" << (char)1 <<"!";
    system("Pause");

   cout<<endl<<endl<<endl<<endl<<endl;
cout<<"             Welcome "<<n<<endl;

{

 


srand(1); // use this for fixed map during testing
//srand(time(NULL)); // try this for random map
//test1_1();

test2_1();
cout<<" This is the Alien shown in the map \n";


}

test2_2();
test2_2();



bool continueY = true;
 
  
       int YN;
       cout << "                                 Would you like to restart the game? \n";
       cout << "                                        Enter 1 (Final Chance!) \n";
       cout << "                                        Enter 2 to Exit" << endl;
       cin >> YN;
       if (YN == 1)
       {
       test2_2();
       
       }
       else
       {
       continueY = false;   
       }
 
}



 

