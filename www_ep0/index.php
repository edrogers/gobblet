<?php
$postdatam0 = $_POST["m0"];
$postdatam1 = $_POST["m1"];
if ($postdatam1 != "") {
  echo exec("./php_gobblet $_POST[s0] $_POST[s1] $_POST[s2] $_POST[s3] $_POST[s4] $_POST[s5] $_POST[s6] $_POST[s7] $_POST[s8] $_POST[s9] $_POST[s10] $_POST[s11] $_POST[s12] $_POST[s13] $_POST[s14] $_POST[s15] $_POST[w0] $_POST[w1] $_POST[w2] $_POST[b0] $_POST[b1] $_POST[b2] $_POST[m0] $_POST[m1]");
} else if ( $postdatam0 != "" ) {
  echo exec("./php_gobblet $_POST[s0] $_POST[s1] $_POST[s2] $_POST[s3] $_POST[s4] $_POST[s5] $_POST[s6] $_POST[s7] $_POST[s8] $_POST[s9] $_POST[s10] $_POST[s11] $_POST[s12] $_POST[s13] $_POST[s14] $_POST[s15] $_POST[w0] $_POST[w1] $_POST[w2] $_POST[b0] $_POST[b1] $_POST[b2] $_POST[m0]");
} else {
  echo exec("./php_gobblet");
}
?>
