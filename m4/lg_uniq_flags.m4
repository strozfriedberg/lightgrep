AC_DEFUN([LG_UNIQ_FLAGS], [{
lg_uniq_flags_out_save=$out
lg_uniq_flags_flag_save=$flag
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
out=$lg_uniq_flags_out_save
flag=$lg_uniq_flags_flag_save
}])
