cd src
echo "meuildingmuh"
g++ -o me_muh.exe -std=c++11 misc.cpp Me_word.cpp Me_line.cpp Me_code.cpp new_main.cpp
echo "built"
echo "file ready"
mv me_muh.exe ..
cd ..
rm *.o
