---

# Setting Up MQTT Mosquitto Broker on AWS EC2

This guide provides comprehensive instructions for setting up an MQTT Mosquitto broker on a `t2.micro` EC2 instance running Ubuntu 20.04, including the configuration of SSL for secure communication.

## Prerequisites

- An active AWS account.
- A registered domain name. Replace `example.com` with your actual domain throughout this guide.
- Basic familiarity with AWS EC2 and SSH.

## Steps for Setup

### Step 1: Launching the EC2 Instance

1. **Log in** to your AWS Console and navigate to the **EC2 Dashboard**.
2. **Launch a new EC2 instance**:
   - **AMI**: Choose Ubuntu Server 20.04 LTS.
   - **Instance Type**: Select `t2.micro`.
   - **Configure Instance**: Use default settings.
   - **Add Storage**: Default settings.
   - **Add Tags**: Optional, for easier identification.
   - **Configure Security Group**: Allow SSH (port 22) and MQTT (ports 1883 and 8883).
   - **Key Pair**: Select an existing key pair or create a new one.

### Step 2: Installing Mosquitto MQTT Broker

1. **SSH into your EC2 instance** using your instance's public IP and your private key.
2. **Update packages**:
   ```bash
   sudo apt-get update
   ```
3. **Install Mosquitto Broker and Clients**:
   ```bash
   sudo apt-get install -y mosquitto mosquitto-clients
   ```
4. **Start and enable the Mosquitto service**:
   ```bash
   sudo systemctl start mosquitto
   sudo systemctl enable mosquitto
   ```

### Step 3: Configuring SSL for Mosquitto

1. **Install Certbot**:
   ```bash
   sudo apt-get install -y certbot
   ```
2. **Generate SSL Certificates**:
   ```bash
   sudo certbot certonly --standalone -d example.com
   ```
3. **Configure Mosquitto to use SSL**:
   - Edit the Mosquitto config file:
     ```bash
     sudo nano /etc/mosquitto/conf.d/default.conf
     ```
   - Add SSL configuration:
     ```
     listener 8883
     cafile /etc/letsencrypt/live/example.com/fullchain.pem
     certfile /etc/letsencrypt/live/example.com/cert.pem
     keyfile /etc/letsencrypt/live/example.com/privkey.pem
     ```
   - Save and exit.
4. **Restart Mosquitto**:
   ```bash
   sudo systemctl restart mosquitto
   ```

### Step 4: Testing the MQTT Broker

1. **Subscribe to the Topic `sun`**:
   ```bash
   mosquitto_sub -h example.com -p 8883 -t sun --capath /etc/ssl/certs/
   ```
2. **Publish to the Topic `sun`**:
   ```bash
   mosquitto_pub -h example.com -p 8883 -t sun -m "Hello from MQTT" --capath /etc/ssl/certs/
   ```
3. **Verify the Message**: Look for the "Hello from MQTT" message in the subscribed terminal.

#### Troubleshooting:

- Check network and firewall settings if the MQTT ports are not open.
- Ensure the EC2 instance's security group allows traffic on port 8883.
- Confirm the SSL certificates are correctly configured on both the MQTT broker and client.

## Conclusion

Your MQTT broker is now running on a `t2.micro` EC2 instance with Ubuntu 20.04 and is configured to use SSL for secure communication on port 8883. Ensure your domain's DNS settings point to the EC2 instance's public IP for SSL functionality.

---

**Note**: Replace `example.com` with your domain and ensure all file paths match your system's configuration.
