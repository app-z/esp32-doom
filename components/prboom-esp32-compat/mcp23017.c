// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <mcp23x17.h>
#include <driver/gpio.h>
#include <string.h>


#include "driver/gpio.h"
#include "soc/gpio_struct.h"

#include "sdkconfig.h"


#define DELAY() asm("nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;nop; nop; nop; nop;")

// #define INTA_GPIO 19  // INTA pin
#define SDA_GPIO 22
#define SCL_GPIO 21

 #define CONFIG_HW_MCPKEYB_ENA 1

#if CONFIG_HW_MCPKEYB_ENA

    mcp23x17_t dev;


    uint16_t val;
    uint32_t lev;


int keybReadInput() {

        mcp23x17_port_read(&dev, &val);
//        printf("read val = %x\n", val);
//        mcp23x17_get_level(&dev, 6, &lev);
//        printf("level val = %x\n", lev);


	return val;
}


void keybControllerInit() {

    memset(&dev, 0, sizeof(mcp23x17_t));


    gpio_set_pull_mode(SDA_GPIO, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(SCL_GPIO, GPIO_PULLUP_ONLY);



    ESP_ERROR_CHECK(mcp23x17_init_desc(&dev, 0, MCP23X17_ADDR_BASE, SDA_GPIO, SCL_GPIO));

    // Setup PORTA0 as input
    for (int i = 0; i< 8; i++){
        mcp23x17_set_mode(&dev, i, MCP23X17_GPIO_INPUT);
        mcp23x17_set_pullup(&dev, i, 1);
        // mcp23x17_set_level(&dev, i, 1);
    }
}


#else

int keybReadInput() {
	return 0xFFFF;
}


void keybControllerInit() {
	printf("MCP controller disabled in menuconfig; no input enabled.\n");
}

#endif

