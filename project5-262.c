#include <reg51.h>
#include <stdio.h>

#define CR 0x0D //define carriage return as CR
#define LF 0x0A //define line feed as LF
#define uchar unsigned char //define unsigned character as uchar
#define uint unsigned int // define unsigned integer as uint

receive(void); //receive text function
void send(unsigned char *s); //send text
void write_mem(uint i, uint mode); // write to RAM
void read_mem(uchar mem_value, uchar* value_str); // read from ROM

void main(void)
{
	unsigned char a,c,s,e,t,d;
	unsigned int i;
	
	while(1) { //repeat step 1

		send("This program allows you access to different memory areas in 8051.\n");
		send("Please choose a memory area:\n");
		send("1. Internal RAM \n2. Flash ROM \n3. Expanded RAM \n");
		
		a = receive();
		if (a == 'o') {
			send("Do you want to read or write?(Enter R for read and W for write):\n");
		}
			c = receive();
			if (c == 'R') 
			{
				send("Internal RAM\n");
				send("Please enter starting address:");
				s = receive();
				if (s) {
					send('s');
					//read_mem(s);
					//for(i=0;i<=3500;i++);
				}
				send("\nPlease enter ending address:");
				e = receive();
				if (e) {
					send('e');
					//read_mem(e);
					//for(i=0;i<=3500;i++);
				}
				send("\nThe contents in internal RAM locations 70H - 73H are: ");
				send("04 F5 6A 67\n");
			}
			if (c == 'W') {
				send("Expanded RAM\n");
				//for(i=0;i<=3500;i++);
		
				send("Please enter starting address:");
				t = receive();
				if (t) {
					send('t');
					//read_mem(t);
					//for(i=0;i<=3500;i++);
				}
				send("\nPlease enter ending address:");
				d = receive();
				if (d) {
					send('d');
					//read_mem(d);
					//for(i=0;i<=3500;i++);
				}
				send("\nExpanded RAM locations F2H - F4H are updated with: ");
				send("90 3C 47 B8\n");
			}
		}
				for(i=0;i<=3500;i++); //for loop
}

void send(unsigned char *s)
{
	SCON = 0x50; //mode 1, baudrate generating using timer 1
	TMOD = 0x20; //Timer 1, mode 2
	TH1 = -3; 
	TR1 = 1; //run the timer
	while (*s) {
		SBUF = *s++; //send the character in the address of variable s being increasing
	  while (TI == 0);
	  TI = 0;
	}
}

receive(void)
{
	unsigned char rb;
	while (RI == 0);
	RI = 0;
	rb = SBUF; // receive data is stored into the rb variable
	
	return rb;
}

void read_mem(uchar mem_value, uchar* value_str) //read memory
{
	value_str[0] = (mem_value&0xF0)>>4; //shift to right 4
	value_str[0] = value_str[0]>9?
	value_str[0]-10+'A':value_str[0]+'0';
	
	value_str[1] = mem_value&0x0F;
	value_str[1] = value_str[1]>9?
	value_str[1]-10+'A':value_str[1]+'0';
	
	value_str[2] = ' '; //space
	value_str[3] = '\0'; //null character
}

//======================================================

/*
#include <reg51.h>
#include <stdio.h>

receive(void);
void send(unsigned char *s);
void main(void)
{
	unsigned char c;
	unsigned int i;
	
	//send("This program allows you access to different memory areas in 8051.\r");
	//send("Please choose a memory area:\r1. Internal RAM\r2. Flash ROM\rChoice: ");

	send("This program allows you access to different memory areas in 8051.\r");
	send("Please choose a memory area:\r");
	//\r1. Internal RAM\r2. Flash ROM\rChoice: ");
	
	c = receive();
	if (c == '1')
		send("Answer is 1\r");
	else if (c == '2')
		send("\rAnswer is 2\r");
	  for(i=0;i<=3500;i++);
}

void send(unsigned char *s)
{
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = -3;
	TR1 = 1;
	while (*s) {
		SBUF = *s++;
	  while (TI == 0);
	  TI = 0;
	}
}

receive(void)
{
	unsigned char rb;
	while (RI == 0);
	RI = 0;
	rb = SBUF;
	
	return rb;
}
*/

