#define  F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "Buzzer.h"
#include "Button.h"
#include "EXT_Interrupt.h"
#include "Keypad.h"
#include "LCD.h"
#include "LED.h"
#include "Relay.h"
#include "Timer.h"
#include "UART.h"
#include "DC_Motor.h"
#include "EEPROM.h"
#include "servoo.h"
#include "App.h"
#include "ALARM.h"
#define D 1000
#include <avr/io.h>
extern Uint8 Var;
Uint8 Page=0;
Uint8 Counter_User_Name =0;
Uint8 Counter_Password=0;
Uint8 Counter_User_Name_Keypad=0;
Uint8 Counter_Password_Keypad=0;
Uint8 Flag_Lamp=0;     //Flag to know if the lamp is on or off
Uint8 Flag_Lamp_2=0;  //Flag to know if the lamp is on or off
Uint8 Flag_Lamp_3=0; //Flag to know if the lamp is on or off
Uint8 Flag_Lamp_4=0; //Flag to know if the lamp is on or off
Uint8 Login=0; // Flag to know if any login is happened
Uint8 Admin_login=0; // Flag to know if the admin is logged in 
Uint8 Check_UART_Option=0; // Flag to make sure that user will choose appropriate choice
Uint8 Flag_Dimmer=0; // Flag to know if Dimmer circuit is on or off
int main(void)
{
	sei();
	/*Initialization*/
	LCD_Init();
	Keypad_Init();
	EEPROM_INIT();
	UART_Init();
	LCD_Init();
	Init_Button(PORTD,PIN_2);
	Keypad_Init();
	INT0_Init();
	Servo_INIT();
	LED0_Init();
	LED1_Init();
	LED2_Init();
	LED3_Init();
	LED4_Init();
	Buzzer_Init();
	DC_Motor1_INIT();
	ADC_Init();
	Timer0_Init();
	Timer0_Start();
	/*Declaring Variables*/
	Uint8 User_Name[4]={0};
	Uint8 Password[4]={0};
	Uint8 User_Name_PC[4]={0};
	Uint8 Password_PC[4]={0};
	Uint8 Counter_Alarm=3;
	Uint8 VAR1=0;
	Uint8 USER_NAME[4]={0};
	Uint8 User_User_Name[4]={0};
	Uint8 User_Password[4]={0};
		
		/*
		Uart Admin Pass: 5555
		Uart User Name :4444
		Uart User Pass:4444

		Lcd Admin Pass: 8888
		Lcd User Name:6666
		Lcd User Pass:6666
		
		*/
		// These the database saved 
	
	Uint8 Check=0;
	//EEPROM_Reset(); // If you want to start the program & reassign the values of user name and password by reseting the data on the EEPROM
	
	
	/*-------------------------->Checking the EEPROM<--------------------------*/
	
	/*check the EEPROM to get the saved data and check if the program start for the first time or not */
	/*Check for counter of user name and get its value to continue on it because every time program start and end it re assign the value of counter to zero*/
	
	if ((EEPROM_ReadByte(7,0)!=0XFF))  // Counter Username For PC
	{
		Counter_User_Name= EEPROM_ReadByte(7,0);
		Counter_User_Name++;
		
	}
	else
	{
		Counter_User_Name=0;
	}
	if ((EEPROM_ReadByte(7,1)!=0XFF)) // Counter Password For PC
	{
		Counter_Password= EEPROM_ReadByte(7,1);
		Counter_Password++;
	}
	else
	{
		Counter_Password=0;
	}
	if((EEPROM_ReadByte(5,1)!=0XFF))
	{
		Counter_Password_Keypad= EEPROM_ReadByte(5,1);
		Counter_Password_Keypad++;
	}
	else
	{
		Counter_Password_Keypad=0;
	}
	if((EEPROM_ReadByte(5,0)!=0XFF))
	{
		Counter_User_Name_Keypad= EEPROM_ReadByte(5,0);
		Counter_User_Name_Keypad++;
	}
	else
	{
		Counter_User_Name_Keypad=0;
	}
	
	/*-------------------------------------------------------------------------------------------------------------------------*/
	
	
   /* send a message to user to inform him how to use the LCD Mode */
	LCD_Init();
	LCD_Clear();
	LCD_Write_String("Press button to");
	LCD_Goto(1,0);
	LCD_Write_String("start LCD Mode");
	/*------------------------------------------------------------*/
		
	/*-------------------------->UART Programing<--------------------------*/
	
	
	UART_TX_Str("Welcome To Home System\r\n");
	/*Check the the address Of Admin Password if it assigned to 255 "Factory mode"  
	* so if it not equal to 255 so it used before and user assigned a value to admin password
	*/
	if((EEPROM_ReadByte(6,0))==255)
	{
		/*Logging In for first time*/
		UART_TX_Str("Login For First Time\r\n");   
		_delay_ms(500);
		UART_TX_Str("Set Admin Password\r\n"); // Get a new Admin Password from user
		_delay_ms(500);
		UART_TX_Str("Admin Password\r\n");
		/*Setting Admin password*/
		
		/*Admin Password consists of 4 Digits get them from user and save it in array that i pass every element of the array
		* to  a specific address in the EEPROM page 6
		*/
		Uint8 Admin_Pass[4]={0};
		for(Uint8 i=0 ;i<4;i++)
		{
			
			while (!Get_Bit(UCSRA,7));
			Admin_Pass[i]=UART_RX_Char();
			EEPROM_WriteByte(6,i,Admin_Pass[i]);
			
		}
		_delay_ms(500);
		UART_TX_Str("\r\n");
		UART_TX_Str("Password Saved\r\n");
	}
	/*------------------------------------------------------------------------*/
	else
	{
		
		while (!Check_UART_Option) // While Loop to make sure that the user will choose the right input 
		{
			
			Check_UART_Option=1; // Flag that will change in default  if the user choose wrong input 
			/*Interfacing*/
			UART_TX_Str("Login System\r\n");
			UART_TX_Str("\r\n");
			_delay_ms(500);
			UART_TX_Str("1. Admin\r\n");
			_delay_ms(500);
			UART_TX_Str("2. Guest\r\n");
			_delay_ms(500);
			UART_TX_Str("Please Enter Your Mode Number\r\n");
			UART_RX_Char();
			while (!Get_Bit(UCSRA,7));
			/*----------------------------------------------*/
			
			
			
			Uint8 Var_Login=UDR;// get data from user that is sent to UDR Register 
			
			switch (Var_Login) // Switch over the value IF it 1 or 2
			{
				/*----------------->Admin Login<-----------------*/
				/*only one Admin and use only password to log in*/
				case '1':
				{
					Counter_Alarm=3; // Flag that control the alarm if user enter password 3 times wrong alarm will turn on
					Uint8 Flag_Admin_pass_PC[4]={0}; // Array will have the input password from user to compare it with EEPROM
					do
					{
						UART_TX_Str("\r\n");
						UART_TX_Str("Admin Pass\r\n");
						for(Uint8 i=0 ;i<4;i++)
						{
							while (!Get_Bit(UCSRA,7)); // waiting until user enter a digit
							Flag_Admin_pass_PC[i]=UART_RX_Char();
						}
						/* check by comparing every element in the array with every byte in EEPROM 
						* by using if Condition and logical And
						* if all is true so it enter if condition and will display login 
						*if any digit is wrong it will enter else and decrease alarm by 1 and it will start take the password again
						*/
						if (Flag_Admin_pass_PC[0]== EEPROM_ReadByte(6,0) && Flag_Admin_pass_PC[1]== EEPROM_ReadByte(6,1) && Flag_Admin_pass_PC[2]== EEPROM_ReadByte(6,2) && Flag_Admin_pass_PC[3]== EEPROM_ReadByte(6,3))
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("Logged In\r\n");
							Admin_login=1;
							Counter_Alarm=0; // To break the while loop
						}
						else
						{
							Counter_Alarm--; //Decrement of alarm counter
							UART_TX_Str("\r\n");
							UART_TX_Str("Invalid pass\r\n");
							UART_TX_Str("Please Try again\r\n");
							if (Counter_Alarm==0)
							{
								//Alarm
								while (1)
								{
									ALARM_ON();
								}
								
							}
							UART_TX_Char(Counter_Alarm);
							
						}
						
						
					} while (Counter_Alarm); // the while loop which make the user enter the password again if it is wrong by checking the counter alarm
				break;} //End Of Case 1
				/*----------------->USER Login<-----------------*/
				/*Users Added by Admin and log in with username and password*/
				case '2':
				{
					/*the same as admin log in except checking for username*/
					Counter_Alarm=3;
					do{
						UART_TX_Str("\r\n");
						UART_TX_Str("Username\r\n");
						for(Uint8 i=0 ;i<4;i++)
						{
							while (!Get_Bit(UCSRA,7));
							User_User_Name[i]=UART_RX_Char();
						}//End Of For Loop
						UART_TX_Str("\r\n");
						UART_TX_Str("Password\r\n");
						
						for(Uint8 i=0 ;i<4;i++)
						{
							while (!Get_Bit(UCSRA,7));
							User_Password[i]=UART_RX_Char();
						}//End Of For Loop
						/*Check For Username & Password*/
						/*
						1- checking for username which is consists of 4 digits if it found ---> if condition to check password
						2- if not found display wrong user name
						3- if username is correct but password is not correct it will display incorrect password and have 3 trials
						if exceeds the 3 trials so alarm will on
						*/
						
						for (Uint8 i=0; i<=Counter_User_Name;i++) // loop to chrck the whole page addresses
						{
							if((User_User_Name[0]== EEPROM_ReadByte(Page_User_Name,i)) && (User_User_Name[1]== EEPROM_ReadByte(Page_User_Name,i+1)) && (User_User_Name[2]== EEPROM_ReadByte(Page_User_Name,i+2)) && (User_User_Name[3]== EEPROM_ReadByte(Page_User_Name,i+3)))// If Condition For checking Username
							{
								if ((User_Password[0]==EEPROM_ReadByte(Page_Password,i)) && (User_Password[1]==EEPROM_ReadByte(Page_Password,i+1)) && (User_Password[2]==EEPROM_ReadByte(Page_Password,i+2)) && (User_Password[3]==EEPROM_ReadByte(Page_Password,i+3)))// If Condition For checking password
								{
									UART_TX_Str("\r\n");
									UART_TX_Str("Logged In\r\n");
									//_delay_ms(5000);
									Counter_Alarm=0;
									break;
									//_delay_ms(5000);
								}//End Of If Condition Of Checking Password
								
								else
								{
									Counter_Alarm--;
									UART_TX_Str("\r\n");
									UART_TX_Str("Invalid pass\r\n");
									UART_TX_Str("Number of trials left\r\n");
									if (Counter_Alarm==0)
									{
										while (1)
										{
											ALARM_ON(); // a pattern of leds and buzzer
										}
										
									}
									UART_TX_Char(Counter_Alarm);
								}// Else For Wrong Password
							}//End Of If Condition Of User
							
						}//End Of For Loop
						if (Counter_Alarm==3)//Condition Of Wrong UserName
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("Wrong Username\r\n");
						}//End Of If Condition (Checking for wrong user name)
					}while(Counter_Alarm);
					
				break;	}// End Of Case 2
				default:
				{
					UART_TX_Str("\r\n");
					UART_TX_Str("Wrong Input Please Try Again\r\n");
					Check_UART_Option=0;
					break;
				}
				
			}// End Of switch Case
			
		}
		
		/*End Of login UART System*/
		/*---------------------------------------------------------------------------------------------------------------------------------------*/	
	}

		//ADC_Read(ADC_PIN7); // Checking the Tempreture sensor
		/*there is a problem i tried hard to solve it but i cant it stack in adc interrupt 
		* but i have meeting on Monday with an instructor trying to solve this problem
		*/
	
	while (1)
	{
		 /*-------------------->UART Controlling System<--------------------*/
		 
		 /*
		 *1- Control all Home (Lamps , Door)
		 *2- Check all status of home 
		 *3- Add an User (Can be created by Admin and user of UART only)
		 *4- Delete User (Can be Deleted by Admin and user of UART only) 
		 */
			UART_TX_Str("\r\n");
			UART_TX_Str("1. Control Home System\r\n");
			UART_TX_Str("2. Check Status Of Home \r\n");
			UART_TX_Str("3. Add User\r\n");
			UART_TX_Str("4. Delete User\r\n");
			_delay_ms(100);
			UART_TX_Str("Enter Your Command Number\r\n");
			UART_RX_Char();
			while (!Get_Bit(UCSRA,7));
			
		
		
		Uint8 Var_status=UDR;
		switch (Var_status)
		{
			/*------------------------------------------>HOME SYSTEM<------------------------------------------*/
			case'1':
			{
				UART_TX_Str("\r\n");
				UART_TX_Str("1. Open Door\r\n");
				_delay_ms(100);
				UART_TX_Str("2. Close The Door \r\n");
				_delay_ms(100);
				UART_TX_Str("3. Room 1\r\n");
				_delay_ms(100);
				UART_TX_Str("4. Room 2\r\n");
				_delay_ms(100);
				UART_TX_Str("5. Reception\r\n");
				_delay_ms(100);
				UART_TX_Str("6. Master Room\r\n");
				_delay_ms(100);
				UART_TX_Str("Enter Your Command Number\r\n");
				while (!Get_Bit(UCSRA,7));
				Uint8 VAR=UDR;
				switch (VAR)
				{
					case '1':
					{
						UART_TX_Str("\r\n");
						Servo_Open();
						_delay_ms(200);
						UART_TX_Str("Door Opened\r\n");
						break;
					}//End of Case 1
					case '2':
					{
						UART_TX_Str("\r\n");
						Servo_Close();
						_delay_ms(200);
						UART_TX_Str("Door Closed\r\n");
						break;
					}// End of case 2
					case  '3': //Room 1
					{
						UART_TX_Str("\r\n");
						UART_TX_Str(" 1. Turn On Lamp\r\n");
						_delay_ms(200);
						UART_TX_Str(" 2. Turn Off Lamp\r\n");
						while (!Get_Bit(UCSRA,7));
						switch (UDR)
						{
							case '1':
							{
								if (Flag_Lamp==0)
								{
									UART_TX_Str("\r\n");
									LED0_ON();
									Flag_Lamp=1;
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched On\r\n");
								}
								else
								{
									UART_TX_Str(" The Lamp Is already On\r\n");
								}//End Of else
								break;
								
							}// END Of Case 1
							case '2':
							{
								UART_TX_Str("\r\n");
								if (Flag_Lamp==1)
								{
									LED0_OFF();
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched Off\r\n");
									Flag_Lamp=0;
								}//End Of iF Condition
								else
								{
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Already Off\r\n");
								}//End of else
								break;
							}//End Of case 2
							default:
							{
								UART_TX_Str("Wrong Input\r\n");
							}
						}//End OF Switch case
						
						break;
					}//End Of Case 3
					case '4' : //Room 2
					{
						UART_TX_Str("\r\n");
						UART_TX_Str(" 1. Turn On Lamp\r\n");
						_delay_ms(200);
						UART_TX_Str(" 2. Turn off Lamp\r\n");
						while (!Get_Bit(UCSRA,7));
						switch (UDR)
						{
							case '1':
							{
								if ( Flag_Lamp_2 ==0)
								{
									LED1_ON();
									Flag_Lamp_2=1;
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched On\r\n");
								}
								else
								{
									UART_TX_Str(" The Lamp Is already On\r\n");
								}//End Of Else
								break;
							}// END Of Case 1
							case '2' :
							{
								UART_TX_Str("\r\n");
								if (Flag_Lamp_2==1)
								{
									LED0_OFF();
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched Off\r\n");
									Flag_Lamp_2=0;
								}//End Of iF Condition
								else
								{
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Already Off\r\n");
								}//End of else
								break;
							}//End Of case 2
							default:
							{
								UART_TX_Str("Wrong Input\r\n");
								break;
							}
						}//End OF Switch case
						break;
					}//End Of Case 4
					case '5': //Reception
					{
						UART_TX_Str("\r\n");
						UART_TX_Str(" 1. Turn On Lamp\r\n");
						_delay_ms(200);
						UART_TX_Str(" 2. Turn off Lamp\r\n");
						while (!Get_Bit(UCSRA,7));
						switch (UDR)
						{
							case '1':
							{
								if (Flag_Lamp_3==0)
								{
									LED2_ON();
									Flag_Lamp_3=1;
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched On\r\n");
								}
								else
								{
									UART_TX_Str(" The Lamp Is already On\r\n");
								}//End Of Else
								break;
							}// END Of Case 1
							case '2' :
							{
								UART_TX_Str("\r\n");
								if (Flag_Lamp_3==1)
								{
									LED2_OFF();
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched Off\r\n");
									Flag_Lamp_3=0;
								}//End Of iF Condition
								else
								{
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Already Off\r\n");
								}//End of else
								break;
							}//End Of case 2
							default:
							{
								UART_TX_Str("Wrong Input\r\n");
								break;
							}
						}//End OF Switch case
						break;
					}//End Of Case 5
					case '6': //Master Room
					{
						UART_TX_Str("\r\n");
						UART_TX_Str(" 1. Turn On Lamp\r\n");
						_delay_ms(200);
						UART_TX_Str(" 2. Turn off Lamp\r\n");
						_delay_ms(200);
						UART_TX_Str(" 3. Dimmer Lamp\r\n");
						while (!Get_Bit(UCSRA,7));
						switch (UDR)
						{
							case '1':
							{
								if (Flag_Lamp_4==0)
								{
									LED3_ON();
									Flag_Lamp_4=1;
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched On\r\n");
								}
								else
								{
									UART_TX_Str(" The Lamp Is already On\r\n");
								}//End Of else
								break;
							}// END Of Case 1
							case '2' :
							{
								UART_TX_Str("\r\n");
								if (Flag_Lamp_4==1)
								{
									LED3_OFF();
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Switched Off\r\n");
									Flag_Lamp_4=0;
								}//End Of iF Condition
								else
								{
									UART_TX_Str("\r\n");
									UART_TX_Str(" The Lamp Is Already Off\r\n");
								}//End of else
								break;
							}//End Of case 2
							case '3':
							{
								Uint8 Check=0;
								
								Timer0_Init();
								UART_TX_Str("Dimmer lamp\r\n");
								UART_TX_Str("Choose the suitable intensity\r\n");
								UART_TX_Str("1- Very Low\r\n");
								UART_TX_Str("2- Low\r\n");
								UART_TX_Str("3- Medium\r\n");
								UART_TX_Str("4- High\r\n");
								UART_TX_Str("5- Very High\r\n");
								UART_TX_Str("6- turn off\r\n");
								
								while (!Get_Bit(UCSRA,7));
								
								while (!Check)
								{
									
									Check=1;
									switch(UDR)
									{
										
										case '1':
										{
											Flag_Dimmer=1;
											PWM0_Gen(20);
											break;
										}//End Of case 1
										case '2':
										{
											Flag_Dimmer=1;
											PWM0_Gen(40);
											break;
										}//End Of case 2
										case '3':
										{
											Flag_Dimmer=1;
											PWM0_Gen(60);
											break;
										}//End Of case 3
										case '4':
										{
											Flag_Dimmer=1;
											PWM0_Gen(80);
											break;
										}//End Of case 4
										case '5':
										{
											Flag_Dimmer=1;
											PWM0_Gen(100);
											break;
										}//End Of case 5
										case '6':
										{
											if (Flag_Dimmer==0)
											{
												UART_TX_Str("Dimmer lamp is off\r\n");
											}
											else
											{
												PWM0_Gen(0);
											}
											
											break;
										}//End Of case 6
										default:
										{
											Check=0;
											UART_TX_Str("Wrong Input\r\n");
											
										}
										
										
									}// End Of Switch case
									
								}//End of while loop
								//Code for Dimmer Circuit
							}//End Of Case 3
						
						}//End OF Switch case
							
						break;
					}//End Of Case 6
					default:
					{
						UART_TX_Str("Wrong Input\r\n");
						break;
					}
					break;
					break;
				}//End Of Case 1
			break;}
			
			/*Function Control System  */
			case '2': // Check For System
			{
				UART_TX_Str("\r\n");
				UART_TX_Str("1. Room 1\r\n");
				_delay_ms(100);
				UART_TX_Str("2. Room 2\r\n");
				_delay_ms(100);
				UART_TX_Str("3. Reception\r\n");
				_delay_ms(100);
				UART_TX_Str("4. Master Room\r\n");
				_delay_ms(100);
				UART_TX_Str("5. Check The Temperature\r\n");
				UART_TX_Str("Enter Your Command Number\r\n");
				while (!Get_Bit(UCSRA,7));
				switch (UDR)
				{
					case '1': //Room 1
					{
						if (Flag_Lamp ==1)
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is On In Room 1\r\n");
						}//End Of If Condition
						else
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is off In Room 1\r\n");
						}//End Of else Condition
						break;
					}//End OF case 1
					case '2': //Room 2
					{
						if (Flag_Lamp_2 ==1)
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is On In Room 2\r\n");
						}//End Of If Condition
						else
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is off In Room 2\r\n");
						}//End Of else Condition
						break;
					}//End Of case 2
					case '3': //Reception
					{
						if (Flag_Lamp_3 ==1)
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is On In The Reception\r\n");
						}//End Of If Condition
						else
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is off In Reception\r\n");
						}//End Of else Condition
						break;
					}//End Of Case 3
					case'4': //Master Room
					{
						if (Flag_Lamp_4 ==1)
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is On In Master Room \r\n");
						}//End Of If Condition
						else
						{
							UART_TX_Str("\r\n");
							UART_TX_Str("The Lamp Is off In Master Room \r\n");
						}//End Of else Condition
						break;
					}//End of case 4
					default:
					{
						UART_TX_Str("Wrong Input\r\n");
						break;
					}
				}//End OF Switch Case
				break;
			}//End Of case 2
			/*-----------------------------------------------------------------------------------------------*/
			
			/*------------------------------------------>ADD USER<------------------------------------------*/
			case '3': //Add User
			{
				UART_TX_Str("\r\n");
				UART_TX_Str("1. Keypad\r\n"); // USER for LCD Mode (Can login only from Keypad)
				UART_TX_Str("2. PC\r\n"); // USER for UART Mode (Can login only from UART)
				UART_RX_Char();
				while (!Get_Bit(UCSRA,7));
				Uint8 Var_1=UDR;
				switch (Var_1)
				{
					case '1':
					UART_TX_Str("\r\n");
					UART_TX_Str("Enter Username \r\n");
					for(Uint8 i=0 ;i<4;i++)//for LOOP itriate 4 times to get four digits
					{
						while (!Get_Bit(UCSRA,7)); // waiting for an input from user 
						User_Name[i]=UART_RX_Char();
						EEPROM_WriteByte(Page_User_Name_KeyPad,Counter_User_Name_Keypad,User_Name[i]); //save every element of the array to EEPROM
						Counter_User_Name_Keypad++; // Increment the counter
					}
					EEPROM_WriteByte(5,0,Counter_User_Name_Keypad); // save the new value of the counter in EEPROM
					UART_TX_Str("\r\n"); 
					
					UART_TX_Str("Enter The Password :\r\n");
					for(Uint8 i=0 ;i<4;i++) //for LOOP itriate 4 times to get four digits
					{
						while (!Get_Bit(UCSRA,7)); // waiting for an input from user 
						Password[i]=UART_RX_Char();
						EEPROM_WriteByte(Page_Password_KeyPad,Counter_Password_Keypad,Password[i]);//save every element of the array to EEPROM
						Counter_Password_Keypad++;// Increment the counter
						
						
					}
					EEPROM_WriteByte(5,1,Counter_Password_Keypad);// save the new value of the counter in EEPROM
					
					UART_TX_Str("\r\n");
					UART_TX_Str("Successfully Added\r\n"); // display a message
					_delay_ms(500);
					break;
					case '2':
					UART_TX_Str("\r\n");
					UART_TX_Str("Enter Username \r\n");
					for(Uint8 i=0 ;i<4;i++)//for LOOP itriate 4 times to get four digits
					{
						while (!Get_Bit(UCSRA,7));// waiting for an input from user 
						User_Name_PC[i]=UART_RX_Char();
						EEPROM_WriteByte(Page_User_Name,Counter_User_Name,User_Name_PC[i]);//save every element of the array to EEPROM
						Counter_User_Name++;// Increment the counter
						
					}
					EEPROM_WriteByte(7,0,Counter_User_Name);// save the new value of the counter in EEPROM
					UART_TX_Str("\r\n");
					
					UART_TX_Str("Enter The Password \r\n");
					for(Uint8 i=0 ;i<4;i++)
					{
						while (!Get_Bit(UCSRA,7));// waiting for an input from user 
						Password_PC[i]=UART_RX_Char();
						EEPROM_WriteByte(Page_Password,Counter_Password,Password_PC[i]);//save every element of the array to EEPROM
						Counter_Password++;// Increment the counter
						
						
					}
					EEPROM_WriteByte(7,1,Counter_Password);
					UART_TX_Str("\r\n");
					UART_TX_Str("Successfully Added\r\n");// save the new value of the counter in EEPROM
					_delay_ms(500);
					break;
					default:
					break;
				}
				break;
				break;
				
			}//End Of Case 3
			/*-----------------------------------------------------------------------------------------------*/
			
			
			/*------------------------------------------>DELETE USER<------------------------------------------*/
			
			case '4': //Delete User
			{
				UART_TX_Str("\r\n");
				UART_TX_Str("1. Keypad\r\n");// Delete User that can login from keypad
				UART_TX_Str("2. PC\r\n");// Delete User that can login from UART
				UART_RX_Char();
				while (!Get_Bit(UCSRA,7));// Waiting for an input
				Uint8 Var_1=UDR;
				Uint8 USER_NAME[4]={0}; // Array will hold the usename that will be deleted
				
				switch(Var_1)
				{
					
					
					case '1':
					{
						UART_TX_Str("\r\n");
						UART_TX_Str("Enter Username :\r\n");
						for(Uint8 i=0 ;i<4;i++)
						{
							while (!Get_Bit(UCSRA,7)); //Waiting for username
							USER_NAME[i]=UART_RX_Char();
						}
						/* search for user name in the EEPROM
						* if it was found it reset the 4 bytes of the username 
						* if was not found it display user is not exists
						*/
						for (Uint8 z=0;z<Counter_User_Name_Keypad;z++)
						{
							if((EEPROM_ReadByte(Page_User_Name_KeyPad,z))== USER_NAME[0]   && (EEPROM_ReadByte(Page_User_Name_KeyPad,z+1))== USER_NAME[1]  && (EEPROM_ReadByte(Page_User_Name_KeyPad,z+2))== USER_NAME[2]  && (EEPROM_ReadByte(Page_User_Name_KeyPad,z+3))== USER_NAME[3])// searching for username
							{
								/*since counter of user = counter password
								 * I can reset the bytes of username and password using only 1 counter 
								*/
								UART_TX_Str("\r\n");
								UART_TX_Str("Found\r\n"); // a message ensure that it found the username in EEPROM
								/* Reseting the bytes of username and password*/
								EEPROM_WriteByte(Page_User_Name_KeyPad,z,255); // reset the first byte of username
								EEPROM_WriteByte(Page_User_Name_KeyPad,z+1,255);// reset the next one byte
								EEPROM_WriteByte(Page_User_Name_KeyPad,z+2,255);// reset the next one byte
								EEPROM_WriteByte(Page_User_Name_KeyPad,z+3,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password_KeyPad,z,255);  // reset the first byte of password
								EEPROM_WriteByte(Page_Password_KeyPad,z+1,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password_KeyPad,z+2,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password_KeyPad,z+3,255);// reset the next one byte
								UART_TX_Str("Deleted\r\n");// a message ensure that it delete the username from EEPROM
								break;
							}
							else
							{
								UART_TX_Str("\r\n");
								UART_TX_Str("User is not exist\r\n");// a message ensure that username is not exist in EEPROM
								break;
							}
						}
						break;
					}
					case'2':
					{
						UART_TX_Str("\r\n");
						UART_TX_Str("Enter Username :\r\n");
						for(Uint8 i=0 ;i<4;i++)
						{
							while (!Get_Bit(UCSRA,7));// Waiting for an input
							USER_NAME[i]=UART_RX_Char();
						}
						/* search for user name in the EEPROM
						* if it was found it reset the 4 bytes of the username 
						* if was not found it display user is not exists
						*/
						for (Uint8 z=0;z<Counter_User_Name;z++)
						{
							if((EEPROM_ReadByte(Page_User_Name,z))== USER_NAME[0]   && (EEPROM_ReadByte(Page_User_Name,z+1))== USER_NAME[1]  && (EEPROM_ReadByte(Page_User_Name,z+2))== USER_NAME[2]  && (EEPROM_ReadByte(Page_User_Name,z+3))== USER_NAME[3])//Searching for Username
							{
								/*since counter of user = counter password
								 * I can reset the bytes of username and password using only 1 counter 
								*/
								UART_TX_Str("\r\n");
								UART_TX_Str("Found\r\n");// a message ensure that it found the username in EEPROM
								/* Reseting the bytes of username and password*/
								EEPROM_WriteByte(Page_User_Name,z,255);// reset the first byte of username
								EEPROM_WriteByte(Page_User_Name,z+1,255);// reset the next one byte
								EEPROM_WriteByte(Page_User_Name,z+2,255);// reset the next one byte
								EEPROM_WriteByte(Page_User_Name,z+3,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password,z,255);// reset the first byte of password
								EEPROM_WriteByte(Page_Password,z+1,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password,z+2,255);// reset the next one byte
								EEPROM_WriteByte(Page_Password,z+3,255);// reset the next one byte
								UART_TX_Str("Deleted\r\n");// a message ensure that it delete the username from EEPROM
								/*---------------------------------------------------------*/
								break;
							}
							else
							{
								UART_TX_Str("\r\n");
								UART_TX_Str("User is not exist\r\n");// a message ensure that username is not exist in EEPROM
								break;
							}
						}
						break;
					}
					default:
					break;
				}
				break;
			}
			default:
			{
				UART_TX_Str("Wrong input\r\n");
			}
			break;
			
		}
		
		/*--------------------------------------------------------------------------------------------------*/
	}//while 1
	
	
}// End Of Switch Case (General)







