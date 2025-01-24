#define STACK_SIZE 1024 //the stack size is being declared here 
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else 
  static const BaseType_t app_cpu = 1;
#endif

const char message[]= "I LOVE EMBEDDED SYSTEMS";

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

void startTask1(void *parameter) //definition of the lower priority task
{
  int str_len = strlen(message);
  while(1)
  {
    Serial.println();
    for(int i=0;i<str_len;i++)
    {
      Serial.print(message[i]);
    }
    Serial.println();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void startTask2(void *parameter) //higher priority task 
{
  while(1)
  {
    Serial.print(" * ");
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
void setup() 
{
    Serial.begin(300);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println();
    Serial.println("---FREERTOS TASK DEMO----");

    Serial.print("Setup and loop task running on core");
    Serial.println(xPortGetCoreID());
    Serial.print("with priority");
    Serial.println(uxTaskPriorityGet(NULL));
    xTaskCreatePinnedToCore(startTask1,"Task 1",STACK_SIZE,NULL,1,&task_1,app_cpu);
    xTaskCreatePinnedToCore(startTask2,"Task 2",STACK_SIZE,NULL,2,&task_2,app_cpu);
}

void loop()
 {
    for(int i=0; i<3 ; i++)
    {
      vTaskSuspend(task_2);
      vTaskDelay(2000/portTICK_PERIOD_MS);
      vTaskResume(task_2);
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }

    if(task_1 != NULL)
    {
      vTaskDelete(task_1);
      task_1=NULL;
    }

 }
