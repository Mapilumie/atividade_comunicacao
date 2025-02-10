#include "pico/stdlib.h"

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

int main() {
    stdio_init_all();

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

    while (1) {
        if (debounce(BOTAO_A)) {
            estado_led_verde = !estado_led_verde;  // Alterna o estado
            gpio_put(LED_VERDE, estado_led_verde);
        }

        if (debounce(BOTAO_B)) {
            estado_led_azul = !estado_led_azul;  // Alterna o estado
            gpio_put(LED_AZUL, estado_led_azul);
        }

        sleep_ms(10);  // Pequeno delay para reduzir consumo de CPU
    }

    return 0;
}