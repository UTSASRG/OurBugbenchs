// addop.c add organizations and persons under dn "dc=korea, dc=my-domain, dc=com"
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

// zjp
#if 1
#define NUM_COUNTRY 1
#define NUM_SCHOOL 1
#define NUM_ORG 1
#define NUM_PERSON 3
#else
#define NUM_COUNTRY 10
#define NUM_SCHOOL 10
#define NUM_ORG 11
#define NUM_PERSON 30
#endif

static char* surnames[] = {"zhang", "wang", "liu", "yu", "bian", "huang", "chen", "su", "meng", "pang"};


int main(void){
	// zjp
	sleep(3);

	LDAP* ld;
	int i, rc;
	int attrNum;
	LDAPMod** mods = NULL;
	char dn[512], msg[512];
	//char* pdn, *prdn; //parent dn, parent relative dn.
	char *cyRdn, *schoolRdn, *orgRdn, *personRdn;
	int cyNum, schoolNum, orgNum, pnNum;
	char strCn[64], strSn[64], strTel[64];
	
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
		// create a country dn, for example, "dc=korea, dc=my-domain, dc=com"
		attrNum = 3;
		mods = (LDAPMod**)malloc(sizeof(LDAPMod*)*(attrNum+1));
		for(i = 0; i < attrNum; i++){
			mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
			mods[i]->mod_op = LDAP_MOD_ADD; //changetype: add
		}
		mods[attrNum] = NULL;
		// add attribute objectClass: country
		mods[0]->mod_type="objectClass";
		mods[0]->mod_values=(char**)malloc(sizeof(char*)*3);
		mods[0]->mod_values[0]="country";
		mods[0]->mod_values[1]="dcObject";
		mods[0]->mod_values[2]=NULL;

		// add attribute, for example, dc: korea
		mods[1]->mod_type="dc";
		mods[1]->mod_values=(char**)malloc(sizeof(char*)*2);
		mods[1]->mod_values[0]=cys[cyNum];
		mods[1]->mod_values[1]=NULL;

		// add attribute, for example, c: korea
		mods[2]->mod_type="c";
		mods[2]->mod_values=(char**)malloc(sizeof(char*)*2);
		mods[2]->mod_values[0]=cys[cyNum];
		mods[2]->mod_values[1]=NULL;

		// add dn and its attributes
		sprintf(cyRdn, "dc=%s", cys[cyNum]); //for example, dc=korea
		sprintf(dn, "%s, %s", cyRdn, BASE_DN);
		rc = ldap_add_s(ld, dn, mods);
		if(rc != LDAP_SUCCESS && rc != LDAP_ALREADY_EXISTS){
			sprintf(msg, "add the entry %s failed!\n", dn);
			ldap_perror(ld, msg);
			exit(1);
		}
		for(i = 0; i < attrNum; i++){ //note "i < attrNum", not "i <= attrNum"
			free((void*)(mods[i]->mod_values));
			free((void*)mods[i]);
			//mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
		}
		free((void*)mods);

		for(schoolNum = 0; schoolNum < NUM_SCHOOL; schoolNum++){
			//create a organization under the country dn
			attrNum = 3;
			mods = (LDAPMod**)malloc(sizeof(LDAPMod*)*(attrNum+1));
			for(i = 0; i < attrNum; i++){
				mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
				mods[i]->mod_op = LDAP_MOD_ADD; //changetype: add
			}
			mods[attrNum] = NULL;
			// add attribute objectClass: dcObject
			// objectClass: organization
			mods[0]->mod_type="objectClass";
			mods[0]->mod_values=(char**)malloc(sizeof(char*)*3);
			mods[0]->mod_values[0]="dcObject";
			mods[0]->mod_values[1]="organization";
			mods[0]->mod_values[2]=NULL;

			// add attribute, for example, dc: hit
			mods[1]->mod_type="dc";
			mods[1]->mod_values=(char**)malloc(sizeof(char*)*2);
			mods[1]->mod_values[0]=schools[schoolNum];
			mods[1]->mod_values[1]=NULL;

			// add attribute, for example, o: hit
			mods[2]->mod_type="o";
			mods[2]->mod_values=(char**)malloc(sizeof(char*)*2);
			mods[2]->mod_values[0]=schools[schoolNum];
			mods[2]->mod_values[1]=NULL;

			//schoolRdn, for example, dc=hit, dc=korea
			sprintf(schoolRdn, "dc=%s, %s", schools[schoolNum], cyRdn);
			sprintf(dn, "%s, %s", schoolRdn, BASE_DN);
			rc = ldap_add_s(ld, dn, mods);
			if(rc != LDAP_SUCCESS && rc != LDAP_ALREADY_EXISTS){
				sprintf(msg, "add the entry %s failed!\n", dn);
				ldap_perror(ld, msg);
				exit(1);
			}
			for(i = 0; i < attrNum; i++){ //note "i < attrNum", not "i <= attrNum"
				free((void*)(mods[i]->mod_values));
				free((void*)mods[i]);
				//mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
			}
			free((void*)mods);

			for(orgNum = 0; orgNum < NUM_ORG; orgNum++){
				//create a organization under the school dn, for example, dc=hit, dc=korea, dc=my-domain, dc=com
				attrNum = 2;
				mods = (LDAPMod**)malloc(sizeof(LDAPMod*)*(attrNum+1));
				for(i = 0; i < attrNum; i++){
					mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
					mods[i]->mod_op = LDAP_MOD_ADD; //changetype: add
				}
				mods[attrNum] = NULL;
				// add attribute objectClass: organizationalUnit
				mods[0]->mod_type="objectClass";
				mods[0]->mod_values=(char**)malloc(sizeof(char*)*2);
				mods[0]->mod_values[0]="organizationalUnit";
				mods[0]->mod_values[1]=NULL;

				// add attribute, for example, ou: cs
				mods[1]->mod_type="ou";
				mods[1]->mod_values=(char**)malloc(sizeof(char*)*2);
				mods[1]->mod_values[0]=orgs[orgNum];
				mods[1]->mod_values[1]=NULL;

				//orgRdn, for example, ou=cs, dc=hit, dc=korea
				sprintf(orgRdn, "ou=%s, %s", orgs[orgNum], schoolRdn);
				sprintf(dn, "%s, %s", orgRdn, BASE_DN);
				rc = ldap_add_s(ld, dn, mods);
				if(rc != LDAP_SUCCESS && rc != LDAP_ALREADY_EXISTS){
					sprintf(msg, "add the entry %s failed!\n", dn);
					ldap_perror(ld, msg);
					exit(1);
				}
				for(i = 0; i < attrNum; i++){ //note "i < attrNum", not "i <= attrNum"
					free((void*)(mods[i]->mod_values));
					free((void*)mods[i]);
					//mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
				}
				free((void*)mods);

				for(pnNum = 0; pnNum < NUM_PERSON; pnNum++){
					attrNum = 4;
					mods = (LDAPMod**)malloc(sizeof(LDAPMod*)*(attrNum+1));
					for(i = 0; i < attrNum; i++){
						mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
						mods[i]->mod_op = LDAP_MOD_ADD;
					}
					mods[attrNum] = NULL;
					//add attribute objectClass: person
					mods[0]->mod_type="objectClass";
					mods[0]->mod_values=(char**)malloc(sizeof(char*)*2);
					mods[0]->mod_values[0]="person";
					mods[0]->mod_values[1]=NULL;

					//add attribute, for example, cn:p1
					mods[1]->mod_type="cn";
					mods[1]->mod_values=(char**)malloc(sizeof(char*)*2);
					sprintf(strCn, "p%d", pnNum);
					sprintf(personRdn, "cn=%s, %s", strCn, orgRdn);
					mods[1]->mod_values[0]=strCn;
					mods[1]->mod_values[1]=NULL;

					//add attribute, for example, sn:zhang1
					mods[2]->mod_type="sn";
					mods[2]->mod_values=(char**)malloc(sizeof(char*)*2);
					//sprintf(strSn, "%s%d", surnames[pnNum%100], pnNum);
					sprintf(strSn, "%s%d", surnames[pnNum/100], pnNum); //note "pnNum/100", not "pnNum%100"
					mods[2]->mod_values[0]=strSn;
					mods[2]->mod_values[1]=NULL;

					//add attribute, for example, telephoneNumber:001-0396-000001
					mods[3]->mod_type="telephoneNumber";
					mods[3]->mod_values=(char**)malloc(sizeof(char*)*2);
					sprintf(strTel, "00%d-0%d-000%03d", cyNum, orgNum+395, pnNum);
					mods[3]->mod_values[0]=strTel;
					mods[3]->mod_values[1]=NULL;

					//orgRdn, for example, cn=p1, ou=cs, dc=hit, dc=korea
					//sprintf(personRdn, "cn=%s, %s", str, OrgRdn);
					sprintf(dn, "%s, %s", personRdn, BASE_DN);
					rc = ldap_add_s(ld, dn, mods);
					if(rc != LDAP_SUCCESS && rc != LDAP_ALREADY_EXISTS){
						sprintf(msg, "add the entry %s failed!\n", dn);
						ldap_perror(ld, msg);
						exit(1);
					}
					for(i = 0; i < attrNum; i++){ //note "i < attrNum", not "i <= attrNum"
						free((void*)(mods[i]->mod_values));
						free((void*)mods[i]);
						//mods[i] = (LDAPMod*)malloc(sizeof(LDAPMod));
					}
					free((void*)mods);
				}
			}
		}
	}
	
	free((void*)cyRdn);
	free((void*)schoolRdn);
	free((void*)orgRdn);
	free((void*)personRdn);

	ldap_unbind(ld); //unbind
	return 0;
}
