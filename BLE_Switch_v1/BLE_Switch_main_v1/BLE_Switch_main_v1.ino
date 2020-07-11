int switchMap[4] = {21,19,18,5};
int switch_val[4] = {1,1,1,1};
int update_switch_flag;
void turn_off(int idx)
{
//  digitalWrite(switchMap[idx],HIGH);
  switch_val[idx] = 1;
  Serial.print(idx);
  Serial.print("Off \r\n");
  update_switch_flag = 1;
}

void turn_on(int idx)
{
//  digitalWrite(switchMap[idx],LOW);
  switch_val[idx] = 0;
  Serial.print(idx);
  Serial.print("On \r\n");
  update_switch_flag = 1;
}

void setup() 
{
  int i;
  Serial.begin(115200);
  for(i=0;i<4;i++)
  {
    pinMode(switchMap[i], OUTPUT);
    digitalWrite(switchMap[i],HIGH);    
  }
  BLE_Initialize();
}

void loop() 
{
  int i;
//  for(i=0;i<4;i++)
//  digitalWrite(switchMap[i],HIGH);
//  delay(7000);
//  for(i=0;i<4;i++)
//  digitalWrite(switchMap[i],LOW);
//  delay(7000);
    if(update_switch_flag)
    {
      for(i=0;i<4;i++)
      {
        delay(50);
        digitalWrite(switchMap[i],switch_val[i]);
        Serial.printf("SwitchState idx %d val %d \r\n",i,switch_val[i]);                
      }
      update_switch_flag = 0;
    }  
}
