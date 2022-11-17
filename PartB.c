
// #include<string.h>
// #include<stdio.h>
// #include<stdlib.h>
#include<xmc_gpio.h>
#include<xmc_common.h>

#define TICKS_PER_SECOND 1000
#define TICKS_DOT 100
#define TICKS_DASH 300
#define TICKS_LETTER_SPACE 200
#define TICKS_WORD_SPACE 700
#define TICKS_SYMBOL_SPACE 100


#define LED1 P1_1
#define LED2 P1_0
#define GPIO_BUTTON1  XMC_GPIO_PORT1, 14
#define GPIO_BUTTON2  XMC_GPIO_PORT1, 15



void delay(uint32_t ticks_in_ms)
{
    delay_ticks=ticks_in_ms;
    while(delay_ticks>0);

}

// Words are seperated by a space equivalent to 7 dots
// Letters are seperated by a space of 3 dots
// 100ms space between dots and dashes 

static const char *alpha[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};
static const char *num[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};


char textString[] = "I CAN MORSE"; 

char* char2morse(char str)
{
  // char* morse = (char*) malloc((strlength*6) * sizeof(char));
  // int morselen=0;
  // char letterBreak = '#';
  // char wordBreak = '!';
  char temp;
  char space_char[] ="**";

  temp = tolower(str);

  if (temp == " ")
  {    
    return space_char;
  }

  else if (isalpha(temp))
  {
    // printf("%s",alpha[(int)str[i]]);
    // printf("%c %d %s\n",temp,(int) temp % 97,alpha[(int) temp % 97]);
    return alpha[(int) temp % 97];
  }
  else if (isdigit(temp))
  {
    // printf("%s",alpha[(int)str[i]]);
    // printf("%c %d %s\n",temp,(int) temp %48,num[(int) temp %48]);
    return num[(int) temp %48];      
  }  

  return space_char;
}

void runMorse()
{
   for(int i=0;i<strlen(textString);i++)
  {
    // printf(char2morse(textString[i]));
    memcpy(morse_str,char2morse(textString[i]),5);
    morse_str_len = strlen(morse_str);
    // printf(morse_str);
    if (morse_str[0] != '*')
    {
      for(int j=0;j<morse_str_len;j++)
      {
        if (morse_str[j] == '.')
        {
          XMC_GPIO_SetOutputHigh(LED1);
          delay(TICKS_DOT);
          XMC_GPIO_SetOutputLow(LED1);
          delay(TICKS_SYMBOL_SPACE);
          
        }
        else if (morse_str[j] == '-')
        {
          XMC_GPIO_SetOutputHigh(LED1);
          delay(TICKS_DASH);  
          XMC_GPIO_SetOutputLow(LED1);  
          delay(TICKS_SYMBOL_SPACE);    
        }

        if (j+1 == morse_str_len)
        {
          XMC_GPIO_SetOutputLow(LED1);
          delay(TICKS_LETTER_SPACE);
          break;
        }       
        
      }

    }
    else if (morse_str[0] == '*')
    {
      XMC_GPIO_SetOutputLow(LED1);
      delay(TICKS_WORD_SPACE);
    }

  }

}

const XMC_GPIO_CONFIG_t in_config = \
      {.mode=XMC_GPIO_MODE_INPUT_TRISTATE,\
       .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
       .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
       };

uint32_t delay_ticks = 0;

void SysTick_Handler(void)
{
  static bool button1_status,button2_status;
  static uint32_t buttonPress_ticks = 0;

  button1_status = 0;
  button2_status = 0;

  






  if (delay_ticks>0){  
  delay_ticks--;
  }
}




int main(void) {

  XMC_GPIO_CONFIG_t config;

  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  
  XMC_GPIO_Init(GPIO_BUTTON1,  &in_config);
  // XMC_GPIO_Init(GPIO_BUTTON2,  &in_config);
  
  XMC_GPIO_Init(LED1, &config);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  char morse_str[5];
  int morse_str_len;

  delay_ticks++;

  while(1){

    while(XMC_GPIO_GetInput(GPIO_BUTTON1) == 0) 
    {
           
    } 
    
}
}
