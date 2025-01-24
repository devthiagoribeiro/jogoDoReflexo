#include <stdio.h>
#include "pico/stdlib.h"
#include <time.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "matriz_leds.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>

#define timeSeta 100
#define led 13
#define led2 11
#define ledBlue 12
#define btnA 5
#define btnB 6
#define buzzer 21

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

struct render_area start(){
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
    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);
    return frame_area;
}

void ligarLed(int r, int g, int b){
    if(r){
        gpio_put(led, 1);
    }
    if(g){
        gpio_put(led2, 1);
    }
    if(b){
        gpio_put(ledBlue, 1);
    }
}

void desligarLed(){
    gpio_put(led, 0);
    gpio_put(led2, 0);
    gpio_put(ledBlue, 0);
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

void displayOled(char *text[8],size_t line_count, struct render_area *frame_area){
    // zera o display inteiro
        uint8_t ssd[ssd1306_buffer_length];
        memset(ssd, 0, ssd1306_buffer_length);
        render_on_display(ssd, frame_area);

        srand(time(NULL));

        restart:

        // Criação do Texto de Exibição

        int y = 0;
        for (uint i = 0; i < line_count; i++)
        {
            ssd1306_draw_string(ssd, 5, y, text[i]);
            y += 8;
        }
        render_on_display(ssd, frame_area);
}

void placar(int A, int B, PIO pio, uint sm, struct render_area *frame_area){
    
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

    char *text[8];
    for (int i = 0; i < 8; i++) {
        text[i] = malloc(32 * sizeof(char)); // Aloca espaço suficiente para cada string
        if (text[i] == NULL) {
            printf("Erro ao alocar memória\n");
        }
    }

    // Preenchendo o array de strings com formato
    snprintf(text[0], 32, "               ");
    snprintf(text[1], 32, "               ");
    snprintf(text[2], 32, "               ");
    snprintf(text[3], 32, "     %dx%d     ", A, B);
    snprintf(text[4], 32, "               ");
    snprintf(text[5], 32, "               ");
    snprintf(text[6], 32, "               ");
    snprintf(text[7], 32, "               ");

    // Liberando memória alocada
    
    displayOled(text, count_of(text), frame_area);
}
    
int main()
{
    //inicialização da matriz de leds
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);
    stdio_init_all();
    //inicializando as portas e obterndo o frame_aera
    struct render_area frame_area = start();
    //semeando tempo randomizado
    srand(time(NULL));
    //variaveis auxiliares para o placar e status de mostragem de alertas
    int A, B, status = 0;
    //definição de textos a serem futuramente renderizados no display oled
    char *start[8] = {
            //"             "
            "               ",
            "               ",
            "   APERTE A    ",
            "               ",
            " PARA COMECAR  ",
            "               ",
            "               ",
            "               "
            };
    char *comecando[8] = {
            //"             "
            "               ",
            "               ",
            "               ",
            "   COMECANDO   ",
            "               ",
            "               ",
            "               ",
            "               "
            };
    char *vitoriaA[8] = {
            //"             "
            "               ",
            "               ",
            " VITORIA PARA  ",
            "               ",
            " O JOGADOR A   ",
            "               ",
            "               ",
            "               "
            };
    char *vitoriaB[8] = {
            //"             "
            "               ",
            "               ",
            " VITORIA PARA  ",
            "               ",
            " O JOGADOR B   ",
            "               ",
            "               ",
            "               "
            };

    //início do programa
    while(true){
    if(status == 0){
        //tela de início do jogo
        displayOled(start,count_of(start), &frame_area);
        imprimir_desenho(seta, pio, sm);
        status = 1;
    }   //início do jogo com contagem regressiva
        if(!gpio_get(btnA)){
            status = 0;
            A = B = 0;
            displayOled(comecando, count_of(comecando), &frame_area);
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
                //exibe o placar e continua no jogo até que um dos jogadores atinja 5 pontos
                placar(A, B, pio, sm, &frame_area);
                if(A == 5 || B == 5){
                    if(A>B){
                        displayOled(vitoriaA, count_of(vitoriaA), &frame_area);
                    }else{
                        displayOled(vitoriaB, count_of(vitoriaB), &frame_area);
                    }
                    victory_sound();
                    break;
                }
                int random_time = (rand() % 5000) + 1000;
                sleep_ms(random_time);
                ligarLed(1,1,1);
                //aguarda que algum botão seja apertado, incrementa a pontuação e reproduz uma indicação sonora
                while(true){
                    if(!gpio_get(btnA)){
                        desligarLed();
                        ligarLed(0,1,0);
                        beep(100);
                        desligarLed();
                        A++;
                        break;
                    }else if(!gpio_get(btnB)){
                        desligarLed();
                        ligarLed(0,0,1);
                        beep(100);
                        sleep_ms(200);
                        beep(100);
                        desligarLed();
                        B++;
                        break;
                    }
                }
                
            }
        }
    }
}