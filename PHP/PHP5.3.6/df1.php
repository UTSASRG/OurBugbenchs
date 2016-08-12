<?php
$xml = <<<EOF
<?xml version='1.0' ?>
<!DOCTYPE wddxPacket SYSTEM 'wddx_0100.dtd'>
<wddxPacket version='1.0'>
	<array><var name="XXXXXXXX"><boolean value="shit"></boolean></var>
		<var name="YYYYYYYY"><var name="ZZZZZZZZ"><var name="EZEZEZEZ">
		</var></var></var>
	</array>
</wddxPacket>
EOF;
$array = wddx_deserialize($xml);
?>
