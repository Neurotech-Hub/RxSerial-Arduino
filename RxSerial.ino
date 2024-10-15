int16_t receive_16bit_value_with_frame() {
    // Wait for start byte (0xAA)
    while (Serial1.available()) {
        byte start_byte = Serial1.read();
        if (start_byte == 0xAA) {  // Check for the start byte
            while (Serial1.available() < 2) {
                // Wait until two bytes are available
            }
            // Read the high byte and low byte
            uint8_t high_byte = Serial1.read();  // Read the upper 8 bits
            uint8_t low_byte = Serial1.read();   // Read the lower 8 bits
            
            // Combine the high and low bytes into a 16-bit integer
            int16_t value = (high_byte << 8) | low_byte;
            
            // Optionally read and check the end byte (if used)
            // if (Serial1.read() != 0x55) { 
            //     // Handle error if end byte is not correct
            // }
            
            return value;  // Return the received 16-bit value
        }
    }
    return 0;  // Default return if no valid frame
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(4800);  // Start Serial1 communication at 4800 baud rate
    delay(2000); // Wait for initialization
    Serial.println("Hello!");
}

void loop() {
    if (Serial1.available() > 0) {
        int16_t adc_value = receive_16bit_value_with_frame();  // Receive 16-bit ADC value
        Serial.print("-512,512,");
        Serial.println(adc_value);  // Print the received value
    }
}
