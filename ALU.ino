int S0, S1, S2;
int S[2], COUT;
int A[2], B[2];
void setup()
{
  Serial.begin(9600);

  
  pinMode(3, INPUT); //S0
  pinMode(4, INPUT); //S1
  pinMode(5, INPUT); //S2


  pinMode(6, INPUT); //A[0]
  pinMode(7, INPUT); //A[1]
  pinMode(8, INPUT); //B[0]
  pinMode(9, INPUT); //B[1]

  
  pinMode(10, OUTPUT); //S[0]
  pinMode(11, OUTPUT); //S[1]
  pinMode(12, OUTPUT); //COUT
}

void loop() {
  S0 = digitalRead(3);
  S1 = digitalRead(4);
  S2 = digitalRead(5);

  A[0] = digitalRead(6);
  A[1] = digitalRead(7);
  B[0] = digitalRead(8);
  B[1] = digitalRead(9);

 
  if (S2 == LOW && S1 == LOW && S0 == LOW)
  {
    //NOT A
    NOT(A);
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }
  else if (S2 == LOW && S1 == LOW && S0 == HIGH)
  {
    //A+1
    B[0] = HIGH;
    B[1] = LOW;
    ADD();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }
  else if (S2 == LOW && S1 == HIGH && S0 == LOW)
  {
    //A-1
    NOT(B);
    AADD1(B);
    ADD();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
   
  }
  else if (S2 == LOW && S1 == HIGH && S0 == HIGH)
  {
    //A+B
    ADD();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }
  else if (S2 == HIGH && S1 == LOW && S0 == LOW)
  {
    //A-B
    NOT(B);
    AADD1(B);
    ADD();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }
  else if (S2 == HIGH && S1 == LOW && S0 == HIGH)
  {
    //A AND B
    AND();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }

  else if (S2 == HIGH && S1 == HIGH && S0 == LOW)
  {
    // A OR B
    OR();
    digitalWrite(10, A[0]);
    digitalWrite(11, A[1]);
    digitalWrite(12, COUT);

  }
  else if (S2 == HIGH && S1 == HIGH && S0 == HIGH)
  {
    // A XOR B
    XOR();
    digitalWrite(10, S[0]);
    digitalWrite(11, S[1]);
    digitalWrite(12, COUT);
  }
}

void ADD()
{
  COUT = LOW;
  for (int i = 0; i <= 1; i++)
  {
    int COUNT = 0;
    if (A[i] == HIGH)
    {
      COUNT = COUNT + 1;
      if (B[i] == HIGH)
      {
        COUNT = COUNT + 1;
        if (COUT == HIGH)
        {
          COUNT = COUNT + 1;
        }
        else if (COUT == LOW)
        {
          COUNT = COUNT + 0;
        }
      }
      else if (B[i] == LOW)
      {
        COUNT = COUNT + 0;
        if (COUT == HIGH)
        {
          COUNT = COUNT + 1;
        }
        else if (COUT == LOW)
        {
          COUNT = COUNT + 0;
        }
      }
    }
    else if (A[i] == LOW)
    {
      COUNT = COUNT + 0;
      if (B[i] == HIGH)
      {
        COUNT = COUNT + 1;
        if (COUT == HIGH)
        {
          COUNT = COUNT + 1;
        }
        else if (COUT == LOW)
        {
          COUNT = COUNT + 0;
        }
      }
      else if (B[i] == LOW)
      {
        COUNT = COUNT + 0;
        if (COUT == HIGH)
        {
          COUNT = COUNT + 1;
        }
        else if (COUT == LOW)
        {
          COUNT = COUNT + 0;
        }
      }
    }
    if (COUNT == 3)
    {
      S[i] = HIGH;
      COUT = HIGH;
    }
    else if (COUNT == 2)
    {
      S[i] = LOW;
      COUT = HIGH;
    }
    else if (COUNT == 1)
    {
      S[i] = HIGH;
      COUT = LOW;
    }
    else if (COUNT == 0)
    {
      S[i] = LOW;
      COUT = LOW;
    }
  }
}

void AADD1(int *X)
{
  if (*(X + 0) == HIGH)
  {
    //Carry=1
    *(X + 0) = LOW;
    if (*(X + 1) == HIGH)
    {
      *(X + 1) = LOW;
      COUT = HIGH;
    }
    else if (*(X + 1) == LOW)
    {
      *(X + 1) = HIGH;
      COUT = LOW;
    }
  }
  else if (*(X + 0) == LOW)
  {
    //Carry=0
    *(X + 0) = HIGH;
    if (*(X + 1) == HIGH)
    {
      *(X + 1) = HIGH;
      COUT = LOW;
    }
    else if (*(X + 1) == LOW)
    {
      *(X + 1) = LOW;
      COUT = LOW;
    }
  }
}

void NOT(int *X)
{
  if (*(X + 0) == LOW && *(X + 1) == LOW)
  {
    *(X + 0) = HIGH;
    *(X + 1) = HIGH;
  }
  else if (*(X + 0) == LOW && *(X + 1) == HIGH)
  {
    *(X + 0) = HIGH;
    *(X + 1) = LOW;
  }
  else if (*(X + 0) == HIGH && *(X + 1) == LOW)
  {
    *(X + 0) = LOW;
    *(X + 1) = HIGH;
  }
  else if (*(X + 0) == HIGH && *(X + 1) == HIGH)
  {
    *(X + 0) = LOW;
    *(X + 1) = LOW;
  }
  COUT = LOW;
}

void AND()
{
  for (int i = 0; i <= 1; i++)
  {
    if (A[i] == HIGH && B[i] == HIGH)
    {
      S[i] = HIGH;
    }
    else
    {
      S[i] = LOW;
    }
  }
  COUT = LOW;
}

void OR()
{
  for (int i = 0; i <= 1; i++)
  {
    if (A[i] == LOW && B[i] == LOW)
    {
      S[i] = LOW;
    }
    else
    {
      S[i] = HIGH;
    }
  }
  COUT = LOW;
}

void XOR()
{
  for (int i = 0; i <= 1; i++)
  {
    if ((A[i] == LOW && B[i] == LOW) || (A[i] == HIGH && B[i] == HIGH))
    {
      S[i] = LOW;
    }
    else
    {
      S[i] = HIGH;
    }
  }
  COUT = LOW;
}

