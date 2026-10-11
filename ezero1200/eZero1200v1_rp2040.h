/* eZero1200v1 PCB header for host controller
 * RP2040 (U4, QFN-56) <-> FPGA (U5, 100-pin) board.
 * Pin map derived from the IPC-D-356 netlist 
 *
 * Naming:   PIN_<NAME>  = GPIO number      MASK_<NAME> = 1u << GPIO number
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware/structs/sio.h"

#define NL_BIT(n)   (1u << (n))

/*  derived from netlist:
 *  GPIO  U4 pin  Net (netlist)        Series part -> destination
 *  ----  ------  -------------------  ------------------------------------------
 *   0      2     PICO_UART0_TX        R7  -> J3-1
 *   1      3     PICO_UART0_RX        R8  <- J3-3
 *   2      4     CONF_INITN           R20 <- FPGA_INITN    (U5-77)
 *   3      5     CONF_DONE            R26 <- FPGA_DONE     (U5-76)
 *   4      6     PICO_I2C0_SDA        R24 -> FPGA_I2C_SDA  (U5-85)
 *   5      7     PICO_I2C0_SCL        R19 -> FPGA_I2C_SCL  (U5-86)
 *   6      8     CONF_TDI             R6  -> JTAG_TDI      (U5-94, J4-5)
 *   7      9     CONF_TDO             R9  <- JTAG_TDO      (U5-95, J4-7)
 *   8     11     CONF_TCK             R3  -> JTAG_TCK      (U5-91, J4-1)
 *   9     12     CONF_TMS             R5  -> JTAG_TMS      (U5-90, J4-3)
 *  10     13     CONF_PROGRAMN        R28 -> FPGA_PROGRAMN (U5-81)
 *  11     14     L0                   direct -> U5-27
 *  12     15     L1                   direct -> U5-28
 *  13     16     L2                   direct -> U5-29
 *  14     17     L3                   direct -> U5-30
 *  15     18     L4                   direct -> U5-34
 *  16     27     PICO_SPI0_MISO       R15 <- FPGA_SPI_SO   (U5-32)
 *  17     28     PICO_SPI0_CS         R11 -> FPGA_SPI_SN   (U5-48)
 *  18     29     PICO_SPI0_SCK        R13 -> FPGA_SPI_MCLK (U5-31)
 *  19     30     PICO_SPI0_MOSI       R16 -> FPGA_SPI_SI   (U5-49)
 *  20     31     L5                   direct -> U5-35
 *  21     32     L6                   direct -> U5-36
 *  22     34     L7                   direct -> U5-37
 *  23     35     L8                   direct -> U5-38
 *  24     36     L9                   direct -> U5-39
 *  25     37     L10                  direct -> U5-40
 *  26     38     PICO_ADC0            J5-2
 *  27     39     PICO_ADC1            J5-3
 *  28     40     PICO_ADC2            J5-4
 *  29     41     PICO_ADC3            J5-5
 *
 */

 /*
 * JTAG config port
 * connected through a series resistor (R6/R9/R3/R5) onto the XO2
 * Keep HIGH-Z whenever an
 * external programmer is plugged into J4 and R6/R9/R3/R5 are soldered
 *   TDI : Pico -> XO2   
 *   TCK : Pico -> XO2   
 *   TMS : Pico -> XO2
 *   TDO : XO2  -> Pico
 */
#define PIN_CONF_TDI        6
#define PIN_CONF_TDO        7
#define PIN_CONF_TCK        8
#define PIN_CONF_TMS        9
#define MASK_CONF_TDI       NL_BIT(PIN_CONF_TDI)
#define MASK_CONF_TDO       NL_BIT(PIN_CONF_TDO)
#define MASK_CONF_TCK       NL_BIT(PIN_CONF_TCK)
#define MASK_CONF_TMS       NL_BIT(PIN_CONF_TMS)
#define MASK_JTAG_OUT       (MASK_CONF_TDI | MASK_CONF_TCK | MASK_CONF_TMS)
#define MASK_JTAG_ALL       (MASK_JTAG_OUT | MASK_CONF_TDO)

/*
 *  XO2 configuration control / status
 *  CONF_PROGRAMN (GPIO10, active low) -> R28 -> FPGA_PROGRAMN 
 *  CONF_INITN    (GPIO2)  <- R20 <- FPGA_INITN (U5-77), input
 *  CONF_DONE     (GPIO3)  <- R26 <- FPGA_DONE  (U5-76), input
 */
#define PIN_CONF_INITN      2
#define PIN_CONF_DONE       3
#define PIN_CONF_PROGRAMN   10
#define MASK_CONF_INITN     NL_BIT(PIN_CONF_INITN)
#define MASK_CONF_DONE      NL_BIT(PIN_CONF_DONE)
#define MASK_CONF_PROGRAMN  NL_BIT(PIN_CONF_PROGRAMN)
#define MASK_CONF_CTRL      (MASK_CONF_INITN | MASK_CONF_DONE | MASK_CONF_PROGRAMN)

 /* 
 * PARALLEL BUS
 *     L0..L4  = GPIO11..15   (5 bits)
 *     L5..L10 = GPIO20..25   (6 bits)
 */
#define PIN_L0              11
#define PIN_L1              12
#define PIN_L2              13
#define PIN_L3              14
#define PIN_L4              15
#define PIN_L5              20
#define PIN_L6              21
#define PIN_L7              22
#define PIN_L8              23
#define PIN_L9              24
#define PIN_L10             25

#define MASK_L0             NL_BIT(PIN_L0)
#define MASK_L1             NL_BIT(PIN_L1)
#define MASK_L2             NL_BIT(PIN_L2)
#define MASK_L3             NL_BIT(PIN_L3)
#define MASK_L4             NL_BIT(PIN_L4)
#define MASK_L5             NL_BIT(PIN_L5)
#define MASK_L6             NL_BIT(PIN_L6)
#define MASK_L7             NL_BIT(PIN_L7)
#define MASK_L8             NL_BIT(PIN_L8)
#define MASK_L9             NL_BIT(PIN_L9)
#define MASK_L10            NL_BIT(PIN_L10)

#define L_COUNT             11
#define L_LO_BASE           11                    /* GPIO of L0 */
#define L_HI_BASE           20                    /* GPIO of L5 */
#define L_MASK_LO           (0x1Fu << L_LO_BASE)  /* L0..L4   = 0x0000F800 */
#define L_MASK_HI           (0x3Fu << L_HI_BASE)  /* L5..L10  = 0x03F00000 */
#define L_MASK              (L_MASK_LO | L_MASK_HI)   /*      = 0x03F0F800 */

/* GPIO number of bus */
#define L_PIN(n)            ((n) < 5 ? (L_LO_BASE + (n)) : (L_HI_BASE + (n) - 5))

#define L_TO_GPIO(v)        (((uint32_t)(v) & 0x1Fu) << L_LO_BASE | \
                             (((uint32_t)(v) >> 5) & 0x3Fu) << L_HI_BASE)
#define L_FROM_GPIO(g)      ((((uint32_t)(g) >> L_LO_BASE) & 0x1Fu) | \
                             ((((uint32_t)(g) >> L_HI_BASE) & 0x3Fu) << 5))

 /* SPI0
 *  MISO GPIO16 <- FPGA_SPI_SO   (U5-32)
 *  CS   GPIO17 -> FPGA_SPI_SN   (U5-48)   active low
 *  SCK  GPIO18 -> FPGA_SPI_MCLK (U5-31)
 *  MOSI GPIO19 -> FPGA_SPI_SI   (U5-49)
 */
#define PIN_SPI0_MISO       16
#define PIN_SPI0_CS         17
#define PIN_SPI0_SCK        18
#define PIN_SPI0_MOSI       19
#define MASK_SPI0_MISO      NL_BIT(PIN_SPI0_MISO)
#define MASK_SPI0_CS        NL_BIT(PIN_SPI0_CS)
#define MASK_SPI0_SCK       NL_BIT(PIN_SPI0_SCK)
#define MASK_SPI0_MOSI      NL_BIT(PIN_SPI0_MOSI)
#define MASK_SPI0_ALL       (0xFu << PIN_SPI0_MISO)

 /* I2C0 
 * external PULL-ups
 */
#define PIN_I2C0_SDA        4
#define PIN_I2C0_SCL        5
#define MASK_I2C0_SDA       NL_BIT(PIN_I2C0_SDA)
#define MASK_I2C0_SCL       NL_BIT(PIN_I2C0_SCL)

 /* connectors
 */
#define PIN_UART0_TX        0
#define PIN_UART0_RX        1
#define MASK_UART0_TX       NL_BIT(PIN_UART0_TX)
#define MASK_UART0_RX       NL_BIT(PIN_UART0_RX)

#define PIN_ADC0            26
#define PIN_ADC1            27
#define PIN_ADC2            28
#define PIN_ADC3            29
#define MASK_ADC_ALL        (0xFu << PIN_ADC0) 
#define ADC_CH(pin)         ((pin) - 26)

/* groupmask*/
#define MASK_FPGA_SPI_I2C   (MASK_SPI0_ALL | MASK_I2C0_SDA | MASK_I2C0_SCL)
#define MASK_FPGA_ALL       (MASK_JTAG_ALL | MASK_CONF_CTRL | L_MASK | \
                             MASK_SPI0_ALL | MASK_I2C0_SDA | MASK_I2C0_SCL)
