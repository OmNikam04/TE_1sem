#simple while loop for menus
ch=0
hello() {
    echo "hello"
}
while [ $ch -lt 7 ]
do
echo "enter your choice: "
read ch
case $ch in 
1)
hello
echo "something"
;;
2)
echo "something 2"
;;
*)
echo "default case"
esac
done
