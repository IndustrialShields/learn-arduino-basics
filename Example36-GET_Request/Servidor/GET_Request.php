<?php

//recojo variables
if(isset($_GET["arduino"]) && isset($_GET["message"])){
	$arduino = $_GET["arduino"];
	$message = $_GET["message"];
}
else {
	die("parameters error");
}

echo ("<h4>Hello Arduino $arduino!!</h4>");
echo ("<p>The received message is: \"$message\"</p>");
echo ("OK")
?>
