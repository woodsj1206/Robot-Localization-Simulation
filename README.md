# Robot-Localization-Simulation
The Robot Localization Simulation is a program developed to simulate a robot attempting to locate itself in a windy maze by using an HMM algorithm. 

## Overview
The program assumes that the windy maze is surrounded by obstacles, and the robot starts in an open square somewhere in the maze. The robot will uncover its location using the following actions defined below:

**1. Sensing:**
- The robot uses its sensors to check the four directions (West, North, East, South) to determine if those positions are a space or an obstacle. The sensors will assign a value for each direction (0 for a space and 1 for an obstacle). However, the sensing of the robot does not have perfect accuracy. Specifically, the robot can detect the obstacle with 85% and may mistake an open square as an obstacle with 10%. 

     - The above information introduces four fundamental relationships that define the accuracy of the robot’s sensors listed below:
       ```
        - The sensors detect an open square: 90%.
        - The sensors mistake an open square for an obstacle: 10%.
        - The sensors detect an obstacle: 85%.
        - The sensors did not detect an obstacle: 15%.
       ```
     - The sensors use the evidence conditional probability and filtering to calculate the location probabilities of each square using the provided evidence. This is implemented in the Sensing function of the Robot class. The Sensing function goes through each square in the maze, checking the four directions and comparing the direction to the corresponding evidence value.

**2. Moving:**
- The robot can move northward and eastward, reaching the square in either direction with 80%. However, in the windy maze, the robot can drift to the left or right with 10%. Also, if the robot drifts into an obstacle, it will bounce back to the original position with 10%. 

     - The information above presents three important relationships that define the robot’s movement listed below:
       ```
        - The robot reaches the square: 80%.
        - The robot drifts left or right: 10%.
        - The robot bounces back to its original position: 10%.
       ```
     - The movement uses transitional probability and prediction to calculate the location probabilities after the specified movement action. This is implemented in the Moving function in the Robot class. The Moving function calculates the location probability of each square by using the neighboring squares in the four directions.

**Related Conditions:**
The program uses the following layout of the windy maze and sequence of actions:
- **Maze Layout:**
  - "-" represents walkable spaces.
  - "X" represents obstacles.
   ```
    [- - - - - - -]
    [- - X X X X -]
    [- - X - - X -]
    [- X X - - X -]
    [- - - - X X -]
    [- - - - - - -]
   ```
- *NOTE: We assume that the maze is surrounded by obstacles.*

**Actions:**
  ```
  1. Sensing: [0, 0, 0, 1]
  2. Moving northward
  3. Sensing: [0, 1, 0, 0]
  4. Moving eastward
  5. Sensing: [0, 1, 0, 0]
  6. Moving eastward
  7. Sensing: [0, 0, 1, 0]
```
