# Big Red Slack Button

It's a big red button that posts a message to Slack when you push it.

# What You Need

## Hardware

A button.
An Arduino Board.
An arduino Ethernet Shield.

## Software

The Arduino IDE.

# Let's Build a Button

## Hardware

1. Acquire a Big Red Button.
2. Solder some jumper wires to its terminals.
3. Attach the Ethernet Shield to the Arduino
4. Wire the button between ground and an avalable pin on the arduino, chosen in software.

## Slack

1. Go to [https://YOUR-TEAM.slack.com/apps/build/custom-integration](https://YOUR-TEAM.slack.com/apps/build/custom-integration).
2. Create an Incoming Webhook and configure it to post to your channel.
3. Optional: Give your webhook a friendly name and icon, such as **Big Red Button** and 🔴.

## Upload

1. Connect your Arduino via USB.
1. Edit the constants in slack_button.ino to configure your network, button connections and your Slack webhook URL.
2. Upload to the Arduino.

## PUSH THE BUTTON

Just push it. You know you really want to.

But don't push it too many times or your boss will fire you.

# License

MIT
