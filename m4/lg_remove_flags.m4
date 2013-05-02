AC_DEFUN([LG_REMOVE_FLAGS], [{
out=
for flag in [$]$1 ; do
  case $2 in
  $flag\ * | *\ $flag | *\ $flag\ * | $flag)
    echo "removing $flag from $1" 
    ;;
  *)
    out+=" $flag"
    ;;
  esac
done
$1=$out
}])
