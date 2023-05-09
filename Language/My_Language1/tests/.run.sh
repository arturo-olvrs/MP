touch tests//.timeout
CMD="valgrind --leak-check=full /home/arturoolvrs/Desktop/RepositorioMP/Language/My_Language1/dist/Debug/GNU-Linux/my_language1  < tests/BodasdeSangre_FedericoGarciaLorca_bigrams.test 1> tests//.out4 2>&1"
eval $CMD
rm tests//.timeout
