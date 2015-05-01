## About ##

Just something quick I hacked up because I couldn't find anything similar for myself; it decrypts img3 files when given a Key and an IV.

I could be totally blind/stupid and maybe such a tool already exists, but I went ahead and did it anyway.

This application is based upon the "imagetool" code in the xpwn sources, in fact it's a simple drop-in replacement. If you want to compile this, grab xpwn from git and make sure it compiles (you'll need CMake to set it up), and then you can move the img3decrypt source in SVN here in place of "imagetool.c" and run a make to build it.

http://github.com/planetbeing/xpwn/tree/master


## How to Use ##

|Usage: **img3decrypt** e <input.dmg> <output.dmg> 

&lt;iv&gt;

 

&lt;key&gt;

|
|:-------------------------------------------------------------------------------|

This tool will output the KBAG data from the img3 file regardless of whether you have the IV or Key, and you can generate the IV and Key from this very data by using the hardware AES engine on the iPhone or iPod touch; I'll leave that as an exercise to the reader.

If you **do** have the IV and Key, then you just plug them into img3decrypt as above, and it will output the final decrypted file.
