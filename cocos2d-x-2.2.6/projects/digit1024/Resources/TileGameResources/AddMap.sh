#!\bin\bash 

echo "started"
maps=`ls |grep map`
echo $maps
x=1
while [ -e "map$x.tmx" ]; do
echo " MAPA map$x.tmx istnieje"
x=$[x + 1]
done
echo " MAPA map$x.tmx NIE istnieje"
echo "kopiujê mapê 1 do mapy $x"
cp "map1.tmx" "map$x.tmx"