#include "stdio.h"
#include "c_pwm.h"

int main (void) {
    int i;
    //initialize_pwm();
    unload_device_tree("P8_13");
    unload_device_tree("P9_14");
    if (pwm_start("P8_13",50,10,0) == -1) {
        printf("Error starting PWM\n");
    } else {
        printf("PWM Started!\n");
    }
    if (pwm_start("P9_14",50,5,0) == -1) {
        printf("Error starting PWM\n");
    } else {
        printf("PWM Started!\n");
    }
    /*
    for (i = 100; i > 0; i--)
    {
        pwm_set_frequency("P8_13",i);
        sleep(10);
    }
    for (i = 0; i < 100; i++)
    {
        pwm_set_frequency("P8_13",i);
        sleep(10);
    }*/
    sleep(5);
    pwm_cleanup();
}
