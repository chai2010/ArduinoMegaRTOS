// Copyright 2008 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <FreeRTOS.h>
#include <task.h>
#include <arduino.h>

// 1st task
void myTask1(void *pvParameters) {
	Serial.begin(9600);
	for(;;) 	{
		vTaskDelay( 1000 );
		Serial.print('A');
	}
}

// 2nd task
// this task will flash a LED on pin PB2
void myTask2(void *pvParameters) {
	pinMode(13, OUTPUT);
	
	for(;;) {
		vTaskDelay(1000);
		digitalWrite(13, HIGH);
		vTaskDelay(1000);
		digitalWrite(13, LOW);
	}
}

// this function starts creates both tasks
void myCreateTask( unsigned portBASE_TYPE uxPriority ) {
	xTaskCreate(myTask1, (signed portCHAR*)"myTask1",
		configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL); 
	xTaskCreate(myTask2, (signed portCHAR*)"myTask2",
		configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL);
}

int main() {
	myCreateTask(tskIDLE_PRIORITY+1);
	vTaskStartScheduler();
	return 0;
}
