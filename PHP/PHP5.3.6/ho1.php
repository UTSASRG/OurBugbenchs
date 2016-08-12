<?php
ini_set('memory_limit', '2148M');
$max = 2147483582;

$name = '';
for ($i = 1; $i<$max; $i++) {
	$name .= 'a';
}

$request = xmlrpc_encode_request($name, "somevalue");
?>
