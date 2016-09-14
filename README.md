### Oschader Cinder

This doesn't actually do anything by itself! You need to send some OSC messages to it to make it do anything. It's designed to be used with [oscillare](https://github.com/ulyssesp/oscillare).

#### OSC Messages

Address: "/progs"
Content: first string is the name of the slot that the program will go into, second is the type of program.

E.g. "s", "sine" will create a sine program and put it in slot "s" (which is the main slot that's shown)

Address: "/progs/uniform"
Content: first is the slot name, second is the uniform name, third is the value

E.g. "s", "time", 0.3 will set the time of the sine program above to 0.5

Address: "/progs/effect"
Content: first string is the slot slot of the main program, second is the slot of the effect

E.g. Osc message "/progs" "p1", "fade" will put a fade effect into "p1"
and "/progs/effect" "s", "p1" will point the sine program above to "p1"

Address: "/progs/connections"
Content: first string is the slot slot of the main program, the rest are layered programs

E.g. Osc message "/progs" "p1", "sine" will put a base sine program into "p1",
message "/progs" "p2", "dots" will put a base dots program into "p2",
message "/progs" "s", "add" will put an add layer program into "s"
and "/progs/connections" "s", "p1", "p2" will make that layer program add p1 and p2 together.

#### Programs

See [oscillare](https://github.com/ulyssesp/oscillare) for a list of programs.

#### Known Bugs

- Using EqTexture as the base program of Add doesn't work. Not sure why yet.
- Loops aren't checked for prior to rendering. Instead, we cap `getEffect()` at 20 for each program.

#### Up next

- Moving all the visualizations from https://github.com/ulyssesp/AVSyn to this
- Creating a multiply layer effect

Copyright 2016 Ulysses Popple

Image Testcard.jpg by wikimedia user [Ughhhg](https://commons.wikimedia.org/wiki/User:Ughhhg)
