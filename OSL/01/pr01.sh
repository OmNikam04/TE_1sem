#!/bin/bash

#Creating file to store the database
create() {
    echo "File name:"
    read fileName
    fileName=$fileName
    touch $fileName
}

add() {
    read -p "Enter number of records to insert " records
    echo -e "Enter id\tName\tMarks"

    for ((i = 0; i < $records; i++)); do
        read id name marks
        echo -e "$id\t$name\t$marks" >>$fileName
    done
}

show() {
    cat $fileName
}

search() {
    read -p "Enter id to search: " to_search

    if grep -wi $to_search $fileName; then
        echo "Found the record"
    else
        echo "Not found the record"
    fi
}

delete() {
    read -p "Enter id to delete: " to_search

    if grep -wi $to_search $fileName; then
        # Logic to delete file
        # find the all all the lines that do not matches the pattern using -v flag of grep command
        # print all those lines into sepearate file temp
        echo "Record being deleted: "
        grep -wv $to_search $fileName >>temp
        # delete the original file
        rm $fileName
        # rename the temp as our old file name
        mv temp $fileName
    else
        echo "Record does not exist"
    fi
}

modify() {
    read -p "Enter id to delete: " to_search

    if grep -wi $to_search $fileName; then
        grep -wv $to_search $fileName >>temp
        rm $fileName
        mv temp $fileName

        echo "Enter id:"
        read id

        echo "Enter name:"
        read name

        echo "Enter marks:"
        read marks

        echo -e "$id\t$name\t$marks" >>$fileName

    else
        echo "Record does not exist"
    fi
}

choice=0

while [ $choice -lt 7 ]; do
    echo -e "\nEnter your choice: "
    echo -e "1:Create address book "
    echo -e "2:View Address book "
    echo -e "3:Insert Record "
    echo -e "4:Delete Record "
    echo -e "5:Search Record "
    echo -e "6:Modify Record "
    echo -e "7:Exit"
    read choice
    case $choice in
    1)
        create
        ;;
    2)
        show
        ;;
    3)
        add
        ;;
    4)
        delete
        ;;
    5)
        search
        ;;
    6)
        modify
    ;;
    *)
        echo "Thanks for using our services..."
        ;;
    esac
done
