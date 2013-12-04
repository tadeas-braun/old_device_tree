/*
 * Created by Munjeni @ 2013
 *
 * Tool for Xperia 2012 devies which have bugs related to the hostapd allways unsecured wifi tethering.
 * This tool runing as a service, repairing these broken things and make wifi tethering secured.
 * Credits to Morando @ MyCity for his help.
 */

#define LOG_TAG "Hostapd Patcher"

#include <cutils/log.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SOFTAP_CONF "/data/misc/wifi/softap.conf"

#define ENC_NONE 0 
#define ENC_WPA  1 
#define ENC_WPA2 4 

int main(void) {
	FILE* pFile;
	char *ssidBuffer, *passBuffer;
	unsigned short int ssidLen, encType, passLen;
	struct stat fileStat;

	if(stat(SOFTAP_CONF, &fileStat) < 0) {
		ALOGE("File %s not exist! I must exit now!\n", SOFTAP_CONF);    
		goto done;
	}

	//check if 6.th byte contain sizeof the SSID
	if (fileStat.st_size < 6) {
		ALOGE("File %s not contain what I wanted! I must exit now!\n", SOFTAP_CONF);    
		goto done;
	}		

	if ((pFile = fopen(SOFTAP_CONF, "rb")) == NULL) {
		ALOGE("Fail to open %s for reading! I must exit now!\n", SOFTAP_CONF);
		goto done;
	}

	// skip to the SSID size atag and read a size of the SSID string
	fseek(pFile, 5, SEEK_SET);
	fread(&ssidLen, 1, 1, pFile);
	if (!ssidLen) {
		ALOGE("Error: there is empty ssid! I must exit now!\n");
		goto fail_done;
	}
	else
		ALOGV("SSID contain %d characters\n", ssidLen);

	// now read SSID string
	ssidBuffer = (char *)malloc(ssidLen+1);
	fread(ssidBuffer, sizeof(char), ssidLen, pFile);
	ssidBuffer[ssidLen] = '\0';
	ALOGV("SSID is: %s\n", ssidBuffer);

	// skip to the encription atag
	fseek(pFile, +3, SEEK_CUR);

	// read encription type
	fread(&encType, 1, 1, pFile);
	if (ENC_NONE == encType) {
		ALOGV("Enc. type is NONE\n");
	} else if(ENC_WPA == encType) {
		ALOGV("Enc. type is WPA\n");
	} else if(ENC_WPA2 == encType) {
		ALOGV("Enc. type is WPA2\n");
	} else {
		ALOGE("Enc. type is UNKNOWN!!! Something is wrong.\n");
		goto free_done;
	}

	// encription things
	if (encType) {
		// skip to the password size atag
		fseek(pFile, +1, SEEK_CUR);

		// read a size of the password string
		fread(&passLen, 1, 1, pFile);
		if (!passLen) {
			ALOGE("Error: there is an empty password! I must exit now!\n");
			goto free_done;
		}
		else
			ALOGV("password contain %d characters\n", passLen);

		// read password
		passBuffer = (char *)malloc(passLen+1);
		fread(passBuffer, sizeof(char), passLen, pFile);
		passBuffer[passLen] = '\0';
		ALOGV("Password is: %s\n", passBuffer);
	}

// be continued :)

free_done:
	free(ssidBuffer);
	if (encType && passLen)
		free(passBuffer);

fail_done:
	fclose(pFile);

done:
	return 0;
}
