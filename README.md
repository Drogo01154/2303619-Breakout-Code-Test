# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

You are to spend between three and eight hours improving this simple Breakout implementation in a way to best demonstrate your capabilities as a games programmer. 

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* Add an actual game loop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball, brick-tracking ball)
    * Note: smallPaddle is too simple to be impressive.
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as Ollama

# Time Details and Changelist
Hour 1: Added mouse control.
    - Added check if mouse position changed within Game Manager, then set paddles X position to that of mouse.
Hour 2: Fixed scaling issues when changing screen size.
    - Made game manager store intial window size.
    - Made Paddle, balls, powerups and brick spawning all use initial window size instead of current windowsize. 
    - Made it so mouse input normalised between -1 and 1 and then multiplied by original screen width for better scaling with window. 
Hour 3-4: Added in Multi-ball powerup. 
    - Changed single ball ptr to a list of balls (so it could be resized efficiently within update loop). 
    - made create ball function in gameManager which adds new balls to list. 
    - Added ball type enum, set MultiBall function and functionality in ball update to allow ball create smaller balls if powerup active and it hits bricks, also return bool on if ball is to be deleted when out of bounds. 
    - Created MultiBall powerup and added it to Powerup managers spawn system. 
    - Changed GameManager update and render logic to loop over all balls in list as well as delete balls if their update notifies them to.
    - Updated GameManagers lose life logic to only lose life if no balls remain and respawn ball on next update if all deleted. 
Last five minuites: Made powerup randomiser seed based on time, so results different each time you load the game. 

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again
* 2026 - James added mouse control, screen scaling fix and multi-ball power up. 

---

Curse you, fast ball!