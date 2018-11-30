#!/bin/bash
sed -i 's/"exited_cleanly":false/"exited_cleanly":true/' /home/pi/.config/chromium/Default/Preferences
sed -i 's/"exit_type":"Crashed"/"exit_type":"Normal"/' /home/pi/.config/chromium/Default/Preferences
export SECRET="some-very-long-string-of-random-characters-CHANGE-TO-YOUR-LIKING"
export APP_SETTINGS="development"
export DATABASE_URL="postgresql://pi:secretpass@localhost/mixfit_device"
export FLASK_APP="run.py"
export MIXFIT_API_URL="http://starling.mixfit-platform-2.c66.me"
/home/pi/webPythonApp/venv/bin/python /home/pi/webPythonApp/run.py &
cd /home/pi/Desktop/
/home/pi/Desktop/MixFitApp -platform xcb &
chromium-browser --enable-experimental-web-platform-features --disable-infobars --app-auto-launched --kiosk http://localhost:5000


