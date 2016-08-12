Setup: Follow PHP 5.6.3 Setup instructions in PHP_SETUP.md

Bugs:
1. Summary: Integer signedness error in the simplestring_addn function in simplestring.c in xmlrpc-epi through 0.54.2, as used in PHP before 5.5.38, 5.6.x before 5.6.24, and 7.x before 7.0.9, allows remote attackers to cause a denial of service (heap-based buffer overflow) or possibly have unspecified other impact via a long first argument to the PHP xmlrpc_encode_request function.

Link: http://www.cvedetails.com/cve/CVE-2016-6296/

Command: 'php ./ho1.php'
  The script takes a few minutes to run. You should see a segmentation fault.

2. Summary: Use After Free Vulnerability in SNMP with GC and unserialize()

Link: https://bugs.php.net/bug.php?id=72479

Command: 'php ./uaf1.php'
  The script runs immediatley and you can see sampler's output.

3. Summany: Use After Free in unserialize() with Unexpected Session Deserialization

Link: https://bugs.php.net/bug.php?id=72562

Command: 'php ./uaf2.php'
  Script runs quickly and Sampler outputs many errors.
