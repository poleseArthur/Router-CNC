#include "Arduino.h"
#include "buttons.h"
#include "heart_beat.h"
#include "lcd_telas.h"
#include "serial.h"
#include "controller.h"
#include <LiquidCrystal.h>
#include <Bounce2.h>

LiquidCrystal lcd(26, 28, 36, 34, 32, 30);

int state = INIT;
bool coverClosed = true;
int overTravel = 0;

void init_lcd_display()
{
  lcd.begin(16, 2);
  pinMode(HEART_BEAT, OUTPUT);
}

void init_screen()
{
	while(state == INIT)
	{
		update_buttons();
		lcd.setCursor(3,0);
		lcd.print("CNC Router");
		lcd.setCursor(0,1);
		lcd.print("Home Ret? <S>");
		if(up_button()) {
			setRpmX(100);
			stepX(-1);
			setRpmY(100);
			stepY(1);
			setRpmZ(100);
			stepZ(1);
			setRpmS(100);
			stepS(1);
		}
		if(set_button()) {
			if(coverClosed == false){
				state = ERROR;
			}
			else{
				state = PROGRESS;
			}

		}
	}

}

void error_screen()
{
	while(state == ERROR)
	{
		lcd.setCursor(0,0);
		lcd.print("Erro: Please");
		lcd.setCursor(0,1);
		lcd.print("Close the Cover!");
		delay(3000);
		coverClosed = true;
		state = INIT;
	}

}

void progress_screen(){
	while (state == PROGRESS){
		update_buttons();
		lcd.setCursor(0, 0);
		lcd.print("Machine Home");
		lcd.setCursor(0, 1);
		lcd.print("in progress...");

		if(coverClosed == false) state = INIT;

		z = y = x = 0;
		if(set_button()) state = POSITION;
	}
}

void position_screen(){
	int aux = 0;
	int aux1 = 0;
	int aux2 = 0;
	z = 149;
	y = 299;
	x = 199;
	while (state == POSITION){
		comands();
		update_buttons();
		if(aux1 == 0){
			lcd.setCursor(0, 0);
			lcd.print("S:    ");
			lcd.print(s);

			lcd.setCursor(10, 0);
			lcd.print("Z: ");
			lcd.print(z);

			lcd.setCursor(0, 1);
			lcd.print("X:    ");
			lcd.print(x);

			lcd.setCursor(10, 1);
			lcd.print("Y: ");
			lcd.print(y);
		}

		if(set_button()) state = OVERTRAVEL;

		if(aux == 0) lcd.noCursor();

		if(p_button()) aux = 1;


			while(aux == 1){ //Z
				update_buttons();

				if(aux2 == 0){
					lcd.setCursor(10, 0);
					lcd.cursor();
				}

				if(p_button()){
					aux2++;
					aux = 2; break;
				}
				if(up_button()){
					z++;
					if(z > 150){
						z = 150;
						aux = 0;
						overTravel = 1;
						state = OVERTRAVEL;
					}
					if(z < 150) stepZ(1);
					lcd.setCursor(13, 0);
					lcd.print(z);
				}
				if(down_button()){
					z--;
					if(z <= -1){
						z = 0;
						overTravel = 2;
						lcd.clear();
						aux = 0;
						state = OVERTRAVEL;
					}
					if(z > 0) stepZ(-1);

					lcd.setCursor(13, 0);
					lcd.print(z);
				}
			}

			while(aux == 2){//X
				update_buttons();

				if(aux2 == 1){
					lcd.setCursor(0, 1);
					lcd.cursor();
				}

				if(p_button()){
					aux2++;
					aux = 3; break;
				}
				if(up_button()){
					x++;
					if(x > 200){
						x = 200;
						aux = 0;
						overTravel = 3;
						state = OVERTRAVEL;
					}

					if(x < 200) stepX(1);

					lcd.setCursor(6, 1);
					lcd.print(x);
				}
				if(down_button()){
					x--;
					if(x <= -1){
						x = 0;
						aux = 0;
						overTravel = 4;
						state = OVERTRAVEL;
					}
					if(x > 0) stepX(1);

					lcd.setCursor(6, 1);
					lcd.print(x);
				}
			}

			while(aux == 3){ //Y
				update_buttons();

				if(aux2 == 2){
					lcd.setCursor(10, 1);
					lcd.cursor();
				}

				if(p_button()){
					aux2 = 0;
					aux = 0; break;
				}
				if(up_button()){
					y++;

					if(y > 300){
						y = 300;
						aux = 0;
						overTravel = 5;
						state = OVERTRAVEL;
					}
					if(y < 300) stepY(1);

					lcd.setCursor(13, 1);
					lcd.print(y);
				}
				if(down_button()){
					y--;
					if(y <= -1){
						y = 0;
						aux = 0;
						overTravel = 6;
						state = OVERTRAVEL;
					}
					if(y > 0) stepY(1);

					lcd.setCursor(13, 1);
					lcd.print(y);
				}
			}


		}

}


void overtravel_screen(){

	while (state == OVERTRAVEL){
		update_buttons();
		lcd.setCursor(2, 0);
		lcd.print("Over  Travel");
		lcd.setCursor(4, 1);
		lcd.print("Axis: ");
		if(overTravel == 1) lcd.print("Z+");
		else if(overTravel == 2) lcd.print("Z-");
		else if(overTravel == 3) lcd.print("X+");
		else if(overTravel == 4) lcd.print("X-");
		else if(overTravel == 5) lcd.print("Y+");
		else if(overTravel == 6) lcd.print("Y-");

		lcd.noCursor();
		if(set_button()) state = POSITION;

	}

}

void funcao_principal()
{
  switch (state)
  {
    case INIT:
      lcd.clear();
      init_screen();
      break;

    case ERROR:
      lcd.clear();
      error_screen();
      break;

    case PROGRESS:
      lcd.clear();
      progress_screen();
      break;

    case POSITION:
      lcd.clear();
      position_screen();
      break;

    case OVERTRAVEL:
      lcd.clear();
      overtravel_screen();
      break;
  }
}

