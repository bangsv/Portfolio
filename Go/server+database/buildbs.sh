#! usr/bin/bash
echo "Script running" 

if [ -f d:/Desktop/Go_Project/server+database/main.exe  ] # check if the file exists 
then
    rm main.exe # remove the old file if it exists
    go build main.go # build the new file
    ./main.exe # run the new file
fi 
go build main.go # build the new file
./main.exe # run the new file



