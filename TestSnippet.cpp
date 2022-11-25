// Stepper movement control
void getAngles ()
{
  elbowAngle = elbowAngle + elbowAngleChange;
  baseAngle = baseAngle + baseAngleChange;
  height = height + heightChange;
}

void stepElbow(int iDirection)
{
    digitalWrite(DirX, iDirection);
    digitalWrite(StepX,HIGH);
    delayMicroseconds(600);
    digitalWrite(StepX,LOW); 
    delayMicroseconds(600);
    
    elbowAngleChange = 0;
    baseAngleChange = 0;
    heightChange = 0;
    
    if (iDirection == 1)
    {
      elbowAngleChange = elbowAnglePerStep;
    }
    else
    {
      elbowAngleChange = -elbowAnglePerStep;
    }
}

void stepBase (int iDirection)
{
    digitalWrite(DirZ, iDirection);
    digitalWrite(StepZ,HIGH);
    delayMicroseconds(900);
    digitalWrite(StepZ,LOW); 
    delayMicroseconds(900);
    
    elbowAngleChange = 0;
    baseAngleChange = 0;
    heightChange = 0;

    if (iDirection == 1)
    {
      baseAngleChange = -baseAnglePerStep;
    }
    else
    {
      baseAngleChange = baseAnglePerStep;
    }
}

void stepUpDown(int iDirection)
{
    digitalWrite(driverDIR,iDirection);
    digitalWrite(driverPUL,HIGH);
    delayMicroseconds(600);
    digitalWrite(driverPUL,LOW);
    delayMicroseconds(600);
    
    elbowAngleChange = 0;
    baseAngleChange = 0;   
    heightChange = 0;
    
    if (iDirection == 1)
    {
      heightChange = heightPerStep_mm;
    }
    else
    {
      heightChange = -heightPerStep_mm;
    }
}

void moveToTarget (int zFirst = 0)
{
    calculateSteps();
    // outputData();

    for(int x = 0; x<T_elbowSteps; x++) 
    {
        stepElbow(elbowDir);
        getAngles();
    }

    for(int x = 0; x<T_baseSteps; x++) 
    {
        stepBase(baseDir);
        getAngles();
    }

    for(int x = 0; x<T_heightSteps; x++) 
    {
        stepUpDown(heightDir);
        getAngles();
    }
    // outputPosition();
}

void calculateSteps ()
{
    T_elbowSteps = (elbowAngle - T_elbowAngle)/elbowAnglePerStep;
    T_baseSteps = (baseAngle - T_baseAngle)/baseAnglePerStep;
    T_heightSteps = (height - T_height)/heightPerStep_mm;

    if (T_elbowSteps > 0)
    {
        elbowDir = 0;
    }
    else
    {
        elbowDir = 1;
    }

    if (T_baseSteps > 0)
    {
        baseDir = 1;
    }
    else
    {
        baseDir = 0;
    }  

    if (T_heightSteps > 0)
    {
        heightDir = 0;
    }
    else
    {
        heightDir = 1;
    }
    T_elbowSteps = abs(T_elbowSteps);
    T_baseSteps = abs(T_baseSteps);
    T_heightSteps = abs(T_heightSteps);
}
/////////////////////////////////

// Coding Misc
void outputPosition ()
{
  Serial.print("Elbow Angle:\t");
  Serial.println(elbowAngle);
  Serial.print("Base Angle:\t");
  Serial.println(baseAngle);
}

void outputData()
{
      Serial.print("Current Elbow Angle:\t");
      Serial.println(elbowAngle);
      Serial.print("Target Elbow Angle:\t");
      Serial.println(T_elbowAngle);
      Serial.print("Elbow Steps:\t");
      Serial.println(T_elbowSteps);
      Serial.print("Elbow Direction:\t");
      Serial.println(elbowDir);

      
      Serial.print("Current Base Angle:\t");
      Serial.println(baseAngle);
      Serial.print("Target Base Angle:\t");
      Serial.println(T_baseAngle);
      Serial.print("Base Steps:\t");
      Serial.println(T_baseSteps);
      Serial.print("Base Direction:\t");
      Serial.println(baseDir);
            
      Serial.print("Current Height:\t");
      Serial.println(height);
      Serial.print("Target Height:\t");
      Serial.println(T_height);
      Serial.print("Height Steps:\t");
      Serial.println(T_heightSteps);
      Serial.print("Height Direction:\t");
      Serial.println(heightDir);
}
/////////////////////////////////
