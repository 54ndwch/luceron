Inspiration from Rudon's Plane by SolarSands: [original](https://youtube.com/watch?v=yeHm6IBG9tQ&t=3164) (audio only) and [storyboard](https://youtube.com/watch?v=mA6P2KK49zk&t=2938) versions.
The goal of this project is to make a map viewer program similar to the one on the computer to capture the feeling of the world. The program is able to navigate the map, but cannot add to it. Adding is only possible through the [map file](#map-file).

# Controls
```
╔══════════════════╗
║ move      [WASD] ║
║ set pos   [F]    ║
║ zoom      [QE]   ║
║ set zoom  [R]    ║
║ get view  [G]    ║
║ set view  [T]    ║
║ hide text [H]    ║
╚══════════════════╝
```

# [Map file](map.txt)
There are three types of data in a map file:
- line (from to): `x1 y1 x2 y2`
- text: One line of text with a `#` before it, then `x y` coordinates in the next line.
```
#This is a text
x y
```
- comment: `## This will not appear on the map.` (Space between the `##` and the comment is not required.)

Preview:
```
┌────────────────────────────────────────────────────────────────────────────────┐
│##                                      ##                                      │
│  ##            ##                      ##                                    ##│
│    ##          ##                      ##                                  ##  │
│    ####        ##                      ##                                ##    │
│    ##  ##      ##                      ##                              ##      │
│    ##    ##    ##                      ##                            ##        │
│    ##      ##  ##                      ##                          ##          │
│    ##        ######################################################            │
│    ##################                  ##          ##          ##              │
│              ########                  ##          ##        ####              │
│              ####  ##                  ##          ##      ##  ##              │
│              ####    ##                ##          ##    ##    ##              │
│              ####  ##  ##              ##          ##  ####    ##              │
│              ####    ##  ##    ##      ##          ######      ##              │
│              ####      ##  ##  ##      ##          ####        ##              │
│              ####        ##  ####      ##        ####          ##              │
│              ####          ##  ####################            ##              │
│              ##################################  ##            ##              │
│              ########################################################          │
│              ##                ####  ##########                ##              │
│################################################################################│
│              ##                ################                ##              │
│              ##              ####################              ##              │
│              ##            ##  ################  ##            ##              │
│              ##############    ##      ##      ##  ##          ##              │
│              ##    ##  ##    ##        ##        ##  ##        ##              │
│              ##    ####    ##          ##          ##  ##      ##              │
│        ##############    ##            ##            ##  ##    ##              │
│              ##    ##  ##              ##              ##      ##              │
│              ##    ####                ##                ##    ##              │
│              ##    ##                  ##                  ##  ##              │
│              ##  ####                  ##                    ####              │
│              ####################################################              │
│              ##                        ##                        ##            │
│            ##                          ##                          ##          │
│          ##                            ##                            ##        │
│        ##                              ##                              ##      │
│      ##                                ##                                ##    │
│    ##                                  ##                                  ##  │
│  ##                                    ##                                    ##│
└────────────────────────────────────────────────────────────────────────────────┘
```
