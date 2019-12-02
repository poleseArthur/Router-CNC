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
bool coverClosed = false;

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
			stepX(1);
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
	while (state == POSITION){
		comands();
		update_buttons();
		lcd.setCursor(0, 0);
		lcd.print("S:    ");
		lcd.print(s);

		lcd.setCursor(10, 0);
		lcd.print("Z:   ");
		lcd.print(z);

		lcd.setCursor(0, 1);
		lcd.print("X:    ");
		lcd.print(x);

		lcd.setCursor(10, 1);
		lcd.print("Y:   ");
		lcd.print(y);
		if(set_button()) state = OVERTRAVEL;

		if(aux == 0) lcd.noCursor();

		if(p_button()) aux = 1;


			while(aux == 1){ //Z
				update_buttons();
				lcd.setCursor(10, 0);
				lcd.cursor();
				if(p_button()){
					aux = 2; break;
				}
				if(up_button()){
					z++;
					if(z > 150) z = 150;
				}
				if(down_button()){
					z--;
					if(z < 0) z = 0;
				}
			}

			while(aux == 2){//X
				update_buttons();
				lcd.setCursor(0, 1);
				lcd.cursor();
				if(p_button()){
					aux = 3; break;
				}
				if(up_button()){
					x++;
					if(x > 200) x = 200;
				}
				if(down_button()){
					x--;
					if(x < 0) x = 0;
				}
			}

			while(aux == 3){ //Y
				update_buttons();
				lcd.setCursor(10, 1);
				lcd.cursor();
				if(p_button()){
					aux = 0; break;
				}
				if(up_button()){
					y++;
					if(y > 300) y = 300;
				}
				if(down_button()){
					y--;
					if(y < 0) y = 0;
				}
			}


		}

}


void overtravel_screen(){
	while (state == OVERTRAVEL){
		lcd.setCursor(2, 0);
		lcd.print("Over  Travel");
		lcd.setCursor(4, 1);
		lcd.print("Axis: X+");
		if(set_button()) state = INIT;

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

