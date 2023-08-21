## Generating New IDs function
- We want to generate new ID automatically without user input
```
    
generate_id() {
    if [ -e "$fileName" ]; then
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

``````

```if [ -e "$fileName" ]; then```

- Checks if file exists or not

``last_id=$(tail -n 1 "$fileName" | cut -f1)``

- This line reads the last line of the file using the tail with the ``-n 1`` option (which means the last one line). 
- Then, it pipes the output of tail to the cut command with the ``-f1`` option, which extracts the first field (column) from each line. 
- This assumes that the lines in the file are tab-separated fields.
The result is stored in the last_id variable.

``if [ -z "$last_id" ]; then``
- this checks whether last_id is empty 

## Validating phone number
``phone=$1``
- This line assigns the first argument passed to the function.

``if [[ $phone =~ ^[0-9]{10}$ ]]; then``

- `^`: Matches the start of the string.
- `[0-9]`: Matches any digit from 0 to 9.
- `{10}`: Specifies that the previous pattern [0-9] should occur exactly 10 times.
$: Matches the end of the string.

## Modifying only specified data in address book

```
awk -v id="$to_update" 
    -v new_name="$new_name" 
    -v new_marks="$new_marks" 
    -v new_phone="$new_phone" 
    'BEGIN{OFS="\t"} {
            if ($1 == id) {
                if (new_name != "") $2 = new_name
                if (new_marks != "") $3 = new_marks
                if (new_phone != "") {
                    if (length(new_phone) == 10) $4 = new_phone
                    else print "Invalid phone number. 
                    Phone number not updated."; exit 1
                }
            }
            print
        }' $fileName > temp
```
- `awk` is a scripting language used for manipulating data and generating reports. The awk command programming language requires no compiling and allows the user to use variables, numeric functions, string functions, and logical operators. 
- `-v` is used to assign value from shell variable like ``$new_name`` to awk varaible ```new name```
- ``BEGIN{OFS="\t"}`` sets the Output Field Separator (OFS) to a tab,
- ```$1 $2 ...``` specifies the arguments passed to awk command