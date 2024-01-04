# Setting Up MQTT Mosquitto Broker on AWS EC2

This guide provides comprehensive instructions for setting up an MQTT Mosquitto broker on a `t2.micro` EC2 instance running Ubuntu 20.04. The setup includes configuring SSL for secure communication.

## Prerequisites

- An active AWS account.
- A registered domain name. Replace `example.com` with your actual domain throughout this guide.
- Basic familiarity with AWS EC2 and SSH.

## Step 1: Launching the EC2 Instance

1. **Log in** to your AWS Console and navigate to the **EC2 Dashboard**.
2. **Launch a new EC2 instance** with the following configuration:
   - **AMI**: Choose Ubuntu Server 20.04 LTS.
   - **Instance Type**: Select `t2.micro`.
   - **Configure Instance**: Use default settings.
   - **Add Storage**: Stick with the default settings.
   - **Add Tags**: Optionally add tags for easier identification.
   - **Configure Security Group**: Allow SSH (port 22) and MQTT (ports 1883 and 8883).
   - **Review and Launch**: Review your settings.
   - **Key Pair**: Select an existing key pair or create a new one for SSH access.

## Step 2: Installing Mosquitto MQTT Broker

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

## Step 3: Configuring SSL for Mosquitto

1. **Install Certbot** for Let's Encrypt SSL certificate management:
   ```bash
   sudo apt-get install -y certbot
   ```
2. **Generate SSL Certificates** for your domain:
   ```bash
   sudo certbot certonly --standalone -d example.com
   ```
   - Follow the on-screen instructions to complete the setup.
3. **Configure Mosquitto to use the SSL certificates**:
   - Open the Mosquitto configuration file:
     ```bash
     sudo nano /etc/mosquitto/conf.d/default.conf
     ```
   - Add the following lines to the file (adjust the paths if needed):
     ```
     listener 8883
     cafile /etc/letsencrypt/live/example.com/fullchain.pem
     certfile /etc/letsencrypt/live/example.com/cert.pem
     keyfile /etc/letsencrypt/live/example.com/privkey.pem
     ```
   - Save the file and exit the editor.
4. **Restart Mosquitto** to apply the SSL configuration:
   ```bash
   sudo systemctl restart mosquitto
   ```

## Conclusion

Your MQTT broker is now set up and running on a `t2.micro` EC2 instance with Ubuntu 20.04. It is configured to use SSL for secure communication over port 8883. Ensure your domain's DNS settings point to the EC2 instance's public IP address for proper SSL functionality.

---

**Note**: Replace `example.com` with your domain and ensure all file paths match your system's configuration.
```
