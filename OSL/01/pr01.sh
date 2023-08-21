#!/bin/bash

# Creating file to store the database
create() {
    echo "File name:"
    read fileName
    fileName=$fileName
    touch $fileName
    # echo "ID Name Marks" >> $fileName
}

generate_id() {
    if [ -e "$fileName" ]; then
        # Get the last used ID from the file or start from 1 if the file is empty
        last_id=$(tail -n 1 "$fileName" | cut -f1)
        if [ -z "$last_id" ]; then
            echo 1
        else
            echo $((last_id + 1))
        fi
    else
        echo 1
    fi
}


validate_phone() {
    phone=$1
    if [[ $phone =~ ^[0-9]{10}$ ]]; then
        return 0
    else
        return 1
    fi
}

add() {
    read -p "Enter name: " name
    read -p "Enter marks: " marks
    read -p "Enter phone number (10 digits only): " phone

    if validate_phone $phone; then
        id=$(generate_id)
        echo -e "$id\t$name\t$marks\t$phone" >> $fileName
        echo "Record added with ID: $id"
    else
        echo "Invalid phone number. Please enter 10 digits."
    fi
}

show() {
    cat $fileName
}

search() {
    read -p "Enter id to search: " to_search

    if grep -wi "$to_search" $fileName; then
        echo "Found the record"
    else
        echo "Record not found"
    fi
}

delete() {
    read -p "Enter id to delete: " to_delete

    if grep -w "$to_delete" $fileName; then
        grep -vw "$to_delete" $fileName > temp
        mv temp $fileName
        echo "Record with ID $to_delete deleted"
    else
        echo "Record with ID $to_delete not found"
    fi
}

modify() {
    read -p "Enter id to update: " to_update

    if grep -w "$to_update" $fileName; then
        echo "Enter new name (or press Enter to keep the existing name):"
        read new_name
        echo "Enter new marks (or press Enter to keep the existing marks):"
        read new_marks
        echo "Enter new phone number (10 digits only, or press Enter to keep the existing number):"
        read new_phone

        awk -v id="$to_update" -v new_name="$new_name" -v new_marks="$new_marks" -v new_phone="$new_phone" 'BEGIN{OFS="\t"} {
            if ($1 == id) {
                if (new_name != "") $2 = new_name
                if (new_marks != "") $3 = new_marks
                if (new_phone != "") {
                    if (length(new_phone) == 10) $4 = new_phone
                    else print "Invalid phone number. Phone number not updated."; exit 1
                }
            }
            print
        }' $fileName > temp

        mv temp $fileName

        echo "Record with ID $to_update updated"
    else
        echo "Record with ID $to_update not found"
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
