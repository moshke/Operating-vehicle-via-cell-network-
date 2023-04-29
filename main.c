#include <absacc.h>
#include <at89c5131.h>
#include <stdio.h>
#define PORT_LCD P0
sbit en_lcd = P3 ^ 0;
sbit RS = P3 ^ 1;
sbit std = P1 ^ 0;

#define motor P2
#define mozes P1_5
//=================================================================================================
//===============================LCD===============================================================
//=================================================================================================
void lcd_config();
void delay_lcd();
void lcd_clr();
void lcd_line(char line_number, char p);
void lcd_display(char character);
void lcd_string(char str[]);
send_command(unsigned char command);
send_data(char data_to_lcd);
// void get_key1();

void delay_lcd()  // small delay_lcd
{
  int timer = 200;
  while (timer--)
    ;
}

Void deley(long time) { For(; time > 0; time--); }

//=======================CONFIG THE
//LCD============================================================

Void lcd_ config()  // Initialization of The LCD
{
  delay_ lcd();
  send_command(0x38);  // 8bit,2 line,5*7 dot
  delay_lcd();
  send_command(0x0e);  // display on ,cursor on,cursor blink
  delay_lcd();
  send_command(0x01);  // clear_display
  delay_lcd();
  send_command(0x06);  // increment cursor,no display shift
}
//===========================LCD LINE
//NUMBER=======================================================
void lcd_line(char line_number, char p) {
  switch (line_number) {
    case 1:
      delay_lcd();
      send_command(0x80 + p);
      break;

    case 2:
      delay_lcd();
      send_command(0xc0 + p);
      break;
  }
}

//==========================================DISPLAY THE CHARACTER ON THE
//LCD=======================

void lcd_display(char character) {
  delay_lcd();
  send_data(character);  // Send The character to the LCD
}

void lcd_string(char str[]) {
  int i = 0;
  while (str[i]) {
    delay_lcd();

    if (str[i] >= 0xa0)  // if hebrew

      send_data(str[i++] - 0x40);
    else

      send_data(str[i++]);
  }
}

void lcd_clr() { send_command(0x01); }
send_command(unsigned char command) {
  RS = 0;
  PORT_LCD = command;
  en_lcd = 0;
  delay_lcd();
  en_lcd = 1;
  delay_lcd();
  en_lcd = 0;
}

send_data(char data_to_lcd) {
  RS = 1;
  PORT_LCD = data_to_lcd;
  en_lcd = 0;
  delay_lcd();
  en_lcd = 1;
  delay_lcd();
  en_lcd = 0;
}
char get_key1() {
  char key1;
  while (std == 0)
    ;
  key1 = P1 & 0x1e;
  return key1;
}
char get_sh1() {
  char key7;

  key7 = P1 & 0xe0;

  return key7;
}

char forward() {
  P2_0 = 1;
  P2_1 = 0;

  P2_2 = 1;
  P2_3 = 0;
}
char back() {
  P2_0 = 0;
  P2_1 = 1;

  P2_2 = 0;
  P2_3 = 1;
}
char yamin() {
  P2_0 = 1;
  P2_1 = 0;

  P2_2 = 0;
  P2_3 = 0;
}
char smual() {
  P2_0 = 0;
  P2_1 = 0;

  P2_2 = 1;
  P2_3 = 0;
}
char stop() {
  P2_0 = 0;
  P2_1 = 0;

  P2_2 = 0;
  P2_3 = 0;
}

//===========================cell
//control========================================

//============================self
//driving===========================================================

//===============================================main=========================================================

void main() {
  char sensors, key, lavan;

  lcd_config();  // Initialization of The LCD

  lcd_line(1, 1);
  lcd_string("welcome");

  deley(9000);

  lcd_clr();

  lcd_line(1, 1);
  lcd_string("to smart ");

  lcd_line(2, 1);
  lcd_string("phone car");
  deley(50000);

  lcd_clr();

  lcd_line(1, 1);
  lcd_string("or");

  lcd_line(2, 1);
  lcd_string("moshe");
  deley(50000);

  while (1) {
    lcd_clr();
    lcd_line(1, 1);
    lcd_string("waiting for call");
    lcd_line(2, 1);
    lcd_string("choose code");
    deley(32000);
  x5:
    lcd_line(1, 1);
    lcd_string("please press");

    lcd_line(2, 1);
    lcd_string("a code number");
    deley(32000);

    while (std == 0)
      ;
    stop();
    lcd_line(1, 1);
    lcd_string("telephone busy");
  x2:
    key = get_key1();

    if (key == 0x04)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("forward");
      lcd_line(2, 1);
      lcd_string("car");
      forward();
      deley(20000);
      goto x2;

    }

    else if (key == 0x0a)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("back");
      lcd_line(2, 1);
      lcd_string("car");
      back();
      deley(30000);

      goto x2;
    } else if (key == 0x10)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("stop ");
      lcd_line(2, 1);
      lcd_string("  car");
      stop();
      deley(20000);
      goto x2;

    } else if (key == 0x0c)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("auto ");
      lcd_line(2, 1);
      lcd_string("      ");
      forward();
    x33:
      while (mozes == 0)

      {
        back();
        deley(30000);
        deley(30000);
        stop();
        goto x2;
      }

      goto x33;
    } else if (key == 0x02)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("left ");
      lcd_line(2, 1);
      lcd_string("      ");
      smual();

      goto x2;

    }

    else if (key == 0x06)

    {
      lcd_clr();
      lcd_line(1, 1);
      lcd_string("right ");
      lcd_line(2, 1);
      lcd_string("      ");
      yamin();

      goto x2;
    }

    else {
      goto x5;
    }
  }
}