/**************************************************************
 * Arduino Bencher
 *
 * @file channels_cfg.h
 *
 * @brief configuration of the ports and mapg to arduino numbers
 *************************************************************/


#ifndef CHANNELS_CFG_H
#define CHANNELS_CFG_H

#include <avr/io.h>


#define INPUT 0
#define OUTPUT 1
#define NOT_GPIO 2

#define HIGH 1
#define LOW 0

#define H 1
#define L 0

typedef struct{
    // uint8_t id; -> the same as the index array
    uint8_t initialportMode;
    uint8_t initialValue_isPullup;
    volatile uint8_t* portIoReg;
    volatile uint8_t* portModeReg;
    uint8_t gpio_bit;
} portConfigType;

#define NUMBER_OF_GIPO 14

// Id's
#define INO_GPIO_0 0
#define INO_GPIO_1 1
#define INO_GPIO_2 2
#define INO_GPIO_3 3
#define INO_GPIO_4 4
#define INO_GPIO_5 5
#define INO_GPIO_6 6
#define INO_GPIO_7 7
#define INO_GPIO_8 8
#define INO_GPIO_9 9
#define INO_GPIO_9 9
#define INO_GPIO_10 10
#define INO_GPIO_11 11
#define INO_GPIO_12 12
#define INO_GPIO_13 13

const portConfigType portConfigurationArray[NUMBER_OF_GIPO] = {

    /******************/
    /***** PORTD ******/
    /******************/

    { 
        /* id: INO_GPIO_0  - RX */
        NOT_GPIO,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        0    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_1  - TX */
        NOT_GPIO,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        1    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_2 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        2    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_3 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        3    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_4 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        4    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_5 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        5    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_6 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        6    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_7 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTD,    /* portIoReg */
        &DDRD,   /* portModeReg */
        7    /* gpio_bit */
    },


    /******************/
    /***** PORTB ******/
    /******************/

    { 
        /* id: INO_GPIO_8 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        0    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_9 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        1    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_10 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        2    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_11 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        3    /* gpio_bit */
    },
    {
        /* id: INO_GPIO_12 */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        4    /* gpio_bit */
    },
    { 
        /* id: INO_GPIO_13 -- LED BUILTIN */
        OUTPUT,   /* initialportMode */
        LOW,    /* initialValue_isPullup */
        &PORTB,    /* portIoReg */
        &DDRB,   /* portModeReg */
        5    /* gpio_bit */
    }
    
    //  6 and 7 are used for the oscilator
};



#endif /* CHANNELS_CFG_H */