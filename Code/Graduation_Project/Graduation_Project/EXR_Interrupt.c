/*
 * EXR_Interrupt.c
 *
 * Created: 9/21/2022 12:28:09 PM
 *  Author: Dell
 */ 
#include "EXT_Interrupt.h"

#define  F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>


extern Uint8 Counter_User_Name_Keypad;
extern Uint8 Counter_Password_Keypad;
extern Uint8 Login;
extern Uint8 Flag_Lamp;
extern Uint8 Flag_Lamp_2;
extern Uint8 Flag_Lamp_3;
extern Uint8 Flag_Lamp_4;
extern Uint8 Admin_login;
extern Uint8 Flag_Dimmer;


void INT0_Init(void)
{
	/*GLobal & Peripherals Enable / Disable*/
	SREG |= Global_INT << 7;
	GICR |= Ext0_INT << 6;
	
	/*INT0 Pin Direction*/
	DIO_SetPin_Dir(DIO_PORTD, PIN_2, PIN_IN);
	
	/*EXT INT0 Trigger*/
	MCUCR |= EXT_INT0_Trigger;
}

void INT1_Init(void)
{
	/*GLobal & Peripherals Enable / Disable*/
	SREG |= Global_INT << 7;
	GICR |= Ext1_INT << 7;
	
	/*INT0 Pin Direction*/
	DIO_SetPin_Dir(DIO_PORTD, PIN_3, PIN_IN);
	
	/*EXT INT0 Trigger*/
	MCUCR |= EXT_INT1_Trigger;
}

void INT2_Init(void)
{
	/*GLobal & Peripherals Enable / Disable*/
	SREG |= Global_INT << 7;
	GICR |= Ext2_INT << 5;
	
	/*INT0 Pin Direction*/
	DIO_SetPin_Dir(DIO_PORTB, PIN_2, PIN_IN);
	
	/*EXT INT0 Trigger*/
	MCUCR |= EXT_INT2_Trigger;
}
void LCD_LogIN_system(void)
/* ---------> Function Descreption<----------*/
/* Function Name: LCD LogIN System
   Function Type: Void To Void Function 
   
   It Takes The input username as numbers from user and the password and starts searching for them
   in the external EEPROM we have 3 scenarios :
   1- the user name and password found in the EEPROM it will make the user able to control the home
   2- the username is correct and the password is wrong so the LCD will Display Invalid and the number of trials left if it gets zero number of Trials
   alarm will start and the user must use reset button to get started 
   3-wrong user name case the LCD will display wrong username only and make the user to re enter the username and password again 
*/
{
/*Initialization*/
LCD_Init();
Keypad_Init();
EEPROM_INIT();
LED0_Init();
LED1_Init();
LED2_Init();
LED3_Init();
LED4_Init();
Timer0_Init();
Servo_INIT();

/*Declaring variables*/
Uint8 Flag_Admin_Pass[4]={0};
Uint8 Flag_Guest_User[4]={0};
Uint8 Flag_Guest_Pass[4]={0};
Uint8 counter_flag_2=3;
Uint8 Button_Flag=NULL_KEYPAD;
Uint8 Flag=0;
Uint8 Deny_var=0;
Uint8 check=0;

extern Uint8 Counter_User_Name;
extern Uint8 Counter_Password;

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




/* Printing Welcome screen */
while(!Deny_var) 
/* Deny Var
* it is a flag will be fired if there is an admin logged in in UART and refused to make an user to enter the system so it will begin again
*/
{
    Button_Flag=NULL_KEYPAD;
	Deny_var=1;
	LCD_Clear();
	LCD_Write_String("Welcome to");

	LCD_Goto(1,0);
	LCD_Write_String("Home System");
	_delay_ms(1000);//Halt the system for the given time in (ms)
	LCD_Clear();
	/*Setting Admin password if not set*/
	//read the state of the the passwords of the admin and guest if both are set or not set
	if(EEPROM_ReadByte(4,0)==255)
	{
		LCD_Write_String("Login For");
		LCD_Goto(1,0);
		LCD_Write_String("First time");
		_delay_ms(1000);
		LCD_Clear();
		LCD_Write_String("Set Admin Pass");
		LCD_Goto(1,0);
		LCD_Write_String("Admin Pass:");
		/*Setting Admin pass*/
		Uint8 Password_Counter=0;
		Uint8 Pass[4]={0};
		for(Uint8 i=0; i<4;)
		{
			Button_Flag=Keypad_GetValue();
			while(Button_Flag!=NULL_KEYPAD)
			{
				Pass[i]=Button_Flag;
				EEPROM_WriteByte(4,i,Pass[i]);
				i++;
				LCD_Write_Char('*');
				Button_Flag=NULL_KEYPAD;
			}
		}
		LCD_Clear();
		LCD_Write_String("Pass Saved");
		Login=1;
		_delay_ms(500);
		LCD_Clear();
	}

	else
	{
		
		if (Login==0)
		{
			
			LCD_Write_String("1. Admin");
			LCD_Goto(1,0);
			LCD_Write_String("2. Guest");
			
			while(Button_Flag==NULL_KEYPAD)
			{
				Button_Flag =Keypad_GetValue();
				Flag =Button_Flag;
			}
			LCD_Clear();
			
			
			
			
			switch(Flag)
			{
				case '1':
				{
					LCD_Clear();
					Uint8 counter_flag=3;
					do{
						LCD_Write_String("admin pass:");
						
						for(Uint8 i=0;i<4;)
						{
							Button_Flag=NULL_KEYPAD;
							Button_Flag=Keypad_GetValue();
							while(Button_Flag != NULL_KEYPAD)
							{
								Flag_Admin_Pass[i]=Button_Flag;
								LCD_Write_Char('*');
								Button_Flag=NULL_KEYPAD;
								i++;
							}
						}
						LCD_Clear();
						if (Flag_Admin_Pass[0]==EEPROM_ReadByte(4,0) && Flag_Admin_Pass[1]==EEPROM_ReadByte(4,1) && Flag_Admin_Pass[2]==EEPROM_ReadByte(4,2) && Flag_Admin_Pass[3]==EEPROM_ReadByte(4,3))
						{
							LCD_Write_String("Logged In");
							_delay_ms(1000);
							Login=1;
							LCD_Clear();
							counter_flag=0;
						}
						else
						{
							counter_flag--;
							LCD_Clear();
							LCD_Write_String("Invalid");
							LCD_Goto(1,0);
							LCD_Write_String("Trials");
							LCD_Goto(1,7);
							LCD_Write_Integer(counter_flag);
							_delay_ms(3000);
							LCD_Clear();
							
							if (counter_flag==0)
							{
								while(1)
								{
									ALARM_ON();
								}
							}
						}
					}while(counter_flag);
					break;
				}
				
				case '2':
				{
					
					// Counter_User_Name_Keypad=8;
					if (Admin_login==1)
					{
						LCD_Init();
						LCD_Write_String("wait for admin");
						LCD_Goto(1,0);
						LCD_Write_String("premision");
						UART_TX_Str("\r\n");
						UART_TX_Str("there is user want to access home system\r\n");
						UART_TX_Str("do you want to let him\r\n");
						UART_TX_Str("1- Yes\r\n");
						UART_TX_Str("2- No\r\n");
						while (!Get_Bit(UCSRA,7));
						Uint8 Var_check=UDR;
						switch (Var_check)													
						{
							case'1':
							{
								LCD_Clear();
								LCD_Write_String("Admin Approved");
								UART_TX_Str("the user Enter the system\r\n");
								break;
							}//End of case 1
							case '2':
							{
								LCD_Clear();
								LCD_Write_String("Admin Denied");
								Deny_var=0;
								
								break;
								
								
							}//End of case 2
								
						}//End of switch case
						
						if (Deny_var==0)
						{
							 Flag=0;
							continue;
						}
					}//End of if condition
					
				
					LCD_Clear();
					LCD_Write_String("Username:");
					do{
						LCD_Clear();
						LCD_Write_String("Username:");
						for(Uint8 i=0;i<4;)
						{
							Button_Flag=NULL_KEYPAD;
							Button_Flag=Keypad_GetValue();
							while(Button_Flag != NULL_KEYPAD)
							{
								Flag_Guest_User[i]=Button_Flag;
								LCD_Write_Char(Flag_Guest_User[i]);
								Button_Flag=NULL_KEYPAD;
								i++;
							}
						}
						LCD_Goto(1,0);
						LCD_Write_String("Guest pass:");
						for(Uint8 i=0;i<4;)
						{
							Button_Flag=NULL_KEYPAD;
							Button_Flag=Keypad_GetValue();
							while(Button_Flag != NULL_KEYPAD)
							{
								Flag_Guest_Pass[i]=Button_Flag;
								LCD_Write_Char('*');
								Button_Flag=NULL_KEYPAD;
								i++;
							}
						}
						LCD_Clear();
						
						/*Check For Username & Password*/
						
						Uint8 Flag_alarm=0;
						for (Uint8 y=0;y<Counter_User_Name_Keypad;y++)
						{
							if (Flag_Guest_User[0]==EEPROM_ReadByte(Page_User_Name_KeyPad,y) && Flag_Guest_User[1]==EEPROM_ReadByte(Page_User_Name_KeyPad,y+1) && Flag_Guest_User[2]==EEPROM_ReadByte(Page_User_Name_KeyPad,y+2) && Flag_Guest_User[3]==EEPROM_ReadByte(Page_User_Name_KeyPad,y+3))

							{
								if (Flag_Guest_Pass[0]==EEPROM_ReadByte(Page_Password_KeyPad,y) && Flag_Guest_Pass[1]==EEPROM_ReadByte(Page_Password_KeyPad,y+1) && Flag_Guest_Pass[2]==EEPROM_ReadByte(Page_Password_KeyPad,y+2) && Flag_Guest_Pass[3]==EEPROM_ReadByte(Page_Password_KeyPad,y+3))
								{
									
									LCD_Write_String("Logged In");
									Login=1;
									_delay_ms(1000);
									LCD_Clear();
									counter_flag_2=0;
									break;
								}
								else
								{
									Flag_alarm=1;
									counter_flag_2--;
									LCD_Write_String("Invalid");
									
									LCD_Goto(1,0);
									LCD_Write_String("Trials");
									
									LCD_Goto(1,7);
									LCD_Write_Integer(counter_flag_2);
									_delay_ms(1000);
									
									if (counter_flag_2==0)
									{
										LCD_Clear();
										LCD_Write_String("use the reset button");
										while(1)
										{
											ALARM_ON();
										}
									}
									break;
								}
							}
						}
					}while (counter_flag_2);
					break;
				}//End Of case
			}//End Of switch
		}//End Of If condition
	
}//End else Condition

		if (Login==1)
		{
			
			
				LCD_Clear();
				LCD_Write_String("1.Control System");
				LCD_Goto(1,0);
				LCD_Write_String("2.Check system");
				Button_Flag=NULL_KEYPAD;
				while(Button_Flag==NULL_KEYPAD)
				{
					Button_Flag=Keypad_GetValue();
					Flag = Button_Flag;
				}
				if (Flag=='1'|| Flag=='2')
				{
					switch(Flag)
					{
						
						case '1' :
						{
							Uint8 check=0;
							while (!check)
							{
								check=1;
								LCD_Clear();
								LCD_Write_String("1.Room1");
								LCD_Goto(1,0);
								LCD_Write_String("2.Room2");
								LCD_Goto(0,9);
								LCD_Write_String("3.Room3");
								LCD_Goto(1,9);
								LCD_Write_String("4.More");
								// while(!(Keypad_GetValue() >= '1') && (Keypad_GetValue() <= '3') )
								Button_Flag=NULL_KEYPAD;
								while(Button_Flag==NULL_KEYPAD)
								{
									Button_Flag=Keypad_GetValue();
									Flag = Button_Flag;
								}
								
								if (Flag=='1'|| Flag=='2' || Flag=='3' || Flag=='4')
								{
									switch(Flag)
									{
										case '1':
										{
											LCD_Clear();
											LCD_Write_String("1.turn on light");
											_delay_ms(100);
											LCD_Goto(1,0);
											LCD_Write_String("2.turn off light");
											_delay_ms(100);
											Button_Flag=NULL_KEYPAD;
											while(Button_Flag==NULL_KEYPAD)
											{
												Button_Flag=Keypad_GetValue();
												Flag = Button_Flag;
											}
											if (Flag=='1'|| Flag=='2')
											{
												switch (Flag)
												{
													case '1' :
													{
														LCD_Clear();
														LED0_ON();
														Flag_Lamp=1;
														break;
													}
													case'2' :
													{
														LCD_Clear();
														LED0_OFF();
														Flag_Lamp=0;
														break;
													}
													
												}//End OF Switch Case
											}//End Of If Condition
											
											break;
										}//End OF Case 1
										case '2':
										{
											LCD_Clear();
											LCD_Write_String("1.turn on light");
											_delay_ms(100);
											LCD_Goto(1,0);
											LCD_Write_String("2.turn off light");
											_delay_ms(100);
											Button_Flag=NULL_KEYPAD;
											while(Button_Flag==NULL_KEYPAD)
											{
												Button_Flag=Keypad_GetValue();
												Flag = Button_Flag;
											}
											if (Flag=='1'|| Flag=='2')
											{
												switch (Flag)
												{
													case '1' :
													{
														LCD_Clear();
														LED1_ON();
														Flag_Lamp_2=1;
														break;
													}
													case'2' :
													{
														LCD_Clear();
														LED1_OFF();
														Flag_Lamp_2=0;
														break;
													}
													
												}//End OF Switch Case
											}//End Of If Condition
											
											break;
										}//End OF Case 2
										case '3':
										{
											LCD_Clear();
											LCD_Write_String("1.turn on light");
											_delay_ms(100);
											LCD_Goto(1,0);
											LCD_Write_String("2.turn off light");
											_delay_ms(100);
											Button_Flag=NULL_KEYPAD;
											while(Button_Flag==NULL_KEYPAD)
											{
												Button_Flag=Keypad_GetValue();
												Flag = Button_Flag;
											}
											if (Flag=='1'|| Flag=='2')
											{
												switch (Flag)
												{
													case '1' :
													{
														LCD_Clear();
														LED2_ON();
														Flag_Lamp_3=1;
														break;
													}
													case'2' :
													{
														LCD_Clear();
														LED2_OFF();
														Flag_Lamp_3=0;

														break;
													}
													
												}//End OF Switch Case
											}//End Of If Condition
											
											break;
										}//End OF Case 3
										case '4' :
										{
											LCD_Clear();
											LCD_Write_String("5.Room4");
											LCD_Goto(1,0);
											LCD_Write_String("6.LAMP");
											LCD_Goto(1,8);
											LCD_Write_String("7.Back");
											Button_Flag=NULL_KEYPAD;
											while(Button_Flag==NULL_KEYPAD)
											{
												Button_Flag=Keypad_GetValue();
												Flag = Button_Flag;
											}
											if ( Flag=='5' || Flag=='6' || Flag=='7')
											{
												switch (Flag)
												{
													case'5':
													{
														LCD_Clear();
														LCD_Write_String("1.turn on light");
														_delay_ms(100);
														LCD_Goto(1,0);
														LCD_Write_String("2.turn off light");
														_delay_ms(100);
														Button_Flag=NULL_KEYPAD;
														while(Button_Flag==NULL_KEYPAD)
														{
															Button_Flag=Keypad_GetValue();
															Flag = Button_Flag;
														}
														if (Flag=='1'|| Flag=='2')
														{
															switch (Flag)
															{
																case '1' :
																{
																	LCD_Clear();
																	LED3_ON();
																	Flag_Lamp_4=1;
																	break;
																}
																case'2' :
																{
																	LCD_Clear();
																	LED3_OFF();
																	Flag_Lamp_4=0;
																	break;
																}
																
															}//End OF Switch Case
														}//End Of If Condition
														
														break;
														
													}//end of case 5
													case '6' :
													{
														LCD_Clear();
														LCD_Write_String("1-25%");
														LCD_Goto(0,7);
														LCD_Write_String("2-50%");
														LCD_Goto(1,0);
														LCD_Write_String("3-75%");
														LCD_Goto(1,7);
														LCD_Write_String("4-100%");
														Button_Flag=NULL_KEYPAD;
														while(Button_Flag==NULL_KEYPAD)
														{
															Button_Flag=Keypad_GetValue();
															Flag = Button_Flag;
														}
														if (Flag=='1'|| Flag=='2' || Flag=='3' || Flag=='4')
														{
															switch (Flag)
															{
																case '1':
																{
																	PWM0_Gen(25);
																	Flag_Dimmer=1;
																	break;
																}//End Of Case 1
																case '2':
																{
																	PWM0_Gen(50);
																	Flag_Dimmer=1;
																	break;
																}//End Of Case 2
																case '3':
																{
																	PWM0_Gen(75);
																	Flag_Dimmer=1;
																	break;
																}//End Of Case 3
																case '4':
																{
																	PWM0_Gen(100);
																	Flag_Dimmer=1;
																	break;
																}//End Of Case 4
															}//End Of switch case
														}//End Of If Conditon
														LCD_Clear();
														LCD_Write_String("Done");
																						
														break;
													}//end of case 6
													case'7' :
													{
														check=0;
														break;
													}//end of case 7
								
							}
							
												
											}//end of switch
										} //end of if condition
										
										break;
									} // end of case 4
									
								}//End OF Switch
							}//End Of IF Condition
							break;
						}// end of case 1
						case '2' :
						{
							Uint8 check=0;
							while (!check)
							{
								check =1;
								LCD_Clear();
								LCD_Write_String("1.Room1");
								LCD_Goto(0,9);
								LCD_Write_String("2.Room2");
								LCD_Goto(1,0);
								LCD_Write_String("3.Room3");
								LCD_Goto(1,9);
								LCD_Write_String("4.More");
								Button_Flag=NULL_KEYPAD;
								while(Button_Flag==NULL_KEYPAD)
								{
									Button_Flag=Keypad_GetValue();
									Flag = Button_Flag;
								}
								
								if (Flag=='1'|| Flag=='2' || Flag=='3' || Flag=='4')
								{
									switch(Flag)
									{
										case '1' :
										{
											if (Flag_Lamp==1)
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS ON");
												_delay_ms(2000);
											}
											else
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS OFF");
												_delay_ms(2000);
											}
											break;
										}//end of case 1
										case '2' :
										{
											if (Flag_Lamp_2==1)
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS ON");
												_delay_ms(2000);
											}
											else
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS OFF");
												_delay_ms(2000);
											}
											break;
										}//end of case 2
										case '3' :
										{
											if (Flag_Lamp_3==1)
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS ON");
												_delay_ms(2000);
											}
											else
											{
												LCD_Clear();
												LCD_Write_String("LAMP IS OFF");
												_delay_ms(2000);
											}
											break;
										}//end of case 3
										case '4' :
										{
											LCD_Clear();
											LCD_Write_String("5.Room 4");
											LCD_Goto(1,0);
											LCD_Write_String("6.Back");
											Button_Flag=NULL_KEYPAD;
											while(Button_Flag==NULL_KEYPAD)
											{
												Button_Flag=Keypad_GetValue();
												Flag = Button_Flag;
											}
											if ( Flag=='5' || Flag=='6' )
											{
												switch (Flag)
												{
													case'5':
													{
														if (Flag_Lamp_4==1)
														{
															LCD_Clear();
															LCD_Write_String("LAMP IS ON");
															_delay_ms(2000);
														}
														else
														{
															LCD_Clear();
															LCD_Write_String("LAMP IS OFF");
															_delay_ms(2000);
														}
														break;
														
													}// end of case 5
													case'6' :
													{
														check=0;
														break;
														
													}//end of case 6
							}
							
												
											}//end of switch
											
										} //end of if
										
										break;
									}//end of case 4
									
									
								}//end of switch
								
							}//end of if
							break;
						}//end of case 2
					}// end of switch
					
				}// end of if
		}//End Of While Loop
		
		
					}
	




	
}
ISR(INT0_vect)
{
	LCD_LogIN_system();	
	LCD_Clear();
	LCD_Write_String("Press the button");
	LCD_Goto(1,0);
	LCD_Write_String("to start");
	
 }//End Of ISR
			 
		 

		 
	 
			
			