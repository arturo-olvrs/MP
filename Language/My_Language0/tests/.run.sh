touch tests//.timeout
CMD="   /home/arturoolvrs/Escritorio/Language/My_Language0/dist/Debug/GNU-Linux/my_language0  < data/SimpleText.txt 1> tests//.out5 2>&1"
eval $CMD
rm tests//.timeout
