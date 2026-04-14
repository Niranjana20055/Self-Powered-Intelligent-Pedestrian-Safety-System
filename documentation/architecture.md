# System Architecture

This system integrates multiple sensors, actuators, and energy harvesting modules to ensure intelligent and sustainable road safety:

- IR sensor detects pedestrians near the crossing
- Ultrasonic sensor measures vehicle distance to prevent collisions
- Sound sensor detects ambulance siren for emergency priority
- Piezoelectric plates generate electrical energy from vehicle pressure
- Arduino processes all inputs using priority-based decision logic
- Servo motor controls the opening and closing of the barrier
- Buzzer provides audible alerts for unsafe conditions
- LCD displays real-time system status and alerts

## Energy Harvesting (Piezoelectric System)

- Piezoelectric plates are embedded under the road prototype
- When vehicles pass over them, mechanical pressure is converted into electrical energy
- The generated AC voltage is rectified and stored using capacitors/batteries
- This stored energy can be used to power system components, making the system **self-sustainable**

## Priority Logic

The system follows a strict priority order to ensure safety and emergency handling:

1. **Ambulance Detection (Highest Priority)**  
   - If the sound sensor detects an ambulance siren, the barrier **opens immediately**  
   - This overrides all other conditions, even if pedestrians are present  

2. **Pedestrian Detection**  
   - If a pedestrian is detected (IR sensor), the barrier **closes** to stop vehicles  

3. **Vehicle Proximity Detection**  
   - If a vehicle comes too close (ultrasonic sensor), the **buzzer is activated**  

4. **Normal Condition (Lowest Priority)**  
   - If no pedestrian or emergency is detected, the barrier **remains open** for smooth traffic flow  
