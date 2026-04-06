/*Dando clic en Pinout->clear pinouts ->
Device Configuration Tool Code Generation
->core->Src->borrar todos los archivos .c y .h
solo dejar system_stm32f4xx.c
De la carpeta Inc solo dejar el archivo stm32f4xx_hal_conf.h
el resto se borra 
Luego -> Create New Header File -> main.h
Luego -> Create New Source File -> main.c

CODIGO PARA CONTROLAR LED CON BOTON STM32F411RE
emepzamos en main.c
*/

/*Incluir Header File*/
#include "stm32f4xx_hal.h"
/*ESpacio para definir variables si las hay*/

void GPIOA_Config(void);
void GPIOC_Config(void);
void delay(uint32_t delayVal);

int main(void)
{
    GPIOA_Config();
    GPIOC_Config();
    while (1)
    {
        /*El LED2 esta conectado al pin PA5 por D13 
        El boton esta conectado al pin PC13 SB17
        Cuando presiono el boton mando a tierra la señal de 5V*/
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==0){
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            delay(500000); //Retardo 
        }
         else{
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
         }

    }
}

//Configuracion de pin LED
void GPIOA_Config(void){
    /*Habilitar reloj del puerto GPIO called RCC O Usar los controladores HAL*/
    __HAL_RCC_GPIOA_CLK_ENABLE(); //Habilidar el pin 5 LED
    GPIO_InitTypeDef GPIOA_Init =  {};
    GPIOA_Init.Pin = GPIO_PIN_5; //Seleccionar el pin; luego en que modo se va a usar
    GPIOA_Init.Mode = GPIO_MODE_OUTPUT_PP; //Seleccionar el modo de salida push-pull
    HAL_GPIO_Init(GPIOA, &GPIOA_Init); //Inicializar el pin con la configuracion dada parametros = Puerto y direccion

}
//Configuracion de pin Boton
void GPIOC_Config(void){
    __HAL_RCC_GPIOC_CLK_ENABLE(); //Habilidar el pin 13
    GPIO_InitTypeDef GPIOC_Init =  {};
    GPIOC_Init.Pin = GPIO_PIN_13; 
    GPIOC_Init.Mode = GPIO_MODE_INPUT; 
    GPIOC_Init.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIOC_Init); 

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
