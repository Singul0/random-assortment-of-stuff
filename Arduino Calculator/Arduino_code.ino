/*
 * Arduino Keypad calculator for a school project.
 * Code is based from Elktros's github gist, adjusted and abstracted as needed. + indonesian  comments
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] = {
  {'1', '2', '3', '/'},
  {'4', '5', '6', '*'},
  {'7', '8', '9', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = { 0, 1, 2, 3 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 9, 6, 5, 4 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


boolean presentValue = false; // variable ini menyatakan jika num1 sudah diberi op (operator). digunakan agar menyatakan input adalah untuk num1 atau num2
boolean is_continuing_from_prev_calculation = false;
boolean final = false;
String calculator_mode = "calculator"; //Mode kalkulator atau game (ide game pending)? TODO: IMPLEMENT GAME AND MODE CHANGES
String num1, num2; // num1 (angka yang dioperasikan dengan num2) num2 (angka yang dioperasikan dengan num2)
int clear_or_reset_counter = 0; //seberapa banyaknya kalkulator sudah direset (buat mengganti mode operasi kalkulator TODO:rencananya)
double answer; //hasil operasi aritmatika
char op; //operator yang digunakan, perkalian/pertambahan/pembagian/pengurangan.

void intro_display_text(String text_above, String text_below)
{
  lcd.setCursor(0, 0);
  lcd.print(text_above);
  lcd.setCursor(0, 1);
  lcd.print(text_below);
  delay(5000);
  lcd.clear();
}


void calculator_actual_mode(char key)
{ //fungsi buat kerjanya kalkulator
  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'))
  {
    if (key == 0)
    {
      if (num1 != NULL || num2 != NULL) //Jika num1 / num2 belum ada nomor maka input 0 tidak akan terdeteksi
      return;
    }
    if (!presentValue && !is_continuing_from_prev_calculation) //Apakah operator sudah dinyatakan? jika sudah num2, jika tidak num1
    {
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //untuk memberikan satu whitespace buat operator
      lcd.print(num1);
    }
    else if (presentValue)
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')) //Pemilihan operator
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      lcd.setCursor(15,0);
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){ 
    if (op == '+'){
      answer = num1.toDouble() + num2.toDouble();
    }
    else if (op == '-'){
      answer = num1.toDouble() - num2.toDouble();
    }
    else if (op == '*'){
      answer = num1.toDouble() * num2.toDouble();
    }
    else if (op == '/'){
      answer = num1.toDouble() / num2.toDouble();
    }    
      lcd.clear();
      lcd.print(answer);
      presentValue = false;
      is_continuing_from_prev_calculation = true;
      final = false;
      num1 = String(answer);
      num2 = "";
      answer = 0;
      op = ' ';

  }
  else if (key != NO_KEY && key == 'C'){ //reset menjadi semula
    lcd.clear();
    presentValue = false;
    final = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
    clear_or_reset_counter = clear_or_reset_counter + 1; //sebenernya bisa si, cuman clear_or_reset_counter++ tapi susah di baca imo -_-
  }
}


void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  intro_display_text("P5 Kelompok 1 XI.1", "Kalkulator");
  intro_display_text("Berdasarkan", "Arduino");
  delay(5000);
  lcd.clear();
}

void loop()
{
  char key = myKeypad.getKey();
  if(calculator_mode == "calculator")
  {
    calculator_actual_mode(key);
  }
  else{
    calculator_actual_mode(key); //TODO: FUNCTION FOR COWS AND BULLS GAMEMODE
  }
}