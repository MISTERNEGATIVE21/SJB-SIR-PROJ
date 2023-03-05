# CReated by MISTERNEGATIVE21 -----SJBTIMER
import machine
import utime
import time

# Create an ADC object for the specified pin
adc = machine.ADC(28)
ov=uv=pv=cv=0
# Define the conversion factor from ADC units to voltage (3.3V reference)
conversion_factor = 3.3 / (65535)

# Define the threshold for the difference between current and previous ADC value
threshold = 0.02
print("Start the experiment in 3")
utime.sleep_ms(1000)
print("Start the experiment in 2")
utime.sleep_ms(1000)
print("Start the experiment in 1")
utime.sleep_ms(1000)
print("Start the experiment")
utime.sleep_ms(1000)
# Initialize the previous ADC value
prev_adc_value = adc.read_u16()
current_adc_value = 5
begin_time = time.ticks_us()
# Loop forever, comparing the current and previous ADC values
while (1):
    # Read the current ADC value
    current_adc_value = adc.read_u16()

    # Convert the ADC value to voltage
    cv = round(current_adc_value * conversion_factor,4)  # current voltage adhust the round of variable for your accuracy
    print("ADC Value: {:d}, Voltage: {:.5f}V".format(current_adc_value,cv))
    
    print(pv,cv)
   # ov=cv*(1+threshold) #ov = over voltage
   # uv=cv*(1-threshold) #ov = under voltage
    # Compare the current and previous ADC values and adjust the LED brightness based on the difference
    if (pv == cv ) :
        break

    else:

    # Update the previous ADC value
        prev_adc_value = current_adc_value
        pv=round(prev_adc_value * conversion_factor,4)
    
    # Wait for 100ms before reading again
    utime.sleep_ms(1000)
end_time = time.ticks_us()
# Calculate the time difference
time_diff = end_time - begin_time

# Print the time difference
print("Time difference: {} seconds".format(time_diff/1000000))

