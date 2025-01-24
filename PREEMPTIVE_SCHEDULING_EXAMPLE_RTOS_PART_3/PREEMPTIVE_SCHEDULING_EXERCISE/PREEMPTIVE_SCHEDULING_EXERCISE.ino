#define STACK_SIZE 1024 //the stack size is being declared here 
int grblinkrate=0; //globalvariable storing the blinkrate
const int ledPin = 2;

//configuring the CORE NUMBER FOR RUNNING MY APPLICATION
#if CONFIG_FREERTOS_UNICORE 
  static const BaseType_t app_cpu = 0;
#else 
  static const BaseType_t app_cpu = 1;
#endif

//Declaring the taskhandler 
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

void StartTask1(void *parameter)
{
    while(1)
    {
      //Serial.println("Task 1");
      int lrblinkrate=grblinkrate;
      if(lrblinkrate==0)
      {
        digitalWrite(ledPin,HIGH);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        digitalWrite(ledPin,LOW);
        vTaskDelay(1000/portTICK_PERIOD_MS);
      }
      else
      {
        digitalWrite(ledPin,HIGH);
        vTaskDelay(lrblinkrate/portTICK_PERIOD_MS);
        digitalWrite(ledPin,LOW);
        vTaskDelay(lrblinkrate/portTICK_PERIOD_MS);
      }

    }
}

void StartTask2(void *parameter)
{
    while (1)
    {
        //Serial.println("Task 2:");
        //Serial.print("Current Blink Rate: ");
        Serial.println(grblinkrate);

        if (Serial.available() > 0)
        {
            int inputRate = Serial.parseInt(); // Parse the input as an integer
            if (inputRate > 0) // Validate the input
            {
                grblinkrate = inputRate;
                Serial.print("Updated Blink Rate: ");
                Serial.println(grblinkrate);
            }
            else
            {
                Serial.println("Invalid Blink Rate! Enter a positive number.");
            }
        }

        //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    pinMode(ledPin,OUTPUT);
    Serial.begin(300);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("RUNTIME CONFIGURABLE LED BLINK RATE PROJECT USING RTOS : ");

    Serial.print("Setup and loop task running on core");
    Serial.println(xPortGetCoreID());
    Serial.print("with priority");
    Serial.println(uxTaskPriorityGet(NULL));
    xTaskCreatePinnedToCore(StartTask1,"Task 1",STACK_SIZE,NULL,2,&task_1,app_cpu);
    xTaskCreatePinnedToCore(StartTask2,"Task 2",STACK_SIZE,NULL,1,&task_2,app_cpu);    
}

void loop() {
  // put your main code here, to run repeatedly:

}
