i=1
while [ $i -lt 111 ]
do
	echo "blabla $i"
	i=1$i
done
echo "fin de boucle"
