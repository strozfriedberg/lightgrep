AC_DEFUN([LG_REMOVE_FLAGS], [{
lg_remove_flags_out_save=$out
lg_remove_flags_flag_save=$flag
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
out=$lg_remove_flags_out_save
flag=$lg_remove_flags_flag_save
}])
