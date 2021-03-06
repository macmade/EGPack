#/bin/bash/

rm -rf test-files-*
rm -rf *.egpk

if [ "$1" ] && [ "$1" -gt 0 ]; then
    
    ./build/bin/egpack -d -a "test-files"
    
else
    
    ./build/bin/egpack -a "test-files"
    
fi

if [ "$2" ] && [ "$2" -gt 0 ]; then
    
    ./build/bin/egpack -d -u "test-files.egpk"
    
else
    
    ./build/bin/egpack -u "test-files.egpk"
    
fi
