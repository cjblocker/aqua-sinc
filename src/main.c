
#include "../lib/common/button_boot.h"
#include "adc.h"
#include "uart.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/scs.h>
#include <stdint.h>
#include <stdio.h>

static const adc_channel temp0 = { // PA0, ADC1 channel 0
    .adc_adc = ADC1,
    .adc_channel = 0,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO0,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp1 = { // PA1, ADC1 channel 1
    .adc_adc = ADC1,
    .adc_channel = 1,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO1,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp2 = { // PA2, ADC1 channel 2
    .adc_adc = ADC1,
    .adc_channel = 2,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO2,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp3 = { // PA3, ADC1 channel 3
    .adc_adc = ADC1,
    .adc_channel = 3,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO3,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp4 = { // PA4, ADC1 channel 4
    .adc_adc = ADC1,
    .adc_channel = 4,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO4,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp5 = { // PA5, ADC1 channel 5
    .adc_adc = ADC1,
    .adc_channel = 5,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO5,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp6 = { // PA6, ADC1 channel 6
    .adc_adc = ADC1,
    .adc_channel = 6,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO6,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp7 = { // PA7, ADC1 channel 7
    .adc_adc = ADC1,
    .adc_channel = 7,
    .adc_gpio = {
        .gp_port   = GPIOA,
        .gp_pin    = GPIO7,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp8 = { // PB0, ADC1 channel 8
    .adc_adc = ADC1,
    .adc_channel = 8,
    .adc_gpio = {
        .gp_port   = GPIOB,
        .gp_pin    = GPIO0,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp9 = { // PB1, ADC1 channel 9
    .adc_adc = ADC1,
    .adc_channel = 9,
    .adc_gpio = {
        .gp_port   = GPIOB,
        .gp_pin    = GPIO1,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp10 = { // PC0, ADC1 channel 10
    .adc_adc = ADC1,
    .adc_channel = 10,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO0,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp11 = { // PC1, ADC1 channel 11
    .adc_adc = ADC1,
    .adc_channel = 11,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO1,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp12 = { // PC2, ADC1 channel 12
    .adc_adc = ADC1,
    .adc_channel = 12,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO2,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp13 = { // PC3, ADC1 channel 13
    .adc_adc = ADC1,
    .adc_channel = 13,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO3,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp14 = { // PC4, ADC1 channel 14
    .adc_adc = ADC1,
    .adc_channel = 14,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO4,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

static const adc_channel temp15 = { // PC5, ADC1 channel 15
    .adc_adc = ADC1,
    .adc_channel = 15,
    .adc_gpio = {
        .gp_port   = GPIOC,
        .gp_pin    = GPIO5,
        .gp_mode   = GPIO_MODE_ANALOG,
        .gp_pupd   = GPIO_PUPD_NONE,
        .gp_af     = 0,
        .gp_ospeed = GPIO_OSPEED_DEFAULT,
        .gp_otype  = GPIO_OTYPE_DEFAULT,
        .gp_level  = 0,
    },
};

/*
 * Gamma correction table
 *
 * The nonlinear tables are calculating with the function:
 * Iout = Iin ** gamma
 */
static const uint16_t gamma_table[] = {
	0,		0,		2,		4,		7,		11,		17,		24,
	32,		42,		53,		65,		79,		94,		111,	129,
	148,	169,	192,	216,	242,	270,	299,	330,
	362,	396,	432,	469,	508,	549,	591,	635,
	681,	729,	779,	830,	883,	938,	995,	1053,
	1113,	1175,	1239,	1305,	1373,	1443,	1514,	1587,
	1663,	1740,	1819,	1900,	1983,	2068,	2155,	2243,
	2334,	2427,	2521,	2618,	2717,	2817,	2920,	3024,
	3131,	3240,	3350,	3463,	3578,	3694,	3813,	3934,
	4057,	4182,	4309,	4438,	4570,	4703,	4838,	4976,
	5115,	5257,	5401,	5547,	5695,	5845,	5998,	6152,
	6309,	6468,	6629,	6792,	6957,	7124,	7294,	7466,
	7640,	7816,	7994,	8175,	8358,	8543,	8730,	8919,
	9111,	9305,	9501,	9699,	9900,	10102,	10307,	10515,
	10724,	10936,	11150,	11366,	11585,	11806,	12029,	12254,
	12482,	12712,	12944,	13179,	13416,	13655,	13896,	14140,
	14386,	14635,	14885,	15138,	15394,	15652,	15912,	16174,
	16439,	16706,	16975,	17247,	17521,	17798,	18077,	18358,
	18642,	18928,	19216,	19507,	19800,	20095,	20393,	20694,
	20996,	21301,	21609,	21919,	22231,	22546,	22863,	23182,
	23504,	23829,	24156,	24485,	24817,	25151,	25487,	25826,
	26168,	26512,	26858,	27207,	27558,	27912,	28268,	28627,
	28988,	29351,	29717,	30086,	30457,	30830,	31206,	31585,
	31966,	32349,	32735,	33124,	33514,	33908,	34304,	34702,
	35103,	35507,	35913,	36321,	36732,	37146,	37562,	37981,
	38402,	38825,	39252,	39680,	40112,	40546,	40982,	41421,
	41862,	42306,	42753,	43202,	43654,	44108,	44565,	45025,
	45487,	45951,	46418,	46888,	47360,	47835,	48313,	48793,
	49275,	49761,	50249,	50739,	51232,	51728,	52226,	52727,
	53230,	53736,	54245,	54756,	55270,	55787,	56306,	56828,
	57352,	57879,	58409,	58941,	59476,	60014,	60554,	61097,
	61642,	62190,	62741,	63295,	63851,	64410,	64971,	65535,
};

static void clock_setup(void)
{
	rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	/* Enable clock. */
	rcc_periph_clock_enable(RCC_TIM1);
	rcc_periph_clock_enable(RCC_TIM2);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM4);
	rcc_periph_clock_enable(RCC_TIM8);

	/* Enable Alternate Function clocks. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
}

static void gpio_setup(void)
{
	/*
	 * Set GPIO8 (in GPIO port A) to
	 * 'output alternate function push-pull'.
	 */

	// PORT A

	// A8 - AF1 - T1 C1
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8);
  	gpio_set_af(GPIOA, GPIO_AF1, GPIO8);

	// A9 - AF1 - T1 C2
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
  	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);

	// A10 - AF1 - T1 C3
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10);
  	gpio_set_af(GPIOA, GPIO_AF1, GPIO10);

	// A11 - AF1 - T1 C4
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11);
  	gpio_set_af(GPIOA, GPIO_AF1, GPIO11);

  	// PORT B

  	// B4 - AF2 - T3 C1
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO4);

  	// B5 - AF2 - T3 C2
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO5);

  	// B6 - AF2 - T4 C1
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO6);

  	// B7 - AF2 - T4 C2
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO7);

  	// B8 - AF2 - T4 C3
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO8);

  	// B9 - AF2 - T4 C4
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
  	gpio_set_af(GPIOB, GPIO_AF2, GPIO9);

  	// B10 - AF1 - T2 C3
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10);
  	gpio_set_af(GPIOB, GPIO_AF1, GPIO10);

  	// B11 - AF1 - T2 C4
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11);
  	gpio_set_af(GPIOB, GPIO_AF1, GPIO11);

  	// PORT C

  	// C6 - AF3 - T8 C1
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
  	gpio_set_af(GPIOC, GPIO_AF3, GPIO6);

  	// C7 - AF3 - T8 C2
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
  	gpio_set_af(GPIOC, GPIO_AF3, GPIO7);

  	// C8 - AF3 - T8 C3
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8);
  	gpio_set_af(GPIOC, GPIO_AF3, GPIO8);

  	// C9 - AF3 - T8 C4
	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
  	gpio_set_af(GPIOC, GPIO_AF3, GPIO9);
}

static void tim_setup_01(void)
{
	/* Reset TIM1 peripheral. */
	timer_reset(TIM1);
	/* Timer global mode:
	* - No divider
	* - Alignment edge
	* - Direction up
	*/
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM1, 0);
	timer_set_repetition_counter(TIM1, 0);
	/* Enable preload. */
	timer_disable_preload(TIM1);
	/* Continous mode. */
	timer_continuous_mode(TIM1);
	/* Period (36kHz). */
	timer_set_period(TIM1, 0xFFFF);
	/* Disable outputs. */
	timer_disable_oc_output(TIM1, TIM_OC1);
	timer_disable_oc_output(TIM1, TIM_OC2);
	timer_disable_oc_output(TIM1, TIM_OC3);
	timer_disable_oc_output(TIM1, TIM_OC4);

	timer_set_deadtime(TIM1, 0);
	timer_set_enabled_off_state_in_idle_mode(TIM1);
	timer_set_enabled_off_state_in_run_mode(TIM1);
	timer_disable_break(TIM1);
	timer_set_break_polarity_high(TIM1);
	timer_disable_break_automatic_output(TIM1);
	timer_set_break_lock(TIM1, TIM_BDTR_LOCK_OFF);

	/* -- OC1 configuration -- */
	/* Configure global mode of line 1. */
	timer_disable_oc_clear(TIM1, TIM_OC1);
	timer_enable_oc_preload(TIM1, TIM_OC1);
	timer_set_oc_slow_mode(TIM1, TIM_OC1);
	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM1, TIM_OC1);
	timer_set_oc_idle_state_set(TIM1, TIM_OC1);
	/* Set the capture compare value for OC1 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM1, TIM_OC1, 0xFFFF);
	timer_enable_oc_output(TIM1, TIM_OC1);


	/* -- OC2 configuration -- */
	/* Configure global mode of line 2. */
	timer_disable_oc_clear(TIM1, TIM_OC2);
	timer_enable_oc_preload(TIM1, TIM_OC2);
	timer_set_oc_slow_mode(TIM1, TIM_OC2);
	timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM1, TIM_OC2);
	timer_set_oc_idle_state_set(TIM1, TIM_OC2);
	/* Set the capture compare value for OC2 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM1, TIM_OC2, 0xFFFF);
	timer_enable_oc_output(TIM1, TIM_OC2);


	/* -- OC3 configuration -- */
	/* Configure global mode of line 3. */
	timer_disable_oc_clear(TIM1, TIM_OC3);
	timer_enable_oc_preload(TIM1, TIM_OC3);
	timer_set_oc_slow_mode(TIM1, TIM_OC3);
	timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM1, TIM_OC3);
	timer_set_oc_idle_state_set(TIM1, TIM_OC3);
	/* Set the capture compare value for OC3 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM1, TIM_OC3, 0xFFFF);
	timer_enable_oc_output(TIM1, TIM_OC3);


	/* -- OC4 configuration -- */
	/* Configure global mode of line 4. */
	timer_disable_oc_clear(TIM1, TIM_OC4);
	timer_enable_oc_preload(TIM1, TIM_OC4);
	timer_set_oc_slow_mode(TIM1, TIM_OC4);
	timer_set_oc_mode(TIM1, TIM_OC4, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM1, TIM_OC4);
	timer_set_oc_idle_state_set(TIM1, TIM_OC4);
	/* Set the capture compare value for OC4 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM1, TIM_OC4, 0xFFFF);
	timer_enable_oc_output(TIM1, TIM_OC4);





	timer_enable_preload(TIM1);
	timer_enable_break_main_output(TIM1);
	/* Counter enable. */
	timer_enable_counter(TIM1);

}


static void tim_setup_02(void)
{
	/* Reset TIM2 peripheral. */
	timer_reset(TIM2);
	/* Timer global mode:
	* - No divider
	* - Alignment edge
	* - Direction up
	*/
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM2, 0);
	timer_set_repetition_counter(TIM2, 0);
	/* Enable preload. */
	timer_disable_preload(TIM2);
	/* Continous mode. */
	timer_continuous_mode(TIM2);
	/* Period (36kHz). */
	timer_set_period(TIM2, 0xFFFF);
	/* Disable outputs. */
	timer_disable_oc_output(TIM2, TIM_OC1);
	timer_disable_oc_output(TIM2, TIM_OC2);
	timer_disable_oc_output(TIM2, TIM_OC3);
	timer_disable_oc_output(TIM2, TIM_OC4);

	timer_set_deadtime(TIM2, 0);
	timer_set_enabled_off_state_in_idle_mode(TIM2);
	timer_set_enabled_off_state_in_run_mode(TIM2);
	timer_disable_break(TIM2);
	timer_set_break_polarity_high(TIM2);
	timer_disable_break_automatic_output(TIM2);
	timer_set_break_lock(TIM2, TIM_BDTR_LOCK_OFF);


	/* -- OC3 configuration -- */
	/* Configure global mode of line 3. */
	timer_disable_oc_clear(TIM2, TIM_OC3);
	timer_enable_oc_preload(TIM2, TIM_OC3);
	timer_set_oc_slow_mode(TIM2, TIM_OC3);
	timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM2, TIM_OC3);
	timer_set_oc_idle_state_set(TIM2, TIM_OC3);
	/* Set the capture compare value for OC3 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM2, TIM_OC3, 0xFFFF);
	timer_enable_oc_output(TIM2, TIM_OC3);


	/* -- OC4 configuration -- */
	/* Configure global mode of line 4. */
	timer_disable_oc_clear(TIM2, TIM_OC4);
	timer_enable_oc_preload(TIM2, TIM_OC4);
	timer_set_oc_slow_mode(TIM2, TIM_OC4);
	timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM2, TIM_OC4);
	timer_set_oc_idle_state_set(TIM2, TIM_OC4);
	/* Set the capture compare value for OC4 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM2, TIM_OC4, 0xFFFF);
	timer_enable_oc_output(TIM2, TIM_OC4);



	timer_enable_preload(TIM2);
	timer_enable_break_main_output(TIM2);
	/* Counter enable. */
	timer_enable_counter(TIM2);

}


static void tim_setup_03(void)
{
	/* Reset TIM3 peripheral. */
	timer_reset(TIM3);
	/* Timer global mode:
	* - No divider
	* - Alignment edge
	* - Direction up
	*/
	timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM3, 0);
	timer_set_repetition_counter(TIM3, 0);
	/* Enable preload. */
	timer_disable_preload(TIM3);
	/* Continous mode. */
	timer_continuous_mode(TIM3);
	/* Period (36kHz). */
	timer_set_period(TIM3, 0xFFFF);
	/* Disable outputs. */
	timer_disable_oc_output(TIM3, TIM_OC1);
	timer_disable_oc_output(TIM3, TIM_OC2);
	timer_disable_oc_output(TIM3, TIM_OC3);
	timer_disable_oc_output(TIM3, TIM_OC4);

	timer_set_deadtime(TIM3, 0);
	timer_set_enabled_off_state_in_idle_mode(TIM3);
	timer_set_enabled_off_state_in_run_mode(TIM3);
	timer_disable_break(TIM3);
	timer_set_break_polarity_high(TIM3);
	timer_disable_break_automatic_output(TIM3);
	timer_set_break_lock(TIM3, TIM_BDTR_LOCK_OFF);

	/* -- OC1 configuration -- */
	/* Configure global mode of line 1. */
	timer_disable_oc_clear(TIM3, TIM_OC1);
	timer_enable_oc_preload(TIM3, TIM_OC1);
	timer_set_oc_slow_mode(TIM3, TIM_OC1);
	timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM3, TIM_OC1);
	timer_set_oc_idle_state_set(TIM3, TIM_OC1);
	/* Set the capture compare value for OC1 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM3, TIM_OC1, 0xFFFF);
	timer_enable_oc_output(TIM3, TIM_OC1);


	/* -- OC2 configuration -- */
	/* Configure global mode of line 2. */
	timer_disable_oc_clear(TIM3, TIM_OC2);
	timer_enable_oc_preload(TIM3, TIM_OC2);
	timer_set_oc_slow_mode(TIM3, TIM_OC2);
	timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM3, TIM_OC2);
	timer_set_oc_idle_state_set(TIM3, TIM_OC2);
	/* Set the capture compare value for OC2 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM3, TIM_OC2, 0xFFFF);
	timer_enable_oc_output(TIM3, TIM_OC2);



	timer_enable_preload(TIM3);
	timer_enable_break_main_output(TIM3);
	/* Counter enable. */
	timer_enable_counter(TIM3);

}

static void tim_setup_04(void)
{
	/* Reset TIM1 peripheral. */
	timer_reset(TIM4);
	/* Timer global mode:
	* - No divider
	* - Alignment edge
	* - Direction up
	*/
	timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM4, 0);
	timer_set_repetition_counter(TIM4, 0);
	/* Enable preload. */
	timer_disable_preload(TIM4);
	/* Continous mode. */
	timer_continuous_mode(TIM4);
	/* Period (36kHz). */
	timer_set_period(TIM4, 0xFFFF);
	/* Disable outputs. */
	timer_disable_oc_output(TIM4, TIM_OC1);
	timer_disable_oc_output(TIM4, TIM_OC2);
	timer_disable_oc_output(TIM4, TIM_OC3);
	timer_disable_oc_output(TIM4, TIM_OC4);

	timer_set_deadtime(TIM4, 0);
	timer_set_enabled_off_state_in_idle_mode(TIM4);
	timer_set_enabled_off_state_in_run_mode(TIM4);
	timer_disable_break(TIM4);
	timer_set_break_polarity_high(TIM4);
	timer_disable_break_automatic_output(TIM4);
	timer_set_break_lock(TIM4, TIM_BDTR_LOCK_OFF);

	/* -- OC1 configuration -- */
	/* Configure global mode of line 1. */
	timer_disable_oc_clear(TIM4, TIM_OC1);
	timer_enable_oc_preload(TIM4, TIM_OC1);
	timer_set_oc_slow_mode(TIM4, TIM_OC1);
	timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM4, TIM_OC1);
	timer_set_oc_idle_state_set(TIM4, TIM_OC1);
	/* Set the capture compare value for OC1 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM4, TIM_OC1, 0xFFFF);
	timer_enable_oc_output(TIM4, TIM_OC1);

	/* -- OC2 configuration -- */
	/* Configure global mode of line 2. */
	timer_disable_oc_clear(TIM4, TIM_OC2);
	timer_enable_oc_preload(TIM4, TIM_OC2);
	timer_set_oc_slow_mode(TIM4, TIM_OC2);
	timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM4, TIM_OC2);
	timer_set_oc_idle_state_set(TIM4, TIM_OC2);
	/* Set the capture compare value for OC2 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM4, TIM_OC2, 0xFFFF);
	timer_enable_oc_output(TIM4, TIM_OC2);

	/* -- OC3 configuration -- */
	/* Configure global mode of line 3. */
	timer_disable_oc_clear(TIM4, TIM_OC3);
	timer_enable_oc_preload(TIM4, TIM_OC3);
	timer_set_oc_slow_mode(TIM4, TIM_OC3);
	timer_set_oc_mode(TIM4, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM4, TIM_OC3);
	timer_set_oc_idle_state_set(TIM4, TIM_OC3);
	/* Set the capture compare value for OC3 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM4, TIM_OC3, 0xFFFF);
	timer_enable_oc_output(TIM4, TIM_OC3);

	/* -- OC4 configuration -- */
	/* Configure global mode of line 4. */
	timer_disable_oc_clear(TIM4, TIM_OC4);
	timer_enable_oc_preload(TIM4, TIM_OC4);
	timer_set_oc_slow_mode(TIM4, TIM_OC4);
	timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM4, TIM_OC4);
	timer_set_oc_idle_state_set(TIM4, TIM_OC4);
	/* Set the capture compare value for OC4 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM4, TIM_OC4, 0xFFFF);
	timer_enable_oc_output(TIM4, TIM_OC4);


	timer_enable_preload(TIM4);
	timer_enable_break_main_output(TIM4);
	/* Counter enable. */
	timer_enable_counter(TIM4);

}

static void tim_setup_08(void)
{
	/* Reset TIM1 peripheral. */
	timer_reset(TIM8);
	/* Timer global mode:
	* - No divider
	* - Alignment edge
	* - Direction up
	*/
	timer_set_mode(TIM8, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM8, 0);
	timer_set_repetition_counter(TIM8, 0);
	/* Enable preload. */
	timer_disable_preload(TIM8);
	/* Continous mode. */
	timer_continuous_mode(TIM8);
	/* Period (36kHz). */
	timer_set_period(TIM8, 0xFFFF);
	/* Disable outputs. */
	timer_disable_oc_output(TIM8, TIM_OC1);
	timer_disable_oc_output(TIM8, TIM_OC2);
	timer_disable_oc_output(TIM8, TIM_OC3);
	timer_disable_oc_output(TIM8, TIM_OC4);

	timer_set_deadtime(TIM8, 0);
	timer_set_enabled_off_state_in_idle_mode(TIM8);
	timer_set_enabled_off_state_in_run_mode(TIM8);
	timer_disable_break(TIM8);
	timer_set_break_polarity_high(TIM8);
	timer_disable_break_automatic_output(TIM8);
	timer_set_break_lock(TIM8, TIM_BDTR_LOCK_OFF);

	/* -- OC1 configuration -- */
	/* Configure global mode of line 1. */
	timer_disable_oc_clear(TIM8, TIM_OC1);
	timer_enable_oc_preload(TIM8, TIM_OC1);
	timer_set_oc_slow_mode(TIM8, TIM_OC1);
	timer_set_oc_mode(TIM8, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM8, TIM_OC1);
	timer_set_oc_idle_state_set(TIM8, TIM_OC1);
	/* Set the capture compare value for OC1 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM8, TIM_OC1, 0xFFFF);
	timer_enable_oc_output(TIM8, TIM_OC1);

	/* -- OC2 configuration -- */
	/* Configure global mode of line 2. */
	timer_disable_oc_clear(TIM8, TIM_OC2);
	timer_enable_oc_preload(TIM8, TIM_OC2);
	timer_set_oc_slow_mode(TIM8, TIM_OC2);
	timer_set_oc_mode(TIM8, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM8, TIM_OC2);
	timer_set_oc_idle_state_set(TIM8, TIM_OC2);
	/* Set the capture compare value for OC2 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM8, TIM_OC2, 0xFFFF);
	timer_enable_oc_output(TIM8, TIM_OC2);

	/* -- OC3 configuration -- */
	/* Configure global mode of line 3. */
	timer_disable_oc_clear(TIM8, TIM_OC3);
	timer_enable_oc_preload(TIM8, TIM_OC3);
	timer_set_oc_slow_mode(TIM8, TIM_OC3);
	timer_set_oc_mode(TIM8, TIM_OC3, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM8, TIM_OC3);
	timer_set_oc_idle_state_set(TIM8, TIM_OC3);
	/* Set the capture compare value for OC3 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM8, TIM_OC3, 0xFFFF);
	timer_enable_oc_output(TIM8, TIM_OC3);

	/* -- OC4 configuration -- */
	/* Configure global mode of line 4. */
	timer_disable_oc_clear(TIM8, TIM_OC4);
	timer_enable_oc_preload(TIM8, TIM_OC4);
	timer_set_oc_slow_mode(TIM8, TIM_OC4);
	timer_set_oc_mode(TIM8, TIM_OC4, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM8, TIM_OC4);
	timer_set_oc_idle_state_set(TIM8, TIM_OC4);
	/* Set the capture compare value for OC4 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM8, TIM_OC4, 0xFFFF);
	timer_enable_oc_output(TIM8, TIM_OC4);


	timer_enable_preload(TIM8);
	timer_enable_break_main_output(TIM8);
	/* Counter enable. */
	timer_enable_counter(TIM8);

}

static void tim_setup(void) {
	tim_setup_01();
	tim_setup_02();
	tim_setup_03();
	tim_setup_04();
	tim_setup_08();
}

static void adc_setup(void) {
	init_adc_channel(&temp0);
	init_adc_channel(&temp1);
	init_adc_channel(&temp2);
	init_adc_channel(&temp3);
	init_adc_channel(&temp4);
	init_adc_channel(&temp5);
	init_adc_channel(&temp6);
	init_adc_channel(&temp7);
	init_adc_channel(&temp8);
	init_adc_channel(&temp9);
	init_adc_channel(&temp10);
	init_adc_channel(&temp11);
	init_adc_channel(&temp12);
	init_adc_channel(&temp13);
	init_adc_channel(&temp14);
	init_adc_channel(&temp15);
}


extern void initialise_monitor_handles(void);

int main(void)
{
	int i, j0, d0, k;
	volatile uint16_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	button_boot();

	clock_setup();
	gpio_setup();
	tim_setup();
	adc_setup();
	uart_init();

	/* Enable and initialise the debug monitor handler. */
    SCS_DEMCR |= SCS_DEMCR_VC_MON_EN;
	initialise_monitor_handles();

	j0 = 0;
	d0 = 1;
	k = 0;
	while (1) {
		/* Set the timer compare value to the on time based on the gamma table.
		 * Using the inverse of the gamma table, because the LED on the 1Bitsy
		 * is on when the PWM signal is low.
		 */
		if ( k ==  0 ) timer_set_oc_value(TIM1, TIM_OC1, 65535 - gamma_table[j0]);
		if ( k ==  1 ) timer_set_oc_value(TIM1, TIM_OC2, 65535 - gamma_table[j0]);
		if ( k ==  2 ) timer_set_oc_value(TIM1, TIM_OC3, 65535 - gamma_table[j0]);
		if ( k ==  3 ) timer_set_oc_value(TIM1, TIM_OC4, 65535 - gamma_table[j0]);
		if ( k ==  4 ) timer_set_oc_value(TIM2, TIM_OC3, 65535 - gamma_table[j0]);
		if ( k ==  5 ) timer_set_oc_value(TIM2, TIM_OC4, 65535 - gamma_table[j0]);
		if ( k ==  6 ) timer_set_oc_value(TIM3, TIM_OC1, 65535 - gamma_table[j0]);
		if ( k ==  7 ) timer_set_oc_value(TIM3, TIM_OC2, 65535 - gamma_table[j0]);
		if ( k ==  8 ) timer_set_oc_value(TIM4, TIM_OC1, 65535 - gamma_table[j0]);
		if ( k ==  9 ) timer_set_oc_value(TIM4, TIM_OC2, 65535 - gamma_table[j0]);
		if ( k == 10 ) timer_set_oc_value(TIM4, TIM_OC3, 65535 - gamma_table[j0]);
		if ( k == 11 ) timer_set_oc_value(TIM4, TIM_OC4, 65535 - gamma_table[j0]);
		if ( k == 12 ) timer_set_oc_value(TIM8, TIM_OC1, 65535 - gamma_table[j0]);
		if ( k == 13 ) timer_set_oc_value(TIM8, TIM_OC2, 65535 - gamma_table[j0]);
		if ( k == 14 ) timer_set_oc_value(TIM8, TIM_OC3, 65535 - gamma_table[j0]);
		if ( k == 15 ) timer_set_oc_value(TIM8, TIM_OC4, 65535 - gamma_table[j0]);

		/* Progress through the gamma table index up and down. */
		j0 += d0;
		if (j0 == 255) {
			d0 = -1;
		}
		if (j0 == 0) {
			d0 = 1;
			k += 1;
			printf("%d\n\r", k);

			t0  = adc_read_single( &temp0  );
			t1  = adc_read_single( &temp1  );
			t2  = adc_read_single( &temp2  );
			t3  = adc_read_single( &temp3  );
			t4  = adc_read_single( &temp4  );
			t5  = adc_read_single( &temp5  );
			t6  = adc_read_single( &temp6  );
			t7  = adc_read_single( &temp7  );
			t8  = adc_read_single( &temp8  );
			t9  = adc_read_single( &temp9  );
			t10 = adc_read_single( &temp10 );
			t11 = adc_read_single( &temp11 );
			t12 = adc_read_single( &temp12 );
			t13 = adc_read_single( &temp13 );
			t14 = adc_read_single( &temp14 );
			t15 = adc_read_single( &temp15 );
		}

		if ( k == 16) {
			k = 0;
		}

		/* Wait a little bit. */
		for (i = 0; i < 10000; i++) asm("nop");

	}

	return 0;
}
