touch tests//.timeout
CMD="valgrind --leak-check=full /home/arturoolvrs/Escritorio/Language/My_Language2/dist/Debug/GNU-Linux/my_language2  ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr tests/output/spanish.bgr 1> tests//.out13 2>&1"
eval $CMD
rm tests//.timeout
