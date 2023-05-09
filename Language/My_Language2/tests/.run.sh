touch tests//.timeout
CMD="valgrind --leak-check=full /home/arturoolvrs/Desktop/RepositorioMP/Language/My_Language2/dist/Debug/GNU-Linux/my_language2  1> tests//.out2 2>&1"
eval $CMD
rm tests//.timeout
