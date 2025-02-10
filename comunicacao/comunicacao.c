#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "comunicacao.pio.h"
//#include "comunicacao.pio"

#define led_pin_g 11
#define led_pin_b 12
#define led_pin_r 13

//número de LEDs
#define NUM_PIXELS 25

//pino de saída
#define OUT_PIN 9

#define LED_VERDE 11
#define LED_AZUL 12
#define BOTAO_A 5
#define BOTAO_B 6

// Função para debounce (aguarda estabilidade do botão)
bool debounce(uint gpio) {
    if (gpio_get(gpio) == 0) {  // Se pressionado
        sleep_ms(50);  // Tempo para evitar ruídos
        if (gpio_get(gpio) == 0) {  // Confirma a pressão
            while (gpio_get(gpio) == 0);  // Aguarda soltar
            sleep_ms(50);  // Garante estabilidade
            return true;
        }
    }
    return false;
}

double desenho_apagado[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double number_1[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double number_2[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double number_3[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double number_4[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};

double number_5[25] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};

double number_6[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};

double number_7[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};

double number_8[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};

double number_9[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};

void voidnumber_1(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_1[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};
}


void voidnumber_2(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_2[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};
}


void voidnumber_3(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_3[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};
}


void voidnumber_4(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_4[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0
};
}


void voidnumber_5(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_5[25] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};
}


void voidnumber_6(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_6[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};
}


void voidnumber_7(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_7[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};
}


void voidnumber_8(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_8[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};
}


void voidnumber_9(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
double number_9[25] = {
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0
};
}


uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        // Define a cor vermelha para cada LED
        valor_led = matrix_rgb(0.0, desenho[24 - i], 0.0); // Apenas o valor vermelho está ativo
        pio_sm_put_blocking(pio, sm, valor_led); // Envia o valor para o LED
    }
}
void desenho_apagado_total(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        // Define a cor nenhuma
        valor_led = matrix_rgb(0.0, 0.0, 0.0); // Nenhum ativo
        pio_sm_put_blocking(pio, sm, valor_led); // Envia o valor para o LED
    }
}


// Inicializa o sistema de clock
void inicializar_clock() {
    bool ok = set_sys_clock_khz(128000, false);
    if (ok) {
        printf("Clock set to %ld\n", clock_get_hz(clk_sys));
    } else {
        printf("Falha ao configurar o clock\n");
    }
}

// Configura a PIO
void configurar_pio(PIO pio, uint *offset, uint *sm) {
    *offset = pio_add_program(pio, &comunicacao_program);
    *sm = pio_claim_unused_sm(pio, true);
    comunicacao_program_init(pio, *sm, *offset, OUT_PIN);
}



int main()
{
    PIO pio = pio0;
    uint offset, sm;
    uint32_t valor_led;
    double r = 0.0, b = 0.0, g = 0.0;

    stdio_init_all(); // Inicializa comunicação USB CDC para monitor serial

    // Configurar LEDs como saída
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);  // Inicia apagado

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);  // Inicia apagado

    // Configurar botões como entrada com pull-up interno
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    bool estado_led_verde = false;
    bool estado_led_azul = false;

 // Configura os pinos dos LEDs como saída
    gpio_init(led_pin_r);
    gpio_set_dir(led_pin_r, GPIO_OUT);
    gpio_put(led_pin_r, 0); // Inicialmente desligado

    gpio_init(led_pin_g);
    gpio_set_dir(led_pin_g, GPIO_OUT);
    gpio_put(led_pin_g, 0); // Inicialmente desligado

    gpio_init(led_pin_b);
    gpio_set_dir(led_pin_b, GPIO_OUT);
    gpio_put(led_pin_b, 0); // Inicialmente desligado

    stdio_init_all();
    inicializar_clock();
    //configurar_teclado(colunas, linhas);
    configurar_pio(pio, &offset, &sm);

    printf("Sistema inicializado. Aguardando entrada...\n");

    while (true)
    {

        if (debounce(BOTAO_A)) {
            estado_led_verde = !estado_led_verde;  // Alterna o estado
            gpio_put(LED_VERDE, estado_led_verde);
        }

        if (debounce(BOTAO_B)) {
            estado_led_azul = !estado_led_azul;  // Alterna o estado
            gpio_put(LED_AZUL, estado_led_azul);
        }

        sleep_ms(10);  // Pequeno delay para reduzir consumo de CPU

        if (stdio_usb_connected())
        { // Certifica-se de que o USB está conectado
            char c;
            if (scanf("%c", &c) == 1)
            { // Lê caractere da entrada padrão
                printf("Recebido: '%c'\n", c);

                switch (c)
                {
                    case '1': // Caso o usuário aperte "1" 
                        desenho_pio(number_1, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '2':
                        desenho_pio(number_2, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '3': //caso aperte "3"
                        desenho_pio(number_3, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '4':
                        desenho_pio(number_4, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '5':
                        desenho_pio(number_5, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '6':
                        desenho_pio(number_6, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                         break;
                    case '7':
                        desenho_pio(number_7, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '8':
                        desenho_pio(number_8, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    case '9':
                        desenho_pio(number_9, valor_led, pio, sm, r, g, b);
                        sleep_ms(50);
                        break;
                    default: // Para outras teclas ou nenhuma tecla pressionada
                        printf("Default acionado. Valor tecla: %c (ASCII: %d)\n", c, c);
                        desenho_pio(desenho_apagado, valor_led, pio, sm, r, g, b);
                        break;
            }
            }
        }
        sleep_ms(40);
    }

    return 0;
}