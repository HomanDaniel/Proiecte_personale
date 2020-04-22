<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" type="text/css" href="css/mobile.css" media="screen and (max-width : 568px)">
	<script type="text/javascript" src="js/mobile.js"></script>
</head>
<body>
<h1> Inserare reusita. Intrati pe MySQL.</h1>

<?php

$x=mysql_connect("localhost", "homandani", "tm68nik");
 if(!$x)
 	die ('Nu s-a realizat conectarea'.mysql_error());

 $y=mysql_select_db("homandani", $x);
 if(!$y)
 	die('Baza de date nu poate fi accesata'. mysql_error());

 $fname=$_POST['fname'];
 $address=$_POST['address'];
 $email=$_POST['email'];
 $phone=$_POST['phone'];
 $message=$_POST['message'];
        
 $z=mysql_query("INSERT INTO homandani.Site_Contact (nume, adresa, email, telefon, mesaj) VALUES ('$fname','$address','$email','$phone','$message')",$x);
 if(!$z)
           die('Inserarea nu a putut fi realizata'.mysql_error());	  
mysql_close($x);
?>

</body>

