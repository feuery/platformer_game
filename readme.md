# Platformer game
This started as a game to be done in 48h, as if in a game jam. What did I achieve in 48h? Well, there's a level editor for a platformer game. Game will probably need another 48h to finish.

# To build
To build you need the following libraries
* SDL2
* SDL2_ttf
* SDL2_image

The project uses SCons - utility to build. If you've installed gcc and these libraries, to build just run 'scons' in the project's root. It should create ./bin/game - executable.

# To build for windows
Fuck if I know. This is a trivial project to build in Linux, but it's difficult to build in Windows for the following reasons:
* No central place to manage libraries in
* I might be wrong in this, but I don't know if there exist good C++11/C11 compilers in Windows, or do I have to use Visual C
  * And I have no interest to use Visual Studio at all
* Again, I'd love to be proven wrong, but last I checked I couldn't find Windows-binaries for scons, and I haven't bothered to learn to use cmake

# Where are the assets?
Some assets are done, but because I've heard git is rubbish with larger binary files, I don't have firsthand experience with git and such files, and I had a schedule, I'd love to keep the assets outside of repo as long as possible. They'll be added to the published binaries, of course.

# Future
When I have time and graphics, I'll do some level design, write the actual game engine to run the files this level editor makes and explore how I should build Windows binaries. This work will be done in this repository

# License
Code is GPLv3. When assets and binaries are published, they'll probably be also GPLv3, if that makes any sense with binary data.

# Credits
Code by [Feuer](http://yearofourlord.blogspot.com).
Assets by [Rinkamari](http://rinkamari.deviantart.com/)
