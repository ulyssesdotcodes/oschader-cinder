### Oschader Cinder

This doesn't actually do anything by itself! You need to send some OSC messages to it to make it do anything. It's designed to be used with https://github.com/ulyssesp/oscillare.

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

#### Programs

There are only a few built in programs currently. They fall into three categories.

##### Base programs

Sine, Dots, AudioData

These programs actually display something. They're usually the first ones in your chain.

Adding more based on a fragment shader is as easy as using ProgramRect::create.

##### Effect programs

Fade, Repeat, Scale

These programs modify something that's already been displayed with a base program.

Adding more based on a fragment shader is easy using EffectRect::create.

##### Passthrough

This is a special program that just defers rendering to a different slot. Use it when you want to keep a program in memory but also want to switch between different programs in a single slot.

##### Layer effect

Add

These combine a base layer with a secondary layer.

#### Known Bugs

- Using EqTexture as the base program of Add doesn't work. Not sure why yet.
- Loops aren't checked for prior to rendering. Instead, we cap `getEffect()` at 20 for each program.

#### Up next

- Moving all the visualizations from https://github.com/ulyssesp/AVSyn to this
- Creating a multiply layer effect
