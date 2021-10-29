#include <Keyboard.h>
#include <Mouse.h>

char Order;

String stringOrder;

void setup() {
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
}

//Function def
void MoveTo( int x,  int y) {
  for (int i = 0; i < 25; i ++) {
    Mouse.move(-120, -120, 0);
  }
  int rep_x =  x / 120;
  int rep_y = y / 120;
  float remain_x = x % 120;
  float remain_y = y % 120;

  for (int i = 0 ; i < rep_x; i++) {
    Mouse.move(120, 0, 0);
    delay(10);
  }
  for (int i = 0 ; i < rep_y; i++) {
    Mouse.move(0, 120, 0);
    delay(10);
  }
  Mouse.move(remain_x, remain_y, 0);
  delay(10);
}

void Move( int x,  int y) {
  int kx = 1;
  int ky = 1;
  if ( x < 0 ) {
    kx = -kx;
  }
  if (y < 0 ) {
    ky = -ky;
  }

  int rep_x =  abs(x) / 120;
  int rep_y = abs(y) / 120;
  float remain_x = abs(x) % 120;
  float remain_y = abs(y) % 120;

  for (int i = 0 ; i < rep_x; i++) {
    Mouse.move(120 * kx, 0, 0);
    delay(10);
  }
  for (int i = 0 ; i < rep_y; i++) {
    Mouse.move(0, 120 * ky, 0);
    delay(10);
  }
  Mouse.move(remain_x * kx, remain_y * ky, 0);
  delay(10);
}

void ArrowPress( char Key, float sec) {
  delay(random(20, 30));
  if ( Key == 'E' ) {
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(sec * 1000);
    Keyboard.release(KEY_RIGHT_ARROW);
  } else if (Key == 'W' ) {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(sec * 1000);
    Keyboard.release(KEY_LEFT_ARROW);
  } else if (Key == 'N' ) {
    Keyboard.press(KEY_UP_ARROW);
    delay(sec * 1000);
    Keyboard.release(KEY_UP_ARROW);
  } else if (Key == 'S' ) {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(sec * 1000);
    Keyboard.release(KEY_DOWN_ARROW);
  }
  delay(random(20, 30));
  Keyboard.releaseAll();
  delay(random(20, 30));
}

void KeyPressControlled( char Key, int rep) {
  Keyboard.press(KEY_LEFT_CTRL);
  delay(random(20, 30));
  for ( int i = 0; i < rep; i++ ) {
    Keyboard.press(Key);
    delay(random(20, 30));
    Keyboard.release(Key);
    delay(random(20, 30));
  }
  Keyboard.release(KEY_LEFT_CTRL);
  delay(random(20, 30));
}

void KeyPressAlted( char Key, int rep) {
  Keyboard.press(KEY_LEFT_ALT);
  delay(random(20, 30));
  for ( int i = 0; i < rep; i++ ) {
    Keyboard.press(Key);
    delay(random(20, 30));
    Keyboard.release(Key);
    delay(random(20, 30));
  }
  Keyboard.release(KEY_LEFT_ALT);
  delay(random(20, 30));
}

void KeyPress( char Key, int rep) {
  for ( int i = 0; i < rep; i++ ) {
    Keyboard.press(Key);
    delay(random(20, 30));
    Keyboard.release(Key);
    delay(random(20, 30));
  }
}

void KeyPress_bold( char Key, int rep) {
  for ( int i = 0; i < rep; i++ ) {
    Keyboard.press(Key);
    delay(100);
    Keyboard.release(Key);
    delay(100);
  }
}
void PressESC() {
  Keyboard.press(KEY_ESC);
  delay(100);
  Keyboard.release(KEY_ESC);
  delay(100);
}
void PressEnter() {
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.release(KEY_RETURN);
  delay(100);
}
void MouseClick( String button, int rep ) {
  if ( button == "left" ) {
    for (int i = 0 ; i < rep ; i++) {
      Mouse.press(MOUSE_LEFT);
      delay(25);
      Mouse.release(MOUSE_LEFT);
      delay(25);
    }
  } else if ( button == "right" ) {
    for (int i = 0 ; i < rep ; i++) {
      Mouse.press(MOUSE_RIGHT);
      delay(25);
      Mouse.release(MOUSE_RIGHT);
      delay(25);
    }
  }
}

void MouseClickBold( String button, int rep ) {
  if ( button == "left" ) {
    for (int i = 0 ; i < rep ; i++) {
      Mouse.press(MOUSE_LEFT);
      delay(100);
      Mouse.release(MOUSE_LEFT);
      delay(100);
    }
  } else if ( button == "right" ) {
    for (int i = 0 ; i < rep ; i++) {
      Mouse.press(MOUSE_RIGHT);
      delay(100);
      Mouse.release(MOUSE_RIGHT);
      delay(100);
    }
  }
}

void loop() {

  while (Serial.available()) {
    stringOrder = Serial.readStringUntil('_');

    if ( stringOrder == "arrowpress") {
      Order = Serial.readStringUntil('_')[0];
      float sec = Serial.readStringUntil('_').toFloat();
      ArrowPress(Order, sec);
    }
    else if (stringOrder == "mouseclick") {
      String button = Serial.readStringUntil('_');
      int rep = Serial.readStringUntil('_').toInt();
      MouseClick(button, rep);
    }
    else if ( stringOrder == "mousemoveto" ) {
      int x = Serial.readStringUntil('_').toInt();
      int y = Serial.readStringUntil('_').toInt();
      MoveTo(x, y);
    }
    else if ( stringOrder == "mousemove" ) {
      int x = Serial.readStringUntil('_').toInt();
      int y = Serial.readStringUntil('_').toInt();
      Move(x, y);
    }
    else if (stringOrder == "keypress") {
      char key = Serial.readStringUntil('_')[0];
      int rep = Serial.readStringUntil('_').toInt();
      KeyPress(key, rep);
    }
    else if (stringOrder == "keypressB") {
      char key = Serial.readStringUntil('_')[0];
      int rep = Serial.readStringUntil('_').toInt();
      KeyPress_bold(key, rep);
    }
    else if (stringOrder == "ctrlkeypress") {
      char key = Serial.readStringUntil('_')[0];
      int rep = Serial.readStringUntil('_').toInt();
      KeyPressControlled(key, rep);
    }
    else if (stringOrder == "altkeypress") {
      char key = Serial.readStringUntil('_')[0];
      int rep = Serial.readStringUntil('_').toInt();
      KeyPressAlted(key, rep);
    }
    else if (stringOrder == "tabpress") {
      Keyboard.press(KEY_TAB);
      delay(50);
      Keyboard.release(KEY_TAB);
      delay(50);
    }
    else if (stringOrder == "mouserelease") {
      Mouse.release(MOUSE_LEFT);
      delay(50);
    }
    else if (stringOrder == "mousepress") {
      Mouse.press(MOUSE_LEFT);
      delay(50);
    }
    else if (stringOrder == "mouseclickB") {
      String button = Serial.readStringUntil('_');
      int rep = Serial.readStringUntil('_').toInt();
      MouseClickBold(button, rep);
    }
    else if (stringOrder == "escpress") {
      PressESC();
    }
    else if (stringOrder == "enterpress") {
      PressEnter();
    }
    else if (stringOrder == "write") {
      delay(10);
      Serial.write('f');
    }
    else {
    }
  }
}
