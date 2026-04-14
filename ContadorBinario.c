
/*Contador Binario con botones para aumentar e invertir la cuenta; solo podra contar hasta 31=11111/
/*se logra escribiendo en el GPIO register*/
//LEDs -> GPIOA registers
//Botones -> GPIOB registers

#include "stm32f4xx_hal.h"


void GPIOA_Config(void);
void GPIOB_Config(void);
void delay(uint32_t delayVal);

#define BtnUp GPIO_PIN_8
#define BtnDown GPIO_PIN_9
#define low GPIO_PIN_RESET
#define high GPIO_PIN_SET

unsigned int countUp = 0; //Variable para almacenar el valor del contador
unsigned int countDown = 0x1F; //Variable para almacenar el valor del contador invertido
unsigned int sequenseVal = 4;
int j = 0;

int main(void)
{
    GPIOA_Config();
    GPIOB_Config();
    int flag = 1; //Variable para mantener el estado del LED
    while (1)
    {
        if(!HAL_GPIO_ReadPin(GPIOB, BtnUp) && !HAL_GPIO_ReadPin(GPIOB, BtnDown)){
            //Que parpaden todos los LEDs
            while (j<2)
            {
                HAL_GPIO_WritePin(GPIOA,0x1F8, HIGH);
                delay(100000);
                HAL_GPIO_WritePin(GPIOA,0x1F8, LOW);
                delay(100000);
                j++;
            }
            HAL_GPIO_WritePin(GPIOA,0x1F8, LOW);
        }
        else if (HAL_GPIO_ReadPin(GPIOB, BtnUp)==1 && HAL_GPIO_ReadPin(GPIOB, BtnDown)==0){
            if (countUp<31)
            {
                  HAL_GPIO_WritePin(GPIOA,0x1F8, LOW);
                  HAL_GPIO_WritePin(GPIOA,countUp<<4, HIGH);
                  delay(100000);
                  countUp++;  
            }
            else
            {
                countUp = 0;
                delay(100000);
            }
            j = 0;   
        }
         else if (HAL_GPIO_ReadPin(GPIOB, BtnUp)==0 && HAL_GPIO_ReadPin(GPIOB, BtnDown)==1){
            if (countDown>0)
            {
                  HAL_GPIO_WritePin(GPIOA,0x1F8, LOW);
                  HAL_GPIO_WritePin(GPIOA,countDown<<4, HIGH);
                  delay(100000);
                  countDown--;  
            }
            else
            {
                countDown = 0x1F;
                delay(100000);
            }
            j = 0;   
        }
        else
        {
            countUp = 0;
            countDown = 0x1F;
            if (sequenseVal <   9)
            {
                    HAL_GPIO_WritePin(GPIOA,0x1F8, LOW);
                    HAL_GPIO_WritePin(GPIOA,1UL<<  sequenseVal, HIGH);
                    delay(100000);
                    sequenseVal++;
                    
            }
            else
            {
                sequenseVal = 4;
                delay(100000);
            }
             j = 0;
            
        }

    }
}

//Configuracion de pin LED
void GPIOA_Config(void){
    /*Habilitar reloj del puerto GPIO called RCC O Usar los controladores HAL*/
    __HAL_RCC_GPIOA_CLK_ENABLE(); //Habilidar el pin  LED

    GPIO_InitTypeDef GPIOA_Init =  {};
    GPIOA_Init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8; 
    GPIOA_Init.Mode = GPIO_MODE_OUTPUT_PP; //Seleccionar el modo de salida push-pull
    GPIOA_Init.Pull = GPIO_NOPULL; //No usar resistencias de pull-up o pull-down

    HAL_GPIO_Init(GPIOA, &GPIOA_Init); //Inicializar el pin con la configuracion dada parametros = Puerto y direccion

}
//Configuracion de pin Boton
void GPIOB_Config(void){
    __HAL_RCC_GPIOB_CLK_ENABLE(); 

    GPIO_InitTypeDef GPIOB_Init =  {};

    GPIOB_Init.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIOB_Init.Mode = GPIO_MODE_INPUT; 
    GPIOB_Init.Pull = GPIO_PULLDOWN; //cuando se presiona va a 5 NO a 0 como en otros casos pull-up

    HAL_GPIO_Init(GPIOB, &GPIOB_Init); 

}

//Retardo por reloj
void delay(uint32_t delayVal){
    /*Usar el timer del microcontrolador para generar un retardo preciso*/
    /*Configurar el timer para contar hasta el valor deseado y luego esperar a que se complete*/
    uint32_t i;
    for(i=0; i<delayVal; i++){    
    }
}

//UNA FORMA DE HACER REFERENCIA a archivo de encabezado #Include "main.h"
