---
released: true
permalink: /project/
title: 'Final Project'
toc: true
---
{% comment %}
Task list to copy/paste when creating PR:

__Before releasing project:__
- [ ] Review writeup/template files (instructor)
- [ ] Update list of sensors to match latest inventory
- [ ] Edit writeup to set correct dates for current quarter
- [ ] Followup on issues from previous quarter postmortem (issue #344)

{% endcomment %}

The final course deliverable is a project of your own choosing. 
The goal of the project is to consolidate 
your knowledge of the key concepts covered in the CS107e course
and do something creative with your Raspberry Pi. We hope you find the project a fun and satisfying way to put your new knowledge and skills into action and build something you are truly proud of!

## Project schedule and deliverables

### Team formation due __Wed Nov 30__

Form a team of 1 to 3 people. We've observed that a 2-person team works out the best, so that is our recommendation. If you have a project in mind that would be better run as a solo effort or requires a team of 3, come talk it through with us to understand the tradeoffs and challenges for the different arrangements.

Agree on a general direction for your project with your teammate and submit this [Google form](https://docs.google.com/forms/d/e/1FAIpQLScClcMu6aZi6wiAipSNRCl6biRJi5mXICIRfzWnzyQJxjMKbg/viewform) with your team information. We will create a new repository for your team's project on GitHub. Your team will use this shared repo to work together on the project code.

### Project lab 1 (Week 9)

The labs in the final two weeks are used as working meetings for your team. You and your teammates should arrange to attend the same lab session.

In the first project lab, your team will brainstorm project options and refine those ideas into a specific project. Review your plan with us to confirm your direction, scope, and schedule are aligned for a great outcome.  You're now ready to draft your project proposal!

<a name="proposal">
### Proposal due __Thu Dec 1 11:59pm__

In your project repository, there is a template file `Proposal.md`. Edit to update with your project proposal. Submit by committing and pushing to Github.

The project proposal should include:

- Name of the project
- Description of project goals
    + What you hope to learn, explore, or do in completing your project
- Resources needed, budget
- Team members and their responsibilities
    + Each team member should be responsible for a clearly identifiable part of the project
- Schedule
    + Include specific __midpoint milestones__ for check-in during second project lab
    + We will review milestones with you and adjust/refine end goals to ensure success in final push

Re: hardware: If you need to mail order parts, it can take time, so figure out what you need ASAP and place the order. Also, check the [list of sensors](sensors) we have on hand. Let us know what you need, and we will help!

### Project lab 2 (Week 10)

In the second project lab, we will review your team's progress on meeting  midpoint milestones and ensure you are on-track for completing the remaining work.

Please take advantage of this check-in with the course staff; we are eager for you to succeed with your project and want to help resolve any snags you encounter.

### Demo session __Wednesday December 14th 3:30pm-6:30pm__

We schedule the demo session for the final projects during the [final exam slot](https://registrar.stanford.edu/students/final-exams) assigned to us by the registrar. Each group should prepare a short demo of the project to deliver to the class. This is a fun event where you get to show off your work and see all the cool things done by your peers. There is much to celebrate!

### Code submission due __Thursday December 15th 11:59pm__

Your team's github repository is used for coordinating the work throughout the project. Be sure to keep up regular commits as you progress. You must make the final submission of all of the code for your project by end of day.

As part of your final submission, edit the `README.md` file of your repository for the writeup of your completed project.  The writeup should include a short description of what work was performed by each member of the team.

If your project was influenced by ideas or work of other people, please attribute those contributions in the writeup. In particular, if incorporating code from others, you must reference where you got the code, and what changes you made. It should be clear what you did, and what others did. Your project will be primarily evaluated on the portion of the work that is original.


## Grading
Our rubric for evaluating final projects considers two major areas and one bonus opportunity:

+  __Challenge/Technical Achievement__.
    This category evaluates the ambitiousness of the project and its goals. Console was seven weeks of steady work for one person, and earned you a wealth of knowledge and an awesome `libmypi` code base. This puts you in prime position to start from there and achieve something substantial with two people over two weeks. A project typically extends from and builds on the work you have done thus far. Learning new things, researching novel hardware, mastering advanced software techniques, digging in to overcome obstacles, and otherwise meeting additional challenges are all examples of efforts that will be further recognized in this category.
      
+ __Execution__.
    This category evaluates the team’s execution on delivering on the project's goals. Our basic expectation is that the core functionality is operational and able to give a successful demo at the project session. Your further efforts to develop a fully complete set of features, add a high level of polish, design a system that is pleasing to use, build in robustness, and so on will be acknowledged as going above and beyond in the execution category. Execution success is highly correlated with strong teamwork, so your upfront investment in thoughtful planning, time management, and good engineering practice will pay off here.

+ __Originality/Artistry__.
    Although you can have a successful project that reproduces the work of another, we want to nudge you toward attempting a project that is uniquely your own, that mixes your interests and inspirations in imaginative ways or builds something particularly delightful or purposeful to you. We round out the project evaluation with a small nod to its creativity and a reward for your efforts to bring beauty, purpose, joy, elegance, inspiration, or fun to the task.

## Additional resources

In addition to going further with the components you have already used in the course, you are welcome to explore additional hardware and software for your project. Here are some resources you may want to check into.

- ### Part suppliers

    Here are some good vendors for electronics hardware.

    * [Jameco](https://www.jameco.com/) has a great selection of electronic parts. They are also located in Burlingame near SFO. 
    If you place an online order, parts will generally arrive the next day via US mail. If you have a car, you can also drive there and pick up parts same day at the Will Call desk.

    * [Pololu](https://www.pololu.com/) has a wide selection of parts for robotics, including sensors and motor drivers. They also document their parts very well.

    * [Adafruit](https://www.adafruit.com/) Limor Fried has founded a company that caters to makers of all types. Besides building great products, they also provide extensive tutorials and learning guides on their web site.

    * [Sparkfun](https://www.sparkfun.com/) is another great source for hobbyist electronics.

    * Visit [lab64](https://ee.stanford.edu/news/lab64), the EE department's Maker Space located in the basement of the Packard building. This workspace has a variety of tools (oscilloscope, soldering stations, 3-D printer, and more) and a store stocked with basic electronic parts such as transistors, op-amps, etc.


- ### Support code
    The `$CS107E/src` directory contains source code for the support modules from `libpi` and modules from the libraries `libpiextra` and `libpisd`.

    The Raspberry Pi has on-board SPI and I2C controllers, which you can use to communicate with many kinds of sensors and devices that speak those protocols. For example, if you need to read analog input, we have an analog-to-digital converter, the MCP3008, which would communicate over a SPI interface with your Pi. You are welcome to write your own SPI or I2C driver for your device as part of your project. However, if you would like to use an existing implementation, `libpiextra` contains the modules `i2c` and `spi` that you may use (make sure to cite that you used these implementations).

   The `$CS107E/examples` directory contains some sample programs in source code that might be useful to review/adopt (use of armtimer, audio, neopixels, etc.).

   The `$CS107E/extras` directory contains various code shared by former students that might serve as model or inspiration for some part of your project. We know this code was part of a successful past project, but other than that, we don't have a lot of information.  If choosing to adopt any of this code, understand there may have unresolved bugs/issues and code may require adjustments to match our current interfaces as they have changed over time.  

   You are welcome to use these resources in your project, but please be sure to cite these contributions. Your project will be primarily evaluated on the portion of the work that is original.


## Suggestions and inspirations

The direction you take the project is open-ended. The best project is one that that you thought of yourself and that resonates with your interests. 

It is fun to see what others have done and can help get your creative juices flowing. Check out our [project gallery](/project_gallery/) for highlights of past quarters -- what a diverse array of clever projects we have seen! 

There are makers worldwide sharing field reports about the cool things they have concocted.
Some sites to check out:
+ [Hackaday](http://hackaday.com)
+ [Adafruit blog](http://adafruit.com/blog)
+ [Instructables](http://instructables.com)
+ [Hackster](http://hackster.io)
+ Everything done by [Mark Rober](https://www.youtube.com/MarkRober) does is crazy-awesome
+ [StuffMadeHere](https://www.youtube.com/c/StuffMadeHere) makes impressive systems that blend mechanical engineering, electrical engineering, and computer science.

### Games

You have the start of a graphics and input library.
Extend your graphics library to draw additional types of objects,
and your input library to handle a game controller.

Some examples of input devices that you could use to control your game:

- A homebrew game pad made of buttons. Most game pads have
two buttons (A and B) for game control,
and 4 buttons used as a d-pad (left, right, up, down).
- Your PS/2 keyboard and/or mouse.
- Atari 2600 paddle controllers (or other paddle controllers).
- Old-school NES, SNES, or other simple gamepads with simple digital protocols.

Once you have better input, you are all set to build a game.
Build a simple game such as Pong or Tetris,
or even better a game of your own design.

Another cool thing you can do is communicate with old game cartridges, since you
can connect the pins on the cartridge to the GPIO pins on the Pi.

### Music

We described how to generate notes on the Raspberry Pi.
With that knowledge, you can:

- Create a simple music player that allows the user 
to choose from a list of simple melodies.
Add buttons on a breadboard for control (skip, pause, play, volume?)

- Turn your keyboard into a music keyboard,
so that keys play individual notes and pressing multiple keys 
at the same time combines the notes.
Use a combination of timers and low-level keyboard access 
to enable you to record and then loop tracks.

- Take a music synthesizer such as the Korg Monotron 
and hack it to add MIDI support with one Pi,
then have a second Pi control it over MIDI.
Alternatively, build your own music synthesizer.

### System components

Your project should be about building a working system that does something cool.

However, if you build some support infrastructure,
then you can build a more impressive system.
A good sub-project for a team member
is to build a component of the system.

### Analog input

Up to now, we have only read digital values using GPIO. The Raspberry Pi, unlike a microcontroller like an Arduino, cannot read analog values.

Many sensors are analog (photodetectors, potentiometers, temperature sensors, joysticks).

In order to read analog values, you will need to interface an analog
to digital converter (ADC) to the Raspberry Pi.  An example of an ADC
is the MCP3008, which can be controlled from the PI using the Serial
Peripheral Interface (SPI) protocol.

Write a program that reads analog inputs to produce an interesting result, such as a screen visualization or sound.

### Network (ambitious)

Build a simple network that allows multiple raspberry pis to communicate
over a shared medium (only one Pi can transmit at a time).
One way to do this is to connect TX and RX pins to a
shared line.

It is also possible to communicate by other means.
For example, you could use sound, light, or radio waves.

Finally, you've seen in class how "digital" lines aren't purely digital.
You could design your circuit to make bits as sharp as possible to see how
fast you can transmit and receive. You might find that sending bits faster
means you'll have to send smaller packets, so optimize for overall data
  transfer, not just the bit rate.

### GPU (ambitious)

The raspberry pi has a very powerful GPU. In fact, the GPU is much faster than the CPU. The GPU assembly language is similar to, but different,
than the CPU assembly language. It is possible to download code to the GPU using a mailbox, and then call that code. Learn about the GPU and build a library for programming the GPU.

Can you think of a computationally intensive task that could be off-loaded to the GPU? At the very least, you can clear your framebuffer faster!
