#!/bin/bash

create(){
    read -p "Enter name of file: " fileName
    if [ -e $fileName ]; then
        echo "File already exists"
    else
        touch $fileName
        echo "File created successfully" 
    fi
}

generate_id(){
    if [ -e $fileName ]; then
        # get the last line then cut the first column
        last_id=$(tail -n 1 $fileName | cut -f1)
        #if last_id is empty then start with 1
        if [ -z $fileName ]; then
            echo 1
        else 
            echo $((last_id + 1))
        fi
    else
        echo "File does not exists"
    fi
}

insert(){
    read -p "Enter name: " name
    read -p "Enter marks: " marks
    read -p "Enter phone: " phone

    id=$(generate_id)
    
    echo -e "$id\t$name\t$marks\t$phone" >> $fileName
}
show(){
    cat $fileName
}


search(){
    read -p "Enter id to search" to_search

    if grep -wi $to_search $fileName; then
        echo "Record found"
    else 
        echo "Record not found"
    fi
}

delete(){
    read -p "Enter id to delete" to_delete

    if grep -w $to_delete $fileName; then
        grep -vw $to_delete $fileName > temp
        mv temp $fileName
    else
        echo "Record with $to_delete not found"
    fi
}

modify(){
    
    read -p "Enter id to modify" to_modify

    if grep -w $to_modify $fileName; then
        # take input from user
        read -p "Enter new data:(id, name, marks, phone) " new_data
        sed -i "/^$to_modify /c$new_data" $fileName
        echo "Data modified successfully"
    else
        echo "Id not found"
    fi
}


choice=0

while [ $choice -lt 8 ]; do
    echo -e "\nEnter your choice: "
    echo -e "1: Create address book"
    echo -e "2: View Address book"
    echo -e "3: Insert Record"
    echo -e "4: Delete Record"
    echo -e "5: Search Record"
    echo -e "6: Modify Record"
    echo -e "7: Exit"
    read choice

    case $choice in
    1)
        create
        ;;
    2) 
        show
        ;;
    3)
        insert
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
        echo "Exiting..."
        ;;
    esac

done