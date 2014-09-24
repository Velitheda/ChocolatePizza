ChocolatePizza
==============

Hackfest project

This was the origional repository me and my Summer of tech 2014 Hackfst team used to create a faster form of xz compression/decompression.

We took an existing xz compression libiary written in C and converted it to asm.js using emscripten.  
In order to do this we had to rewrite the main function in the C code by writing a C++ function that took in a compressed string
and returned a decompressed string, calling the libiary in order to do so.  We also had to expose that function (called unxz) to 
the JavaScript that would be calling it using embind.  

The principle this hinges on is that asm.js is very fast, as it avoids dynamically typed variables.  If a variable in asm.js changes 
type, the code gets recompiled.  In C all variables are typed so this does not happen and we are instantly creating fast javascript by this method.

We managed to very sucessfully speed up the rate of decompression with this code, however the overhead of creating even a simple 
"hello world" program with the method we used means that the file itself is quite large and this currently hampers some of its
potential.

While we used this one during the competition, the official repo with a live demo linked is being hosted here: https://github.com/rcar863/ChocolatePizza
