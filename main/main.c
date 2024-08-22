#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define EX_UART_NUM UART_NUM_0
#define BUF_SIZE (1024)

void uart_init() {

    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(EX_UART_NUM, &uart_config);
    uart_set_pin(EX_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
}

void uart_task(void *pvParameters) {
    while (1) {
        const char *test_msg = "H2 Muito Mais História\n";
        uart_write_bytes(EX_UART_NUM, test_msg, strlen(test_msg));
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2 segundos
    }
}

void app_main() {
    uart_init();
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
}
