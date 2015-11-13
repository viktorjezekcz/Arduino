/*
 * BUDIK SE ZOBRAZOVANIM AKTUALNI TEPLOTY
 * ZAVERECNA MATURITNI PRACE
 *
 * Adresa displeje na I2C sbernici: 0x3F
 *
 * Autor: Viktor Jezek <viktorjezek[at]outlook[dot]cz>
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; //řádky
const byte COLS = 4; //sloupce

/* Jak membránová klávesnice vypadá: */
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {52, 50, 48, 46};
byte colPins[COLS] = {44, 42, 40, 38};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //načte modul klávesnice

//nastavíme adresu a typ displeje
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
  lcd.init(); //oživení LCD
  lcd.backlight();

}

void loop()
{
  uvod();
}

void uvod() {
  char customKey = customKeypad.getKey();
  lcd.setCursor ( 6, 3 ); //lcd.setCursor (pozice na řádku, číslo řádku);
  lcd.print ("MENU (#)");
  if (customKey) {
    //char volba;
    switch (customKey)
    {
      case ('#'):
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("                    ");
        menu();
        break;
      default:
        break;
    }          // konec příkazu switch
  }
}

void menu () {
zac:
  char customKey = customKeypad.getKey();

  lcd.setCursor(0, 0);
  lcd.print("(A) Datum a cas");
  lcd.setCursor(0, 1);
  lcd.print("(B) Budik");
  lcd.setCursor(0, 2);
  lcd.print("(C) Ostatni");
  lcd.setCursor(0, 3);
  lcd.print("(D) Zpet");
  if (customKey) {
    switch (customKey)
    {
      case ('A'):
        lcd.setCursor(1, 0);
        lcd.print("(A) Datum");
        lcd.setCursor(2,0);
        lcd.print("(B) Cas");
        break;
      case ('B'):
        lcd.setCursor(1, 0);
        /* zde bude část kódu pro nastavení budíku; využití paměti EEPROM */
        break;
      case ('C'):
        /* zde bude část kódu, která bude sloužit pro nastavení jazyka a stupnice pro teplotu (°C nebo °F) */
        break;
      case ('D'):
        lcd.clear();
        goto konec;
        break;
      default:
        break;
    }
  }
  goto zac;
  konec:
  lcd.clear();
}
