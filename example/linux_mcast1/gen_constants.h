#ifndef LINUX_CONSTANTS_H_INCLUDED
#define LINUX_CONSTANTS_H_INCLUDED

#include "local_constants.h"

#define SDDS_LOCAL_BYTEORDER_LITTLE_ENDIAN
#define SDDS_NET_VERSION 0x01
#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
#define SDDS_MAX_DATA_WRITERS 5
#define SDDS_MAX_DATA_READERS 4
#else
#define SDDS_MAX_DATA_WRITERS 1
#define SDDS_MAX_DATA_READERS 0
#endif

#ifndef SDDS_NET_MAX_OUT_QUEUE
#define SDDS_NET_MAX_OUT_QUEUE 2
#endif /*SDDS_NET_MAX_OUT_QUEUE */

#ifndef SDDS_NET_MAX_BUF_SIZE
#define SDDS_NET_MAX_BUF_SIZE 128
#endif /* SDDS_NET_MAX_BUF_SIZE */

#ifndef SDDS_NET_MAX_LOCATOR_COUNT
#define SDDS_NET_MAX_LOCATOR_COUNT 20
#endif /* SDDS_NET_MAX_LOCATOR_COUNT */

#define SDDS_QOS_DW1_LATBUD 100
#define SDDS_QOS_DW2_LATBUD 500

#define SDDS_TOPIC_HAS_SUB

#ifndef SDDS_TOPIC_APP_MSG_COUNT
#define SDDS_TOPIC_APP_MSG_COUNT 5
#endif /* SDDS_TOPIC_APP_MSG_COUNT */

#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
#define SDDS_TOPIC_MAX_COUNT 5
#else
#define SDDS_TOPIC_MAX_COUNT 1
#endif

#define SDDS_MNG_WORKER_CYCLE_TIME 10000
#define SDDS_MNG_BUILTINT_PUBCYCLE_PRESCALER 2



/* TWI bus speed in Hz */
#define DRIVER_TWI_BUS_SPEED 10000UL // 10kh to use internal pull ups
//#define DRIVER_TWI_BUS_SPEED 100000UL

/* TWI data and clock pin and port */
#define DRIVER_TWI_CLOCK_PORT D
#define DRIVER_TWI_DATA_PORT D
#define DRIVER_TWI_CLOCK_PIN 0
#define DRIVER_TWI_DATA_PIN 1


/* adc reference voltage, see adc.h */
#define DRIVER_WIND_VANE_ADC_REFERENCE ADC_USE_AVCC

/* adc channel for the wind vane */
#define DRIVER_WIND_VANE_ADC_CHANNEL 0

/* resistor used as voltage divider */
#define DRIVER_WIND_VANE_DIVIDER_RESISTOR 5.4f

/* internal = 10bit resoluti0on, pcf8591 = 8bit */
#define DRIVER_WIND_VANE_POSSIBLE_VALUES (1 << 10)

/* define port and pin for the anemometer interrupt */
#define DRIVER_ANEMOMETER_PORT E
#define DRIVER_ANEMOMETER_PIN 5

/* which interrupt is used for the anemometer (5 == PE5) */
#define DRIVER_ANEMOMETER_INTERRUPT 5

/* the external interrupt control register for this interrupt */
#define DRIVER_ANEMOMETER_EICR EICRB

/* how often is the callback called (in seconds) */
#define DRIVER_ANEMOMETER_CALLBACK_PERIOD 1

/* define port and pin for the rain gauge interrupt */
#define DRIVER_RAINGAUGE_PORT E
#define DRIVER_RAINGAUGE_PIN 4

/* which interrupt is used for the rain gauge (4 == PE4) */
#define DRIVER_RAINGAUGE_INTERRUPT 4

/* the external interrupt control register for this interrupt */
#define DRIVER_RAINGAUGE_EICR EICRB

/* how often is the callback called (in seconds) */
#define DRIVER_RAINGAUGE_CALLBACK_PERIOD 1

/* SHT15 bus speed in Hz */
#define DRIVER_SHT15_BUS_SPEED 100000

/* SHT15 data and clock pin and port */
#define DRIVER_SHT15_CLOCK_PORT D
#define DRIVER_SHT15_DATA_PORT D
#define DRIVER_SHT15_CLOCK_PIN 7
#define DRIVER_SHT15_DATA_PIN 5

/*
 * SHT15 temperature coefficients
 * 5V = -4010, 4V = -3980, 3.5V = -3970, 3V = -3960, 2.5V = -3940
 */
#define DRIVER_SHT15_TEMPERATURE_COEFFICIENT -3960

/*
 * SHT15 measurement resolution
 * can be 14bit temperature/12bit humidity
 * or 12bit temperature/8bit humidity
 */
#define DRIVER_SHT15_HIGH_RESOLUTION

/* settings for the AMN31112 PIR Sensor
 */

#define DRIVER_AMN31112_PORT B
#define DRIVER_AMN31112_PIN 5

/* settings for the TSL2561 light sensor
*/

#define DRIVER_TSL2561_TWI_ADDRESS (0x29<<1)

/*
 * Settings for the one wire bus
 */
#define DRIVER_ONEWIRE_PORT E
#define DRIVER_ONEWIRE_PIN 6

/* Settings for LEDS
*/

//#define DRIVER_LED_DIMMING 1

//#define DRIVER_LED_DIMMING_GAMMACORRECTION
/* value is the bit length of the pwm register */
//#define DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT
/*#define DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT*/
/*#define DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT */

/*
 * Settings for WieDAS
 */

#define WIEDAS_SENSORAPP_DOOR_INTERVALL			10
#define WIEDAS_SENSORAPP_WINDOW_INTERVALL		10
#define WIEDAS_SENSORAPP_SWITCH_INTERVALL		10
#define WIEDAS_SENSORAPP_TEMPERATUR_INTERVALL	5
#define WIEDAS_SENSORAPP_LIGHT_INTERVALL		5
#define WIEDAS_SENSORAPP_HUMIDITY_INTERVALL		10
#define WIEDAS_SENSORAPP_MOVEMENT_INTERVALL		10
#define WIEDAS_SENSORAPP_BATTERY_INTERVALL		60
#define WIEDAS_SENSORAPP_SIMPLELAMP_INTERVALL	10
#define WIEDAS_SENSORAPP_DIMMERLAMP_INTERVALL	10
#define WIEDAS_SENSORAPP_ONOFFOUTPUT_INTERVALL	10
#define WIEDAS_SENSORAPP_POWERMETER_INTERVALL	5


#endif
