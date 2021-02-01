#!/bash/bin

choice=-1
echo "*************MENU*************
            1. Copy
            2. Remove
            3. Rename
            4. Exit "
while [ $choice -ne 4 ]
do
  read -p "Enter you choice: " choice
  case $choice in
  1) read -p "Enter the file to be copied: " f1
     cp $f1 ${f1}_copy
     echo "File copied. New file name is ${f1}_copy..."
    ;;
  2) read -p "Enter the file to be removed: " f1
     rm $f1
     echo "File $f1 removed..."
    ;;
  3) read -p "Enter the file to be renamed: " f1
     read -p "Enter the new filename : " f2
     mv $f1 $f2
     echo "File $f1 renamed as $f2..."
    ;;
  4) exit
    ;;
  *) echo "Wrong choice try again..."
    ;;
  esac
done