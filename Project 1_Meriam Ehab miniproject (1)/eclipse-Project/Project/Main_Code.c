/*
 * Main_Code.c
 *
 *  Created on: Aug 25, 2022
 *      Author: Meriam Ehab
 */

#include <stdio.h>
#include "Prototype.h"

#define ON 1
#define OFF 0

struct structure
{
	int engine_state;
	int ac_state;
	float room_temp;
	int engine_controller_state;
	float engine_temp;
	int vehicle_speed;

}vehicle;

struct structure *ptr=&vehicle;

int main (void)
{
	setvbuf (stdout, NULL,_IONBF,0);
	setvbuf (stderr, NULL,_IONBF,0);
    menu(&ptr->engine_state);
    return 0;
}

////////////////////////////////////////////////////////////

// First menu will be displaced on the screen
void menu (int *state)
{
	char ch;
		int count = 0;
		do{
			if(count == 0 ){
				printf ("Please choose: \n "
						"a:Turn on the vehicle engine \n"
						" b:Turn off the vehicle engine \n"
						" c:Quit the engine \n");
				count++;
				scanf (" %c",&ch);
			}

			switch (ch)
			{
			case 'a':
				printf ("Turn on the vehicle engine \n");
				*state=ON;
				sensors_set_menu ();
				display_vehicle_state (&ptr->engine_state, &ptr->vehicle_speed, &ptr->ac_state,&ptr->engine_controller_state, &ptr->room_temp, &ptr->engine_temp);
				printf ("\n");
			//	sensors_set_menu ();
				break;
			case 'b':
				printf ("Turn off the vehicle engine \n");
				*state=OFF;
				count = 0;
				break;
			case 'c':
				printf ("Quit the engine \n");
				exit(0);
				break;
			}
		} while (ch != 'c');
}

////////////////////////////////////////////////////////////

// Menu that would be printed in case: a
void sensors_set_menu()
{
	char ch;
	printf ("a: Turn off the engine \n"
			"b: Set the traffic light color \n"
			"c: Set the room temperature (Temperature Sensor) \n"
			"d: Set the engine temperature (Engine Temperature Sensor) \n ");
	scanf (" %c", &ch);
	switch (ch)
	{
	    case 'a':
			printf ("Turn on the vehicle engine \n");
			menu (&ptr->engine_state);
			break;
		case 'b':
			traffic_light(&ptr->vehicle_speed,&ptr->ac_state,&ptr->engine_controller_state,&ptr->room_temp, &ptr->engine_temp);
			break;
		case 'c':
			room_tem(&ptr->room_temp,&ptr->ac_state);
			break;
		case 'd':
			engine_tem(& ptr->engine_temp,& ptr->engine_controller_state);
			break;
	}

}

////////////////////////////////////////////////////////////

// Menu that would be printed in case: b in sensors menu

void traffic_light (int *speed0, int *state11, int *state22,float *temp11, float *temp22)
{
	char c;
	printf ("Enter the required traffic color: \n");
	scanf (" %c" ,&c);
	switch (c)
		{
		    case 'g':
				*speed0=100;
				break;
			case 'o':
				*speed0=30;
				break;
			case 'r':
				*speed0=0;
				break;
		}
	if (*speed0==30)
	{
		*state11=ON;
		*state22=ON;
		*temp11=(*temp11)* ((5/4)+1);
		*temp22=(*temp22)* ((5/4)+1);
	}
}

////////////////////////////////////////////////////////////

// Menu that would be printed in case: c in sensors menu

void room_tem(float *r_temp,int *AC)
{
	printf ("Plz enter the required room temperature: ");
	scanf ("%f" , r_temp);
	if (*r_temp<10)
	{
		*AC=ON;
		*r_temp=20;
	}
	else if (*r_temp>30)
		{
			*AC=ON;
			*r_temp=20;
		}
	else
	{
		*AC=OFF;
		*r_temp=0;
	}
}

////////////////////////////////////////////////////////////

// Menu that would be printed in case: d in sensors menu

void engine_tem(float *e_temp,int *e_con)
{
	printf ("Plz enter the required engine temperature: ");
	scanf ("%f" , e_temp);
	if (*e_temp<100)
	{
		*e_con=ON;
		*e_temp=125;
	}
	else if (*e_temp>150)
		{
			*e_con=ON;
			*e_temp=125;
		}
	else
	{
		*e_con=OFF;
		*e_temp=0;
	}
}

void display_vehicle_state (int *state, int *speed, int *state1, int *state2,float *temp1, float *temp2)
{
	if (*state==ON)
	{
		printf ("Engine State: ON \n");
	}
	if (*state==OFF)
	{
		printf ("Engine State: OFF \n");
	}

	printf ("vehicle speed is %d km/hr \n", *speed);

	if (*state1==ON)
	{
		printf ("AC State: ON \n");
	}
	if (*state1==OFF)
	{
		printf ("AC State: OFF \n");
	}
	if (*state2==ON)
	{
		printf ("Engine Controller State: ON \n");
	}
	if (*state2==OFF)
	{
		printf ("Engine Controller State: OFF \n");
	}

	printf ("room temperature is %f \n", *temp1);
	printf ("Engine temperature is %f \n" , *temp2);
}

