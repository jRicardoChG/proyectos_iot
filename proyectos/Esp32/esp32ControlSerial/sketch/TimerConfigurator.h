
    void ARDUINO_ISR_ATTR onTimer(){
      timerFlag = true;
    }

class TimerModule{
    private:
    bool timerFlag;

    public:
    TimerModule(){
    }

    void resetFlag(){
        timerFlag = false;
    }

    bool getFlag(){
        return timerFlag;
    }
    void turnOnFlag(){
        timerFlag = true;
    }

    void timerSetup(uint8_t microSeconds, void (*fn)()){
        // Use 1st timer of 4 (counted from zero).
        // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
        // info).
        hw_timer_t * timer = timerBegin(0, 80, true);

        // Attach onTimer function to our timer.

        timerAttachInterrupt(timer, &fn, true);

        // Set alarm to call onTimer function every second (value in microseconds).
        // Repeat the alarm (third parameter)
        timerAlarmWrite(timer, microSeconds, true);

        // Start an alarm
        timerAlarmEnable(timer);
    }
};