#include <pgmspace.h>
 
#define SECRET
 
const char WIFI_SSID[] = "THE_WiFi";               //TAMIM2.4G
const char WIFI_PASSWORD[] = "*150618*";           //0544287380
 
#define THINGNAME "pool-green2b"
 
int8_t TIME_ZONE = -3; 
 
const char MQTT_HOST[] = "a33yv9okseqbmj-ats.iot.us-east-1.amazonaws.com";  //endpoint AWS
 
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAI3+NEA4dvuTQv3SSGYLyORKODZCMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA2MDkyMzMz
NTBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDVD5abT7Chn6AKZVG3
8BdjcaTko6NztJ1iotohR+WDeCrsua0asFjGyAqjGgbYp9T8CRBAKJ/WqLVejFwe
W+PgtKHHAFbf203NWVOqhQXD9zxK/IB+D8vSk+ym0G71yqt6S0oIXpUzIVQuTLfp
oR1NiEbeq0S7bErtAvGqtuMqpGSIHWYfCVrmjmekWVhfm3vEy2zJ+NK9M6KaUD/1
8C49M+swLCWsHpp6OQVpgogl/EBVMaavGw2nPhDX44DrB+mtNqR2wjwg9uFpZ1ih
ze6awpZSkqpd6vdp4DxVnWaU0kxvFE4FPtjIlkEmeEhr82y2+KGyTDGfQ63wPPvm
/5QnAgMBAAGjYDBeMB8GA1UdIwQYMBaAFOhjULU2qTDgS77SWqXC8szV228hMB0G
A1UdDgQWBBTVpdp95iZqxSP/MiH0+91fDWVwiDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAuXjlNoPEH6jdT+08qCBJSovt
TdT0AMf7q8aPGr3vcTzr15KiQrXXiLsK34dzpRs4G8KAaMLpFw3x86NrcL3yMelF
ac1Jp31Iu9Aq9AMje9gpduLbsWbNHFcH1KeUcP5h55/teAERU55H7NACLTbHIz5s
RhhgJcB66Hu6f1k8UMIhL5TflmC682ZCMJ9GZhI7rJTH1u10+Tov4Ty41FpCD7B/
7cRrvmFiwkm/N4+mSxWT45K96QwKDygxQDPuJHFzO7cq6Mo6SPYz+EkURcRpNaGS
SZLmeQ7boJc/wLbyD+ZMjJyv5nIN/5gP2LpbVSC83eoqOWmHlSVrWUcu3ZFs2g==
-----END CERTIFICATE-----
 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA1Q+Wm0+woZ+gCmVRt/AXY3Gk5KOjc7SdYqLaIUflg3gq7Lmt
GrBYxsgKoxoG2KfU/AkQQCif1qi1XoxcHlvj4LShxwBW39tNzVlTqoUFw/c8SvyA
fg/L0pPsptBu9cqrektKCF6VMyFULky36aEdTYhG3qtEu2xK7QLxqrbjKqRkiB1m
Hwla5o5npFlYX5t7xMtsyfjSvTOimlA/9fAuPTPrMCwlrB6aejkFaYKIJfxAVTGm
rxsNpz4Q1+OA6wfprTakdsI8IPbhaWdYoc3umsKWUpKqXer3aeA8VZ1mlNJMbxRO
BT7YyJZBJnhIa/Nstvihskwxn0Ot8Dz75v+UJwIDAQABAoIBAH4OvgXgLVpC7laY
QbQ5ai0dFPlt1AxmRWQRhEuClUmmtIbhCIks4ymhO6HqiThwfDQuTJ4ZKxC/OqfZ
FbuklHvjg4ARNFU4FJ01h6nxEEs0oUiggomTYP2TJcZAthXYtoIhv4iaJV5eDsdh
/sJM3+B6i6u822qklOQMBN4DXP5htrVRSWsffuclbtt6DX3t3c+Q0yQOc/CvNDsw
6811Nkxaura+DigRKM5clgnNRBbqqiKGaHgfNYLxB3aYQ5+ihmRUFqytkIpAdHo5
w9CRtHMtolo7Z3o6l9wzw8O9cKZNEjH2TR94eLpMAZImbUAGen4vYtFuDj/O/IhZ
93DhArECgYEA9ARv8VRqzij/xk/o9HxyFOqqzqGWR6tZGj1GUsQoiNQUIejabYAZ
RrFGignB0XIgsITPFGzUreagFGsiWHQY8GoV76BnnmkBEGpnfIiF6ktWZpTyGjMp
IuQ62oJjVj86NKm72oTYu+H66gxYyYyR4UUy5Hic8zf39NuWol7Fl78CgYEA34X+
tg0rhQSseork/eCDCpwnsND7L5og5+8k76eRyXzlxbeGZiOPsmXEN70WAhQehwgm
cfh9rSmAqbwfC+C0y4Q/pO11xqxXJB6rJ0MzqYLVVFnMDA9Af83X7cFXEj59ADNp
+rxbJuXm8Vx5npYmvE2IpiiSjzIHGqipOssY3ZkCgYBJOxutPTxgaoV4KnsrBD3o
cRSZtny3PYEcEs+L/zp69cqk8pC60/rB8GnO+2ajSLDuyKys4IxjNBdOiWhhS1ZA
sFWs+GKgc7rSBlzQTtiBm+JuHr0Zh8kMo5nWAdN2CruZGmc6CSxSFluK6fGravhM
tsuzLU9M3rsXTN9EE1URWQKBgQDCo3/FL3qx/fvjSYdVu2bgmlHFmnTgYqo8zPWw
6o38khHTNZiG4HiEtDFFCBZeAP8EPoibvfJSE03Cf9nZEfbdMW/qQgzIz9Gh1kLb
kZ0vAoqZRQh1h+J2Z9ybYDxd2qQmxJ6Ig/Qrzw5nJkuRWNaqKinP5oyYvMuK30td
svUYIQKBgGdMFCmMqCDp3qwSpQmlx3mtiZbyUTvXNaDo54O+tSLzSoLhncvBaS1P
d+DFDRHJevOHsPQpNXxObfmQxh5/Z8v5XeJr1u8fVOcYFHN6F1ILO8KeHhiJXlV9
b0LStYjMfNaUDKvWp7qx++WV1rxq/ZSwL5G12iPLlmsUlV3OdF60
-----END RSA PRIVATE KEY-----
 
)KEY";