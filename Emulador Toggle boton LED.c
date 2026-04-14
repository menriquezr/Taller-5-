
/*EMULADOR DE FUNCION DE CAMBIO DE ESTADO = Interruptor que mantiene el estado y se
reinicia cuando se presiona/

/*Incluir Header File*/
#include "stm32f4xx_hal.h"


void GPIOA_Config(void);
void GPIOC_Config(void);
void delay(uint32_t delayVal);

int main(void)
{
    GPIOA_Config();
    GPIOC_Config();
    int flag = 1; //Variable para mantener el estado del LED
    while (1)
    {
        //Registrar el estado del botón
        //El boton normalmente esta en estado alto, cuando se presiona se pone en estado bajo
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==1 && flag == 1){ //Si el NO boton esta presionado y el flag es 1, entonces cambia el estado del LED
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); //esta funcion cambia el estado del pin, si esta encendido lo apaga y viceversa
            flag = 0;
        }
         else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==0){
            flag = 1; 
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
