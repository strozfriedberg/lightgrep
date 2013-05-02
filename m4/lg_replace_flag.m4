AC_DEFUN([LG_REPLACE_FLAG], [{
out=
for flag in [$]$1 ; do
  if test x"$flag" = x"$2" ; then
    echo "replacing $flag with $3 in $1"
    out+=" $3"
  else
    out+=" $flag"
  fi
done
$1=$out
}])
