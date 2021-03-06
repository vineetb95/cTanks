#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <fstream.h>

class player{
public:
	char name[30];
	int x;  //Tank coordinates
	int c;	//Color of tank.
	float theta;  //Angle of projection
	int v; //Velocity of projection
	int move; //Moves left
	int bomb; //Bomb strength
	int points; 

	player(){
		v = 50;
		move = 4;
		bomb = 100;
		points = 0;
	}
}player1,player2;

float d_r(float theta);
void set_b(void);
void set_b1(player pl1,player pl2);
int modify(int i,player &pl1,player &pl2);
void d_volley(int i,int l);
void instructions();
void environment(void);
void display_d(player pl,char a);
void tank (int x,int c,float theta);
void fire(player &pl,player &pl1);
void explode(int x1,int y1);
void point(player &pl2,player &pl1,int x1,int y1);
void tankmove(player &pl1,player &pl2,char a);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
void display_d_all(void);

int xmax,ymax;

char points[20],bomb[20],v[20],move[20],theta[20];

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
        while (i<j)
   {
        temp = str[i];
	str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
            }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0'; 
       return i;
}
 
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
 
float d_r(float theta){  //degree to radians converter.
	return (theta*0.01745);
}



void set_b(void){   //function to set the background for fire and explode functions.
	environment();	
	tank(player1.x,player1.c,player1.theta);
	tank(player2.x,player2.c,player2.theta);
}

void set_b1(player pl1,player pl2){ //function to set background for tankmove function.  tank pl1 is moved.  
	environment();
	display_d(player1,'1');
	display_d(player2,'2');
	tank(pl2.x,pl2.c,pl2.theta);
}

int modify(int i,player &pl1,player &pl2){ 
	setcolor(BLACK);
	if(i==2){
		outtextxy(5,ymax-185,"Enter Velocity(0-100)");
		float n;
		cin>>n;	
		if(n<=100&&n>=0) {
			pl1.v=n; return 1;
		}
		else{
			outtextxy(5,ymax-185,"WRONG INPUT!");
			delay(2000);
			return 0;
		} 
	}

	else if(i==3){
		if(pl1.move>0){
			outtextxy(5,ymax-185,"Where to move? Backward(b or B) or Forward(f or F)");
			char a;
			cin>>a;
			tankmove(pl1,pl2,a);
			--pl1.move;
			return 1;
			}
		else{
			outtextxy(5,ymax-175,"NO moves left");
			delay(2000);
			return 0;
			}
		}
	
	else if(i==4){
		outtextxy(5,ymax-185,"Enter Angle.(30-150)");
		float j;
		cin>>j;
		if(j>=30&&j<=150){
		pl1.theta=j;
		return 1;
		}
		else
		return 0;
	}
	else if(i==1){
		if(pl1.points-pl2.points<150){
			outtextxy(5,ymax-185,"Not enough lead");
			delay(2000);
			return 0;
		}
		else{
			outtextxy(5,ymax-185,"How much points to sacrifice?");
			int p;
			cin>>p;
			pl1.points -= p;
			pl1.bomb += 2*p;
			return 1;
		} 
	}
}

void d_volley(int i,char l){
	setfillstyle(SOLID_FILL,BLACK);
	bar(xmax*0.5-100,0,xmax*0.5+100,20);
	setcolor(CYAN);
	if(i==1){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"1");
	}
	else if(i==2){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"2");
	}
	else if(i==3){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"3");
	}
	else if(i==4){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"4");
	}
	else if(i==5){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"5");
	}
	else if(i==6){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"6");
	}
	else if(i==7){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"7");
	}
	else if(i==8){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"8");
	}
	else if(i==9){
		outtextxy(xmax*0.5-32,5,"VOLLEY"); 
		outtextxy(xmax*0.5+24,5,"9");
	}
	else 
		outtextxy(xmax*0.5-48,5,"FINAL VOLLEY");
	}

void instructions(){
	setcolor(BLACK);
	outtextxy((0.5*xmax)-50,ymax-195,"INSRUCTIONS");
	outtextxy(5,ymax-185,"1. Enter the number written against the feature to modify it.");
	outtextxy(5,ymax-175,"2. It will give a message if it is succesfully modified.");
	outtextxy(5,ymax-165,"3. Velocity,angle(in degrees) can be changed and you can move backward or forward.");
	outtextxy(5,ymax-155,"4. Bomb Strength can be upgraded on the expense of points .");
	outtextxy(5,ymax-145,"You must be ahead of your opponent by 150 points to upgrade it.");
	outtextxy(5,ymax-135,"For a single point bomb strength increases by 2 points.");
	outtextxy(5,ymax-125,"Press any key to continue.");
	getch();
	environment();
}


void environment(void){
	setfillstyle(SOLID_FILL,BROWN);
	bar(0,ymax-199,xmax,ymax);
}

void display_d_all(void){
	display_d(player1,'1');
	display_d(player2,'2');
}

void display_d(player pl,char a){    //display details.
	if(a=='1'){
	setfillstyle(SOLID_FILL,BLACK);
	bar(75-5,ymax-465,75+225,ymax-260);
	setcolor(RED);
	outtextxy(75,ymax-460,"0. FIRE");
	setcolor(LIGHTGRAY);
	outtextxy(75,ymax-440,"Points : ");
	outtextxy(75,ymax-430,"1. Bomb Strength : ");
	outtextxy(75,ymax-420,"2. Velocity : ");
	outtextxy(75,ymax-410,"3. Moves Left : ");
	outtextxy(75,ymax-400,"4. Angle : ");
	setcolor(pl.c);
	ftoa(pl.points,points,1);
	ftoa(pl.bomb,bomb,1);
	ftoa(pl.v,v,1);
	ftoa(pl.move,move,1);
	ftoa(pl.theta,theta,1);
	outtextxy(75,ymax-450,pl.name);
	outtextxy(147,ymax-440,points);
	outtextxy(223,ymax-430,bomb);
	outtextxy(179,ymax-420,v);
	outtextxy(195,ymax-410,move);
	outtextxy(155,ymax-400,theta);
}

else if(a=='2'){
	setfillstyle(SOLID_FILL,BLACK);
	bar(xmax-200-5,ymax-465,xmax-200+225,ymax-260);
	setcolor(RED);
	outtextxy(xmax-200,ymax-460,"0. FIRE");
	setcolor(LIGHTGRAY);
	outtextxy(xmax-200,ymax-440,"Points : ");
	outtextxy(xmax-200,ymax-430,"1. Bomb Strength : ");
	outtextxy(xmax-200,ymax-420,"2. Velocity : ");
	outtextxy(xmax-200,ymax-410,"3. Moves Left : ");
	outtextxy(xmax-200,ymax-400,"4. Angle : ");
	setcolor(pl.c);
	ftoa(pl.points,points,1);
	ftoa(pl.bomb,bomb,1);
	ftoa(pl.v,v,1);
	ftoa(pl.move,move,1);
	ftoa(pl.theta,theta,1);
	outtextxy(xmax-200,ymax-450,pl.name);
	outtextxy(xmax-200+72,ymax-440,points);
	outtextxy(xmax-200+148,ymax-430,bomb);
	outtextxy(xmax-200+104,ymax-420,v);
	outtextxy(xmax-200+120,ymax-410,move);
	outtextxy(xmax-200+80,ymax-400,theta);
	}

}

void tank (int x,int c,float theta){
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	circle(x-24,ymax-208,8);                 //Radius of wheel is 8 pixels.
	floodfill(x-24,ymax-208,LIGHTGRAY);
	circle(x-8,ymax-208,8);
	floodfill(x-8,ymax-208,LIGHTGRAY);
	circle(x+8,ymax-208,8);
	floodfill(x+8,ymax-208,LIGHTGRAY);
	circle(x+24,ymax-208,8);
	floodfill(x+24,ymax-208,LIGHTGRAY);
	setcolor(YELLOW);
	line(x-24,ymax-200,x+24,ymax-200);
	arc(x-24,ymax-208,90,270,8);
	arc(x+24,ymax-208,270,90,8);
	setcolor(CYAN);				//theta is angle of projection.
	line(x+6,ymax-230,x+6+34*cos(d_r(theta)),ymax-230-34*sin(d_r(theta))); //Thick Line
	line(x+6,ymax-229,x+6+34*cos(d_r(theta)),ymax-229-34*sin(d_r(theta)));
	setcolor(c);
	setfillstyle(SOLID_FILL,c);
	bar(x-24,ymax-230,x+24,ymax-216);
	arc(x,ymax-230,0,180,12); //Radius of dome is 12 pixels.
	floodfill(x,ymax-236,c);
	setcolor(YELLOW);
	line(x-24,ymax-216,x+24,ymax-216);
}


void fire(player &pl,player &pl1,char u){
	int x1=pl.x+6+cos(d_r(pl.theta)),y1=ymax-230-sin(d_r(pl.theta)),count=0,vx=5*(pl.v)*cos(d_r(pl.theta)),vy=5*(pl.v)*sin(d_r(pl.theta));
	int x2=x1;
	int y2=y1;
	for(;y1<=ymax-200;x1=x2+vx*count*0.1,y1=y2-vy*count*0.1+0.5*60*count*count*0.01){
	++count;
	cleardevice();
	set_b();
	setcolor(LIGHTMAGENTA);
	setfillstyle(SOLID_FILL,LIGHTMAGENTA);
	circle(x1,y1,7); //Radius of bomb is 7 pixels.
	floodfill(x1,y1,LIGHTMAGENTA);
	delay(100);
	if(x1<=0||x1>=xmax)
		break;
	if(pow(x1-(pl1.x),2) + pow((y1-(ymax-199-15)),2) <= 576)         
		break;
	}
	cleardevice();
	set_b();
	explode(x1,y1);
	point(pl1,pl,x1,y1);
	display_d_all();
}


void explode(int x1,int y1){
	int w=720; //Angular velocity
	int r=100,count=0;
	int vr=284;  //Rate of change of radius.
	for(int i=0;count*0.1<=2;++i,i=i%15){
	setcolor(RED);
	arc(x1,y1,0+w*count*0.1,72+w*count*0.1,r);    //repeated to thicken
	arc(x1,y1,0+w*count*0.1,72+w*count*0.1,r-1);
	arc(x1,y1,0+w*count*0.1,72+w*count*0.1,r-2);
	arc(x1,y1,0+w*count*0.1,72+w*count*0.1,r-3);
	arc(x1,y1,0+w*count*0.1,72+w*count*0.1,r-4);

	setcolor(BLUE);
	arc(x1,y1,72+w*count*0.1,144+w*count*0.1,r);    //repeated to thicken
	arc(x1,y1,72+w*count*0.1,144+w*count*0.1,r-1);
	arc(x1,y1,72+w*count*0.1,144+w*count*0.1,r-2);
	arc(x1,y1,72+w*count*0.1,144+w*count*0.1,r-3);
	arc(x1,y1,72+w*count*0.1,144+w*count*0.1,r-4);

	setcolor(YELLOW);
	arc(x1,y1,144+w*count*0.1,216+w*count*0.1,r);    //repeated to thicken
	arc(x1,y1,144+w*count*0.1,216+w*count*0.1,r-1);
	arc(x1,y1,144+w*count*0.1,216+w*count*0.1,r-2);
	arc(x1,y1,144+w*count*0.1,216+w*count*0.1,r-3);
	arc(x1,y1,144+w*count*0.1,216+w*count*0.1,r-4);

    setcolor(GREEN);
	arc(x1,y1,216+w*count*0.1,288+w*count*0.1,r);    //repeated to thicken
	arc(x1,y1,216+w*count*0.1,288+w*count*0.1,r-1);
	arc(x1,y1,216+w*count*0.1,288+w*count*0.1,r-2);
	arc(x1,y1,216+w*count*0.1,288+w*count*0.1,r-3);
	arc(x1,y1,216+w*count*0.1,288+w*count*0.1,r-4);

	setcolor(GREEN);
	arc(x1,y1,288+w*count*0.1,360+w*count*0.1,r);    //repeated to thicken
	arc(x1,y1,216+w*count*0.1,360+w*count*0.1,r-1);
	arc(x1,y1,216+w*count*0.1,360+w*count*0.1,r-2);
	arc(x1,y1,216+w*count*0.1,360+w*count*0.1,r-3);
	arc(x1,y1,216+w*count*0.1,360+w*count*0.1,r-4);

    setcolor(i);
    setfillstyle(SOLID_FILL,i);
    circle(x1,y1,r-5);
    floodfill(x1,y1,i);

    delay(100);
	count++;
	}
	cleardevice();
	set_b();
}

void point(player &pl2,player &pl1,int x1,int y1){   //player pl2 is the one who has been atatcked and pl1 is the attacker.
	int red_f; //reducing factor.
	int distance = pow(pow(x1-(pl2.x),2) + pow((y1-(ymax-199-15)),2),0.5);
	if(distance<100){
	 red_f = abs(pl2.x-x1);
	 }
	if(distance>100);
		//no INCREMENT in points.
	else if(distance<40)
		pl1.points += pl1.bomb;  //MAXX IMPACT.
	else
		pl1.points += pl1.bomb - red_f ;
}


void tankmove(player &pl1,player &pl2,char a){   //pl1 is moving.
	int v = 20;   //velocity(pixel per second)
	int i=pl1.x;  //initial value
	if(a=='f'||a=='F'){
		for(int count=0;count*0.1<=2;){
			cleardevice();
			set_b1(pl1,pl2);
			pl1.x = i + v*count*0.1;
			tank(pl1.x,pl1.c,pl1.theta);
			delay(100);
			++count;
		}
	}else if(a=='b'||a=='B'){
		for(int count=0;count*0.1<=2;){
			cleardevice();
			set_b1(pl1,pl2);
			pl1.x = i + (-1)*v*count*0.1;
			tank(pl1.x,pl1.c,pl1.theta);
			delay(100);
			++count;
		}
	}
}


void main(){
ofstream game_history("game_history.txt",ios::app);

clrscr();
cout<<"Welcome to cTanks \n";
cout<<"Enter details of Player 1: \n";
cout<<"Name : \t ";
cin>>player1.name;
cout<<'\n';
cout<<"Select Tank color (by entering color code) : \n";
cout<<"Blue\t(1)\nGreen\t(2)\nCyan\t(3)\nRed\t(4)\nMagenta\t(5)\n";
cin>>player1.c;

cout<<" \nEnter details of Player 2: \n";
cout<<"Name : \t ";
cin>>player2.name;
cout<<'\n';
cout<<"Select Tank color (by entering color code) : \n";
cout<<"Blue\t(1)\nGreen\t(2)\nCyan\t(3)\nRed\t(4)\nMagenta\t(5)\n";
cin>>player2.c;

game_history<<"\n \n"<<player1.name<<" VS "<<player2.name;

clrscr();

/* initialising graphics */
int gd = DETECT,gm,choice;
initgraph(&gd,&gm,"C:\\TC\\BGI");
xmax = getmaxx(); ymax = getmaxy();
player1.x = 75;
player1.theta = 45;
player2.x = xmax-200;
player2.theta = 135;
environment();
tank(player1.x,player1.c,player1.theta);	// constructing tank for player 1
getch();
tank(player2.x,player2.c,player2.theta);	// constructing tank for player 2
getch();
display_d(player1,'1');
display_d(player2,'2');
instructions();

int stest;
char l='1';
for(int i=1;i<=10;i++,l++){
	game_history<<"\n\nVOLLEY "<<i;
	label1:
	d_volley(i,l);
	environment();
	setcolor(BLACK);
	outtextxy(5,ymax-195,"Player1's Turn (Press Number)");
	cin>>choice;
	if(choice==0)
		fire(player1,player2,'1');
	else if(choice==1||choice==2||choice==3||choice==4){
		stest = modify(choice,player1,player2);
		if(stest){
			outtextxy(5,ymax-12,"MODIFICATION SUCCESSFUL!");
			setfillstyle(SOLID_FILL,BLACK);
			bar(player1.x-40,ymax-270,player1.x+40,ymax-200);
			tank(player1.x,player1.c,player1.theta);
		}
		else{
			outtextxy(5,ymax-12,"MODIFICATION UNSUCCESSFUL!");
		}
		delay(2000);
		display_d(player1,'1');
		goto label1;
		}

	else{
		outtextxy(5,ymax-185,"WRONG CHOICE");
		delay(2000);
		goto label1;
	}
	display_d(player1,'1');
	d_volley(i,l);
	game_history<<'\n'<<player1.name;
	game_history<<'\n'<<"ANGLE : "<<player1.theta;
	game_history<<'\n'<<"VELOCITY : "<<player1.v;
	game_history<<'\n'<<"BOMB : "<<player1.bomb;
	game_history<<'\n'<<"POINTS : "<<player1.points;

	label2:
	environment();
	setcolor(BLACK);
	outtextxy(5,ymax-195,"Player2's Turn (Press Number)");
	cin>>choice;
	if(choice==0)
		fire(player2,player1,'2');
	else if(choice==1||choice==2||choice==3||choice==4){
		stest = modify(choice,player2,player1);
		if(stest){
			outtextxy(5,ymax-12,"MODIFICATION SUCCESSFUL!");
			setfillstyle(SOLID_FILL,BLACK);
			bar(player2.x-60,ymax-270,player2.x+40,ymax-200);
			tank(player2.x,player2.c,player2.theta);
		}
		else{
			outtextxy(5,ymax-12,"MODIFICATION UNSUCCESSFUL!");
		}
		delay(2000);
		display_d(player2,'2');
		goto label2;
	}
	else{
		outtextxy(5,ymax-185,"WRONG CHOICE");
		delay(2000);
		goto label2;
	}
	display_d(player2,'2');
	game_history<<'\n\n'<<player2.name;
	game_history<<'\n'<<"ANGLE : "<<player2.theta;
	game_history<<'\n'<<"VELOCITY : "<<player2.v;
	game_history<<'\n'<<"BOMB : "<<player2.bomb;
	game_history<<'\n'<<"POINTS : "<<player2.points;
	}


if(player1.points>player2.points){
	outtextxy(xmax*0.5,ymax*0.5-50,player1.name);
	outtextxy(xmax*0.5,ymax*0.5-40,"WINS");
	game_history<<'\n'<<player1.name<<" WON";
}
else if(player2.points>player1.points){
	outtextxy(xmax*0.5,ymax*0.5-50,player2.name);
	outtextxy(xmax*0.5,ymax*0.5-40,"WINS");
	game_history<<'\n'<<player2.name<<" WON";
}
else{
	outtextxy(xmax*0.5,ymax*0.5-50,"ITS A TIE!");
	game_history<<"IT WAS A TIE";
}
getch();
closegraph();	


}