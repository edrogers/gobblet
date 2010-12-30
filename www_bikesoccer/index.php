<html>
<head>
</head>
<body>
<?php
$postdatas0  = $_POST["s0"];
$postdatas1  = $_POST["s1"];
$postdatas2  = $_POST["s2"];
$postdatas3  = $_POST["s3"];
$postdatas4  = $_POST["s4"];
$postdatas5  = $_POST["s5"];
$postdatas6  = $_POST["s6"];
$postdatas7  = $_POST["s7"];
$postdatas8  = $_POST["s8"];
$postdatas9  = $_POST["s9"];
$postdatas10 = $_POST["s10"];
$postdatas11 = $_POST["s11"];
$postdatas12 = $_POST["s12"];
$postdatas13 = $_POST["s13"];
$postdatas14 = $_POST["s14"];
$postdatas15 = $_POST["s15"];
$postdataw0  = $_POST["w0"];
$postdataw1  = $_POST["w1"];
$postdataw2  = $_POST["w2"];
$postdatab0  = $_POST["b0"];
$postdatab1  = $_POST["b1"];
$postdatab2  = $_POST["b2"];
$postdatam0 = $_POST["m0"];
$postdatam1 = $_POST["m1"];
if ($postdatam1 != "") {
	$execute_cmd = 'curl -d "s0=' . $postdatas0 . '&s1=' . $postdatas1 . '&s2=' . $postdatas2 . '&s3=' . $postdatas3 . '&s4=' . $postdatas4 . '&s5=' . $postdatas5 . '&s6=' . $postdatas6 . '&s7=' . $postdatas7 . '&s8=' . $postdatas8 . '&s9=' . $postdatas9 . '&s10=' . $postdatas10 . '&s11=' . $postdatas11 . '&s12=' . $postdatas12 . '&s13=' . $postdatas13 . '&s14=' . $postdatas14 . '&s15=' . $postdatas15 . '&w0=' . $postdataw0 . '&w1=' . $postdataw1 . '&w2=' . $postdataw2 . '&b0=' . $postdatab0 . '&b1=' . $postdatab1 . '&b2=' . $postdatab2 . '&m0=' . $postdatam0 . '&m1=' . $postdatam1 . '" http://ep0.mine.nu/index.php';
	$output = exec("${execute_cmd}");
	echo "$output";
} else if ( $postdatam0 != "" ) {
	$execute_cmd = 'curl -d "s0=' . $postdatas0 . '&s1=' . $postdatas1 . '&s2=' . $postdatas2 . '&s3=' . $postdatas3 . '&s4=' . $postdatas4 . '&s5=' . $postdatas5 . '&s6=' . $postdatas6 . '&s7=' . $postdatas7 . '&s8=' . $postdatas8 . '&s9=' . $postdatas9 . '&s10=' . $postdatas10 . '&s11=' . $postdatas11 . '&s12=' . $postdatas12 . '&s13=' . $postdatas13 . '&s14=' . $postdatas14 . '&s15=' . $postdatas15 . '&w0=' . $postdataw0 . '&w1=' . $postdataw1 . '&w2=' . $postdataw2 . '&b0=' . $postdatab0 . '&b1=' . $postdatab1 . '&b2=' . $postdatab2 . '&m0=' . $postdatam0 . '&m1=' . $postdatam1 . '" http://ep0.mine.nu/index.php';
	$output = exec("${execute_cmd}");
	echo "$output";
} else {
	$execute_cmd = 'curl http://ep0.mine.nu/index.php';
	$output = exec("${execute_cmd}");
	echo "$output";
}
?>
</body>
</html>