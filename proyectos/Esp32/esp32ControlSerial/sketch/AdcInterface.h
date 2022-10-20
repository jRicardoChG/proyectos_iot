class AdcConfigurer{
    
    private:
    uint8_t pinAdc;
    String mode;
    uint8_t resolution;
    
    public:

    AdcConfigurer(String arg_mode, uint8_t arg_pinAdc, uint8_t arg_resolution){
        pinAdc = arg_pinAdc;
        mode = arg_mode;
        resolution = arg_resolution;
    }
    
    void adcSetup(){
        analogRead(pinAdc);
        analogReadResolution(resolution);
        adcAttachPin(pinAdc);
    }

    uint32_t adcRead(){
        return analogRead(pinAdc); 
    }
};