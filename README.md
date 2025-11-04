# projectILE is a trajectory calculator

# THIS IS PUBLIC VERSION OF THE PROJECTILE!
**Public version miss some GUI tweaks, but you don't need buy it. It's only made for people who want support me.**
*Paid version:* https://sceawere.itch.io/projectile

### projectILE is a trajectory calculator. It comes with 2 "calculators"
### One, artificial shot.

You give information about your projectile and the calculator gives the results like:

How far it landed, How much time it spend on air, Maximum altitude it reached?

### Two, launch angle calculator.

In this one, with the information about your projectile, you also write "how far away your desired landing spot". And it calculates to find the best angle to launch, of course. If it's impossible to reach, you will recieve an error.
You can also change the environmental variables.

### These effects/forces calculated:

**Projectile:**

Weight, diameter, launch angle(1), muzzle velocity, drag coefficient(aerodynamic)

**Environment:**

(Existence of air), Air pressure, air temperature, gravitational acceleration, gas constant in the air.

### Known bugs/Missing calculations:

**Bug:** You only get error if your first calculation is impossible, otherwise. The program doesn't give any errors, but also don't change the results.

**Missing calculations:** Altitude-based temperature, atmosphere. No wind, Projectile spinning or not?

*I couldn't create an actual .exe file with MinGW, because it never can found the "SDL.h" file, so i created 2 version. Also since it's open-source, you just can re-compile it on your system.*

### Versions:

SDL2 included: Has it's own SDL2 files installed already.

SDL2 system: Don't contain SDL2 files, try to pull them from your system.
