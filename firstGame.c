#include <stdio.h>
#include "pico/stdlib.h"
#include <time.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "matriz_leds.h"

#define timeSeta 100
#define led 13
#define led2 11
#define ledBlue 12
#define btnA 5
#define btnB 6
#define buzzer 21


void start(){
    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);
    gpio_init(ledBlue);
    gpio_set_dir(ledBlue, GPIO_OUT);
    gpio_init(led2);
    gpio_set_dir(led2, GPIO_OUT);
    gpio_init(buzzer);
    gpio_set_dir(buzzer, GPIO_OUT);
    gpio_init(btnA);
    gpio_set_dir(btnA, GPIO_IN);
    gpio_pull_up(btnA);
    gpio_init(btnB);
    gpio_set_dir(btnB, GPIO_IN);
    gpio_pull_up(btnB);
}

void beep(int duration){
    for(int i = 0; i < duration; i++){
        gpio_put(buzzer, 1);
        sleep_ms(1);
        gpio_put(buzzer, 0);
        sleep_ms(1);
    }
}

void victory_sound() {
    int frequencies[] = {523, 587, 659, 784, 659, 587, 523, 880}; // Frequências para uma melodia
    int durations[] = {200, 200, 200, 400, 200, 200, 200, 600};  // Durações das notas em milissegundos

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (durations[i] * 1000) / (1000000 / frequencies[i]); j++) {
            gpio_put(buzzer, 1);
            sleep_us(1000000 / frequencies[i]); // Tempo ligado
            gpio_put(buzzer, 0);
            sleep_us(1000000 / frequencies[i]); // Tempo desligado
        }
        sleep_ms(100); // Pausa entre as notas
    }
}

Matriz_leds_config matriz = {
            //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
            //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
            };

Matriz_leds_config seta = {
            //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
            //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
            };

Matriz_leds_config um = {
            //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
            //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
            };


Matriz_leds_config dois = {
            //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
            //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
            };

Matriz_leds_config tres = {
            //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
            //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}, {0.0, 0.0, 0.0}}  // Linha 4
            };

void placar(int A, int B, PIO pio, uint sm){
    
    for(int i = 0; i<5;i++){
        for(int j = 0; j<5;j++){
            if(A == 0 && j != 2 && j!=3 && j!=4){
                matriz[i][j] = (Led_config){0.0, 0.0, 0.0};
            } 
            if(B == 0 && j != 0 && j != 1 && j!=2){
                matriz[i][j] = (Led_config){0.0, 0.0, 0.0};
            }
            if(A == 5 && i == 0){
                if(j == 0){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
                if(j == 1){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
            }else if(A == 1 && i == 4){
                if(j == 0){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
                if(j == 1){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
            }else if(A == 2 && i == 3){
                if(j == 0){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
                if(j == 1){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
            }else if(A == 3 && i == 2){
                if(j == 0){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
                if(j == 1){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
            }else if(A == 4 && i == 1){
                if(j == 0){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
                if(j == 1){
                    matriz[i][j] = (Led_config){0.0, 0.05, 0.0};
                }
            }
            //placar para lado B
            if(B == 5 && i == 0){
                if(j == 3){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
                if(j == 4){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
            }else if(B == 1 && i == 4){
                if(j == 3){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
                if(j == 4){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
            }else if(B == 2 && i == 3){
                if(j == 3){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
                if(j == 4){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
            }else if(B == 3 && i == 2){
                if(j == 3){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
                if(j == 4){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
            }else if(B == 4 && i == 1){
                if(j == 3){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
                if(j == 4){
                    matriz[i][j] = (Led_config){0.0, 0.0, 0.05};
                }
            }
        }
    }
    imprimir_desenho(matriz, pio, sm);
}
    



int main()
{
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);
    stdio_init_all();
    start();
    srand(time(NULL));
    int A, B, status = 0;

    while(true){
    if(status == 0){
        printf("Aperte A para comecar\n");
        imprimir_desenho(seta, pio, sm);
        status = 1;
    }
        if(!gpio_get(btnA)){
            status = 0;
            A = B = 0;
            imprimir_desenho(tres, pio, sm);
            beep(100);
            sleep_ms(1000);
            imprimir_desenho(dois, pio, sm);
            beep(100);
            sleep_ms(1000);
            imprimir_desenho(um, pio, sm);
            beep(100);
            sleep_ms(1000);
            beep(300);
            while (true) {
                printf("%d x %d\n", A, B);
                placar(A, B, pio, sm);
                if(A == 5 || B == 5){
                    if(A>B){
                        printf("vitoria do jogador A\n");
                    }else{
                        printf("vitoria do jogador B\n");
                    }
                    victory_sound();
                    break;
                }
                int random_time = (rand() % 5000) + 1000;
                sleep_ms(random_time);
                gpio_put(led, 1);
                while(true){
                    if(!gpio_get(btnA)){
                        gpio_put(led, 0);
                        gpio_put(led2, 1);
                        beep(100);
                        gpio_put(led2, 0);
                        A++;
                        break;
                    }else if(!gpio_get(btnB)){
                        gpio_put(led, 0);
                        gpio_put(ledBlue, 1);
                        beep(100);
                        sleep_ms(200);
                        beep(100);
                        gpio_put(ledBlue, 0);
                        B++;
                        break;
                    }
                }
                
            }
        }
    }
}