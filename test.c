#include <stdio.h>
#include <curl/curl.h>

int main(void){
	CURL *curl;
	CURLcode res;
	char uname[40],email[40],postdata[100];
	
	curl_global_init(CURL_GLOBAL_ALL);//glolly initiate libcurl
	curl = curl_easy_init();

	if(curl){	//if handler is okay
		curl_easy_setopt(curl,CURLOPT_URL,"http://www.cc.puv.fi/~e1601137/test.php");
		while(1){
		printf("User name : "); scanf("%s",uname);
		printf("Email: ");scanf("%s",email);
		sprintf(postdata,"name=%s&email=%s",uname,email);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,postdata);

		res=curl_easy_perform(curl);
		if(res !=CURLE_OK)
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
