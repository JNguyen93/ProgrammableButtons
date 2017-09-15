//Created by Justin Nguyen
//For use by Texas Panic Room
//9/15/2017

//Pin Assignment
const byte button0 = 2;
const byte button1 = 3;
const byte button2 = 4;
const byte button3 = 5;
const byte button4 = 6;
const byte button5 = 7;
const byte button6 = 8;
const byte button7 = 9;
const byte button8 = 10;
const byte button9 = 11;
const byte resetbutton = 12;
const byte lightbulb = A0;

//State Variables
bool flag0;
bool flag1;
bool flag2;
bool flag3;
bool flag4;
bool flag5;
bool flag6;
bool flag7;
bool flag8;
bool flag9;
bool flagp0;
bool flagp1;
bool flagp2;
bool flagp3;
bool flagp4;
bool flagp5;
bool flagp6;
bool flagp7;
bool flagp8;
bool flagp9;
bool reset;
bool programming;
bool setting;
bool correct;

//State and Input Tracking
bool flags[10];
bool flagps[10];
byte buttons[10];
int inputs[10];
int input;
int sol[10];
int prog[10] = {0, 0, 9, 9, 4, 4, 5, 5, 7, 7};

void setup() {
  input = 0;
  flagp0 = false;
  flagp1 = false;
  flagp2 = false;
  flagp3 = false;
  flagp4 = false;
  flagp5 = false;
  flagp6 = false;
  flagp7 = false;
  flagp8 = false;
  flagp9 = false;
  flags[0] = flag0;
  flags[1] = flag1;
  flags[2] = flag2;
  flags[3] = flag3;
  flags[4] = flag4;
  flags[5] = flag5;
  flags[6] = flag6;
  flags[7] = flag7;
  flags[8] = flag8;
  flags[9] = flag9;
  flagps[0] = flagp0;
  flagps[1] = flagp1;
  flagps[2] = flagp2;
  flagps[3] = flagp3;
  flagps[4] = flagp4;
  flagps[5] = flagp5;
  flagps[6] = flagp6;
  flagps[7] = flagp7;
  flagps[8] = flagp8;
  flagps[9] = flagp9;
  buttons[0] = button0;
  buttons[1] = button1;
  buttons[2] = button2;
  buttons[3] = button3;
  buttons[4] = button4;
  buttons[5] = button5;
  buttons[6] = button6;
  buttons[7] = button7;
  buttons[8] = button8;
  buttons[9] = button9;
  correct = false;
  
  for (int a = 0; a < (sizeof(buttons)/sizeof(buttons[0])) - 1; a++){
    pinMode(buttons[a], INPUT);
  }
  pinMode(resetbutton, INPUT);
  pinMode(lightbulb, OUTPUT);

  for (int b = 0; b < (sizeof(sol)/sizeof(sol[0])) - 1; b++){
    sol[b] = 0;
  }
}

void loop() {
  //Reset
  reset = digitalRead(resetbutton);
  if (reset){
    for (int j = 0; j < (sizeof(inputs)/sizeof(inputs[0])) - 1; j++){
      inputs[j] = 0;
    }
    input = 0;
  }

  //Main Loop
  for (int i = 0; i < (sizeof(flags)/sizeof(flags[0])) - 1; i++){
    flags[i] = digitalRead(buttons[i]);
    delay(5);
    
    if (flags[i] != flagps[i]){
      if (flags[i]){
        inputs[input] = i;
        if(input >= 9){
          input = 0;
        }
        else{
          input++;
        }
      }
      delay(50);
    }
    flagps[i] = flags[i];
  }

  //Programming Check
  programming = checkEqual(inputs, prog);

  if (programming && !setting) {
    for (int j = 0; j < (sizeof(inputs)/sizeof(inputs[0])) - 1; j++){
      inputs[j] = 0;
    }
    input = 0;
    setting = true;
  }

  //Solution Check
  correct = checkEqual(inputs, sol);

  if (correct && !setting){
    digitalWrite(lightbulb, LOW);
  }
  else{
    digitalWrite(lightbulb, HIGH);
  }

  //Programming Confirmation
  if (setting && reset){
    memcpy(sol, inputs, sizeof(inputs[0])*sizeof(inputs));
    setting = false;
  }
}

bool checkEqual(int inputs[], int sol[]){
  for (int x = 0; x < (sizeof(sol)/sizeof(sol[0])) - 1; x++){
    if(inputs[x] != sol[x]){
      return false;
    }
  }
  return true;
}

