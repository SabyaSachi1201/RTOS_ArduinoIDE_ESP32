#define LED_BUILTIN 2

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif 

static const int led_pin = LED_BUILTIN;

//task : Blink LED
void toggleLED(void *parameter)
{
  while(1)
  {
    digitalWrite(led_pin,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(led_pin,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);

  }
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  // put your setup code here, to run once:
  xTaskCreatePinnedToCore()
}

void loop() {
  // put your main code here, to run repeatedly:

}
