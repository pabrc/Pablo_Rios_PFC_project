/*
 *
 * File: frec_gen.c
 * Date (lastest version): 7/11/2014
 * Description: This program allows you to control a frequency meter and a function generator that
 * 				are integrated into the dev board. It can be controlled through commands sent over
 * 				a UDP connection between the board (server listening at port 80) an a PC (client).
 */


//---------------------------------------------------------------------------
// Includes
#include "includes.h"
#include "system.h"

#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "DM9000A.C"
#include "frec_gen.h"
#include "VI_protocol.h"

#include <alt_types.h>

#include <sys/alt_irq.h>
//#include "priv/alt_legacy_irq.h"
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_lcd_16207.h>


//---------------------------------------------------------------------------
//Definition of Task Stacks
#define   TASK_STACKSIZE       2048
OS_STK    VITask_stk[TASK_STACKSIZE];
OS_STK    RICTask_stk[TASK_STACKSIZE];


//////////////////////////////////////////////////////////////////////////////
//							    	MAIN									//
//////////////////////////////////////////////////////////////////////////////
int main()
{

	// Create and launch the threads
	OSTaskCreateExt(VITask,
				  NULL,
				  (void *)&VITask_stk[TASK_STACKSIZE-1],
				  VI_TASK_PRIORITY,
				  VI_TASK_PRIORITY,
				  VITask_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);


	OSTaskCreateExt(RICTask,
	              NULL,
	              (void *)&RICTask_stk[TASK_STACKSIZE-1],
	              RIC_TASK_PRIORITY,
	              RIC_TASK_PRIORITY,
	              RICTask_stk,
	              TASK_STACKSIZE,
	              NULL,
				  0);


  OSStart(); // Operative System: to manage the threads

  while(1); /*In normal execution this is never executed */
  return(0);
}



/////////////////////////////////////////////////////////////////////////////////////
//                  	         THREADS CODE     		                           //
/////////////////////////////////////////////////////////////////////////////////////

/* Thread 1: VITask */
/* We call the instrument's function that is activated in 'sc.activated_device' */
void VITask(void* pdata)
{

	first = last = NULL; // pointer to the list of frequency
	lcd_init();
	system_config_init();
	assign_interruptions(); //assign the interruptions to a specific ISR

	while(1) {

		if (sc.activated_device == FREQUENCY_METER){ 			 // Frequency Meter activated

			frequency_meter();
			IOWR(PIO_OUT_GREEN_BASE, 0, 0x0001); 			 // LEDG0 of the dev board is ON
			IOWR(PIO_OUT_RED_BASE, 0, 0x0000);				 // Clear Red leds (info of the Function Generator)

		} else if (sc.activated_device == FUNCTION_GENERATOR){ // Function Generator activated

			function_generator();
			IOWR(PIO_OUT_GREEN_BASE, 0, 0x0002);			 // LEDG1 of the dec board isON

		}
	}
}


/* Thread 2: RICTask */
/* We receive packets via Ethernet connection */
void RICTask(void* pdata)
{

	unsigned int num_packets;

	while(DM9000_init() != DMFE_SUCCESS); //initialization of the Ethernet controller

	// Register the ISR after the initialization
	alt_ic_isr_register(DM9000A_IRQ_INTERRUPT_CONTROLLER_ID, DM9000A_IRQ, (void *)ethernet_interrupts , NULL, NULL);


	/*
	 *	We receive 'num_packets', then we suspend the task for 100ms. Then we receive
	 *		'num_packets' ..., and so on.
	 */

	num_packets = 25; // burst of packets to be read each time
	while (1) {

		while (num_packets != 0) {
			TransmitPacket(0,0x00); // clear the Ethernet Flag, so we can receive other packet
			num_packets--;
		}
		num_packets = 25;
		OSTimeDlyHMSM(0, 0, 0, 100); // the task is suspended for 100ms, and we execute the VITask for that time.
									 //  As VITask has less priority than RICTask, we need to suspend RICTask in order
									 //	 to execute VITask.
	}
}


///////////////////////////////////////////////////////////////////////////
//					  		  LCD FUNCTIONS								 //
///////////////////////////////////////////////////////////////////////////

/* To initialize the LCD */
void lcd_init( void )
{
  /* Set Function Code Four Times -- 8-bit, 2 line, 5x7 mode */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
  usleep(4100);   /* Wait 4.1 ms */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
  usleep(100);    /* Wait 100 us */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
  usleep(5000);   /* Wait 5.0 ms */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x38 );
  usleep(100);

  /* Set Display to OFF */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x08 );
  usleep(100);

  /* Set Display to ON */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x0C );
  usleep(100);

  /* Set Entry Mode -- Cursor increment, display doesn't shift */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x06 );
  usleep(100);

  /* Set the cursor to the home position */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 );
  usleep(2000);

  /* Clear the display */
  IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x01 );
  usleep(2000);
}


/* To clear the LCD */
void lcd_clear( void )
{

	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 ); //cursor to home
	usleep(2000);

	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x01 ); //clear display
	usleep(2000);
}


/* Write a message in the first line of the LCD */
void lcd_write_first_line(char *message)
{

	char final_message[ALT_LCD_WIDTH]; //ALT_LCD_WIDTH = 16
	int i=0;
	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 ); //cursor to home
	usleep(2000);

	if (strlen(message) > ALT_LCD_WIDTH) printf("ERROR: Input not valid on the first line of the LCD");
	else {
		strncpy(final_message, message, strlen(message));

		// Rest of the line is filled with the ' ' space symbol
		for (i = strlen(message); i <= ALT_LCD_WIDTH; i++) {
			final_message[i] = ' ';
		}
		for( i = 0; i < strlen(final_message) ; i++ ) { //show message
			IOWR( LCD_BASE, LCD_WR_DATA_REG, final_message[i] );
			usleep(50);
	    }
	}
}


/* Write a message in the second line of the LCD */
void lcd_write_second_line(char *message)
{

	char final_message[ALT_LCD_WIDTH]; //ALT_LCD_WIDTH = 16
	int i=0;

	//IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0x02 ); //cursor to home
	//usleep(2000);

	IOWR( LCD_BASE, LCD_WR_COMMAND_REG, 0xC0 ); // change of line: to the second line
    usleep(100);

	if (strlen(message) > ALT_LCD_WIDTH) printf("ERROR: Input not valid on the second line of the LCD");
	else {
		strncpy(final_message, message, strlen(message));

		// Rest of the line is filled with the ' ' space symbol
		for (i = strlen(message); i <= ALT_LCD_WIDTH; i++) {
			final_message[i] = ' ';
		}
		for( i = 0; i < strlen(final_message) ; i++ ) { //show message
			IOWR( LCD_BASE, LCD_WR_DATA_REG, final_message[i] );
			usleep(50);
	    }
	}
}


///////////////////////////////////////////////////////////////////////////////
//				FUNCTIONS TO OPERATE WITH THE FREQUENCY LIST				 //
///////////////////////////////////////////////////////////////////////////////

/* TO create an empty node */
struct node *create(float data)
{
	struct node *temp;

	temp = (struct node *)malloc(sizeof(struct node));
	temp->prev = NULL;
	temp->next = NULL;
	temp->frequency = data;
	num_nodes++;
	return temp;
}


/*  TO insert at beginning */
void insert_beginning(float data)//struct node *first, struct node *last, float data)
{

	struct node *temp;

	if (first == NULL) { //the list is empty
        first = create(data);
        last = first;
    } else { //the list is not empty
        temp = create(data);
        temp->next = first;
        first->prev = temp;
        first = temp;
    }
}


/* To insert at end */
void insert_at_end(float data)//struct node *first, struct node *last, float data)
{

	struct node *temp;

	if (first == NULL) { //the list is empty
        first = create(data);
        last = first;
    } else { //the list is not empty
        temp = create(data);
        last->next = temp;
        temp->prev = last;
        last = temp;
    }
}


/* To delete the first element */
void delete_beginning()//struct node *first, struct node *last)
{

	struct node *temp;

	if(first == NULL) return; // the list is empty
	else if (first == last) { // the list has only one item
		free(first);
		first = NULL;
		last = NULL;
		num_nodes--;
	} else { // the list has more than one item
		temp = first->next;
		temp->prev = NULL;
		free(first);
		first = temp;
		num_nodes--;
	}
}


/* To delete the last element of the list*/
void delete_at_end()//struct node *first, struct node *last)
{

	struct node *temp;

	if(first == NULL) return; // the list is empty
	else if (first == last) { // the list has only one item
		free(first);
		first = NULL;
		last = NULL;
		num_nodes--;
	} else { // the list has more than one item
		temp = last->prev;
		free(last);
		temp->next = NULL;
		last = temp;
		num_nodes--;
	}
}


/* To delete all the list */
void delete_list()//struct node *first, struct node *last)
{

	struct node *temp;

	if(first == NULL) return; // the list is empty
	else if (first == last) { //the list has only one item
		free(first);
		first = NULL;
		last = NULL;
		num_nodes = 0;

	} else { //the list has two items or more
		temp = last->prev;
		while (temp != first) {

			free(temp->next);
			temp = temp->prev;
		}
		free(temp->next);
		free(first);
		first = NULL;
		last = NULL;
		num_nodes = 0;
	}

}


/////////////////////////////////////////////////////////////////////////////////////
//							FREQUENCY METER FUNCTIONS							   //
/////////////////////////////////////////////////////////////////////////////////////

/* Instrument: Frequency Meter */
void frequency_meter( void )
{

	float frecuencia_int = 0;

	if (last_instrument != FREQUENCY_METER){ // When the frequency meter is chosen, we do a reset of the ccp module ...
											// ... and configure the CCP in function generator mode

		last_instrument = FREQUENCY_METER;
		reset_ccp();						// reset of the CCP module
		OSTimeDlyHMSM(0, 0, 1, 0);			// Delay(hour,minutes,seconds,miliseconds)
		lcd_write_first_line("Frequency Meter");
		configuration_ccp_captura_0();		// CCP configured in mode captura_0
	}

	if (captura_valida == 1) {

			frecuencia_int = calculate_new_freq(); // Calculates the frequency with the values of capturaant and captura (global variables)
												   // ... that are modified by the ISR of captura_0
			frecuencia = calculate_average_frequency(frecuencia_int);

			//printf("capturaant= %d , captura= %d, frecuencia media: %f\n", capturaant, captura, frecuencia_int);
			//show_frequency_lcd(frecuencia);	   // Shows the frequency in the second line of the LCD

			captura_valida = 0;
	}

	configuration_ccp_captura_0(); // Configuration in capture mode (captura_0)
}


/* Calculate new frequency with capturaant and captura */
float calculate_new_freq ( void )//unsigned long int captura_int, unsigned long int capturaant_int )
{

	float frequency;
	float tPer = 0.00000001;  // period of a 100MHz signal

	if (captura > capturaant) {
		frequency = (1/((captura-capturaant)*tPer));
		return frequency;
	} else {
		return frecuencia;
	}


}


/* Calculate average frequency */
float calculate_average_frequency(float new_freq)
{
	float av_freq;
	struct node *temp;

	temp = first;
	av_freq = 0.0;

	// We operate with the frequency list to create/delete nodes
	if (num_nodes < sc.num_freq_nodes) { // insert a node at the beginning

		insert_beginning(new_freq);

	} else { // delete the last node and insert a new one

		delete_at_end();
		insert_beginning(new_freq);
	}

	switch ( sc.average_type ) {
			case SIMPLE_MOVING_AVERAGE: {

				// Calculates the average frequency
				int k = 1;
				temp = first;
				for(k = 1; k <= num_nodes; k++) {

					av_freq = av_freq + (temp->frequency);
					temp = temp->next;
				}
				av_freq = av_freq/num_nodes;
				break;
			}
			case WEIGHTED_MOVING_AVERAGE: {

				// Calculates the weights
				int sum = 0;
				int i = 0;

				for(i = 1; i <= num_nodes; i++) sum += i; // sum of the indexes of the nodes (1+2+3+ ... +num_nodes )

				// Calculates the average frequency by using the weights (i/sum)
				i = num_nodes;
				temp = first;
				for(i = num_nodes; i >= 1; i--) {

					av_freq = av_freq + ((temp->frequency)*(i*1.0/sum));
					temp = temp->next;
				}
				break;
			}
			case EXPONENTIAL_MOVING_AVERAGE: {

				// Calculates the exponential weights
				float alpha = 0, sum = 0;
				int i = 0;

				if (num_nodes == sc.num_freq_nodes) {

					alpha = 4.0/(num_nodes+1);
					for(i = 1; i <= num_nodes; i++) sum += (alpha*pow((1-alpha), (1-i)));

					// Calculates the average frequency by using the exponential weights (alpha*pow((1-alpha), (1-i))/sum)
					i = num_nodes;
					temp = first;
					for(i = num_nodes; i >= 1; i--) {

						av_freq = av_freq + ((temp->frequency)*((alpha*pow((1.0-alpha), (1.0-i)))/sum));
						temp = temp->next;
					}

				}
				break;
			}
			default: {
				printf("ERROR: sc->average_type not recognized\n");
			}
			break;
	}//end switch
	return av_freq;
}


/* Show frequency in the second line of the LCD display */
void show_frequency_lcd ( float frequency )
{

	char* s_freq;

	if (frequency < 10){

		sprintf(s_freq, "%.4f", frequency ); // It transform the frequency in a character array
		strcat(s_freq, " Hz"); 				 // Append the units
		lcd_write_second_line(s_freq);

	}else if ((frequency >= 10)&&(frequency < 1000)){

		sprintf(s_freq, "%.3f", frequency );
		strcat(s_freq, " Hz");
		lcd_write_second_line(s_freq);

	}else if ((frequency >= 1000)&&(frequency < 1000000)){

		frequency = frequency/1000;

		sprintf(s_freq, "%.3f", frequency );
		strcat(s_freq, " kHz");
		lcd_write_second_line(s_freq);

	}else if (frequency >= 1000000){

		frequency = frequency/1000000;

		sprintf(s_freq, "%.3f", frequency );
		strcat(s_freq, " MHz");
		lcd_write_second_line(s_freq);
	}
}


/////////////////////////////////////////////////////////////////////////////////////
//				  FUNCTIONS ASSOCIATED WITH THE FUNCTION GENERATOR				   //
/////////////////////////////////////////////////////////////////////////////////////

/* Instrument: Function generator */
void function_generator( void )
{
	float freq;

	freq = 1/(sc.per_pwm*0.00000001); // Frequency of the output signal

	if (last_instrument != FUNCTION_GENERATOR) { // When the function generator is chosen, we do a reset of the ccp module ...
												// ... and configure the CCP in function generator mode
		last_instrument = FUNCTION_GENERATOR;
		lcd_write_first_line("F. Generator");
		reset_ccp();
	}

	if (sc.square_activated == SQUARE_SIGNAL_ACTIVATED) { // Squared signal

		configuration_function_generator_square();
		ccp_activate_square();
		IOWR(PIO_OUT_RED_BASE, 0, 0x0001); 			 // LEDR0 of the dev board is ON

	} else { // Non-Square signal

		configuration_function_generator_non_square(); //it has to be configure in a loop
		ccp_activate_non_square();					   //it has to be configure in a loop
		IOWR(PIO_OUT_RED_BASE, 0, 0x0002); 			 // LEDR0 of the dev board is ON

	}

	show_frequency_lcd(freq); // Shows the frequency in the second line of the LCD

}


/* Write signal values in the CCP's RAM */
void write_ram_function_generator(int *function, int num)
{

	int i=0;

	IOWR(PIO_EN_MUX_BASE,0,1);				// mux enabled

	IOWR(PIO_DIREC_BASE,0,0xB); 			// write in RAM

	for (i = 0; i < num ; i++){
		IOWR(PIO_DIREC_RAM_BASE,0,i); 		// i position of the RAM
		IOWR(PIO_DATOS_BASE,0,function[i]&0x0ff); // value to introduce
		IOWR(PIO_WR_BASE,0,1); 				// Edge to ...
		IOWR(PIO_WR_BASE,0,0); 				// ... write the value
	}
}



/////////////////////////////////////////////////////////////////////////////////////
//								  CCP CONFIGURATION								   //
/////////////////////////////////////////////////////////////////////////////////////

/* Reset of the CCP module */
void reset_ccp( void )
{

	IOWR(PIO_CAPTURA_0_BASE, 2, 0x0); // Disable interruption in captura_0
	IOWR(PIO_CAPTURA_0_BASE, 3, 0x1); // Erase the interruption flag of edgecapture register of captura_0,
									  //   that had been activated due to the input edge

	IOWR(PIO_ASYNC_RESET_BASE,0,1);
	IOWR(PIO_ASYNC_RESET_BASE,0,0);  // Reset of the CP module

	IOWR(PIO_EN_MUX_BASE,0,1);		 // mux enabled

}


/* CCP configuration in mode captura_0 */
void configuration_ccp_captura_0( void )
{

	IOWR(PIO_CAPTURA_0_BASE, 2, 0x01); // Enable interruption in captura_0
	IORD(PIO_CAPTURA_0_BASE, 2);
	IOWR(PIO_CAPTURA_0_BASE, 3, 0x01); // Erase the interruption flag of edgecapture register of captura_0,
	  	  	  	  	  	  	  	  	   //   that had been activated due to the input edge

	IOWR(PIO_EN_MUX_BASE,0,1);		   //  mux enabled

	IOWR(PIO_DIREC_BASE,0,0x00); 	   // Select to write in the RConf (Configuration register of the CCP)
	IOWR(PIO_DATOS_BASE,0,0x0001);     // CAPTURA_0 activated y and flag erased
	IOWR(PIO_WR_BASE,0,1);			   // Edge ...
	IOWR(PIO_WR_BASE,0,0);			   // ... to write in the CCP

}


/* CCP configuration. To change the frequency in the function generator. SQUARE FUNCTION */
// The parameter Ton is changed automatically depending to a specific freqcuency         //
// The output frequency is fout = 100MHz / per_pwm						 		         //
void configuration_function_generator_square( void )
{

	IOWR(PIO_DIREC_BASE,0,0x0002);  // Select to write in the PWM period
	IOWR(PIO_DATOS_BASE,0, sc.per_pwm);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr to write
	IOWR(PIO_DIREC_BASE,0,0x0003);  // Select to write in the Ton of the PWM
	IOWR(PIO_DATOS_BASE,0, (unsigned int)sc.ton_pwm);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr


	IOWR(PIO_DIREC_BASE,0,0x0009); 	// Select to write in the PWM1 period
	IOWR(PIO_DATOS_BASE,0, (unsigned int)(sc.per_pwm)/RAM_PWM_SIZE);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr
	IOWR(PIO_DIREC_BASE,0,0x000A);  // Select to write in the Ton of the PWM1
	IOWR(PIO_DATOS_BASE,0, (unsigned int)((sc.per_pwm)/RAM_PWM_SIZE)/2);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr

}


/* CCP configuration. To change the frequency in the function generator. NON SQUARE FUNCTION */
void configuration_function_generator_non_square( void )
{


	IOWR(PIO_DIREC_BASE,0,0x0002);      // Select to write in the PWM period
	IOWR(PIO_DATOS_BASE,0, 0x000000FF); // 255
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			    // Edge in wr
	IOWR(PIO_DIREC_BASE,0,0x0003);      // Select to write in the Ton of the PWM
	IOWR(PIO_DATOS_BASE,0, 0x0000007F); // 127 = 255/2
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			    // Edge in wr


	IOWR(PIO_DIREC_BASE,0,0x0009); 	    // Select to write in the PWM1 period
	IOWR(PIO_DATOS_BASE,0, (sc.per_pwm)/RAM_PWM_SIZE);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			    // Edge in wr
	IOWR(PIO_DIREC_BASE,0,0x000A);      // Select to write in the Ton of the PWM1
	IOWR(PIO_DATOS_BASE,0, ((sc.per_pwm)/RAM_PWM_SIZE)/2);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			    // Edge in wr

}


/* CCP configuration. To change only Ton in the function generator */
void configuration_function_generator_ton( void )
{

	IOWR(PIO_DIREC_BASE,0,0x0003);  // Select to write in the Ton of the PWM
	IOWR(PIO_DATOS_BASE,0,sc.ton_pwm);
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr
}


/* CCP configuration. PWM functionality is activated. Square signal */
void ccp_activate_square( void )
{

	IOWR(PIO_DIREC_BASE,0,0x0); 	// Select to write in the BD0
	IOWR(PIO_DATOS_BASE,0,0x0003);  // and PWM
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr
}


/* CCP configuration. PWM functionality is activated. NON Square signal */
void ccp_activate_non_square( void )
{

	IOWR(PIO_DIREC_BASE,0,0x0); 	// Select to write in the BD0
	IOWR(PIO_DATOS_BASE,0,0x0007);  // RAM and PWM signal
	IOWR(PIO_WR_BASE,0,1);
	IOWR(PIO_WR_BASE,0,0);			// Edge in wr
}



///////////////////////////////////////////////////////////////////////////////////////
//               	OTHER FUNCTIONS RELATED WITH THE INSTRUMENTS		             //
///////////////////////////////////////////////////////////////////////////////////////

/* Initialization of the system configuration parameters */
void system_config_init ( void )
{

	sc.activated_device = FREQUENCY_METER;
	sc.average_type =	SIMPLE_MOVING_AVERAGE;
	sc.num_freq_nodes = NUM_FREQ_NODES_DEFAULT;
	sc.per_pwm = PERIOD_PWM_DEFAULT;
	sc.ton_pwm = TON_PWM_DEFAULT;
	sc.square_activated = SQUARE_SIGNAL_ACTIVATED;

}


/* Assigns the interruption functions */
void assign_interruptions( void )
{
	printf("assign_interruptions\n");

	// Enable the EDGE buttons
	IOWR(PIO_IN_KEY_EDGE_BASE, 3, 0x07); // Clear the edge interruption flag
	IOWR(PIO_IN_KEY_EDGE_BASE, 2, 0x07); // Enable edge interruption


	// Assign interruptions
	alt_ic_isr_register(PIO_CAPTURA_0_IRQ_INTERRUPT_CONTROLLER_ID, PIO_CAPTURA_0_IRQ, (void *)interrupt_captura_0, NULL, NULL);
	alt_ic_isr_register(PIO_IN_KEY_EDGE_IRQ_INTERRUPT_CONTROLLER_ID, PIO_IN_KEY_EDGE_IRQ, (void *)edge_button_interrupts , NULL, NULL);

}


/* To convert decimal number to binary number */
void decimal_to_binary(long decimal, char *binario,int tam)
{

   int c, d, count = 0;

   for ( c = (tam - 1) ; c >= 0 ; c-- )
   {
	  d = decimal >> c;

	  if ( d & 1 ) *(binario+count) = 1 + '0';
	  else	*(binario+count) = 0 + '0';

	  count++;
   }
   *(binario+count) = '\0';
}



///////////////////////////////////////////////////////////////////////////////////////
//                       		    INTERRUPTS   				                     //
///////////////////////////////////////////////////////////////////////////////////////

/* Interruption of the external signal to meassure the frequency. Used by the frequency meter */
void interrupt_captura_0(void* context)
{

	//printf("external interrupt\n");

	IOWR(PIO_EN_MUX_BASE,0,1);		 // mux enabled
	IOWR(PIO_SEL_SALIDA_BASE,0,0x9); // Select to show captura_0 at the output

	if (captura_valida == 0) { // If the VITask program does not finish to use the previous values of captura and capturaant,
							   //  we do not modified them in order to not have any inconsistency with the data

		IOWR(PIO_DIREC_BASE,0,0x00); 	 // Select to write in RConf
		IOWR(PIO_DATOS_BASE,0,0x0009);	 // Stop the captura and continue in capture mode ("1001" in RConf)
		IOWR(PIO_WR_BASE,0,1);
		IOWR(PIO_WR_BASE,0,0);  		 // Edge in wr

		captura = (IORD(PIO_IN_32_BASE, 0)); // Get the last captured value and stores it in 'captura'

		IOWR(PIO_DIREC_BASE,0,0x00); 	 // Select to write in RConf
		IOWR(PIO_DATOS_BASE,0,0x0019);   // Active lec to show the previous capture
		IOWR(PIO_WR_BASE,0,1);
		IOWR(PIO_WR_BASE,0,0); 		     // Edge in wr

		capturaant = (IORD(PIO_IN_32_BASE, 0)); // Get the previous of the last capture value, and stores it in 'capturaant'

		captura_valida = 1;

	}

	IOWR(PIO_CAPTURA_0_BASE, 2, 0x0); 	// Interruption is disabled
	IOWR(PIO_CAPTURA_0_BASE, 3, 0x1);  	// Clear the flag of the edgecapture register
	IORD(PIO_CAPTURA_0_BASE, 3); 		// Delay

	IOWR(PIO_DIREC_BASE,0,0x0); 	 	// Select write in RConf
	IOWR(PIO_DATOS_BASE,0,0x0001);	 	// Desactivates 'lec' and continues in capture mode (RConf)
	IOWR(PIO_WR_BASE,0,1);  		 	// Edge ...
	IOWR(PIO_WR_BASE,0,0);  		 	// ... to write

}


/* Interruption function of the edge activated buttons */
void edge_button_interrupts(void* context)
{

	volatile int button;
	char* text;
	button = IORD(PIO_IN_KEY_EDGE_BASE, 3); //read the state of the edge capture register of the buttons

	if (button == 1) {

		reset_ccp();

	} else if (button == 2) {

		sprintf(text, "MAC-%.2x%.2x%.2x%.2x%.2x%.2x", (int)DEFAULT_SOURCE_MAC_5, (int)DEFAULT_SOURCE_MAC_4,
				(int)DEFAULT_SOURCE_MAC_3, (int)DEFAULT_SOURCE_MAC_2, (int)DEFAULT_SOURCE_MAC_1, (int)DEFAULT_SOURCE_MAC_0);
		lcd_write_second_line(text);
		//usleep(500000); // 0.5 seconds

	} else if (button == 4) {

		sprintf(text, "%d.%d.%d.%d", (int)DEFAULT_IP_SOURCE_3,  (int)DEFAULT_IP_SOURCE_2, (int)DEFAULT_IP_SOURCE_1,  (int)DEFAULT_IP_SOURCE_0);
		lcd_write_second_line(text);
		//usleep(500000); // 0.5 seconds

	}

	IOWR(PIO_IN_KEY_EDGE_BASE, 3, 0xF); // Clear the edge interruption flags
}


/* Ethernet interrupt. Is called when we received a packet from the network */
void ethernet_interrupts()
{

	packet_num++;
    aaa=ReceivePacket(RXT,&rx_len);
    if(!aaa)
    {
      if (pkt_is_viprotocol(RXT, rx_len)) {

    		struct pkt_buffer *pkt;
    		pkt = (struct pkt_buffer *)RXT;

    		int command=0;
    		// Extract the command from the packet
    		command += pkt->ip.udp.data[3]&0x0ff;
    		command += (pkt->ip.udp.data[2] << 8)&0x0ff00;
    		command += (pkt->ip.udp.data[1] << 16)&0x0ff0000;
    		command += (pkt->ip.udp.data[0] << 24)&0x0ff000000;

    		switch (command) {
    		// The server changes the instrument's parameters depending on the received command //

				case CMD_ACTIVATE_FREQ_METER:
				{
					// Activation of the frequency meter

					sc.activated_device = FREQUENCY_METER;

	    			//printf("\n CMD_ACTIVATE_FREQ_METER\n");
					break;
				}
				case CMD_FREQ_REQUEST:
				{	// The client requests the current average frequency

	    			pkt_changes_to_send(pkt);

					// Send command CMD_FREQ_ANSWER to the destination
	    			pkt->ip.udp.data[0] = (unsigned char)CMD_FREQ_ANSWER >> 24;
	    			pkt->ip.udp.data[1] = (unsigned char)CMD_FREQ_ANSWER >> 16;
	    			pkt->ip.udp.data[2] = (unsigned char)CMD_FREQ_ANSWER >> 8;
	    			pkt->ip.udp.data[3] = (unsigned char)CMD_FREQ_ANSWER;

	    			// Pointer to char to extract the bytes of the float number and put them on
	    			//  the packet to send (the network is big endian)
					char *s_freq;
					s_freq = (char *)&frecuencia;
					pkt->ip.udp.data[7] = s_freq[0]&0x0ff;
					pkt->ip.udp.data[6] = s_freq[1]&0x0ff;
					pkt->ip.udp.data[5] = s_freq[2]&0x0ff;
					pkt->ip.udp.data[4] = s_freq[3]&0x0ff;

	    			TransmitPacket(RXT,PKT_LENGTH);

	    			//printf("\n CMD_FREQ_REQUEST\n");
					break;
				}
				case CMD_NFREQ_NODES:
				{
					// To change the number of nodes of the frequency average

	    			int num=0;
	    			delete_list();
	    			num += pkt->ip.udp.data[7]&0x0ff;
					num += (pkt->ip.udp.data[6] << 8)&0x0ff00;
					num += (pkt->ip.udp.data[5] << 16)&0x0ff0000;
					num += (pkt->ip.udp.data[4] << 24)&0x0ff000000;

	    			sc.num_freq_nodes = (int)num;

	    			//printf("\n CMD_NFREQ_NODES, num = %d\n", num);
					break;
				}
				case CMD_AV_SIMPLE:
				{
					// Simple average

					sc.average_type = SIMPLE_MOVING_AVERAGE;

	    			//printf("\n CMD_AV_SIMPLE\n");
					break;
				}
				case CMD_AV_WEIGHTED:
				{
					// Weighted average

					sc.average_type = WEIGHTED_MOVING_AVERAGE;

	    			//printf("\n CMD_AV_WEIGHTED\n");
					break;
				}
				case CMD_AV_EXP:
				{
					// Exponential average

					sc.average_type = EXPONENTIAL_MOVING_AVERAGE;

	    			//printf("\n CMD_AV_EXP\n");
					break;
				}
				case CMD_ACTIVATE_FUNC_GEN:
				{
					// Activation of the function generator

					sc.activated_device = FUNCTION_GENERATOR;

	    			//printf("\n CMD_ACTIVATE_FUNC_GEN\n");
					break;
				}
				case CMD_RAM_VALUES:
				{
					// Change the RAM values of the CCP
					int i=0;
					for(i = 0; i < RAM_PWM_SIZE; i++) {

						custom_signal[i] = (unsigned int)pkt->ip.udp.data[4+i];

					}

	    			write_ram_function_generator(custom_signal, RAM_PWM_SIZE);

	    			//printf("\n CMD_RAM_VALUES\n");
					break;
				}
				case CMD_FG_SQUARE:
				{
					// Square signal in the function generator

					sc.square_activated = SQUARE_SIGNAL_ACTIVATED;

	    			//printf("\n CMD_FG_SQUARE\n");
					break;
				}
				case CMD_FG_NON_SQUARE:
				{
					// Non square signal in the function generator

					sc.square_activated = NON_SQUARE_SIGNAL_ACTIVATED;

	    			//printf("\n CMD_FG_NON_SQUARE\n");
					break;
				}
				case CMD_FG_CHANGE_FREQ:
				{
					// Change the frequency (and also Ton) of the function generator's signal
					//	Fout = 100MHz/per_pwm

	    			int new_freq=0;
	    			// Extract the new frequency from the packet
	    			new_freq += pkt->ip.udp.data[7]&0x0ff;
	    			new_freq += (pkt->ip.udp.data[6] << 8)&0x0ff00;
					new_freq += (pkt->ip.udp.data[5] << 16)&0x0ff0000;
					new_freq += (pkt->ip.udp.data[4] << 24)&0x0ff000000;

	    			sc.per_pwm = (unsigned int)(100e6/new_freq);
	    			sc.ton_pwm = sc.per_pwm/2;

	    			//printf("\n CMD_FG_CHANGE_FREQ, freq = %d\, sc.per_pwm = %d, sc.ton_pwm = %d \n", (unsigned int)new_freq, sc.per_pwm, sc.ton_pwm);
					break;
				}
				case CMD_FG_CHANGE_TON:
				{
					// Change the Ton of the function generator's signal. We receive the
					//	Duty cycle --> Ton = per_pwm/(100/DC)

	    			int new_dc=0;
					// Extract the new duty cycle from the packet to change Ton
	    			new_dc += pkt->ip.udp.data[7]&0x0ff;
					new_dc += (pkt->ip.udp.data[6] << 8)&0x0ff00;
					new_dc += (pkt->ip.udp.data[5] << 16)&0x0ff0000;
					new_dc += (pkt->ip.udp.data[4] << 24)&0x0ff000000;

					if ((new_dc > 0) && (new_dc <= 100)) {

						sc.ton_pwm = (unsigned int)(sc.per_pwm/(100.0/new_dc));
					}

	    			//printf("\n CMD_FG_CHANGE_TON, dcycle = %x %d %d\n", new_dc, sc.per_pwm, sc.ton_pwm);
					break;
				}
				case CMD_RESET:
				{
					// Reset of the system

	    			reset_ccp();
	    			system_config_init();

	    			//printf("\n CMD_RESET\n");
					break;
				}
				default:
					//printf("WARNING: Unknown Command = %.2x%.2x%.2x%.2x ! -- We do not do anything!\n", pkt->ip.udp.data[0], pkt->ip.udp.data[1], pkt->ip.udp.data[2], pkt->ip.udp.data[3]);
					break;
    		}

      }//end if(packet_is_for_me())
      else if (pkt_is_arprequest(RXT, rx_len)) { // If we receive an ARP Request

    	  //printf("---- PACKET ARP FOR ME -----\n");
    	  struct pkt_buffer_2 *pkt;

    	  pkt = (struct pkt_buffer_2 *)RXT;
    	  int pkt_length;
    	  pkt_length = rx_len - 4; //do not count the Ethernet CRC

    	  // Now we change the content of the packet in order to send
    	  //   an ARP Replay
    	  pkt_arp_changes_to_send(pkt);
    	  if (pkt_length == 42) pkt_length += 18; // 18 bytes of padding (any value)
    	  TransmitPacket(RXT, pkt_length); // the length of ARP replay is always 60 bytes

      }
    }
    //TransmitPacket(0,0x00);
}


///////////////////////////////////////////////////////////////////////////////////////
//                       		 NETWORK CONNECTION				                     //
///////////////////////////////////////////////////////////////////////////////////////

/* Assign default values to the fields of the pkt */
void assign_pkt_defaults( struct pkt_buffer *pkt )
{

	// Ethernet header
	pkt->mac_dest0 = DEFAULT_DEST_MAC_0;
	pkt->mac_dest1 = DEFAULT_DEST_MAC_1;
	pkt->mac_dest2 = DEFAULT_DEST_MAC_2;
	pkt->mac_dest3 = DEFAULT_DEST_MAC_3;
	pkt->mac_dest4 = DEFAULT_DEST_MAC_4;
	pkt->mac_dest5 = DEFAULT_DEST_MAC_5;
	pkt->mac_source0 = DEFAULT_SOURCE_MAC_0;
	pkt->mac_source1 = DEFAULT_SOURCE_MAC_1;
	pkt->mac_source2 = DEFAULT_SOURCE_MAC_2;
	pkt->mac_source3 = DEFAULT_SOURCE_MAC_3;
	pkt->mac_source4 = DEFAULT_SOURCE_MAC_4;
	pkt->mac_source5 = DEFAULT_SOURCE_MAC_5;
	pkt->ethertype_h = DEFAULT_ETHERTYPE_H;
	pkt->ethertype_l = DEFAULT_ETHERTYPE_L;

	// IP header
	pkt->ip.version_ihl = DEFAULT_VERSION_IHL;
	pkt->ip.dscp_ecn = DEFAULT_DSCP_ECN;
	pkt->ip.iplength_h = DEFAULT_IP_LENGTH_H;
	pkt->ip.iplength_l = DEFAULT_IP_LENGTH_L;
	pkt->ip.id_h = DEFAULT_ID_H;
	pkt->ip.id_l = DEFAULT_ID_L;
	pkt->ip.flags_offset_h = DEFAULT_FLAGS_OFFSET_H;
	pkt->ip.flags_offset_l = DEFAULT_FLAGS_OFFSET_L;
	pkt->ip.ttl = DEFAULT_TTL;
	pkt->ip.protocol = DEFAULT_PROTOCOL;
	pkt->ip.ipcrc_h = DEFAULT_IP_CRC_H;
	pkt->ip.ipcrc_l = DEFAULT_IP_CRC_L;
	pkt->ip.ipsource0 = DEFAULT_IP_SOURCE_0;
	pkt->ip.ipsource1 = DEFAULT_IP_SOURCE_1;
	pkt->ip.ipsource2 = DEFAULT_IP_SOURCE_2;
	pkt->ip.ipsource3 = DEFAULT_IP_SOURCE_3;
	pkt->ip.ipdest0 = DEFAULT_IP_DEST_0;
	pkt->ip.ipdest1 = DEFAULT_IP_DEST_1;
	pkt->ip.ipdest2 = DEFAULT_IP_DEST_2;
	pkt->ip.ipdest3 = DEFAULT_IP_DEST_3;

	// UDP header
	pkt->ip.udp.source_port_h = DEFAULT_SOURCE_PORT_H;
	pkt->ip.udp.source_port_l = DEFAULT_SOURCE_PORT_L;
	pkt->ip.udp.dest_port_h = DEFAULT_DEST_PORT_H;
	pkt->ip.udp.dest_port_l = DEFAULT_DEST_PORT_L;
	pkt->ip.udp.udplength_h = DEFAULT_UDP_LENGTH_H;
	pkt->ip.udp.udplength_l = DEFAULT_UDP_LENGTH_L;
	pkt->ip.udp.crc_h = DEFAULT_UDP_CRC_H;
	pkt->ip.udp.crc_l = DEFAULT_UDP_CRC_L;

}


/* Calculate the IP checksum */
unsigned int calculate_ip_checksum( struct pkt_buffer *pkt)
{

	char *ptr;
	int i;
	unsigned int sum = 0, sum_aux;

	ptr = (char *)pkt;
	ptr += ETHERNET_HEADER_LENGTH; //ptr pointing to the first field of the IP header
	sum = 0xffff;

	for (i = 0; i < IP_HEADER_LENGTH/2; i++) {
		sum += ((*(ptr)&0xff)<<8) | (*(ptr+1)&0xff);
		ptr += 2;
		if (sum > 0xffff) sum -= 0xffff;
	}

	sum_aux = sum&0x0ffff;

	// return ones's complement
	return ~sum_aux;
}


/* Calculate the UDP checksum (it's optional) */
unsigned int calculate_udp_checksum( struct pkt_buffer *pkt)
{

	/*	It's optional. We do not use it. When it's not used
	 * 		the checksum value is 0x0000
	 */

	return 0;

}


/* To determine if a received packet is for me or not */
int pkt_is_viprotocol(unsigned char *buffer, int rx_len)
{

	// Packet IS a vi_protocol packet      --> return 1
	// Packet IS NOT a vi_protocol packet  --> return 0

	int pkt_length = 0;
	struct pkt_buffer *pkt;
	pkt = (struct pkt_buffer *)buffer;

	pkt_length = rx_len - 4; // we don't count the four bytes of FCS (Ethernet checksum)

	// Check whether the packet length is the expected one
	if (pkt_length != PKT_LENGTH) return 0;

	// Check Ethernet header
	// MAC is broadcast
	if ( (pkt->mac_dest5 == (char)0xFF) && (pkt->mac_dest4 == (char)0xFF) && (pkt->mac_dest3 == (char)0xFF)
			&& (pkt->mac_dest2 == (char)0xFF) && (pkt->mac_dest1 == (char)0xFF) && (pkt->mac_dest0 == (char)0xFF)) {
		pkt_length = rx_len - 4; //is just an assignment to complete the if statement
	} else { // IF it's not not my MAC
		if (pkt->mac_dest5 != (char)DEFAULT_SOURCE_MAC_5) return 0;
		else if (pkt->mac_dest5 != (char)DEFAULT_SOURCE_MAC_5) return 0;
		else if (pkt->mac_dest4 != (char)DEFAULT_SOURCE_MAC_4) return 0;
		else if (pkt->mac_dest3 != (char)DEFAULT_SOURCE_MAC_3) return 0;
		else if (pkt->mac_dest2 != (char)DEFAULT_SOURCE_MAC_2) return 0;
		else if (pkt->mac_dest1 != (char)DEFAULT_SOURCE_MAC_1) return 0;
		else if (pkt->mac_dest0 != (char)DEFAULT_SOURCE_MAC_0) return 0;
	}

	// Check the IP header
	// If it's not my IP address
	if (pkt->ip.ipdest3 != (char)DEFAULT_IP_SOURCE_3) return 0;
	else if (pkt->ip.ipdest2 != (char)DEFAULT_IP_SOURCE_2) return 0;
	else if (pkt->ip.ipdest1 != (char)DEFAULT_IP_SOURCE_1) return 0;
	else if (pkt->ip.ipdest0 != (char)DEFAULT_IP_SOURCE_0) return 0;


	// Check the IP Length
	if (pkt->ip.iplength_h != (char)DEFAULT_IP_LENGTH_H) return 0;
	else if (pkt->ip.iplength_l != (char)DEFAULT_IP_LENGTH_L) return 0;


	// Check the UDP header
	// Destination port
	if (pkt->ip.udp.dest_port_h != (char)DEFAULT_SOURCE_PORT_H) return 0;
	else if (pkt->ip.udp.dest_port_l != (char)DEFAULT_SOURCE_PORT_L) return 0;

	// UDP Length
	if (pkt->ip.udp.udplength_h != (char)DEFAULT_UDP_LENGTH_H) return 0;
	else if (pkt->ip.udp.udplength_l != (char)DEFAULT_UDP_LENGTH_L) return 0;

	return 1; //the packet is a vi_protocol packet!!
}


/* To determine if a received packet is an ARP Request for me */
int pkt_is_arprequest(unsigned char *buffer, int rx_len)
{

	// Packet IS an ARP Request packet asking me      --> return 1
	// Packet IS NOT an ARP Request packet asking me  --> return 0

	int pkt_length = 0;
	struct pkt_buffer_2 *pkt;			// ARP buffer
	pkt = (struct pkt_buffer_2 *)buffer;

	pkt_length = rx_len - 4; // we don't count the four bytes of FCS (Ethernet checksum)

	// Ethertype ARP (0x0806)
	if ((pkt->ethertype_h == 0x08) && (pkt->ethertype_l == 0x06)) {
		pkt_length = rx_len - 4;//is just an assignment to complete the if statement
	} else {
		return 0;
	}

	// Check whether the packet length is the expected one
	if ((pkt_length == 42) || (pkt_length == 60)) {
		pkt_length = rx_len - 4; // it's just an assignment to complete the if statement
	} else {
		return 0;
	}

	// Check Ethernet header
	// MAC is broadcast
	if ( (pkt->mac_dest5 == (char)0xFF) && (pkt->mac_dest4 == (char)0xFF) && (pkt->mac_dest3 == (char)0xFF)
			&& (pkt->mac_dest2 == (char)0xFF) && (pkt->mac_dest1 == (char)0xFF) && (pkt->mac_dest0 == (char)0xFF)) {
		pkt_length = rx_len - 4; // it's just an assignment to complete the if statement
	}

	// OPcode ARP request
	if (pkt->arp.opcode_l != 0x01) return 0;

	// We verify if the ARP Request is requesting my MAC (we see whether the target IP Address is my IP Address or not)
	if ( (pkt->arp.iptarget3 == (char)DEFAULT_IP_SOURCE_3) && (pkt->arp.iptarget2 == (char)DEFAULT_IP_SOURCE_2)
			&& (pkt->arp.iptarget1 == (char)DEFAULT_IP_SOURCE_1) && (pkt->arp.iptarget0 == (char)DEFAULT_IP_SOURCE_0)) {
		pkt_length = rx_len - 4; // it's just an assignment to complete the if statement
	} else {
		return 0;
	}

	return 1;
}


/* Change header parameters in order to send the packet to the client */
void pkt_changes_to_send(struct pkt_buffer *pkt)
{
	// We need to change some parameters in the packet:
	//		Ethernet: Dest/Source MAC
	//		IP:	TTL, Source/Dest IP, Checksum
	//		UDP: Source/Dest Port, Checksum
	//

	unsigned int ip_checksum, udp_checksum;

	// Ethernet changes
	pkt->mac_dest0 = pkt->mac_source0;
	pkt->mac_dest1 = pkt->mac_source1;
	pkt->mac_dest2 = pkt->mac_source2;
	pkt->mac_dest3 = pkt->mac_source3;
	pkt->mac_dest4 = pkt->mac_source4;
	pkt->mac_dest5 = pkt->mac_source5;
	pkt->mac_source0 = DEFAULT_SOURCE_MAC_0;
	pkt->mac_source1 = DEFAULT_SOURCE_MAC_1;
	pkt->mac_source2 = DEFAULT_SOURCE_MAC_2;
	pkt->mac_source3 = DEFAULT_SOURCE_MAC_3;
	pkt->mac_source4 = DEFAULT_SOURCE_MAC_4;
	pkt->mac_source5 = DEFAULT_SOURCE_MAC_5;

	// IP changes
	pkt->ip.ttl = DEFAULT_TTL;
	pkt->ip.ipdest0 = pkt->ip.ipsource0;
	pkt->ip.ipdest1 = pkt->ip.ipsource1;
	pkt->ip.ipdest2 = pkt->ip.ipsource2;
	pkt->ip.ipdest3 = pkt->ip.ipsource3;
	pkt->ip.ipsource0 = DEFAULT_IP_SOURCE_0;
	pkt->ip.ipsource1 = DEFAULT_IP_SOURCE_1;
	pkt->ip.ipsource2 = DEFAULT_IP_SOURCE_2;
	pkt->ip.ipsource3 = DEFAULT_IP_SOURCE_3;

	pkt->ip.ipcrc_l = 0x00;	// we clear it because the field is used to ...
	pkt->ip.ipcrc_h = 0x00;	// ... calculate the IP checksum
	ip_checksum = calculate_ip_checksum(pkt);
	pkt->ip.ipcrc_l = (char)ip_checksum&0xff;
	pkt->ip.ipcrc_h = (char)(ip_checksum >> 8)&0xff;

	// UDP changes
	pkt->ip.udp.dest_port_h = pkt->ip.udp.source_port_h;
	pkt->ip.udp.dest_port_l = pkt->ip.udp.source_port_l;
	pkt->ip.udp.source_port_h = DEFAULT_SOURCE_PORT_H;
	pkt->ip.udp.source_port_l = DEFAULT_SOURCE_PORT_L;

	pkt->ip.udp.crc_h = 0x00; // we clear it because the field is used to ...
	pkt->ip.udp.crc_l = 0x00; // ... calculate the UDP checksum
	udp_checksum = calculate_udp_checksum(pkt); // UDP checksum
	pkt->ip.udp.crc_l = (char)udp_checksum&0xff;
	pkt->ip.udp.crc_h = (char)(udp_checksum >> 8)&0xff;

}


/* Change ARP Request fields in order to send the ARP Replay */
void pkt_arp_changes_to_send(struct pkt_buffer_2 *pkt)
{

	// Ethernet Header
	// Changes: MAC dest/source
	pkt->mac_dest5 = pkt->arp.mac_sender5;
	pkt->mac_dest4 = pkt->arp.mac_sender4;
	pkt->mac_dest3 = pkt->arp.mac_sender3;
	pkt->mac_dest2 = pkt->arp.mac_sender2;
	pkt->mac_dest1 = pkt->arp.mac_sender1;
	pkt->mac_dest0 = pkt->arp.mac_sender0;

	pkt->mac_source5 = DEFAULT_SOURCE_MAC_5;
	pkt->mac_source4 = DEFAULT_SOURCE_MAC_4;
	pkt->mac_source3 = DEFAULT_SOURCE_MAC_3;
	pkt->mac_source2 = DEFAULT_SOURCE_MAC_2;
	pkt->mac_source1 = DEFAULT_SOURCE_MAC_1;
	pkt->mac_source0 = DEFAULT_SOURCE_MAC_0;

	// ARP Header
	// Changes: OPCode, Sender/Target MAC, Sender/Target IP
	pkt->arp.opcode_l = 0x02; // ARP Replay

	pkt->arp.mac_target5 = pkt->arp.mac_sender5;
	pkt->arp.mac_target4 = pkt->arp.mac_sender4;
	pkt->arp.mac_target3 = pkt->arp.mac_sender3;
	pkt->arp.mac_target2 = pkt->arp.mac_sender2;
	pkt->arp.mac_target1 = pkt->arp.mac_sender1;
	pkt->arp.mac_target0 = pkt->arp.mac_sender0;

	pkt->arp.iptarget3 = pkt->arp.ipsender3;
	pkt->arp.iptarget2 = pkt->arp.ipsender2;
	pkt->arp.iptarget1 = pkt->arp.ipsender1;
	pkt->arp.iptarget0 = pkt->arp.ipsender0;

	pkt->arp.mac_sender5 = DEFAULT_SOURCE_MAC_5;
	pkt->arp.mac_sender4 = DEFAULT_SOURCE_MAC_4;
	pkt->arp.mac_sender3 = DEFAULT_SOURCE_MAC_3;
	pkt->arp.mac_sender2 = DEFAULT_SOURCE_MAC_2;
	pkt->arp.mac_sender1 = DEFAULT_SOURCE_MAC_1;
	pkt->arp.mac_sender0 = DEFAULT_SOURCE_MAC_0;

	pkt->arp.ipsender3 = DEFAULT_IP_SOURCE_3;
	pkt->arp.ipsender2 = DEFAULT_IP_SOURCE_2;
	pkt->arp.ipsender1 = DEFAULT_IP_SOURCE_1;
	pkt->arp.ipsender0 = DEFAULT_IP_SOURCE_0;

}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

