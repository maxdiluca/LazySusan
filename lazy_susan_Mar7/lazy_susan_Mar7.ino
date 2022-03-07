#include <Stepper.h>
#include <ezButton.h>

// parameters
int seed = 1;
const int n_stimuli = 7;
const int n_repetitions = 5;
const int n_trials = n_stimuli * n_repetitions;

// hardware variables
const int stepsPerRevolution = 32;  // change this to fit the number of steps per revolution
const int gearRed = 64; // for your motor
const int stepsPerOutRev = stepsPerRevolution * gearRed;
const int stepsperdivision = stepsPerOutRev / n_stimuli;
const int ledPin = 13;      // pin 13 has the internal and the external LED attached to it
const int pushButton = 12; // digital pin which has a pushbutton attached to it
ezButton button(pushButton);
//2048
//2ms
//500s/s
//4s rotation
// initialize the stepper library on pins 2 through 5  
Stepper myStepper(stepsPerRevolution,    5, 3, 2, 4);


// randomization variables
long randNumber;
int f;
int i;
int n;
int chosen_element;
int chosen_position;
int r;
int x;
int count = 0;


// trials variables
int randomized_trials[n_stimuli * n_repetitions];
int ordered_array[n_stimuli + 1];

// control of the trial variables
int currentstepangle;
int desiredstepangle;
int trialcount = -1;
int buttonState;





void setup() {

  
  // initialize serial connection. Needs to be higher than 9600 as otherwise some of the numbers are not outputed correctly
  Serial.begin(115200);

  randomSeed(seed);//analogRead(0));

  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  
  
  
  //create an array of stimuli
  for ( r = 0; r < n_repetitions; r = r + 1)
  {

    //define series of ordered stimuli for each repetition
    for ( i = 0; i < n_stimuli + 1; i = i + 1) {
      ordered_array[i] = i + 1;
      // Serial.print(ordered_array[i]);
    }
    //  Serial.println(" ");

    for (n = n_stimuli - 1; n > -1; n--) // here we pick random elements in the array until we got 'em all
    {
      chosen_position = random(n);
      chosen_element  = ordered_array[chosen_position];
      randomized_trials[count] = chosen_element ;
      count = count + 1;
      //    Serial.print( chosen_element );
      for ( x = chosen_position; x < n; x++) // here we shift all elements (who come AFTER the chosen one) in the array one place to the left
      {
        ordered_array[x] = ordered_array[x + 1];
      }

    }

    Serial.println(" ");


  }
  // Serial.println(-1);
  for ( i = 0; i < (n_trials); i = i + 1) {
    Serial.print(randomized_trials[i]);

  }
  Serial.println(" ");

  
  
  delay(500);

  
  
  //ask to press and release the button to check that it works, while the led flashes
  button.loop(); // MUST call the loop() function first
  int buttonState = button.getState();

  while (buttonState == 0)

  {
    button.loop(); // MUST call the loop() function first
    buttonState = button.getState();
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(50);

  }

  digitalWrite(ledPin, LOW);
  while (buttonState == 1)

  {
    button.loop(); // MUST call the loop() function first
    buttonState = button.getState();

  }

// flash three times
     delay(200);
  for ( i = 0; i < 3; i = i + 1) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(200);
  }

// ready to go

  delay(1000);


   currentstepangle = 0;

  // button.setCountMode(COUNT_FALLING);
 
}




void loop() {


  if (trialcount < n_trials) {
    myStepper.setSpeed(800);//trial and error max 1100


    desiredstepangle = stepsperdivision * randomized_trials[trialcount];
    myStepper.step(desiredstepangle - currentstepangle);

    // Serial.print(currentstepangle);
    // Serial.print(desiredstepangle);
    // Serial.println(desiredstepangle - currentstepangle);



    //indicate how long to touch the sample for
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);

    delay(2000);

    /*if (abs(desiredstepangle-currentstepangle)<abs(stepsPerOutRev-(desiredstepangle-currentstepangle)))
       {
       Serial.println("clockwise");
       myStepper.step(desiredstepangle-currentstepangle);

       }else{
       Serial.println("counter-clockwise");
        myStepper.step(stepsPerOutRev-(desiredstepangle-currentstepangle));
       }*/



    //start flashing to wait for a button press and release to advance to next trial
    button.loop(); // MUST call the loop() function first
    int buttonState = button.getState();

    while (buttonState == 0)

    {
      button.loop(); // MUST call the loop() function first
      buttonState = button.getState();
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    digitalWrite(ledPin, LOW);

    while (buttonState == 1)

    {
      button.loop(); // MUST call the loop() function first
      buttonState = button.getState();

    }

// advance to next trial
    delay(100);
    trialcount = trialcount + 1;
    currentstepangle = desiredstepangle;

  }





}
