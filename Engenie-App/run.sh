./build.sh $1
executable="$(find build -maxdepth 1 -type f -executable)"
$("./$executable")
