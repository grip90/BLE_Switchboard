#include <BLEDevice.h>
#include <BLEServer.h>

#define SERVICE_UUID                 "e1a57cf6-a7f3-11ea-bb37-0242ac130002"
#define CHARACTERISTIC_UUID_SWSTATE  "ed583f84-a7f3-11ea-bb37-0242ac130002"

char switchState[4]= {'0','0','0','0'};
class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onWrite(BLECharacteristic *pCharacteristic) 
    {
      int i;
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) 
      {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (i = 0; i < rxValue.length(); i++)
        {
          Serial.printf("%c",rxValue[i]);
          switchState[i] = rxValue[i];
        }               
        Serial.println("*********");         
        {
          for(i=0;i<4;i++)
          {
            if(switchState[i] == '1')
            {
//              delay(50);
              turn_on(i);
//              delay(50);
            }
            else
            {
//              delay(50);
              turn_off(i);
//              delay(50);
            }
          }
        }        
      }
    }

    void onRead(BLECharacteristic *pCharacteristic)
    {
      Serial.print("Tx Value: ");  
      for(int i=0;i<4;i++)
      {
        Serial.print(switchState[i]);               
      }
      Serial.print("\r\n");
      pCharacteristic->setValue(switchState);      
    }
};

void BLE_Initialize(void)
{
  BLEDevice::init("Reshma_Home");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_SWSTATE,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setValue("0000");  
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}
