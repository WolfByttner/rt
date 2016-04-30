mkdir ~/RTv1

cd OpenGl
make fclean
cp -R * ~/RTv1
echo $1 > ~/RTv1/auteur
echo "Your auteur file contains"
cat -e ~/RTv1/auteur
echo "Remember to check your auteur file"

