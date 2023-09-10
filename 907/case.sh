#! /bin/sh

echo "Is it morning please answer the question(yes or no)."
read YES_OR_NO
case "$YES_OR_NO" in
yes|y|Yes|YES)
    echo "good Morning!";;
[nN*])
    echo "good afternoon!";;
*)
    echo "Sorry ,$YES_OR_NO not recongnized. Enter yes or no"
    exit 1;;
esac
exit 0;