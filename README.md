# Pathfinder Second Edition Combatant Manager v1.0.0

Stack: **QT**, **STL**, **boost**

Build system: **CMake**

> **Boost provided by vcpkg packege manager! (the path should be set 
in CMakeLists.txt)**

## ![screenshot](.\misc\images\screenshot.png)

The app allows to manage combatant turns, the caused effects and 
commands like heal, harm and their mass analogues. 

## Buttons

There are six buttons: create combatant (1), create effect (2), create command (3), create combatants order (4), remove combatant (5) and next turn (6).

1. **Create combatant** rise combatant creation dialog which includes its name, initiative, maximum hit points, command and livingness. The incorrect input just reject creation.
2. **Create effect** should be pressed with combatant picked by user (see [dark green](#combatant-widget-color), [7](#screenshot)). Then effect menu shows we can set predefined effect name, it\'s duration and value. Cthere are some effects that don\'t need duration and/or value. So, they can be set without it\'s input.
3. **Create command** allows user to exert [commands](#commands) on combatants. Commands dialog provides command subject (invoker), objects (recievers), command type (heal/harm), coefficient for everyone combatant and it\'s value that suppors Reverse Polish Notaion with random operation addition. Examples, *3d6 = sum of three random numbers from 1 to 6*, *10В3 - 10 = residual of ten random numbers (1-3) sum and 10*. Cyrillic **в** and **В** are also supported.
4. **Create combatants order** button sorts combatants by their initiative in acsedental order.
5. **Remove combatant** delete [user picked](#combatant-widget-color) combatant.
6. **Next turn** button takes next combatant which effects are executing - dealing damage or just duration decrease. The current combatant paints it\'s widget into [gradient](#combatant-widget-color), [9](#screenshot).

## Combatants
Combatants [(7-9)](#screenshot) have maximum, current hit point (HP) and initiative values that can't be negative. Each combatant have type like team, eneamy or other and alive, dead and contruct. Also at the rigth widget path we can see effects panel [(10-11)](#screenshot) with **active (dark green)** and **disabled (brown)** effects. Another feature is drag&drop mechanic between combatant widget which allows us to change the order by ourselves.

### Combatant widget color:
+ **[Beige](#screenshot)** \- unselected combatant
+ **[Dark green](#screenshot)** \- combatant selected by user (target for effect exertion)
+ **[Gradient from beige to dark green](#screenshot)** \- current combatant in initiative queue

## Effects

Effects show their names, source, duration (in turns!) and values. Combatants, commands and other effect can be a source for current effect. Effects can be picked by Rigth Mouse Button (RMB) with menu appearence. There are three options:
+ **Get Desciption** - get effects standart descriprion (to close pick
effects field [(10-11)](#screenshot) and press ESC)
+ **Activate Effect / Disable Effect** - activate or turn off the effect
+ **Remove Effect** - remove efffect from combatant with 
its deactivation

Peculiar effect feature is "complex effect" that can produce other effects or commands. So, the creation, activation/diactivation and removing of base effect also expanding on child effects.

## Commands

There are two base command - **harm** and **heal** - and two derivatives - **mass harm** and **mass heal**. Every command have name, value and description (subject, object and real value).
At LMB click we can select command and recieve description with it\'s information.
At RMB click command menu with some options shoud arise: 
1. **Do command / undo command** - do disabled command or undo active one
2. **Remove command** - remove command from log

### Commands icons:
+ ![harm](.\misc\images\harm.png) - harm command at signle foe
+ ![heal](.\misc\images\heal.png) - heal command at single foe
+ ![massharm](.\misc\images\massharm.png) - mass harm command
+ ![massheal](.\misc\images\massheal.png) - mass heal command
