#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  
  //If green light is on make noise in a period of 1000
  // else dont do any noise 
   
  if(green_on && red_on){
    buzzer_set_period(1000);
  }
  else{
    buzzer_set_period(0);
  }
 
  return changed;
}
  




void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}




