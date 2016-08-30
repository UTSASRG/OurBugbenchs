// delop.c delete organizations and persons under dn "dc=korea, dc=my-domain, dc=com"
#include <stdio.h>
#include <stdlib.h>
#include <ldap.h>

#define HOSTNAME "localhost"
#define BIND_DN "cn=Manager, dc=my-domain, dc=com"
#define BASE_DN "dc=my-domain, dc=com"
#define PASS "muzi132126"

static char* cys[] = {"korea", "china", "japan", "british", "french", "germany", "austrilia", "russia", "america", "sealand"};
static char* schools[] = {"hit", "heu", "haut", "hrbust", "hlju", "zzu", "hust", "nudt", "hrbnu", "tsinghua"};
static char* orgs[] = {"cs", "math", "management", "hangtian", "dianxin", "renwen", "jiaotong", "huagong", "jixie", "jianzhu", "yanjiusheng"};

#define NUM_COUNTRY 10
#define NUM_SCHOOL 10
#define NUM_ORG 11

#define NUM_PERSON 30

int main(void){
	LDAP* ld;
	int rc;
	LDAPMod** mods = NULL;
	char dn[512], msg[512];
	char *cyRdn, *schoolRdn, *orgRdn, *personRdn;
	int cyNum, schoolNum, orgNum, pnNum;
	
	if((ld=ldap_init(HOSTNAME, LDAP_PORT)) == NULL){
		printf("ldap initialization failed\n");
		exit(1);
	}

	rc = ldap_simple_bind_s(ld,BIND_DN, PASS);
	if(rc != LDAP_SUCCESS){
		ldap_perror(ld, "bind failed!\n");
		exit(1);
	}
	cyRdn = (char*)malloc(sizeof(char)*32);
	schoolRdn = (char*)malloc(sizeof(char)*64);
	orgRdn = (char*)malloc(sizeof(char)*128);
	personRdn = (char*)malloc(sizeof(char)*256);
	
	for(cyNum = 0; cyNum < NUM_COUNTRY; cyNum++){
		sprintf(cyRdn, "dc=%s", cys[cyNum]); //for example, dc=korea

		for(schoolNum = 0; schoolNum < NUM_SCHOOL; schoolNum++){
			sprintf(schoolRdn, "dc=%s, %s", schools[schoolNum], cyRdn);

			for(orgNum = 0; orgNum < NUM_ORG; orgNum++){
				//orgRdn, for example, ou=cs, dc=hit, dc=korea
				sprintf(orgRdn, "ou=%s, %s", orgs[orgNum], schoolRdn);

				for(pnNum = 0; pnNum < NUM_PERSON; pnNum++){
					sprintf(personRdn, "cn=p%d, %s", pnNum, orgRdn);

					//orgRdn, for example, cn=p1, ou=cs, dc=hit, dc=korea
					sprintf(dn, "%s, %s", personRdn, BASE_DN);
					rc = ldap_delete_s(ld, dn);
					if(rc != LDAP_SUCCESS && rc != LDAP_NO_SUCH_OBJECT){
						sprintf(msg, "delete the entry %s failed!\n", dn);
						ldap_perror(ld, msg);
						exit(1);
					}
				}

				sprintf(dn, "%s, %s", orgRdn, BASE_DN);
				rc = ldap_delete_s(ld, dn);
				if(rc != LDAP_SUCCESS && rc != LDAP_NO_SUCH_OBJECT){
					sprintf(msg, "delete the entry %s failed!\n", dn);
					ldap_perror(ld, msg);
					exit(1);
				}
			}

			sprintf(dn, "%s, %s", schoolRdn, BASE_DN);
			rc = ldap_delete_s(ld, dn);
			if(rc != LDAP_SUCCESS && rc != LDAP_NO_SUCH_OBJECT){
				sprintf(msg, "delete the entry %s failed!\n", dn);
				ldap_perror(ld, msg);
				exit(1);
			}
		}

		sprintf(dn, "%s, %s", cyRdn, BASE_DN);
		rc = ldap_delete_s(ld, dn);
		if(rc != LDAP_SUCCESS && rc != LDAP_NO_SUCH_OBJECT){
			sprintf(msg, "delete the entry %s failed!\n", dn);
			ldap_perror(ld, msg);
			exit(1);
		}
	}

	free((void*)cyRdn);
	free((void*)schoolRdn);
	free((void*)orgRdn);
	free((void*)personRdn);
	ldap_unbind(ld); //unbind
	return 0;
}
