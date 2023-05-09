touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/arturoolvrs/Escritorio/Language/My_Language1/dist/Debug/GNU-Linux/my_language1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
