#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

class player{
private:
	char name[30];
public:
	int x;  //Tank coordinates
	int c;	//Color of tank.
	float theta;  //Angle of projection
	int v; //Velocity of projection
	int move; //Moves left
	int bomb; //Bomb strength
	int points; 
};

void environment(){
	int gd = DETECT,gm;
	void initgraph(&gd,&gm,"");
	setcolor(BROWN);
	bar(0,ymax-200,xmax,ymax);
}

void tank (int x,int c,float theta){
	int ymax=getmaxy();
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
	setcolor(c);
	setfillstyle(SOLID_FILL,c);
	bar(x-24,ymax-230,x+24,ymax-216);
	arc(x,ymax-230,0,180,12); //Radius of dome is 12 pixels.
	floodfill(x,ymax-236,c);
	setcolor(CYAN);				//theta is angle of projection.
	line(x+6,ymax-230,x+6+34*cos(theta),ymax-230-34*sin(theta)); //Thick Line
	line(x+6,ymax-229,x+6+34*cos(theta),ymax-229-34*sin(theta));
	setcolor(YELLOW);
	line(x-24,ymax-216,x+24,ymax-216);
}



void fire(player pl){
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,LIGHTMAGENTA);
	int x1=x2=pl.x+6+cos(pl.theta),y1=y2=ymax-230-sin(pl.theta),count=0,vx=(pl.v)*cos(pl.theta),vy=(pl.v)*sin(pl.theta);
	for(;y<=ymax-200;x1=x2+vx*count*0.1,y1=y2+vy*count*0.1+0.5*(-10)*count*count*0.01){
	++count;
	circle(x1,y1,7); //Radius of bomb is 7 pixels.
	floodfill((int)x1,(int)y1,BLACK);
	delay(100);
	}
}


void explode(int x1,int y1){
	int w=720; //Angular velocity
	int r=5,count=0; 
	int vr=284;  //Rate of change of radius.
	for(;count*0.1<=2;){
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
    delay(100);
	count++;
	}
	
}

void point(player pl,int x1,int y1){   //player pl is the one who has been atatcked.
	if(abs(pl.x-x1)>100)
		//no INCREMENT in points.
	else
			
	
 
}
























