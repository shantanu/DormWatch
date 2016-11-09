#include <Time.h>
#include <TimeLib.h>

#include <Time.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message

int OUT_PIN=13;
void setup() {
  // put your setup code here, to run once:
    pinMode(OUT_PIN, OUTPUT);

}
void loop()
{
  if(dayOfWeek()==1&&dayOfWeek()==7)//If day of the week is Sunday(1) or Saturday(7)
  {
   if(hour()>0&&hour()<10)//Quiet hours are between 12 and 10
   {
    digitalWrite(OUT_PIN, HIGH);
   }
   else
   {
    digitalWrite(OUT_PIN, LOW);
   }
  }
  else
  {
  if(hour()>=23||hour()<10)//Quiet hours are after 11pm or before 10am
   {
    digitalWrite(OUT_PIN, HIGH);
   }
   else
   {
    digitalWrite(OUT_PIN, LOW);
   }
  }
   
  
}

