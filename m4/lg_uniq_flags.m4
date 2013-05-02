AC_DEFUN([LG_UNIQ_FLAGS], [{
out=
for flag in [$]$1 ; do
  case $out in
  $flag\ * | *\ $flag | *\ $flag\ * | $flag)
    echo "removing duplicate $flag from $1" 
    ;;
  *)
    out+=" $flag"
    ;;
  esac
done
$1=$out
}])
