class DataSerialStruct{
    private:
    uint32_t value;
    uint32_t time;

    public:
        DataSerialStruct(uint32_t arg_value, uint32_t arg_time){
            value = arg_value;
            time = arg_time;
        }

        String toJsonString(){
            return String(String(value)+","+String(time));

        }
};