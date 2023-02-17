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


#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;



class Mars
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_;     
    int points_;     // underscore(_) to indicate private data
public:
    Mars(int dimX=15 , int dimY=5); // Constructor don't have return value
    void init(int dimX, int dimY);
    void display() const;
    int getDimX() const;
    int getDimY() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);

    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);
    bool collect(int x, int y);
   
    
};



class Rover: public Mars
{
    private:
        int x_, y_;
        char heading_; 
        int points_;
    public:
        Rover(){};
        void land(Mars &mars);
        int getX() const;
        int getY() const;
        char getHeading() const;
        void turnLeft(Mars &mars);
        void turnRight(Mars &mars);
        void move(Mars &mars);
        void autoMove(Mars &mars, Rover &curiosity);
        int geth(Mars &mars);
        
        

      
};

int Mars::getDimX() const
{
    return dimX_;
}
int Mars::getDimY() const
{
    return dimY_;
}

Mars::Mars(int dimX, int dimY)
{
    init(dimX, dimY);}


void Mars::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'z', 'r', 'p', 'h'};
    int noOfObjects = 10;

    map_.resize(dimY_);
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_);
    }

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void test2_1()
{
    int row, col;
    cout << "Enter the number of rows: ";
    cin >> row;
    cout << "Enter the number of columns: ";
    cin >> col;

    Mars mars;
    mars.init(row, col);

    Rover curiosity;
    curiosity.land(mars);
    mars.display();

    cout << "Status of the Alien:" << endl
         << " Location: (" << curiosity.getX() << ", " << curiosity.getY() << ")"
         << endl
         << " Heading: " << curiosity.getHeading() << endl;
}
void test2_11()
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

void Mars::display() const
{
    // comment this out during testing
    // system("clear"); system("cls");
    cout << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "  = Welcome to Aliens vs Zombies =" << endl;
    cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << endl;
   
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << " ";
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
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
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
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

char Mars::getObject(int x, int y) const
{
    return map_[dimY_-y][x-1];
}
void Mars::setObject(int x, int y, char ch)
{
     map_[dimY_-y][x-1] = ch;
}

bool Mars::isEmpty(int x, int y){
    return map_[dimY_-y][x-1] == ' ';
} 
bool Mars::collect(int x, int y){
    return map_[dimY_-y][x-1] == 'h';

}
bool Mars::isInsideMap(int x, int y){
    return x >= 1 && x <= dimX_ && y >= 1 && y <= dimY_;
}

 void Rover::land(Mars &mars)
{
    char possibleHeading[] = {'^', '>', '<', 'v'};
    x_ = rand() % mars.getDimX() + 1;
    y_ = rand() % mars.getDimY() + 1;
    heading_ = possibleHeading[rand() % 4];
    mars.setObject(x_, y_, heading_);
}

void Rover::turnLeft(Mars &mars){
    // char possibleHeading[] = {'^', '>', '<', 'v'};
    mars.setObject(x_, y_, heading_);
    if (heading_ == '^'){
        heading_ = '<';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == '<'){
        heading_ = 'v';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == '>'){
        heading_ = '^';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == 'v'){
        heading_ = '>';
        mars.setObject(x_, y_, heading_);
    }
}

void Rover::turnRight(Mars &mars){
    if (heading_ == '^'){
        heading_ = '>';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == '<'){
        heading_ = '^';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == 'v'){
        heading_ = '<';
        mars.setObject(x_, y_, heading_);
    }
    else if (heading_ == '>'){
        heading_ = 'v';
        mars.setObject(x_, y_, heading_);
    }
}

void Rover::move(Mars &mars)

{
    {
    int x_new = x_;
    int y_new = y_;
    switch (heading_)
    {
    case 'N':
        y_new--;
        break;
    case 'S':
        y_new++;
        break;
    case 'W':
        x_new--;
        break;
    case 'E':
        x_new++;
        break;
    }
    if (mars.getObject(x_new, y_new) == 'p')
    {
        autoMove(mars, *this); // Call the autoMove function to move the rover randomly
    }
    else if (mars.isInsideMap(x_new, y_new) && mars.isEmpty(x_new, y_new))
    {
        mars.setObject(x_, y_, ' ');
        x_ = x_new;
        y_ = y_new;
        mars.setObject(x_, y_, heading_);
    }
}
{
    if (heading_ == '^'){
        if (y_ != 5){
            if (mars.isEmpty(x_, y_+1) || mars.collect(x_, y_+1)){
                y_++;
                mars.setObject(x_, y_, heading_);
                mars.setObject(x_, y_-1, ' ');
            }
        }
    }
    if (heading_ == 'v'){
        if (y_ != 1){
            if (mars.isEmpty(x_, y_-1) || mars.collect(x_, y_-1)){
                y_--;
                mars.setObject(x_, y_, heading_);
                mars.setObject(x_, y_+1, ' ');
            }
        } 
    }
    if (heading_ == '<'){
        if ((mars.isEmpty(x_-1, y_) || mars.collect(x_-1, y_)) && mars.isInsideMap(x_-1, y_)){
            x_--;
            mars.setObject(x_, y_, heading_);
            mars.setObject(x_+1, y_, ' ');
        }
    }
    if (heading_ == '>'){
        if ((mars.isEmpty(x_+1, y_) || mars.collect(x_+1, y_)) && mars.isInsideMap(x_+1, y_)){
            x_++;
            mars.setObject(x_, y_, heading_);
            mars.setObject(x_-1, y_, ' ');
        }
    }
        if (mars.getObject(x_, y_) == 'z') {
        // execute desired program
        system("program.exe");
    }
    else {
        mars.setObject(x_, y_, heading_);  // mark new position
    }
}
}




int Rover::geth(Mars &mars){

    int H=0;

    if (heading_ == '^'){
        if (y_ != 5){
            if (mars.isEmpty(x_, y_+1) || mars.collect(x_, y_+1)){
                if (mars.collect(x_, y_+1)){
                    H++;
                }
            }
        }
    }
    else if (heading_ == 'v'){
        if (y_ != 1){
            if (mars.isEmpty(x_, y_-1) || mars.collect(x_, y_-1)){
                if (mars.collect(x_, y_-1)){
                    H++;
                }
            }
        } 
    }
    else if (heading_ == '<'){
        if ((mars.isEmpty(x_-1, y_) || mars.collect(x_-1, y_)) && mars.isInsideMap(x_-1, y_)){
            if (mars.collect(x_-1, y_)){
                   H++;
                }
        }
    }
    else if (heading_ == '>'){
        if ((mars.isEmpty(x_+1, y_) || mars.collect(x_+1, y_)) && mars.isInsideMap(x_+1, y_)){
            if (mars.collect(x_+1, y_)){
                   H++;
                }
        }
    }
    
    return H;
}


int Rover::getX() const
{
    return x_;
}

int Rover::getY() const
{
    return y_;
}
char Rover::getHeading() const
{
    return heading_;
}

void Rover::autoMove(Mars &mars, Rover &curiosity){
    bool obstacle =true;
    while (not obstacle){
        mars.display();
        int x = getX(), y= getY();
        curiosity.move(mars);
        if (getX() == x && getY() == y){
            srand(time(NULL));
            int r = rand();
            if (r%2 == 0){
                curiosity.turnRight(mars);
            }
            else{
                curiosity.turnLeft(mars);
            }
           
        }
        system("read -n 1 -s -p \"Press any key to continue....\"");
        cout << endl;
    }
}





void test2_3(){

    Mars mars;
    Rover curiosity;

    curiosity.autoMove(mars, curiosity);
    mars.display();
}

void test2_4(){

    Mars mars;
    Rover curiosity;

    int collected = 0;

    curiosity.land(mars);
    mars.display();

    string command;
    cout << "Enter moves: ";
    cin >> command;
    

    for (int i=0; i<command.length(); i++){
        mars.display();
        // system("read -n 1 -s -p \"Press any key to continue...\""); system("pause");
        if (command.at(i) == 'M'){
            curiosity.move(mars);
            cout << curiosity.getX() << "  " << curiosity.getY() << endl;
            getch();
        }
        if (command.at(i) == 'L'){
            curiosity.turnLeft(mars);
            getch();
        }
        if (command.at(i) == 'R'){
            curiosity.turnRight(mars);
            getch();
        }
       // if (command.at(i) == 'A'){
       //     curiosity.autoMove(mars, curiosity);
      //  }
        collected += curiosity.geth(mars);
    }
    
    mars.display();
    cout << endl << "Total Health (H) =  \n" << collected << endl;
    cout<<"Press Enter to play again\n";
    getch();
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
cout<<"\nInstruction: This is Alien vs Zombie where you will need to control the Alien's movement.\n";
cout<<"When map appers, you need to send commands for the Alien to move.\n";
cout<< "  L - Left\n";
cout<< "  R - Right\n";
cout<< "  M - Move\n";
cout<<"The Objective is to collect as many health pack(h) and avoid clashing zombies\n";
cout<<"You will be given 3 rounds to play\n";
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

 


//srand(1); // use this for fixed map during testing
srand(time(NULL)); // try this for random map
//test1_1();
test2_11();
test2_1();
getch();


}


test2_4();
test2_4();
test2_4();

cout << endl;


bool continueY = true;
 
  
       int YN;
       cout << "                                 Would you like to restart the game? \n";
       cout << "                                        Enter 1 (2 CHANCES LEFT!) \n";
       cout << "                                        Enter 2 to Exit" << endl;
       cin >> YN;
       if (YN == 1)
       {
       test2_4();
       test2_4();
       }
       else
       {
       continueY = false;   
       }
 
}



 

