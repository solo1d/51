#include <reg52.h>
#include <intrins.h>

unsigned int i =0;
unsigned int n =0;
unsigned int  smg1=0;	 //h0 
unsigned int  smg2=1;	 //h1
unsigned int  smg3=2;	 //m0
unsigned int  smg4=3;	 //m1

sbit k2 = P3^4;  // h1 +
sbit k3 = P3^5;	 // h1 -
sbit k4 = P3^6;	 //	m1 +
sbit k5 = P3^7;	 //	m1 -

unsigned char  zi[14] = {
 0x3f, 0x06, 0x5b , 0x4f , 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f ,0x3f,0x3f,0x3f,0x3f
}; 


void init_sys(void){
	P0 = 0xff;
	P1 = 0xfe;
	P2 = 0x0f;
	P3 = 0xff;
	ES = 0;
	EA = 0;
}

void init_timer1(void){
	TMOD = 0x10;
	TH1 = 0x4c;	  //50ms
//	TH1 = 0xdc;    //10ms
	TL1 = 0x00;
	EA =1;
	ET1 = 1;
	TR1 = 1;
}

void delay(void){
 	int j,i;
	for(j=20; j>0; j--)
		for( i =10; i>0; i--);
}

void msg(void){

  	n++;
	n %= 4;
	switch(n){
	case 0 : P2 = 0x8f; P0 = zi[smg4]; break;
	case 1 : P2 = 0x4f; P0 = zi[smg3]; break;
	case 2 : P2 = 0x2f; P0 = zi[smg2] | 0x80; break;
	case 3 : P2 = 0x1f; P0 = zi[smg1]; break;
	}
}

void anjian(void){
		if( k2 == 0)
			smg2++;
		
		while( k3 == 0){
			if( smg2 == 0){
				  if(smg1 == 0){
				   	   smg1 = 2;
				  	   smg2 = 3;
					   break;
				  }
				  else{
				  	smg2 = 9;
					smg1--;
					break;
				  }
		    }
			smg2--;
			break;
		}
		
		if( k4 == 0)
			smg4++;

		if( k5 == 0){
			if( smg4 == 0){
				do{
					if( smg1 == 0 && smg2 ==0 && smg3 == 0 ){
						smg1=2;
						smg2=3;
						smg3=5;
						break;
					}
					if( smg1 != 0 && smg2 ==0 && smg3 ==0  ){
						smg1--;
						smg2=9;
						smg3=5;
						break;
					}
					if( smg2 !=0 && smg3 ==0 ){
						smg2--;
						smg3=5;
						break;
					}
					if(  smg3 != 0){
						smg3--;
						break;
					}
			   }while(0);
			smg4=9;
			}
		else
			smg4--;
	}
}


void main(void){
	init_sys();
	init_timer1();

	while(1){
		msg();
 	    delay();

	}
}
	
void timer1() interrupt 3{
	TH1 = 0x4c;
	TL1 = 0x00;
	i++;
	if( (i%5) == 0)
		anjian();
	if( (i % 20) == 0 ){
		P1 = _crol_(P1,1);
		
		if( i >= 1200 ){
			i= 0;
			smg4++;
		}
		if( smg4 > 9 ){
		 	smg4=0;
			smg3++;
		}
		if( smg3 >= 6 ){
			smg3 =0; 
			smg2++;
		}
		if( smg2 >= 10  && smg1 < 2 ) {
			smg2 = 0;
			smg1++;
		}
		if( smg1 >= 2 && smg2 >= 4){
		 	smg2 = 0;
			smg1 = 0;
		}
//		if( smg1 >= 3){
//			smg1=0;
//		}
			
	}
}
