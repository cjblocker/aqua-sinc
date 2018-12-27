
#include "../lib/common/button_boot.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

/*
 * Gamma correction table
 *
 * The nonlinear tables are calculating with the function:
 * Iout = Iin ** gamma
 */
static const uint16_t gamma_table[] = {
	0,	0,	2,	4,	7,	11,	17,	24,
	32,	42,	53,	65,	79,	94,	111,	129,
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

static void tim_setup(void)
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
	timer_set_oc_value(TIM1, TIM_OC1, 0xFFFF/2);
	timer_enable_oc_output(TIM1, TIM_OC1);
	timer_enable_preload(TIM1);
	timer_enable_break_main_output(TIM1);
	/* Counter enable. */
	timer_enable_counter(TIM1);

}

static void tim_setup_1(void)
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
	timer_set_oc_value(TIM8, TIM_OC1, 0xFFFF/2);
	timer_enable_oc_output(TIM8, TIM_OC1);

	timer_disable_oc_clear(TIM8, TIM_OC2);
	timer_enable_oc_preload(TIM8, TIM_OC2);
	timer_set_oc_slow_mode(TIM8, TIM_OC2);
	timer_set_oc_mode(TIM8, TIM_OC2, TIM_OCM_PWM1);
	timer_set_oc_polarity_high(TIM8, TIM_OC2);
	timer_set_oc_idle_state_set(TIM8, TIM_OC2);
	/* Set the capture compare value for OC2 to max value -1 for max duty cycle/brightness. */
	timer_set_oc_value(TIM8, TIM_OC2, 0xFFFF/2);
	timer_enable_oc_output(TIM8, TIM_OC2);


	timer_enable_preload(TIM8);
	timer_enable_break_main_output(TIM8);
	/* Counter enable. */
	timer_enable_counter(TIM8);

}

static void tim_setup_2(void)
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
	timer_set_oc_value(TIM4, TIM_OC1, 0xFFFF/2);
	timer_enable_oc_output(TIM4, TIM_OC1);
	timer_enable_preload(TIM4);
	timer_enable_break_main_output(TIM4);
	/* Counter enable. */
	timer_enable_counter(TIM4);

}


int main(void)
{
	int i, j0, d0;

	button_boot();

	clock_setup();
	gpio_setup();
	tim_setup();
	tim_setup_1();
	tim_setup_2();

	j0 = 0;
	d0 = 1;
	while (1) {
		/* Set the timer compare value to the on time based on the gamma table.
		 * Using the inverse of the gamma table, because the LED on the 1Bitsy
		 * is on when the PWM signal is low.
		 */
		timer_set_oc_value(TIM1, TIM_OC1, 65535-gamma_table[j0]);
		timer_set_oc_value(TIM4, TIM_OC1, 65535-gamma_table[j0]);
		timer_set_oc_value(TIM8, TIM_OC1, 65535-gamma_table[j0]);
		timer_set_oc_value(TIM8, TIM_OC2, gamma_table[j0]);

		/* Progress through the gamma table index up and down. */
		j0 += d0;
		if (j0 == 255)
			d0 = -1;
		if (j0 == 0)
			d0 = 1;

		/* Wait a little bit. */
		for (i = 0; i < 100000; i++) asm("nop");

	}

	return 0;
}
