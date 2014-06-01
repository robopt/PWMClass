#include <string>
using namespace std;

/* PWM Class for Beaglebone Black
 */

class PWMClass {
    public:
        PWMClass(); //create a pwm class object with the default pin of P8_13
        PWMClass(string pin); //create a pwm class object with the specified pin

        int open_pwm(); //initialize/open pwm
        int close_pwm(); //close pwm
        int set_duty(int duty); //set the PWM duty cycle
        int set_period(int period); //set the PWM period
        int set_run(bool runstate); //set whether the pwm is running (0/1)
    private:
        string pin;
}
