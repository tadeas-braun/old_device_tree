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

static void patch_hostapd(void) {
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

free_done:
	free(ssidBuffer);
	if (encType && passLen)
		free(passBuffer);

fail_done:
	fclose(pFile);

done:
	return;
}

int main(void) {
	/*
	 * driver=nl80211
	 * logger_syslog=-1
	 * logger_syslog_level=2
	 * logger_stdout=-1
	 * logger_stdout_level=2
	 * dump_file=/data/misc/wifi/hostapd.dump
	 * ctrl_interface=wlan0
	 * ctrl_interface_group=0
	 * hw_mode=g
	 * channel=11
	 * beacon_int=100
	 * dtim_period=2
	 * max_num_sta=5
	 * supported_rates=10 20 55 110 60 90 120 180 240 360 480 540
	 * preamble=1
	 * macaddr_acl=0
	 * auth_algs=1
	 * ignore_broadcast_ssid=0
	 * wme_enabled=0
	 * eap_server=0
	 * own_ip_addr=127.0.0.1
	 * interface=wlan0
	 * ap_table_max_size=255
	 * ap_table_expiration_time=3600
	 * tx_queue_data2_aifs=2
	 * tx_queue_data2_cwmin=15
	 * tx_queue_data2_cwmax=63
	 * tx_queue_data2_burst=0
	 * # from this line we need to generate next lines
	 * # by hostapdpatcher into hostapd_xperia.conf
	 * ssid=AndroidAP
	 * wpa=1
	 * wpa_passphrase=myhomelanpass
	 * wpa_key_mgmt=WPA-PSK
	 * wpa_pairwise=CCMP
	 */
	ALOGV("be continued :)\n");

	return 0;
}
