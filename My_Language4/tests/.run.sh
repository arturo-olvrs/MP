touch tests//.timeout
CMD="valgrind --leak-check=full /home/arturoolvrs/Desktop/Language/My_Language4/dist/Debug/GNU-Linux/my_language4  ../Books/fortunata.bgr ../Books/quijote.bgr ../Books/fortunata.bgr 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
