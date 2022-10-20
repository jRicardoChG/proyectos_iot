class PWM{
    private:
        uint32_t pwmResolutionValue;
        uint32_t actualDuty;
        uint8_t gpioPin;
        uint8_t channel;
        uint8_t resolutionBits;
        uint32_t frecuency;
        uint32_t maxValue;
        uint32_t analogArgument;

    public:
        PWM(uint32_t arg_gpioPin, uint8_t arg_resolution, uint32_t arg_frecuency, uint32_t arg_maxValue, uint8_t arg_channel){
            gpioPin = arg_gpioPin;
            resolutionBits = arg_resolution;
            frecuency = arg_frecuency;
            actualDuty = 0;
            maxValue = arg_maxValue;
            channel = arg_channel;
            pwmResolutionValue = pow(2, resolutionBits)-1;
            analogArgument = (pwmResolutionValue / maxValue);
        }

        void generatePWM(uint32_t value){
            actualDuty = analogArgument * min(value,maxValue);
            ledcWrite(channel, actualDuty);    
        }

        void setup(){
            ledcSetup(channel, frecuency, resolutionBits);
            ledcAttachPin(gpioPin, channel);
        }

        uint32_t getMaxValue(){
            return maxValue;
        }

        uint32_t getActualDuty(){
            return actualDuty;
        }

        uint32_t getAnalogArgument(){
            return analogArgument;
        }

        uint32_t getPwmResolutionValue(){
            return pwmResolutionValue;
        }
};