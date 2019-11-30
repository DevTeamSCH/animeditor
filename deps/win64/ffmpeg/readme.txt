In this folder, you need to put your ffmpeg binaries, library files and includes.

The structure should be as follows:
/include contains all header files for the ffmpeg project
/lib contains all .lib files
/bin contains all .dll files

For Windows, you can get the necessary files from:
https://ffmpeg.zeranoe.com/builds/win64/dev/ffmpeg-4.2.1-win64-dev.zip
https://ffmpeg.zeranoe.com/builds/win64/shared/ffmpeg-4.2.1-win64-shared.zip

Download the dev version and extract it into this folder for the lib and include dirs.
Download the shared version for the dlls and extract that one as well.
Make sure that bin, lib and include are present.