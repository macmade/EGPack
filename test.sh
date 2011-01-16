#/bin/bash/

rm *.txt
rm *.bin
rm *.egpk

clear

if [ "$2" ] && [ "$2" -gt 0 ]; then
    
    ./build/bin/egpack -d -a "test-files"
    
else
    
    ./build/bin/egpack -a "test-files"
    
fi

if [ "$3" ] && [ "$3" -gt 0 ]; then
    
    ./build/bin/egpack -d -u -x "$1.egpk"
    
else
    
    ./build/bin/egpack -x -u "$1.egpk"
    
fi
