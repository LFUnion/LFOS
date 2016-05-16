#include "driver_api.h"


int driver_counter = 0;
int *list_of_drivers;


// for futur use
// request 
void driver_counter_increase(){
	 ++driver_counter;
		
}

void driver_counter_reset(){
	driver_counter = 0;
		
}



void send_to_master_api(int number){
	if (number ==ATA){
		
	}	
	else if (number == KEYBOARD){
		
	}
	else if (number == RTC){
		
	}
	else if (number == SERIAL){
		
	}
	else if (number == VGA){
		
	}


}
// end


