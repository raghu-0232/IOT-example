#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "secrets/Secrets.h"

#define DHTPIN 25 // M5Atom uses GPIO 25 for DHT
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure espClient;
PubSubClient client(espClient);

float t = 0.0;
float h = 0.0;

const long interval = 10000;
unsigned long previousMillis = 0;

// SSL/TLS Certificates and Key
const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n"
"MIIDbTCCAlWgAwIBAgIUUCG67h5CZAw4fuw1qFmZw7mdBPQwDQYJKoZIhvcNAQEL\n"
"BQAwRjELMAkGA1UEBhMCSU4xCzAJBgNVBAgMAkFQMQwwCgYDVQQHDANCWkExDjAM\n"
"BgNVBAoMBVJBR0hVMQwwCgYDVQQLDANlc3AwHhcNMjMxMjI3MTkwNjU1WhcNMjYx\n"
"MDE2MTkwNjU1WjBGMQswCQYDVQQGEwJJTjELMAkGA1UECAwCQVAxDDAKBgNVBAcM\n"
"A0JaQTEOMAwGA1UECgwFUkFHSFUxDDAKBgNVBAsMA2VzcDCCASIwDQYJKoZIhvcN\n"
"AQEBBQADggEPADCCAQoCggEBALbePBXKxIP1NzPOjgpgPZo5sQvE+kpBvBu37cp8\n"
"cFPkiWDNw35FuOyxSR9ltW4Q1m5TjGF3xyE9BZ6c5Aa5lRcHKLr0TviF7yoFgJCZ\n"
"8pWvVThIKuJP+qKbMloC260GSeShjEAwQPh8O0tPAj6+KMhsEY7ib4Bs4HRGp60V\n"
"Gaxs44yQReDmfiYna1agK6cWa6J/qVGjx/egu76DkZx2iWJdRharZutRSZeIcacl\n"
"ONROT6D5QiQ1NIc6pUXRQalQW3gWOARIUFv1QUjOG0BSWX5FDQZcPY78fHFlk+Fh\n"
"FDJm0fjqsvsA5QOSbUnQMNlT9Kuglqv+6QkDjAEFKnEPn9sCAwEAAaNTMFEwHQYD\n"
"VR0OBBYEFMCDETB9TKHYADn4HwoROFukYfIfMB8GA1UdIwQYMBaAFMCDETB9TKHY\n"
"ADn4HwoROFukYfIfMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEB\n"
"AEKgWDrxFnzwiA9qAuPBbo0hsTJNcnkygrXzL+qouavTpjzWQOzuJk/C3sQyu+59\n"
"auQEClJJMMFaijAE3lkVza7Q9hy7dLjPGQvj9H0AA9bp6cQN4f6nQmVwFZW71h/W\n"
"CuwXg8NVyzNgrwsvpj82ANzF3pEqazL+5zi7M0SaUnVmNLxwbfyYvBpYt3CxIZ93\n"
"afsBVv4TmphyCq1/Jo75aKhw8v1/6lzJViI8xgNBCutfqLGdBN3436iSpAB/HOdM\n"
"XPe03Gfj7smHjudKOKZZ5UO+wLgGQhyAgmsAabve1cmSZUa756/kSj7Wu279btFk\n"
"WkPDnWsvrVsKXj+8c6u21ME=\n"
"-----END CERTIFICATE-----\n";

const char* clientCertificate = \
"-----BEGIN CERTIFICATE-----\n"
"MIIDEzCCAfsCFGM/UiLO5YN0a7xAeLjwHXp6kdzNMA0GCSqGSIb3DQEBCwUAMEYx\n"
"CzAJBgNVBAYTAklOMQswCQYDVQQIDAJBUDEMMAoGA1UEBwwDQlpBMQ4wDAYDVQQK\n"
"DAVSQUdIVTEMMAoGA1UECwwDZXNwMB4XDTIzMTIyNzE5MDgwN1oXDTI1MDUxMDE5\n"
"MDgwN1owRjELMAkGA1UEBhMCSU4xCzAJBgNVBAgMAkFQMQwwCgYDVQQHDANCWkEx\n"
"DjAMBgNVBAoMBVJBR0hVMQwwCgYDVQQLDANlc3AwggEiMA0GCSqGSIb3DQEBAQUA\n"
"A4IBDwAwggEKAoIBAQCs4ytyuDKtLkHjHIh4bE8G+i0KbFhTr5XuMQBuQ67h4piZ\n"
"HDzy242zqbTX0I7cdPAFGIjNNsE6fUH8ibHFWxYqPcoH6zXTjCh3TCEaORs8uIR4\n"
"jZL8qc165IzUvq3Hn5FsvqX02GN9FXjPl9CphMCTPLpQpyLoE3LGIKUKrqAByWxn\n"
"qO/dwXXG6qXMMvAVxwleM+a8E8VL4Yj+cQ7zyJv/2VqL0wle34eaReIpWPJj+B4O\n"
"PY48BNkRY5qlMNSDtYTQrxH4SS7ajN3czo/CKfSwBloucBwcErBsB9dpqqtXWuCl\n"
"XX8FNPeYKlVmGsXaRiaIrnE4SbECU4yTAp917Y6NAgMBAAEwDQYJKoZIhvcNAQEL\n"
"BQADggEBAKu19aLukD4UgpdyJz48sc3V9LFyN6P8+13ei6MNmbZoKedwiyQN3Ynx\n"
"LaG/aPraVMaV9bIsMpNfMeIbiaMvts7rozIaSbaUTGBd/2On7ChaTQQf5C7P+eLy\n"
"uqSavImXaDtoP4hB5HtE/54IWBUDi4d/u85/5+572xjLHLms0w3cVLkjB4zHgVyq\n"
"OZjaTyFPQp6JJwvYZP6Y0c0oDEaFH68BZQrgkX/n4EPNIPq8OWx/DDw8rzujp1oU\n"
"2aCJwrzALLDzSwwIdRPViQtt3+WuwNxOx2BpP+lxuJj3o7mWM8K+/uNPxWNX/+Ua\n"
"t2MDw+hYn4gzwjhvrRfcvaWTr3JVaI8=\n"
"-----END CERTIFICATE-----\n";



const char* clientPrivateKey = \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEowIBAAKCAQEArOMrcrgyrS5B4xyIeGxPBvotCmxYU6+V7jEAbkOu4eKYmRw8\n" \
"8tuNs6m019CO3HTwBRiIzTbBOn1B/ImxxVsWKj3KB+s104wod0whGjkbPLiEeI2S\n" \
"/KnNeuSM1L6tx5+RbL6l9NhjfRV4z5fQqYTAkzy6UKci6BNyxiClCq6gAclsZ6jv\n" \
"3cF1xuqlzDLwFccJXjPmvBPFS+GI/nEO88ib/9lai9MJXt+HmkXiKVjyY/geDj2O\n" \
"PATZEWOapTDUg7WE0K8R+Eku2ozd3M6Pwin0sAZaLnAcHBKwbAfXaaqrV1rgpV1/\n" \
"BTT3mCpVZhrF2kYmiK5xOEmxAlOMkwKfde2OjQIDAQABAoIBAF9hRMsZi/u3FWpy\n" \
"h2fIeSDkTIz/kQs6R4ENT6uFc6nzFTUDOyzQq7B+4+JckTRW30QwcOimWJwoFot4\n" \
"e7bhtazAQgF0ZlG7dWe7fFe3QauSMKNBl+IE2/P8uyVzvPPwuI5B79TQvLJ5chk1\n" \
"LE0ZjBSu4Cs2yi82648a23K1PFk/Gd0Jz/L37I6s87DjFipyPkbXN4dCGWwQKEqG\n" \
"LpQm+2nltSMbyNNEIb1Uaaz2ccQC9E4o2EkbohujwMqimotfOVuE150dh8PdPFoS\n" \
"hZjf8EzPXhWblRUUmZXP9yywm12JEvU21L4O0YJmCajf/Ot0RsrW7pQAMxbLBheO\n" \
"ao7W/IECgYEA4w3lf11wVpjs0huyHVYPC4KTGOGNDGT4rE2UB1MKepoXP1mFJIQ8\n" \
"rS8qm/wpQKPpt2VpN/eGY8nQO5YaKjn82LzgFRVEFe3u3urC7z1jFe8SaSPkfjGY\n" \
"aRTvABieSxTkQ2o7+Mra2C9+86p6eBgMjlsO3Ot48EdYcAX3pmYqx9UCgYEAwu19\n" \
"5xQoOoUgcpbv9uBmKkI6JkGplNyIXhLlSrvdJVP22R28dmC0UhE5+15+Wk2+pRKa\n" \
"WFl7HyiM2rHUU87K5/yY9MXeZ1ZVxiMUCnl3MVzlBhsLjioTiXRQZruuYDdUbScf\n" \
"hygAr47LL8f2eVmKGODb+r9M6/TbBEoO84ep/9kCgYAOJUh+BeFA0+g1MtqG71yi\n" \
"l/D4JN03v3aqrW6igi7t8nmuTbJ40vBAzeZ2r2AWkd+2uE+01+v8fY9GlxRsOw6g\n" \
"pivDxH5oa1ltc+zPIODydeGMwVqz7f0T1uUI+X+rJ9MMzCqOVn0J6POc1Ksqnjzy\n" \
"BYRIiTcQqTE+UXDbYhQaPQKBgCJY7sJ1DtGg+6K1bfs2d0oi+VQcZeFRKsZI1hZh\n" \
"HAqjzO9dCgRh7eQ4HNtqPyFyaZF0wbWnrsZCwu8WPq+11JMkM1+OLi5PTDXpoHJo\n" \
"DNSp5cE5qsOWLnMeB7zSfVt+5GWHa0rJhbVpl+wHdCrV2DuiA6EfbFJ3htAurIvE\n" \
"7/OhAoGBAIf8z5c3FixmSAKpBmgi86KY5yyheCQSjLsK1j0GWSIwKl3rgJXS/JGg\n" \
"kJPslrnvwoQPEXjTbHR+6GaxNecuL67lwYsXqhYyCbgqS1p0xEiUMRhO2N1ePlUd\n" \
"lbtF4vEDP6zv+sTSR1GOnP4WteWVLuk90zOUHGHHK+7zWRVexu4X\n" \
"-----END RSA PRIVATE KEY-----\n";


void setup() {
  M5.begin();
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());

  espClient.setCACert(rootCACertificate);
  espClient.setCertificate(clientCertificate);
  espClient.setPrivateKey(clientPrivateKey);

  client.setServer(mqttBroker, mqttPort);
}

void loop() {
  M5.update();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    if (!isnan(newT)) {
      t = newT;
    }

    float newH = dht.readHumidity();
    if (!isnan(newH)) {
      h = newH;
    }

    if (!client.connected()) {
      reconnect();
    }

    if (t == 0.0 && h == 0.0) {
      if (publishToMQTT("test", "Sensor not connected or error occurred", 1)) {
        Serial.println("Error message published to MQTT");
      } else {
        Serial.println("Failed to publish error message to MQTT. Retrying in 5 seconds...");
      }
    } else {
      String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
      if (publishToMQTT("test", payload, 1)) {
        Serial.println("Data published to MQTT");
      } else {
        Serial.println("Failed to publish data to MQTT. Retrying in 5 seconds...");
      }
    }

    delay(1000);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("M5AtomClient")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
}

bool publishToMQTT(const char *topic, const String &payload, int qos) {
  // Convert String payload to a character array.
  const char* charPayload = payload.c_str();

  // Publish with the correct parameters - topic, payload, and QoS
  if (client.publish(topic, charPayload, qos)) {
    return true;
  } else {
    Serial.print("Failed to publish to topic ");
    Serial.print(topic);
    Serial.println(". Retrying...");
    return false;
  }
}
