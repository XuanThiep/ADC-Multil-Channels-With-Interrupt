#include "driverlib.h"
#include "mymsp430.h"


/* In this example ADC 8 channels from A0 to A7, then store adc value to array buffer */

volatile uint16_t adc_value[8];

void Adc_Init(void);

#pragma vector=ADC12_VECTOR
__interrupt void Adc_Isr(void)
{
	if(ADC12_A_getInterruptStatus(ADC12_A_BASE,ADC12IFG7))
	{
		for(uint8_t i=0;i<8;i++)
		{
			adc_value[i]=ADC12_A_getResults(ADC12_A_BASE,i);
		}
		/* For debugger set break point here */
		__no_operation();
	}
}

void main( void )
{
	/* Stop watchdog timer */
	WDT_A_hold(WDT_A_BASE);

	Clk_Using_DCO_Init(16000,8000,SMCLK_CLOCK_DIVIDER_2);

	Adc_Init();

	__enable_interrupt();

	/* Repeat conversion */
	//ADC12_A_startConversion(ADC12_A_BASE,ADC12_A_MEMORY_0,ADC12_A_REPEATED_SEQOFCHANNELS);

	/* One Shot conversion */
	//ADC12_A_startConversion(ADC12_A_BASE,ADC12_A_MEMORY_0,ADC12_A_SEQOFCHANNELS);

	while(1)
	{

	}
}

void Adc_Init(void)
{

	ADC12_A_configureMemoryParam param;

	//Enable A/D channel inputs
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
			GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 |
			GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 |
			GPIO_PIN6 | GPIO_PIN7
	);

	//Initialize the ADC12_A Module
	/*
	 * Base address of ADC12_A Module
	 * Use internal ADC12_A bit as sample/hold signal to start conversion
	 * USE MODOSC 5MHZ Digital Oscillator as clock source
	 * Use default clock divider of 1
	 */
	ADC12_A_init(ADC12_A_BASE,
			ADC12_A_SAMPLEHOLDSOURCE_SC,
			ADC12_A_CLOCKSOURCE_ADC12OSC,
			ADC12_A_CLOCKDIVIDER_1
	);

	ADC12_A_enable(ADC12_A_BASE);

	/*
	 * Base address of ADC12_A Module
	 * For memory buffers 0-7 sample/hold for 256 clock cycles
	 * For memory buffers 8-15 sample/hold for 256 clock cycles
	 * Enable Multiple Sampling
	 */
	ADC12_A_setupSamplingTimer(ADC12_A_BASE,
			ADC12_A_CYCLEHOLD_256_CYCLES,
			ADC12_A_CYCLEHOLD_256_CYCLES,
			ADC12_A_MULTIPLESAMPLESENABLE // for repeat or multi channel scan.
	);

	//Configure Memory Buffers
	/*
	 * Base address of the ADC12_A Module
	 * Configure memory buffer 0
	 * Map input A0 to memory buffer 0
	 * Vref+ = AVcc
	 * Vref- = AVss
	 * Memory buffer 0 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_0;
	param.inputSourceSelect = ADC12_A_INPUT_A0;
	param.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
	param.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
	param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);

	/*
	 * Configure memory buffer 1
	 * Map input A1 to memory buffer 1
	 * Vref+ = AVcc
	 * Vref- = AVss
	 * Memory buffer 1 is not the end of a sequence
	 *
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_1;
	param.inputSourceSelect = ADC12_A_INPUT_A1;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);


	/*
	 * Configure memory buffer 2
	 * Map input A2 to memory buffer 2
	 * Vref+ = AVcc
	 * Vref- = AVss
	 * Memory buffer 2 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_2;
	param.inputSourceSelect = ADC12_A_INPUT_A2;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);


	/*
	 * Base address of the ADC12_A Module
	 * Configure memory buffer 3
	 * Map input A3 to memory buffer 3
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 3 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_3;
	param.inputSourceSelect = ADC12_A_INPUT_A3;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);

	/*
	 * Configure memory buffer 3
	 * Map input A3 to memory buffer 3
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 3 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_3;
	param.inputSourceSelect = ADC12_A_INPUT_A3;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);

	/*
	 * Configure memory buffer 4
	 * Map input A4 to memory buffer 4
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 4 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_4;
	param.inputSourceSelect = ADC12_A_INPUT_A4;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);

	/*
	 * Configure memory buffer 5
	 * Map input A4 to memory buffer 5
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 5 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_5;
	param.inputSourceSelect = ADC12_A_INPUT_A5;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);


	/*
	 * Configure memory buffer 6
	 * Map input A4 to memory buffer 6
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 6 is not the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_6;
	param.inputSourceSelect = ADC12_A_INPUT_A6;
	ADC12_A_configureMemory(ADC12_A_BASE,&param);

	/*
	 * Configure memory buffer 7
	 * Map input A4 to memory buffer 7
	 * Vr+ = AVcc
	 * Vr- = AVss
	 * Memory buffer 7 IS the end of a sequence
	 */
	param.memoryBufferControlIndex = ADC12_A_MEMORY_7;
	param.inputSourceSelect = ADC12_A_INPUT_A7;
	param.endOfSequence = ADC12_A_ENDOFSEQUENCE;

	ADC12_A_configureMemory(ADC12_A_BASE,&param);


    //Enable memory buffer 7 interrupt
    ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12IFG7);
    ADC12_A_enableInterrupt(ADC12_A_BASE,ADC12IE7);

}
