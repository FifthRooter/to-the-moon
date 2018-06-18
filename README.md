# to-the-moon

**Introduction**

*To the Moon!* is an SFML-based C++ serious game that puts the player in the shoes of a project
called *LOw Frequency ARray on the Moon (LOFAR)*, whose main objective is to deploy
a network of radio telescopes on the Moon in such a place that the array would be 
protected from the electromagnetic radiation coming from the Earth. 
The reason for this is because the absence of electromagnetic pollution from the Earth would allow for
an unperturbed observation of deep-space radio waves and result in better analysis results
than the ones that are currently obtained by radio telescope arrays on Earth. 


**Game description**

- Vega rocket is used to bring small spacecraft into Low Earth Orbit (LEO), at 300km altitude (Vega specs: https://en.wikipedia.org/wiki/Vega_(rocket)#Specifications)
- The spacecraft will need to bring itself into Low Lunar Orbit (LLO) in order to deliver its (scientific) payload using a
Chemical Propulsion System (CPS).
- The total mass of the spacecraft is 2200kg (can be modified in the CONFIG file). The user can determine how much of that is used for fuel.
This will determine the total possible change in velocity (delta-v) the spacecraft (SC) can achieve.
- The user inputs the distance between the SC and the Lunar surface at first approach to the Moon. From this, the initial velocity boost *dV_0*
is calculated to bring the SC out of LEO towards the Moon, thus performing the Orbital Injection phase of the mission. When the SC has reached 
the set approach distance, a second instantaneous velocity change, *dV_1*, is applied to bring the SC in elliptical orbit around the Moon.
- The third user input will be the height of LLO.
- At exactly half an (elliptical) orbital period, a third (and final) velocity change *dV_2* is applied to circularize the SC orbit at LLO height.
*dV_0*, *dV_1* and *dV_2* are automatically calculated from the user inputs. From the wet mass user input, the maximum allowed dV can be calculated.
The program will check it *dV_0 + dV_1 + dV_2 <= dV_max*. If so, the mission is successful and the rocket will be locked in LLO. If not, 
the user will be shown a message saying the rocket did not have enough fuel, and the mission parameters will need to be adjusted.


**Assumptions**

- Earth is stationary
- Rotation of the Earth and the Moon is ignored
- The Moon is in a circular orbit around Earth
- No drag is taken into account, since the SC is already in space (the SC has already been brought to LEO)
- Gravity effects of the Sun and between the Earth and the Moon are ignored (negligible)
- SC uses CPS
- SC is already positioned at the correct inclination to reach the Moon when launched from LEO
- *M_SC_tot = 2200kg*, *I_sp = 300s*
- All velocity changes are applied instantaneously


** Project installation Guide**

 - The project uses SFML (Simple and Fast Multimedia Library) to build all graphical/interactive parts of the game
 - In addition, some additional libraries for general Math and for solving ODEs are used
 - The project is set up and compiled in Visual Studio 2017
 
 **_setting up SFML in Visual Studio_**
 
 This part is a bit tedious and not very intuitive. 
 - Original SFML documentation: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
 - A video tutorial I followed to set it up (was easier because video - very visual): https://www.youtube.com/watch?v=axIgxBQVBg0
 
 
