Setup: Follow PHP 5.6.3 Setup instructions in PHP_SETUP.md

Bugs: https://www.cvedetails.com/vulnerability-list/vendor_id-74/product_id-128/version_id-178179/PHP-PHP-5.6.3.html

1. Summary: Integer signedness error in the simplestring_addn function in simplestring.c in xmlrpc-epi through 0.54.2, as used in PHP before 5.5.38, 5.6.x before 5.6.24, and 7.x before 7.0.9, allows remote attackers to cause a denial of service (heap-based buffer overflow) or possibly have unspecified other impact via a long first argument to the PHP xmlrpc_encode_request function.

Link: http://www.cvedetails.com/cve/CVE-2016-6296/
      https://bugs.php.net/bug.php?id=72606

Command: 'php ./ho1.php'
  The script takes a few minutes to run. You should see a segmentation fault. Runs very slowly with SANA, bug verified with address sanitizer.

2. Summary: ext/session/session.c in PHP before 5.5.38, 5.6.x before 5.6.24, and 7.x before 7.0.9 does not properly maintain a certain hash data structure, which allows remote attackers to cause a denial of service (use-after-free) or possibly have unspecified other impact via vectors related to session deserialization.

Link: https://www.cvedetails.com/cve/CVE-2016-6290/
      https://bugs.php.net/bug.php?id=72562

Command: 'php ./uaf1.php'
  Output of "Warning: session_decode(): Failed to decode session object. Session has been destroyed in /home/corey/OurBugbenchs/PHP/PHP5.6.3/uaf1.php on line 6" is normal. Use after free bug verified with address sanitizer.

3. Summary: Double free vulnerability in the php_wddx_process_data function in wddx.c in the WDDX extension in PHP before 5.5.37, 5.6.x before 5.6.23, and 7.x before 7.0.8 allows remote attackers to cause a denial of service (application crash) or possibly execute arbitrary code via crafted XML data that is mishandled in a wddx_deserialize call. PHP Sec Bug #72340. Double Free Courruption in wddx_deserialize

Link: https://bugs.php.net/bug.php?id=72340
      https://www.cvedetails.com/cve/CVE-2016-5772/

Command: 'php ./df1.php'

4. Summary: spl_array.c in the SPL extension in PHP before 5.5.37 and 5.6.x before 5.6.23 improperly interacts with the unserialize implementation and garbage collection, which allows remote attackers to execute arbitrary code or cause a denial of service (use-after-free and application crash) via crafted serialized data.

Link: https://bugs.php.net/bug.php?id=72433
      https://www.cvedetails.com/cve/CVE-2016-5771/

Command: 'php ./uaf2.php'
  Use after free bug verified with address sanitizer.

5. Summary: Use-after-free vulnerability in wddx.c in the WDDX extension in PHP before 5.5.33 and 5.6.x before 5.6.19 allows remote attackers to cause a denial of service (memory corruption and application crash) or possibly have unspecified other impact by triggering a wddx_deserialize call on XML data containing a crafted var element. 

Link: https://www.cvedetails.com/cve/CVE-2016-3141/
      https://bugs.php.net/bug.php?id=71587

Command: 'php ./uaf3.php'
  Use after free bug verified with address sanitizer.

6. Summary: The session deserializer in PHP before 5.4.45, 5.5.x before 5.5.29, and 5.6.x before 5.6.13 mishandles multiple php_var_unserialize calls, which allow remote attackers to execute arbitrary code or cause a denial of service (use-after-free) via crafted session content.

Link: https://www.cvedetails.com/cve/CVE-2015-6835/
      https://bugs.php.net/bug.php?id=70219

Command: 'php ./uaf4.php'
  Use after free bug verified with address sanitizer.

7. Summary: Multiple use-after-free vulnerabilities in ext/date/php_date.c in PHP before 5.4.38, 5.5.x before 5.5.22, and 5.6.x before 5.6.6 allow remote attackers to execute arbitrary code via crafted serialized input containing a (1) R or (2) r type specifier in (a) DateTimeZone data handled by the php_date_timezone_initialize_from_hash function or (b) DateTime data handled by the php_date_initialize_from_hash function.

Link: https://www.cvedetails.com/cve/CVE-2015-0273/
      https://bugs.php.net/bug.php?id=68942

Command: 'php ./uaf5.php'
  Use after free bug verified with address sanitizer.

