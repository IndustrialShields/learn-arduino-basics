<?php

//recojo variables
if(isset($_POST["arduino"]) && isset($_POST["message"])){
	$arduino = $_POST["arduino"];
	$message = $_POST["message"];
}
else {
	die("parameters error");
}

echo ("<h4>Hello Arduino $arduino!!</h4>");
echo ("<p>The received message is: \"$message\"</p>");
echo ("OK")
?>
