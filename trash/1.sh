a1=25; b1=25

add() {

        a=`expr $a1 \* $b1`

                return $a

}

add; 
echo $a
